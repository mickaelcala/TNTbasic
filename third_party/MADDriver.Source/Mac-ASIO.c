/********************						***********************/
//
//	Player PRO 5.9 - DRIVER SOURCE CODE -
//
//	Library Version 5.9
//
//	To use with MAD Library for Mac: Symantec, CodeWarrior and MPW
//
//	Antoine ROSSET
//	20 Micheli-Du-Crest
//	1205 GENEVA
//	SWITZERLAND
//
//	COPYRIGHT ANTOINE ROSSET 1996, 1997, 1998, 1999, 2000, 2001, 2002
//
//	Thank you for your interest in PlayerPRO !
//
//	FAX:			(+41 22) 346 11 97
//	PHONE: 			(+41 79) 203 74 62
//	Internet: 		RossetAntoine@bluewin.ch
//
/********************						***********************/

#include "RDriver.h"
#include "RDriverInt.h"
#include <Timer.h>
#include "asiosys.h"
#include "asio.h"
#include "asiodrivers.h"

/********************						***********************/

extern Boolean DirectSaveAlways( Ptr myPtr, MADDriverSettings *driverType, MADDriverRec *intDriver);

char ASIO_DRIVER_NAME[ 255] = "Not Activated";

enum {
	// number of input and outputs supported by the host application
	// you can change these to higher or lower values
	kMaxInputChannels = 0,
	kMaxOutputChannels = 2
};

/********************						***********************/

// some external references
extern AsioDrivers* asioDrivers;
bool loadAsioDriver(char *name);

static	Ptr		bufTampons;
static	long	TamponPos, TamponSize;
static	Boolean	ASIOOK;

/********************						***********************/

// internal data storage
typedef struct DriverInfo
{
	// ASIOInit()
	ASIODriverInfo driverInfo;

	// ASIOGetChannels()
	long           inputChannels;
	long           outputChannels;

	// ASIOGetBufferSize()
	long           minSize;
	long           maxSize;
	long           preferredSize;
	long           granularity;

	// ASIOGetSampleRate()
	ASIOSampleRate sampleRate;

	// ASIOOutputReady()
	bool           postOutput;

	// ASIOGetLatencies ()
	long           inputLatency;
	long           outputLatency;

	// ASIOCreateBuffers ()
	long inputBuffers;	// becomes number of actual created input buffers
	long outputBuffers;	// becomes number of actual created output buffers
	ASIOBufferInfo bufferInfos[kMaxInputChannels + kMaxOutputChannels]; // buffer info's

	// ASIOGetChannelInfo()
	ASIOChannelInfo channelInfos[kMaxInputChannels + kMaxOutputChannels]; // channel info's
	// The above two arrays share the same indexing, as the data in them are linked together

	// Information from ASIOGetSamplePosition()
	// data is converted to double floats for easier use, however 64 bit integer can be used, too
	double         nanoSeconds;
	double         samples;
	double         tcSamples;	// time code samples

	// bufferSwitchTimeInfo()
	ASIOTime       tInfo;			// time info state
	unsigned long  sysRefTime;      // system reference time, when bufferSwitch() was called

	// Signal the end of processing in this example
	bool           stopped;
	
	//
	MADDriverRec 	*MADDriver;	
} DriverInfo;


DriverInfo asioDriverInfo = {0};
ASIOCallbacks asioCallbacks;

/*************************/

//----------------------------------------------------------------------------------

unsigned long get_sys_reference_time()
{	// get the system reference time
#if WINDOWS
	return timeGetTime();
#elif MAC
static const double twoRaisedTo32 = 4294967296.;
	UnsignedWide ys;
	Microseconds(&ys);
	double r = ((double)ys.hi * twoRaisedTo32 + (double)ys.lo);
	return (unsigned long)(r / 1000.);
#endif
}

