// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// CPersistCString.cpp
// TNT Library
// Copyright Mark Tully and TNT Software 2000
// 18/8/00
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

/* ***** BEGIN LICENSE BLOCK *****
*
* Copyright (c) 2000, Mark Tully and John Treece-Birch
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or other
*   materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
* ***** END LICENSE BLOCK ***** */

#pragma once

#include <LStream.h>
#include "CCString.h"
#include "UPersistanceMgr.h"
#include "Endian.h"
#include "cstring"

class CPersistCString : public CPersistor, public CCString
{
protected:
    virtual void		FlattenToStreamSelf(
							LStream	&outStream)
						{
						    CStringToStream(outStream,mString,GetLength());
						}     
     
	static void			CStringToStream(
						    LStream &outStream,
						    const char *inStr,
						    SInt32 inLen=0)
						{
						    if (!inLen)
							inLen=std::strlen(inStr);

						    SInt32	len=inLen;

						    /* HToBE32(len);  Should be done automatically now */

							outStream << len;
						    outStream.PutBytes(inStr,inLen);
						}

    virtual void		AssignFromStreamSelf(
							LStream &inStream)
						{
						     
						    SInt32	len=0;

						    inStream >> len;

						 /*   BEToH32(len);  Should be done automatically now */

						    SetMaxLength(len);
						    inStream.GetBytes(mString,len);
						    mString[len]=0;
						}

public:
    enum { kPersistorId = FOUR_CHAR_CODE('CStr') };

					    CPersistCString(
							CPersistor *inContainer,
							const char *inStr="",
							SInt32 inDefaultMaxLen=256) :
							CCString(inStr,inDefaultMaxLen),
							CPersistor(inContainer,kPersistorId)
							{
							}
};