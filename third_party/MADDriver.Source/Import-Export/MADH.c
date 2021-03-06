/********************						***********************/
//
//	Player PRO 5.0 - DRIVER SOURCE CODE -
//
//	Library Version 5.0
//
//	To use with MAD Library for Mac: Symantec, CodeWarrior and MPW
//
//	Antoine ROSSET
//	16 Tranchees
//	1206 GENEVA
//	SWITZERLAND
//
//	COPYRIGHT ANTOINE ROSSET 1996, 1997, 1998
//
//	Thank you for your interest in PlayerPRO !
//
//	FAX:				(+41 22) 346 11 97
//	PHONE: 			(+41 79) 203 74 62
//	Internet: 	RossetAntoine@bluewin.ch
//
/********************						***********************/

#include <PlayerPROCore/PlayerPROCore.h>
#include "MOD.h"
#include "MADH.h"

//TODO: Byteswap on Intel!

#ifndef _SRC
Cmd* GetMADCommand( register short PosX, register short	TrackIdX, register PatData*	tempMusicPat)
{
	if( PosX < 0) PosX = 0;
	else if( PosX >= tempMusicPat->header.size) PosX = tempMusicPat->header.size -1;
		
	return( & (tempMusicPat->Cmds[ (tempMusicPat->header.size * TrackIdX) + PosX]));
}
#endif

enum
{
	ins 	= 1,
	note	= 2,
	cmd		= 4,
	argu	= 8,
	vol		= 16
};


static oldPatData* oldDecompressPartitionMAD1( oldMADSpec *header, oldPatData* myPat)
{
	oldPatData*				finalPtr;
	Byte 					*srcPtr;
	oldCmd					*myCmd;
	short					maxCmd;
	Byte					set;
	
	finalPtr = ( oldPatData*) NewPtrClear( sizeof( oldPatHeader) + myPat->header.size * header->numChn * sizeof( oldCmd));
	if( finalPtr == NULL) return NULL;
	
	BlockMoveData( myPat, finalPtr, sizeof( oldPatHeader));

	srcPtr = (Byte*) myPat->Cmds;
	myCmd = (oldCmd*) finalPtr->Cmds;
	maxCmd = finalPtr->header.size * header->numChn;
	
	/*** Decompression Routine ***/
	
	while( maxCmd != 0)
	{
		maxCmd--;
		
		myCmd->cmd 	= 0;
		myCmd->note = 0xFF;
		myCmd->arg 	= 0;
		myCmd->ins 	= 0;
		myCmd->vol 	= 0xFF;
		
		set = *srcPtr++;
		
		if( set & ins)	myCmd->ins = *srcPtr++;
		if( set & note)	myCmd->note = *srcPtr++;
		if( set & cmd)	myCmd->cmd = *srcPtr++;
		if( set & argu)	myCmd->arg = *srcPtr++;
		if( set & vol)	myCmd->vol = *srcPtr++;
		
		myCmd++;
	}
	
	return finalPtr;
}

static oldCmd* GetOldCommand( short PosX, short	TrackIdX, oldPatData*	tempMusicPat)
{
	if( PosX < 0) PosX = 0;
	else if( PosX >= tempMusicPat->header.size) PosX = tempMusicPat->header.size -1;
	
	return( &(tempMusicPat->Cmds[ (tempMusicPat->header.size * TrackIdX) + PosX]));
}

static inline void MADHmystrcpy( Ptr a, BytePtr b)
{
	BlockMoveData( b + 1, a, b[ 0]);
}