long init_asio_static_data (DriverInfo *asioDriverInfo)
{	// collect the informational data of the driver
	// get the number of available channels
	if(ASIOGetChannels(&asioDriverInfo->inputChannels, &asioDriverInfo->outputChannels) == ASE_OK)
	{
		//printf ("ASIOGetChannels (inputs: %d, outputs: %d);\n", asioDriverInfo->inputChannels, asioDriverInfo->outputChannels);

		// get the usable buffer sizes
		if(ASIOGetBufferSize(&asioDriverInfo->minSize, &asioDriverInfo->maxSize, &asioDriverInfo->preferredSize, &asioDriverInfo->granularity) == ASE_OK)
		{
		//	printf ("ASIOGetBufferSize (min: %d, max: %d, preferred: %d, granularity: %d);\n",
			//		 asioDriverInfo->minSize, asioDriverInfo->maxSize,
				//	 asioDriverInfo->preferredSize, asioDriverInfo->granularity);

			// get the currently selected sample rate
			if(ASIOGetSampleRate(&asioDriverInfo->sampleRate) == ASE_OK)
			{
			//	printf ("ASIOGetSampleRate (sampleRate: %f);\n", asioDriverInfo->sampleRate);
				if (asioDriverInfo->sampleRate <= 0.0 || asioDriverInfo->sampleRate > 96000.0)
				{
					// Driver does not store it's internal sample rate, so set it to a know one.
					// Usually you should check beforehand, that the selected sample rate is valid
					// with ASIOCanSampleRate().
					if(ASIOSetSampleRate(44100.0) == ASE_OK)
					{
						if(ASIOGetSampleRate(&asioDriverInfo->sampleRate) != ASE_OK) return -6;
						
						/*
							printf ("ASIOGetSampleRate (sampleRate: %f);\n", asioDriverInfo->sampleRate);
						else
							return -6;*/
					}
					else
						return -5;
				}

				// check wether the driver requires the ASIOOutputReady() optimization
				// (can be used by the driver to reduce output latency by one block)
				if(ASIOOutputReady() == ASE_OK)
					asioDriverInfo->postOutput = true;
				else
					asioDriverInfo->postOutput = false;
				//printf ("ASIOOutputReady(); - %s\n", asioDriverInfo->postOutput ? "Supported" : "Not supported");

				return 0;
			}
			return -3;
		}
		return -2;
	}
	return -1;
}

// conversion from 64 bit ASIOSample/ASIOTimeStamp to double float
#if NATIVE_INT64
	#define ASIO64toDouble(a)  (a)
#else
	const double twoRaisedTo32 = 4294967296.;
	#define ASIO64toDouble(a)  ((a).lo + (a).hi * twoRaisedTo32)
#endif

void reverseEndian(void* buffer, long byteWidth, long frames)
{
	char* a = (char*)buffer;
	char* b = a;
	char c;
	
	if(byteWidth == 2)
	{
		while(--frames >= 0)
		{
			c = a[0];
			a[0] = a[1];
			a[1] = c;
			a += 2;
		}
	}
	else if(byteWidth == 3)
	{
		while(--frames >= 0)
		{
			c = a[0];
			a[0] = a[2];
			a[2] = c;
			a += 3;
		}
	}
	else if(byteWidth == 4)
	{
		while(--frames >= 0)
		{
			c = a[0];
			a[0] = a[3];
			a[3] = c;
			c = a[1];
			a[1] = a[2];
			a[2] = c;
			a += 4;
		}
	}
}


