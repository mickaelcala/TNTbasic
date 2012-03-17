// Copyright ©2005, 2006 Freescale Semiconductor, Inc.
// Please see the License for the specific language governing rights and
// limitations under the License.
// ===========================================================================
//	LSimpleAEAction.cp			PowerPlant 2.2.2	©1995-2005 Metrowerks Inc.
// ===========================================================================
//
//	Abstract class for an action for which undo and redo are implemented
//	by sending AppleEvents to the application.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include <LSimpleAEAction.h>
#include <UAppleEventsMgr.h>
#include <LModelObject.h>

#ifndef __MACH__
#include <AEInteraction.h>
#endif

PP_Begin_Namespace_PowerPlant


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ LSimpleAEAction						Constructor				  [public]
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Parameters specify undo/redo menu strings

LSimpleAEAction::LSimpleAEAction(
	ResIDT		inStringResID,
	SInt16		inStringIndex,
	bool		inAlreadyDone)

	: LAction(inStringResID, inStringIndex, inAlreadyDone)
{
	mRecordOnlyFinalState	= false;
	mUndoAEKeyFed			= typeNull;
	mPostUndoAEKeyFed		= typeNull;
	mFromReplyKey			= typeNull;
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ LSimpleAEAction						Copy Constructor		  [public]
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

LSimpleAEAction::LSimpleAEAction(
	const LSimpleAEAction&	inOriginal)

	: LAction(inOriginal)
{
		mRecordOnlyFinalState	= inOriginal.mRecordOnlyFinalState;
		mUndoAEKeyFed			= inOriginal.mUndoAEKeyFed;
		mPostUndoAEKeyFed		= inOriginal.mPostUndoAEKeyFed;
		mFromReplyKey			= inOriginal.mFromReplyKey;
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ operator=								Assignment Operator		  [public]
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

LSimpleAEAction&
LSimpleAEAction::operator=(
	const LSimpleAEAction&	inOriginal )
{
	if (this != &inOriginal) {

		LAction::operator=(inOriginal);

		mRecordOnlyFinalState	= inOriginal.mRecordOnlyFinalState;
		mUndoAEKeyFed			= inOriginal.mUndoAEKeyFed;
		mPostUndoAEKeyFed		= inOriginal.mPostUndoAEKeyFed;
		mFromReplyKey			= inOriginal.mFromReplyKey;
	}

	return *this;
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ ~LSimpleAEAction						Destructor				  [public]
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

LSimpleAEAction::~LSimpleAEAction()
{
}


#pragma mark === AppleEvent Configuration ===

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ SetRedoAE
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
void
LSimpleAEAction::SetRedoAE(
	AEEventClass	inEventClass,
	AEEventID		inEventID)

	// Don't use this routine if the associated event has parameters.
	// Instead, make an AppleEvent and use SetRedoAE(AppleEvent).

{
	UAppleEventsMgr::MakeAppleEvent(inEventClass, inEventID, mRedoEvent.mDesc);
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ SetRedoAE
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::SetRedoAE(
	const AppleEvent&	inAppleEvent)

{
	ThrowIfOSErr_(::AEDuplicateDesc(&inAppleEvent, &mRedoEvent.mDesc));
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ SetUndoAE
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::SetUndoAE(
	AEEventClass	inEventClass,
	AEEventID		inEventID,
	Boolean			inFeedUndoWithRedoReply)

	// Don't use this routine if the associated event has parameters.
	// Instead, make an AppleEvent and use SetUndoAE(AppleEvent).

	// Avoid using explicitly using the optional inFeedUndoWithRedoReply.
	// Instead, call UndoAESetKeyFed after all SetUndoAE's have been called.

{
	UAppleEventsMgr::MakeAppleEvent(inEventClass, inEventID, mUndoEvent.mDesc);
	if (inFeedUndoWithRedoReply) {
		UndoAESetKeyFed(keyDirectObject);
	}
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ SetUndoAE
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::SetUndoAE(
	const AppleEvent&	inAppleEvent,
	Boolean				inFeedUndoWithRedoReply)

	// Avoid using explicitly using the optional inFeedUndoWithRedoReply.
	// Instead, call UndoAESetKeyFed after all SetUndoAE's have been called.

{
	ThrowIfOSErr_(::AEDuplicateDesc(&inAppleEvent, &mUndoEvent.mDesc));
	if (inFeedUndoWithRedoReply) {
		UndoAESetKeyFed(keyDirectObject);
	}
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ SetPostUndoAE
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::SetPostUndoAE(
	const AppleEvent&	inAppleEvent)

{
	ThrowIfOSErr_(::AEDuplicateDesc(&inAppleEvent, &mPostUndoEvent.mDesc));
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ UndoAESetKeyFed
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::UndoAESetKeyFed(
	DescType inKey,
	DescType inFromReplyKey)

	// Used to set the "key parameter receiver" for the undo event
	// from the reply of the redo event.

	// Avoid calling this method with typeNull because that is the natural
	// constructed state of an LSimpleAEAction.

{
	mUndoAEKeyFed = inKey;
	mFromReplyKey = inFromReplyKey;
}

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ PostUndoAESetKeyFed
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::PostUndoAESetKeyFed(
	DescType inKey,
	DescType inFromReplyKey)
{
	mPostUndoAEKeyFed = inKey;
	mPostFromReplyKey = inFromReplyKey;
}

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ RedoAEAdd
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::RedoAEAdd(
	AEKeyword		theAEKeyword,
	const AEDesc&	inDesc)
{
	ThrowIfOSErr_(::AEPutParamDesc(&mRedoEvent.mDesc, theAEKeyword, &inDesc));
}

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ UndoAEAdd
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::UndoAEAdd(
	AEKeyword		theAEKeyword,
	const AEDesc&	inDesc)
{
	ThrowIfOSErr_(::AEPutParamDesc(&mUndoEvent.mDesc, theAEKeyword, &inDesc));
}


#pragma mark === Undo/Redo Implementation ===

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ RedoSelf
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::RedoSelf()
{
	Assert_(CanRedo());

	// Do the event

	SendAppleEvent(mRedoEvent.mDesc, mRecordOnlyFinalState ? kAEDontRecord : 0);

	// Record information from reply for undo

	if ((mUndoEvent.mDesc.descriptorType != typeNull) && (mUndoAEKeyFed != typeNull)) {
		StAEDescriptor aeResult;

		// keyDirectObject -- the result from the original operation
		Assert_(mFromReplyKey != typeNull);
		aeResult.GetParamDesc(mReply.mDesc, mFromReplyKey, typeWildCard);
		UndoAEAdd(mUndoAEKeyFed, aeResult.mDesc);
		mUndoAEKeyFed = typeNull;	// Don't add it twice
	}
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ UndoSelf
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::UndoSelf()
{
	Assert_(CanUndo());

	// Do the event

	SendAppleEvent(mUndoEvent.mDesc, mRecordOnlyFinalState ? kAEDontRecord : 0);

	// Post undo AE

	if (mPostUndoAEKeyFed != typeNull) {
		StAEDescriptor aeResult;

		// mPostFromReplyKey -- the result from the undo operation
		Assert_(mPostFromReplyKey != typeNull);
		aeResult.GetParamDesc(mReply.mDesc, mPostFromReplyKey, typeWildCard);
		ThrowIfOSErr_(::AEPutParamDesc(&mPostUndoEvent.mDesc, mPostFromReplyKey, &aeResult.mDesc));
		mPostUndoAEKeyFed = typeNull;	//	Don't add it twice
	}

	if (mPostUndoEvent.mDesc.descriptorType != typeNull) {
		SendAppleEvent(mPostUndoEvent.mDesc, mRecordOnlyFinalState ? kAEDontRecord : 0);
	}
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ Finalize
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::Finalize()
{
	if (mRecordOnlyFinalState && mIsDone) {
		SendAppleEvent(mRedoEvent.mDesc, kAEDontExecute);
	}

	// Once an event has been finalized, subsequent redos & undos must be recorded.

	SetRecordOnlyFinalState(false);
	LAction::Finalize();
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ CanRedo
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

Boolean
LSimpleAEAction::CanRedo() const
{
	return LAction::CanRedo() && (mRedoEvent.mDesc.descriptorType != typeNull);
}

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ CanUndo
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

Boolean
LSimpleAEAction::CanUndo() const
{
	return LAction::CanUndo() && (mUndoEvent.mDesc.descriptorType != typeNull);
}


#pragma mark === Accessor Methods ===

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ SetRecordOnlyFinalState
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::SetRecordOnlyFinalState(
	Boolean inRecordOnlyFinalState)
{
	mRecordOnlyFinalState = inRecordOnlyFinalState;
}


// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ GetReplyDesc
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::GetReplyDesc(
	AEDesc*		outDesc)
{
	ThrowIfOSErr_(::AEDuplicateDesc(&mReply.mDesc, outDesc));
}


#pragma mark === AppleEvent Implementation ===

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ SendAppleEvent
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
LSimpleAEAction::SendAppleEvent(
	AppleEvent&		inAppleEvent,
	AESendMode		inSendModifiers)
{
	StAEDescriptor aeResult;
	StAEDescriptor aeHole;

	inSendModifiers |= kAEWaitReply;

	ThrowIfOSErr_(::AEDisposeDesc(&mReply.mDesc));
	ThrowIfOSErr_(::AESend(&inAppleEvent, &mReply.mDesc, inSendModifiers, kAENormalPriority,
						kAEDefaultTimeout, nil, nil));
}


PP_End_Namespace_PowerPlant