static OSErr MADH2Mad( Ptr MADPtr, long size, MADMusic *theMAD, MADDriverSettings *init)
{
	short		i, x;
	long		inOutCount, OffSetToSample = 0, z;
	OSErr		theErr = noErr;
	Ptr			tempPtr;
	long		finetune[16] = 
				{
					8363,	8413,	8463,	8529,	8581,	8651,	8723,	8757,
					7895,	7941,	7985,	8046,	8107,	8169,	8232,	8280
				};


/**** Old MADH variables ****/

	oldMADSpec				*oldMAD;

	oldMAD = (oldMADSpec*) MADPtr;


/**** HEADER ****/
	if( oldMAD->MAD != 'MADH') return MADFileNotSupportedByThisPlug;
	OffSetToSample += sizeof( oldMADSpec);

// Conversion
	inOutCount = sizeof( MADSpec);
	theMAD->header = (MADSpec*) MADPlugNewPtrClear( inOutCount, init);	
	if( theMAD->header == NULL) return MADNeedMemory;

	theMAD->header->MAD = 'MADK';

	BlockMoveData( oldMAD->name, theMAD->header->name, 32);
	theMAD->header->numPat			= oldMAD->numPat;
	theMAD->header->numChn			= oldMAD->numChn;
	theMAD->header->numPointers		= oldMAD->numPointers;
	BlockMoveData( oldMAD->oPointers, theMAD->header->oPointers, 256);
	theMAD->header->speed			= oldMAD->speed;
	theMAD->header->tempo			= oldMAD->tempo;

	theMAD->sets = (FXSets*) NewPtrClear( MAXTRACK * sizeof(FXSets));
	for( i = 0; i < MAXTRACK; i++) theMAD->header->chanBus[ i].copyId = i;
	MADHmystrcpy( theMAD->header->infos, "\pConverted by PlayerPRO MAD-H Plug (?Antoine ROSSET <rossetantoine@bluewin.ch>)");

/**** Patterns *******/

	for( i = 0; i < oldMAD->numPat; i++)
	{
		struct oldPatData		*tempPat, *tempPat2;
		struct oldPatHeader		tempPatHeader;
	
	/** Lecture du header de la partition **/
		inOutCount = sizeof( struct oldPatHeader);
		BlockMoveData( MADPtr + OffSetToSample, &tempPatHeader, inOutCount);
	
	/*************************************************/
	/** Lecture du header + contenu de la partition **/
	/*************************************************/
	
		if( tempPatHeader.compMode == 'MAD1')
		{
			inOutCount = sizeof( oldPatData) + tempPatHeader.patBytes;
		}
		else
		{
			inOutCount = sizeof( oldPatData) + oldMAD->numChn * tempPatHeader.size * sizeof( oldCmd);
		}
	
		tempPat = (struct oldPatData*) MADPlugNewPtr( inOutCount, init);
		if( tempPat == NULL) DebugStr("\pMemory Prob1");
	
		BlockMoveData( MADPtr + OffSetToSample, tempPat, inOutCount);
		OffSetToSample += inOutCount;
	
		if( tempPat->header.compMode == 'MAD1')
		{
			tempPat2 = oldDecompressPartitionMAD1( oldMAD, tempPat);
		
			DisposePtr( (Ptr) tempPat);
		
			tempPat = tempPat2;
		}
	
	/**************/
	/* CONVERSION */
	/**************/
	
		theMAD->partition[ i] = (PatData*) MADPlugNewPtrClear( sizeof( PatHeader) + theMAD->header->numChn * tempPat->header.size * sizeof( Cmd), init);
		if( theMAD->partition[ i] == NULL) return MADNeedMemory;
	
		theMAD->partition[ i]->header.size 		= tempPat->header.size;
		theMAD->partition[ i]->header.compMode 	= 'NONE';
	
		BlockMoveData( tempPat->header.name, theMAD->partition[ i]->header.name, 20);
	
		theMAD->partition[ i]->header.patBytes = 0;		theMAD->partition[ i]->header.unused2 = 0;
	
		for( x = 0; x < theMAD->partition[ i]->header.size; x++)
		{
			for( z = 0; z < theMAD->header->numChn; z++)
			{
				struct oldCmd *oldCmd;
				Cmd	*aCmd;
			
				aCmd = GetMADCommand(  x,  z, theMAD->partition[ i]);
			
				oldCmd 	= GetOldCommand(	x,
										z,
										tempPat);
			
				aCmd->ins 		= oldCmd->ins;
				aCmd->note 		= oldCmd->note;
				aCmd->cmd 		= oldCmd->cmd;
				aCmd->arg 		= oldCmd->arg;
				aCmd->vol		= oldCmd->vol;
				aCmd->unused 	= oldCmd->unused;
			}
		}
	
		DisposePtr( (Ptr) tempPat);
		tempPat = NULL;
	}
	for( i = theMAD->header->numPat; i < MAXPATTERN ; i++) theMAD->partition[ i] = NULL;

	for( i = 0; i < MAXTRACK; i++)
	{
		if( i % 2 == 0) theMAD->header->chanPan[ i] = MAX_PANNING/4;
		else theMAD->header->chanPan[ i] = MAX_PANNING - MAX_PANNING/4;
	
		theMAD->header->chanVol[ i] = MAX_VOLUME;
	}

	theMAD->header->generalVol		= 64;
	theMAD->header->generalSpeed	= 80;
	theMAD->header->generalPitch	= 80;

/**** Instruments header *****/

	theMAD->fid = ( InstrData*) MADPlugNewPtrClear( sizeof( InstrData) * (long) MAXINSTRU, init);
	if( !theMAD->fid) return MADNeedMemory;

	theMAD->sample = ( sData**) MADPlugNewPtrClear( sizeof( sData*) * (long) MAXINSTRU * (long) MAXSAMPLE, init);
	if( !theMAD->sample) return MADNeedMemory;

	for( i = 0; i < MAXINSTRU; i++) theMAD->fid[ i].firstSample = i * MAXSAMPLE;

	for( i = 0; i < 64; i++)
	{
		InstrData	*curIns = &theMAD->fid[ i];
	
		BlockMoveData( oldMAD->fid[ i].name, theMAD->fid[ i].name, 32);
	
		theMAD->fid[ i].type = oldMAD->fid[ i].type;
		theMAD->fid[ i].numSamples = oldMAD->fid[ i].numSamples;
		BlockMoveData( oldMAD->fid[ i].what, theMAD->fid[ i].what, 96);
		BlockMoveData( oldMAD->fid[ i].volEnv, theMAD->fid[ i].volEnv, 12 * sizeof( EnvRec));
		BlockMoveData( oldMAD->fid[ i].pannEnv, theMAD->fid[ i].pannEnv, 12 * sizeof( EnvRec));
		theMAD->fid[ i].volSize = oldMAD->fid[ i].volSize;
		theMAD->fid[ i].pannSize = oldMAD->fid[ i].pannSize;
		theMAD->fid[ i].volSus = oldMAD->fid[ i].volSus;
		theMAD->fid[ i].volBeg = oldMAD->fid[ i].volBeg;
		theMAD->fid[ i].volEnd = oldMAD->fid[ i].volEnd;
		theMAD->fid[ i].pannSus = oldMAD->fid[ i].pannSus;
		theMAD->fid[ i].pannBeg = oldMAD->fid[ i].pannBeg;
		theMAD->fid[ i].pannEnd = oldMAD->fid[ i].pannEnd;
		theMAD->fid[ i].volType = oldMAD->fid[ i].volType;
		theMAD->fid[ i].pannType = oldMAD->fid[ i].pannType;
		theMAD->fid[ i].volFade = oldMAD->fid[ i].volFade;
		theMAD->fid[ i].vibDepth = oldMAD->fid[ i].vibDepth;
		theMAD->fid[ i].vibRate = oldMAD->fid[ i].vibRate;
	
		for( x = 0; x < oldMAD->fid[ i].numSamples ; x++)
		{
			oldsData	 *oldcurData;
			sData		 *curData;
		
			oldcurData = (oldsData*) (MADPtr + OffSetToSample);
			OffSetToSample += sizeof( oldsData);
		
			curData = theMAD->sample[ i*MAXSAMPLE + x] = (sData*) MADPlugNewPtrClear( sizeof( sData), init);
		
			curData->size		= oldcurData->size;
			curData->loopBeg 	= oldcurData->loopBeg;
			curData->loopSize 	= oldcurData->loopSize;
			curData->vol		= oldcurData->vol;
			curData->c2spd		= oldcurData->c2spd;
			curData->loopType	= oldcurData->loopType;
			curData->amp		= oldcurData->amp;
	//	curData->panning	= oldcurData->panning;
			curData->relNote	= oldcurData->relNote;
		
			curData->data 		= MADPlugNewPtr( curData->size, init);
			if( curData->data == NULL) return MADNeedMemory;
			
			BlockMoveData( MADPtr + OffSetToSample, curData->data, curData->size);
			OffSetToSample += curData->size;
		}
	}

	return noErr;
}