ASIOTime *bufferSwitchTimeInfo(ASIOTime *timeInfo, long index, ASIOBool processNow)
{	
	long	xx;
	
	// the actual processing callback.
	// Beware that this is normally in a seperate thread, hence be sure that you take care
	// about thread synchronization. This is omitted here for simplicity.
	static long processedSamples = 0;
	
	// store the timeInfo for later use
	asioDriverInfo.tInfo = *timeInfo;
	
	// get the time stamp of the buffer, not necessary if no
	// synchronization to other media is required
	if (timeInfo->timeInfo.flags & kSystemTimeValid)
		asioDriverInfo.nanoSeconds = ASIO64toDouble(timeInfo->timeInfo.systemTime);
	else
		asioDriverInfo.nanoSeconds = 0;

	if (timeInfo->timeInfo.flags & kSamplePositionValid)
		asioDriverInfo.samples = ASIO64toDouble(timeInfo->timeInfo.samplePosition);
	else
		asioDriverInfo.samples = 0;

	if (timeInfo->timeCode.flags & kTcValid)
		asioDriverInfo.tcSamples = ASIO64toDouble(timeInfo->timeCode.timeCodeSamples);
	else
		asioDriverInfo.tcSamples = 0;

	// get the system reference time
	asioDriverInfo.sysRefTime = get_sys_reference_time();

#if WINDOWS && _DEBUG
	// a few debug messages for the Windows device driver developer
	// tells you the time when driver got its interrupt and the delay until the app receives
	// the event notification.
	static double last_samples = 0;
	char tmp[128];
	sprintf (tmp, "diff: %d / %d ms / %d ms / %d samples                 \n", asioDriverInfo.sysRefTime - (long)(asioDriverInfo.nanoSeconds / 1000000.0), asioDriverInfo.sysRefTime, (long)(asioDriverInfo.nanoSeconds / 1000000.0), (long)(asioDriverInfo.samples - last_samples));
	OutputDebugString (tmp);
	last_samples = asioDriverInfo.samples;
#endif

	// buffer size in samples
	long buffSize = asioDriverInfo.preferredSize;
	
	
	// **** **** **** **** **** **** **** **** **** 
	
	if( TamponPos + buffSize*4 < TamponSize)
	{
		
	}
	else
	{
		BlockMoveData( bufTampons + TamponPos, bufTampons, TamponSize - TamponPos);
		
		TamponSize -= TamponPos;
		
		TamponPos = 0;
		
		do
		{
		//	if( TamponSize < 0) DebugStr("\p1");
			
			if( !DirectSaveAlways( (Ptr) bufTampons + TamponSize, &asioDriverInfo.MADDriver->DriverSettings, asioDriverInfo.MADDriver))
			{
				Ptr tempPtr = bufTampons + TamponSize;
				
			//	if( tempPtr < bufTampons) DebugStr("\p2");
			//	if( tempPtr > bufTampons + 16000L) DebugStr("\p3");
				
				for( xx = 0; xx < asioDriverInfo.MADDriver->BufSize / asioDriverInfo.MADDriver->DriverSettings.oversampling; xx++) tempPtr[ xx] = 0;
			}
						
		/*	{
				Str255 str;
				NumToString( TamponSize, str);
				DebugStr( str);
			}*/
			
			asioDriverInfo.MADDriver->OscilloWavePtr	= (char*) bufTampons + TamponSize;
		
			if( asioDriverInfo.MADDriver->useOsciBuffers)
			{
				asioDriverInfo.MADDriver->curDrawPtr++;
				if( asioDriverInfo.MADDriver->curDrawPtr >= MAXDRAW) asioDriverInfo.MADDriver->curDrawPtr = 0;
			
				BlockMoveData( asioDriverInfo.MADDriver->OscilloWavePtr, asioDriverInfo.MADDriver->OsciDrawPtr[ asioDriverInfo.MADDriver->curDrawPtr], asioDriverInfo.MADDriver->OscilloWaveSize);
				asioDriverInfo.MADDriver->newData[ asioDriverInfo.MADDriver->curDrawPtr] = true;
				asioDriverInfo.MADDriver->curTime = TickCount();
			}
			
			TamponSize += asioDriverInfo.MADDriver->BufSize / asioDriverInfo.MADDriver->DriverSettings.oversampling;
		}
		while( buffSize*4 > TamponSize);
	}
	
	// **** **** **** **** **** **** **** **** **** 

	// perform the processing
	for (int i = 0; i < asioDriverInfo.outputBuffers; i++)		//asioDriverInfo.inputBuffers + 
	{
		if (asioDriverInfo.bufferInfos[i].isInput == false)
		{
			// OK do processing for the outputs only
			switch (asioDriverInfo.channelInfos[i].type)
			{
			case ASIOSTInt16LSB:
			{	short	*buff = (short*) asioDriverInfo.bufferInfos[i].buffers[index];
				short	*src = (short*) ( (Ptr) bufTampons + TamponPos + i*2);
				
				for( xx = 0; xx < buffSize; xx++)
				{
					buff[ xx] = src[ xx*2];
				}
				
				reverseEndian( buff, 16, buffSize);
			}
			break;
			
			case ASIOSTInt24LSB:		// used for 20 bits as well
				memset (asioDriverInfo.bufferInfos[i].buffers[index], 0, buffSize * 3);
				break;
			case ASIOSTInt32LSB:
				memset (asioDriverInfo.bufferInfos[i].buffers[index], 0, buffSize * 4);
				break;
			case ASIOSTFloat32LSB:		// IEEE 754 32 bit float, as found on Intel x86 architecture
				memset (asioDriverInfo.bufferInfos[i].buffers[index], 0, buffSize * 4);
				break;
			case ASIOSTFloat64LSB: 		// IEEE 754 64 bit double float, as found on Intel x86 architecture
				memset (asioDriverInfo.bufferInfos[i].buffers[index], 0, buffSize * 8);
				break;

				// these are used for 32 bit data buffer, with different alignment of the data inside
				// 32 bit PCI bus systems can more easily used with these
			case ASIOSTInt32LSB16:		// 32 bit data with 18 bit alignment
			{	long	*buff = (long*) asioDriverInfo.bufferInfos[i].buffers[index];
				short	*src = (short*) ( (Ptr) bufTampons + TamponPos + i*2);
				
				for( xx = 0; xx < buffSize; xx++)
				{
					buff[ xx] = ((long) src[ xx*2]);
				}
				
				reverseEndian( buff, 32, buffSize);
			}
			break;
			
			case ASIOSTInt32LSB18:		// 32 bit data with 18 bit alignment
			{	long	*buff = (long*) asioDriverInfo.bufferInfos[i].buffers[index];
				short	*src = (short*) ( (Ptr) bufTampons + TamponPos + i*2);
				
				for( xx = 0; xx < buffSize; xx++)
				{
					buff[ xx] = ((long) src[ xx*2])<<2;
				}
				
				reverseEndian( buff, 32, buffSize);
			}
			break;
			
			case ASIOSTInt32LSB20:		// 32 bit data with 20 bit alignment
			{	long	*buff = (long*) asioDriverInfo.bufferInfos[i].buffers[index];
				short	*src = (short*) ( (Ptr) bufTampons + TamponPos + i*2);
				
				for( xx = 0; xx < buffSize; xx++)
				{
					buff[ xx] = ((long) src[ xx*2])<<4;
				}
				
				reverseEndian( buff, 32, buffSize);
			}
			break;
			
			case ASIOSTInt32LSB24:		// 32 bit data with 24 bit alignment
			{	long	*buff = (long*) asioDriverInfo.bufferInfos[i].buffers[index];
				short	*src = (short*) ( (Ptr) bufTampons + TamponPos + i*2);
				
				for( xx = 0; xx < buffSize; xx++)
				{
					buff[ xx] = ((long) src[ xx*2])<<8;
				}
				
				reverseEndian( buff, 32, buffSize);
			}
			break;

			case ASIOSTInt16MSB:
			{	short	*buff = (short*) asioDriverInfo.bufferInfos[i].buffers[index];
				short	*src = (short*) ( (Ptr) bufTampons + TamponPos + i*2);
				
				for( xx = 0; xx < buffSize; xx++)
				{
					buff[ xx] = src[ xx*2];
				}
			}
			break;
			
			case ASIOSTInt24MSB:		// used for 20 bits as well
				memset (asioDriverInfo.bufferInfos[i].buffers[index], 0, buffSize * 3);
				break;
			case ASIOSTInt32MSB:
			{	short	*buff = (short*) asioDriverInfo.bufferInfos[i].buffers[index];
				short	*src = (short*) ( (Ptr) bufTampons + TamponPos + i*2);
				
				for( xx = 0; xx < buffSize; xx++)
				{
					buff[ xx] = src[ xx*2]<<16;
				}
			}
			break;
			case ASIOSTFloat32MSB:		// IEEE 754 32 bit float, as found on Intel x86 architecture
				memset (asioDriverInfo.bufferInfos[i].buffers[index], 0, buffSize * 4);
				break;
			case ASIOSTFloat64MSB: 		// IEEE 754 64 bit double float, as found on Intel x86 architecture
				memset (asioDriverInfo.bufferInfos[i].buffers[index], 0, buffSize * 8);
				break;

				// these are used for 32 bit data buffer, with different alignment of the data inside
				// 32 bit PCI bus systems can more easily used with these
			case ASIOSTInt32MSB16:		// 32 bit data with 18 bit alignment
			case ASIOSTInt32MSB18:		// 32 bit data with 18 bit alignment
			case ASIOSTInt32MSB20:		// 32 bit data with 20 bit alignment
			case ASIOSTInt32MSB24:		// 32 bit data with 24 bit alignment
				memset (asioDriverInfo.bufferInfos[i].buffers[index], 0, buffSize * 4);
				break;
			}
		}
	}
	
	TamponPos += buffSize* 4;
	
	// finally if the driver supports the ASIOOutputReady() optimization, do it here, all data are in place
	if (asioDriverInfo.postOutput)
		ASIOOutputReady();

/*	if (processedSamples >= asioDriverInfo.sampleRate * TEST_RUN_TIME)	// roughly measured
		asioDriverInfo.stopped = true;
	else*/
	
		processedSamples += buffSize;

	return 0L;
}

