// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// TSafePtr.h
// Mark Tully
// 7/7/98
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

/* ***** BEGIN LICENSE BLOCK *****
*
* Copyright (c) 1998, Mark Tully and John Treece-Birch
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

#include				"TListener.h"
#include				"TBroadcaster.h"

template <class T>
class TSafePtr : public TListener
{
	protected:
		T						mPtr;
		virtual void			BroadcasterDied(TBroadcaster *inNowDead);

		virtual T				GetPtr();

	public:
		/*e*/					TSafePtr(TBroadcaster *inWatchMe,T inPtr);
								operator T();
};

/*e*/
template <class T>
TSafePtr<T>::TSafePtr(TBroadcaster *inWatchMe,T inPtr)
{
	if (!inWatchMe)
		Throw_(paramErr);
	if (!inWatchMe->AddListener(this))
		Throw_(memFullErr);
		
	mPtr=inPtr;
}

template <class T>
T TSafePtr<T>::GetPtr()
{
	return mPtr;
}

template <class T>
TSafePtr<T>::operator T()
{
	return GetPtr();
}

template <class T>
void TSafePtr<T>::BroadcasterDied(TBroadcaster *inNowDead)
{
	mPtr=0L;
}