static OSErr TestoldMADFile( Ptr AlienFile)
{
	OSType	myMADSign = *((OSType*) AlienFile);
	MOT32(&myMADSign);

	if(	myMADSign == 'MADH') return noErr;
	else return  MADFileNotSupportedByThisPlug;
}

static OSErr ExtractoldMADInfo( PPInfoRec *info, Ptr AlienFile)
{
	oldMADSpec	*myMOD = ( oldMADSpec*) AlienFile;
//	long		PatternSize;
	short		i;
//	short		tracksNo;
	
	/*** Signature ***/
	
	info->signature = myMOD->MAD;
	MOT32(&info->signature);
	
	/*** Internal name ***/
	
	myMOD->name[ 31] = '\0';
	strcpy( info->internalFileName, myMOD->name);
	
	/*** Tracks ***/
	
	info->totalTracks = myMOD->numChn;
		
	/*** Total Patterns ***/
	
	info->totalPatterns = 0;
	for( i = 0; i < 128; i++)
	{
		if( myMOD->oPointers[ i] >= info->totalPatterns)	info->totalPatterns = myMOD->oPointers[ i];
	}
	info->totalPatterns++;
	
	/*** Partition Length ***/
	
	info->partitionLength = myMOD->numPointers;
	
	/*** Total Instruments ***/
	
	for( i = 0, info->totalInstruments = 0; i < 64 ; i++)
	{
		short numSamSwap = myMOD->fid[ i].numSamples;
		MOT16(&numSamSwap);
		if( numSamSwap > 0) info->totalInstruments++;
	}
	
	strcpy( info->formatDescription, "MADH Plug");

	return noErr;
}