//----------------------------------------------------------------------------------
void bufferSwitch(long index, ASIOBool processNow)
{	// the actual processing callback.
	// Beware that this is normally in a seperate thread, hence be sure that you take care
	// about thread synchronization. This is omitted here for simplicity.

	// as this is a "back door" into the bufferSwitchTimeInfo a timeInfo needs to be created
	// though it will only set the timeInfo.samplePosition and timeInfo.systemTime fields and the according flags
	ASIOTime  timeInfo;
	memset (&timeInfo, 0, sizeof (timeInfo));

	// get the time stamp of the buffer, not necessary if no
	// synchronization to other media is required
	if(ASIOGetSamplePosition(&timeInfo.timeInfo.samplePosition, &timeInfo.timeInfo.systemTime) == ASE_OK)
		timeInfo.timeInfo.flags = kSystemTimeValid | kSamplePositionValid;

	bufferSwitchTimeInfo (&timeInfo, index, processNow);
}

OSErr	ASIOSndClose( MADDriverRec *inMADDriver)
{
	OSErr		err;
	short		i;


	ASIODisposeBuffers();
	
	ASIOExit();
	
	asioDrivers->removeCurrentDriver();
	
	ASIOOK = false;
	
	return noErr;
}

void sampleRateChanged(ASIOSampleRate sRate)
{
	// do whatever you need to do if the sample rate changed
	// usually this only happens during external sync.
	// Audio processing is not stopped by the driver, actual sample rate
	// might not have even changed, maybe only the sample rate status of an
	// AES/EBU or S/PDIF digital input at the audio device.
	// You might have to update time/sample related conversion routines, etc.
}

