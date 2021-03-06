// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// TNT Data Store Library
// CDataStoreSection.h
// © Mark Tully and TNT Software 1999
// 28/8/99
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

/* ***** BEGIN LICENSE BLOCK *****
*
* Copyright (c) 1999, Mark Tully and John Treece-Birch
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

#include		<LSharable.h>
#include		<LAttachment.h>
#include		"CDataStoreMarker.h"
#include		"CListElementT.h"
#include		"CMarkableDataStore.h"

class			CDataSectionSorter;
class			CDataStoreSection;

class CDataStoreSectionMarker : public CDataStoreMarker
{
	private:
		virtual void				Set(
										CMarkableDataStore				*inDataStore,
										CDataStore::TDataOffset			inOffset)		{ CDataStoreMarker::Set(inDataStore,inOffset); }


	public:
		typedef OSType					EMarkerClass;
		
		enum
		{
			kStartMarkerClass='Star',
			kEndMarkerClass='End '
		};

	protected:
		CDataStoreSection				*mSection;
		EMarkerClass					mMarkerClass;

	public:
										CDataStoreSectionMarker(
											EMarkerClass					inClass);
		
		CDataStoreSection				*GetSection() const									{ return mSection; }	
		EMarkerClass					GetMarkerClass()								{ return mMarkerClass; }

		virtual void					Set(
											CDataStoreSection				*inSection,
											CDataStore::TDataOffset			inOffset);

};

class CDataStoreSection : public LSharable
{
	protected:
		CDataStoreSectionMarker			mStart,mEnd;
		TSharablePtr<CDataStoreSection>	mParentSection;				// The root section will not have a parent section
		CMarkableDataStore				*mDataStore;
		bool							mLocked;
		virtual void					NoMoreUsers();

		static CDataSectionSorter /*e*/ *GetSectionSorter(
											CMarkableDataStore		*inStore);
									
	public:
		/*e*/							CDataStoreSection(
											CMarkableDataStore		*inStore,
											CDataStore::TDataOffset	inStartOffset,
											CDataStore::TDataOffset	inLength);
											
										CDataStoreSection(
											CDataStoreSection		*inParentSection,
											CDataStore::TDataOffset	inStartOffset,
											CDataStore::TDataOffset	inLength);
		virtual							~CDataStoreSection();

		virtual void					SetLock(
											bool					inLocked);
		virtual bool					GetLock()										{ return mLocked; }
		
		virtual CDataStore::TDataOffset GetStartOffset();
		virtual CDataStore::TDataOffset	GetLength() const;
		virtual void /*e*/				SetLength(
											CDataStore::TDataOffset	inLength);
											
		virtual CMarkableDataStore		*GetDataStore()	const							{ return mDataStore; }
		virtual CDataStoreSection		*GetParentSection()								{ return mParentSection; }
		virtual UInt32					GetHierarchicalDepth();

		virtual EMarkerOrder			OrderSubSections(
											CDataStoreSection		*inSectionA,
											CDataStoreSection		*inSectionB);
};