/*****************/
/* MAIN FUNCTION */
/*****************/

OSErr mainMADH( OSType order, Ptr AlienFileName, MADMusic *MadFile, PPInfoRec *info, MADDriverSettings *init)
{
	OSErr	myErr = noErr;
	Ptr		AlienFile;
	UNFILE	iFileRefI;
	long	sndSize;
	
	switch( order)
	{
		case 'IMPL':
			iFileRefI = iFileOpen( AlienFileName);
			if( iFileRefI)
			{
				sndSize = iGetEOF( iFileRefI);
				
				// ** MEMORY Test Start
				AlienFile = MADPlugNewPtr( sndSize * 2L, init);
				if( AlienFile == NULL) myErr = MADNeedMemory;
				// ** MEMORY Test End
				
				else
				{
					DisposePtr( AlienFile);
					
					AlienFile = MADPlugNewPtr( sndSize, init);
					myErr = iRead(sndSize, AlienFile, iFileRefI);
					if( myErr == noErr)
					{
						myErr = TestoldMADFile( AlienFile);
						if( myErr == noErr)
						{
							myErr = MADH2Mad( AlienFile, GetPtrSize( AlienFile), MadFile, init);
						}
					}
					DisposePtr( AlienFile);	AlienFile = NULL;
				}
				iClose( iFileRefI);
			}
			else myErr = MADReadingErr;
			break;
		
		case 'TEST':
			iFileRefI = iFileOpen( AlienFileName);
			if( iFileRefI)
			{
				sndSize = 5000L;	// Read only 5000 first bytes for optimisation
				
				AlienFile = MADPlugNewPtr( sndSize, init);
				if( AlienFile == NULL) myErr = MADNeedMemory;
				else
				{
					myErr = iRead( sndSize, AlienFile, iFileRefI);
					if(myErr == noErr) myErr = TestoldMADFile( AlienFile);
					
					DisposePtr( AlienFile);	AlienFile = NULL;
				}
				iClose( iFileRefI);
			}
			else myErr = MADReadingErr;
			break;

		case 'INFO':
			iFileRefI = iFileOpen( AlienFileName);
			if( iFileRefI)
			{
				info->fileSize = iGetEOF( iFileRefI);
			
				sndSize = 5000L;	// Read only 5000 first bytes for optimisation
				
				AlienFile = MADPlugNewPtr( sndSize, init);
				if( AlienFile == NULL) myErr = MADNeedMemory;
				else
				{
					myErr = iRead( sndSize, AlienFile, iFileRefI);
					if( myErr == noErr)
					{
						myErr = ExtractoldMADInfo( info, AlienFile);
					}
					DisposePtr( AlienFile);	AlienFile = NULL;
				}
				iClose( iFileRefI);
			}
			else myErr = MADReadingErr;
			break;
		
		default:
			myErr = MADOrderNotImplemented;
			break;
	}

	return myErr;
}

#define PLUGUUID (CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault, 0x16, 0x94, 0x9F, 0x32, 0x8E, 0x4F, 0x4D, 0x37, 0xAC, 0x8C, 0xE1, 0xD3, 0x83, 0x59, 0x6C, 0x51))
//16949F32-8E4F-4D37-AC8C-E1D383596C51

#define PLUGMAIN mainMADH
#define PLUGINFACTORY MADHFactory
#include "CFPlugin-bridge.c"