long asioMessages(long selector, long value, void* message, double* opt)
{
	// currently the parameters "value", "message" and "opt" are not used.
	long ret = 0;
	switch(selector)
	{
		case kAsioSelectorSupported:
			if(value == kAsioResetRequest
			|| value == kAsioEngineVersion
			|| value == kAsioResyncRequest
			|| value == kAsioLatenciesChanged
			// the following three were added for ASIO 2.0, you don't necessarily have to support them
			|| value == kAsioSupportsTimeInfo
			|| value == kAsioSupportsTimeCode
			|| value == kAsioSupportsInputMonitor)
				ret = 1L;
			break;
		case kAsioResetRequest:
			// defer the task and perform the reset of the driver during the next "safe" situation
			// You cannot reset the driver right now, as this code is called from the driver.
			// Reset the driver is done by completely destruct is. I.e. ASIOStop(), ASIODisposeBuffers(), Destruction
			// Afterwards you initialize the driver again.
			asioDriverInfo.stopped;  // In this sample the processing will just stop
			ret = 1L;
			break;
		case kAsioResyncRequest:
			// This informs the application, that the driver encountered some non fatal data loss.
			// It is used for synchronization purposes of different media.
			// Added mainly to work around the Win16Mutex problems in Windows 95/98 with the
			// Windows Multimedia system, which could loose data because the Mutex was hold too long
			// by another thread.
			// However a driver can issue it in other situations, too.
			ret = 1L;
			break;
		case kAsioLatenciesChanged:
			// This will inform the host application that the drivers were latencies changed.
			// Beware, it this does not mean that the buffer sizes have changed!
			// You might need to update internal delay data.
			ret = 1L;
			break;
		case kAsioEngineVersion:
			// return the supported ASIO version of the host application
			// If a host applications does not implement this selector, ASIO 1.0 is assumed
			// by the driver
			ret = 2L;
			break;
		case kAsioSupportsTimeInfo:
			// informs the driver wether the asioCallbacks.bufferSwitchTimeInfo() callback
			// is supported.
			// For compatibility with ASIO 1.0 drivers the host application should always support
			// the "old" bufferSwitch method, too.
			ret = 1;
			break;
		case kAsioSupportsTimeCode:
			// informs the driver wether application is interested in time code info.
			// If an application does not need to know about time code, the driver has less work
			// to do.
			ret = 0;
			break;
	}
	return ret;
}

ASIOError create_asio_buffers (DriverInfo *asioDriverInfo)
{	// create buffers for all inputs and outputs of the card with the 
	// preferredSize from ASIOGetBufferSize() as buffer size
	long i;
	ASIOError result;

	// fill the bufferInfos from the start without a gap
	ASIOBufferInfo *info = asioDriverInfo->bufferInfos;

	// prepare inputs (Though this is not necessaily required, no opened inputs will work, too
	if (asioDriverInfo->inputChannels > kMaxInputChannels)
		asioDriverInfo->inputBuffers = kMaxInputChannels;
	else
		asioDriverInfo->inputBuffers = asioDriverInfo->inputChannels;
	for(i = 0; i < asioDriverInfo->inputBuffers; i++, info++)
	{
		info->isInput = ASIOTrue;
		info->channelNum = i;
		info->buffers[0] = info->buffers[1] = 0;
	}

	// prepare outputs
	if (asioDriverInfo->outputChannels > kMaxOutputChannels)
		asioDriverInfo->outputBuffers = kMaxOutputChannels;
	else
		asioDriverInfo->outputBuffers = asioDriverInfo->outputChannels;
	for(i = 0; i < asioDriverInfo->outputBuffers; i++, info++)
	{
		info->isInput = ASIOFalse;
		info->channelNum = i;
		info->buffers[0] = info->buffers[1] = 0;
	}

	// create and activate buffers
	result = ASIOCreateBuffers(asioDriverInfo->bufferInfos,
		asioDriverInfo->inputBuffers + asioDriverInfo->outputBuffers,
		asioDriverInfo->preferredSize, &asioCallbacks);
	if (result == ASE_OK)
	{
		// now get all the buffer details, sample word length, name, word clock group and activation
		for (i = 0; i < asioDriverInfo->inputBuffers + asioDriverInfo->outputBuffers; i++)
		{
			asioDriverInfo->channelInfos[i].channel = asioDriverInfo->bufferInfos[i].channelNum;
			asioDriverInfo->channelInfos[i].isInput = asioDriverInfo->bufferInfos[i].isInput;
			result = ASIOGetChannelInfo(&asioDriverInfo->channelInfos[i]);
			if (result != ASE_OK)
				break;
		}

		if (result == ASE_OK)
		{
			// get the input and output latencies
			// Latencies often are only valid after ASIOCreateBuffers()
			// (input latency is the age of the first sample in the currently returned audio block)
			// (output latency is the time the first sample in the currently returned audio block requires to get to the output)
			result = ASIOGetLatencies(&asioDriverInfo->inputLatency, &asioDriverInfo->outputLatency);
			//if (result == ASE_OK)
				//printf ("ASIOGetLatencies (input: %d, output: %d);\n", asioDriverInfo->inputLatency, asioDriverInfo->outputLatency);
		}
	}
	return result;
}

OSErr	InitASIOManager( MADDriverRec *inMADDriver, long init)
{
	OSErr			err = -1;

	ASIOOK = false;
	
	if( !asioDrivers)
	{
		asioDrivers = new AsioDrivers();
		if(asioDrivers)
		{
			//asioDrivers->getName( 0, ASIO_DRIVER_NAME);
		}
	}
	
	if (loadAsioDriver (ASIO_DRIVER_NAME))
	{
		// initialize the driver
		if (ASIOInit (&asioDriverInfo.driverInfo) == ASE_OK)
		{
			if (init_asio_static_data (&asioDriverInfo) == 0)
			{
				// set up the asioCallback structure and create the ASIO data buffer
				asioCallbacks.bufferSwitch = &bufferSwitch;
				asioCallbacks.sampleRateDidChange = &sampleRateChanged;
				asioCallbacks.asioMessage = &asioMessages;
				asioCallbacks.bufferSwitchTimeInfo = &bufferSwitchTimeInfo;
				if (create_asio_buffers (&asioDriverInfo) == ASE_OK)
				{
					long longest;
					
					ASIOOK = true;
					
					err = noErr;
					asioDriverInfo.MADDriver = inMADDriver;
					
					TamponPos = 0;
					TamponSize = 0;
					
					if( asioDriverInfo.preferredSize*2 > asioDriverInfo.MADDriver->BufSize / asioDriverInfo.MADDriver->DriverSettings.oversampling) longest = asioDriverInfo.preferredSize;
					else longest = asioDriverInfo.MADDriver->BufSize / asioDriverInfo.MADDriver->DriverSettings.oversampling;
					
					bufTampons = NewPtrClear( longest * 16L);
					if( bufTampons == 0L) DebugStr("\pbufTampons");
				}
			}
		}
	}
	else
	{
		strcpy( ASIO_DRIVER_NAME, "Driver Not Working");
	}
	
	return noErr;
}

void ASIOStopChannel( MADDriverRec *inMADDriver)
{
	if( ASIOOK) ASIOStop();
}

void ASIOPlayChannel( MADDriverRec *inMADDriver)
{
	if( ASIOOK) ASIOStart();
}
