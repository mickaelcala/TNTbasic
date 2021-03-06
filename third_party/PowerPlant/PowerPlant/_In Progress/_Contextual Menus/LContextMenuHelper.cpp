/********************************************************************************/
/*																				*/
/*	? 2006, Aurbach & Associates, Inc.  All rights reserved.					*/
/*																				*/
/*	Redistribution and use in source and binary forms, with or without			*/
/*	modification, are permitted provided that the following condition			*/
/*	are met:																	*/
/*																				*/
/*	  ?	Redistributions of source code must retain the above copyright			*/
/*		notice, this list of conditions and the following disclaimer.			*/
/*																				*/
/*	  ?	Redistributions in binary form must reproduce the above copyright		*/
/*		notice, this list of conditions and the following disclaimer in the		*/
/*		documentation and/or other materials provided with the distribution.	*/
/*																				*/
/*	  ?	Neither the name of Aurbach & Associates, Inc. nor the names of any		*/
/*		of its employees may be used to endorse or promote products derived		*/
/*		from this software without specific prior written permission.			*/
/*																				*/
/*	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS			*/
/*	?AS IS? AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT			*/
/*	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A		*/
/*	PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER	*/
/*	OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,	*/
/*	EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,			*/
/*	PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; */
/*	OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,	*/
/*	WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR		*/
/*	OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF		*/
/*	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.									*/
/*																				*/
/********************************************************************************/
/*
 *	Module Name:	LContextMenuHelper
 *
 *	SuperClass:		LMenu
 *
 *	Notes:			This module is a helper class providing common logic for the
 *					support of contextual menus.
 *
 *	Change History:
 *
 *	Who     	Date	    Description
 * ---------------------------------------------------------------------------
 *	RLA		06-Jan-2006		Original Code (AContextMenu.h)
 *	RLA		27-Sep-2006		Adapted for contribution to open-powerplant
 */

#include			<LContextMenuHelper.h>
#ifndef __MACH__
#include			<Menus.h>
#endif
#include			<PP_Resources.h>
#include			<UCMMUtils.h>


/***
 * ==>	LContextMenuHelper
 *
 *	Default Constructor
 *
 ***/

LContextMenuHelper::LContextMenuHelper ( 
	LCommander *			inCtxCmdr )	:	LMenu(0, Str_Empty, false)
{
	mCtxCmdr = inCtxCmdr;
	mCtxPane = dynamic_cast<LPane*>(inCtxCmdr);		// default
	mHelpType = kCMHelpItemNoHelp;
}


/***
 * ==>	LContextMenuHelper
 *
 *	Parameterized Constructor
 *
 ***/

LContextMenuHelper::LContextMenuHelper ( 
	ResIDT					inMENUid,
	LCommander *			inCtxCmdr )	:	LMenu(inMENUid)
{
	mCtxCmdr = inCtxCmdr;
	mCtxPane = dynamic_cast<LPane*>(inCtxCmdr);		// default
	mHelpType = kCMHelpItemNoHelp;
}


/***
 * ==>	~LContextMenuHelper
 *
 *	Destructor
 *
 ***/

LContextMenuHelper::~LContextMenuHelper ( void )
{
}


/***
 * ==>	AppendMenuCommand
 *
 *	Add a menu command to the end of this menu.
 *
 ***/

void
LContextMenuHelper::AppendMenuCommand (
	const char *			inMenuString,
	CommandT				inCommand ) 
{
	LStr255					str(inMenuString);
	InsertCommand(str, inCommand, 32000);
}


void
LContextMenuHelper::AppendMenuCommand (
	ConstStringPtr			inMenuString,
	CommandT				inCommand ) 
{
	InsertCommand(inMenuString, inCommand, 32000);
}


void
LContextMenuHelper::AppendMenuCommand (
	ResIDT					inStringResID,
	SInt16					inStringIndex,
	CommandT				inCommand ) 
{
	LStr255					str(inStringResID, inStringIndex);
	AppendMenuCommand(str, inCommand);
}


/***
 * ==>	AppendMenuCommandList
 *
 *	Add a list of menu items to the contextual menu, using
 *	another menu resource as the basis.
 *
 ***/

void
LContextMenuHelper::AppendMenuCommandList (
	ResIDT					inMenuID ) 
{
	LMenu					cmdList(inMenuID);
	MenuHandle				menuH = cmdList.GetMacMenuH();
	SInt16					count = CountMenuItems(menuH);
	for (SInt16 index = 1; index <= count; index++) {
		LStr255				itemTxt;
		::GetMenuItemText(menuH, index, itemTxt);
		CommandT			cmd = cmdList.CommandFromIndex(index);
		AppendMenuCommand(itemTxt, cmd);
	}
}


/***
 * ==>	AppendMenuSeparator
 *
 *	Add a separator line to the contextual menu.
 *
 ***/

void
LContextMenuHelper::AppendMenuSeparator ( void ) 
{
	InsertCommand("\p-", cmd_Nothing, 32000);
}


/***
 * ==>	TrackMenu
 *
 *	Display a popup menu and track the user interaction with it.
 *	If the user makes a selection, process the selection.
 *	Return a boolean to indicate whether a menu item was processed.
 *
 *	NOTE:		The Help menu is added automatically.
 *
 *	The inExecuteCommand parameter is a hook. Most contextual menus contain
 *	commands that can be processed by calling the context commander's 
 *	ProcessCommand method. But this is not always the case. For cases when
 *	other alternatives are needed, set inExecuteCommand to false to return
 *	the command, rather than process it.
 *
 ***/

CommandT
LContextMenuHelper::TrackMenu ( 
	Point					inGlobalPt,
	bool					inExecuteCommand )
{
	CommandT				cmd = cmd_Nothing;
	
	if (mCtxCmdr != nil) {
		GetContext();
		PreCMSelect(inGlobalPt);
		PrepareMenuItems();
		FinalizeMenu();
		
		UInt32				selectionType;
		SInt16				menuID;
		MenuItemIndex		menuIndex;
		OSStatus			err;
		
		if (mHelpStr.Length() == 0) {
			mHelpStr.Assign(STRx_Standards, str_HelpMenuTitle);
			if (mHelpStr.Length() == 0) {
				mHelpStr.Assign("\pHelp");
			}
		}
		UInt32				helpType = mHelpType;
		if (helpType == kCMHelpItemOtherHelp) {
			helpType = (IsHelpAvailable() ? kCMHelpItemOtherHelp : kCMHelpItemNoHelp);
		}
		
		AEDesc *			selDesc = mSelection;
		if (mSelection.IsNull()) {
			selDesc = nil;
		}
		
		::MacInsertMenu(mMacMenuH, hierMenu);
		
		err = ::ContextualMenuSelect(mMacMenuH, inGlobalPt, false, helpType, mHelpStr,
								selDesc, &selectionType, &menuID, &menuIndex);
		if (err == noErr) {
			PostCMSelect(inGlobalPt);
			if (selectionType == kCMShowHelpSelected) {
				cmd = cmd_Help;
			} else if (selectionType == kCMMenuItemSelected) {
				cmd = CommandFromIndex(menuIndex);
			}
		}
		
		if (inExecuteCommand) {
			if (cmd == cmd_Help) {
				ShowHelp();
			} else if (cmd != cmd_Nothing) {
				mCtxCmdr->ProcessCommand(cmd);
			}
		}
	}
	return cmd;
}


#pragma mark -
/***
 * ==>	GetContext
 *
 *	Obtain the object specifier for the current selection. Used by
 *	::ContextualMenuSelect() to actually determine our context and
 *	how to build the menu accordingly (used by CMM plugins).
 *
 *	You shouldn't need to override this method, however you may need to
 *	implement LPane::GetSelection(AEDesc&) in the context pane.
 *
 ***/

void
LContextMenuHelper::GetContext ( void )
{
	mSelection.Dispose();
	
	// If we have a context pane defined, use it.
	// If we have no context pane defined, see if the context commander
	// is a visual object.
	LPane *					pane = dynamic_cast<LPane*>(mCtxPane);
	if (pane == nil) {
		pane = dynamic_cast<LPane*>(mCtxCmdr);
	}
	
	if (pane != nil) {
		pane->GetSelection(mSelection);
	}
}


/***
 * ==>	PrepareMenuItems
 *
 *	Enable or disable each item in the menu.
 *
 ***/

void
LContextMenuHelper::PrepareMenuItems ( void ) 
{
	if (mCtxCmdr) {
		SInt16				count;
	
		count = ::CountMenuItems(mMacMenuH);
		for (SInt16 index = 1; index <= count; index++) {
			MenuItemAttributes	attr = 0;
			::GetMenuItemAttributes(mMacMenuH, index, &attr);
			if ((attr & kMenuItemAttrSeparator) != 0) {
				continue;
			}
			Boolean			enabled = false, usesMark = false;
			UInt16			mark;					// not used
			LStr255			name;
			CommandT		cmd = CommandFromIndex(index);
			CheckCommandStatus(cmd, enabled, usesMark, mark, name);
			if (enabled) {
				::EnableMenuItem(mMacMenuH, index);
			} else {
				::DisableMenuItem(mMacMenuH, index);
			}
			::CheckMenuItem(mMacMenuH, index, usesMark);
			if (name.Length() != 0) {
				::SetMenuItemText(mMacMenuH, index, name);
			}
		}
	}
}


/***
 * ==>	FinializeMenu
 *
 *	Perform last minute tweaks on the menu
 *
 ***/

void
LContextMenuHelper::FinalizeMenu ( void ) 
{
	Assert_(mMacMenuH != nil);
	
	UCMMUtils::StripDoubleDividers(mMacMenuH);
	UCMMUtils::StripFirstDivider(mMacMenuH);
	UCMMUtils::StripLastDivider(mMacMenuH);
}


/***
 * ==>	CheckCommandStatus
 *
 *	This function is a hook-proc for contextual menu handling.
 *
 *	Contextual menus that exclusively consist of functions that are implemented
 *	as Commands use this method; contextual menus that handle other cases should
 *	override this method to provide the proper status for the command.
 *
 ***/

void
LContextMenuHelper::CheckCommandStatus (
	CommandT						inCommand,
	Boolean &						outEnabled,
	Boolean &						outUsesMark,
	UInt16 &						outMark,
	Str255							outName ) 
{
	if (mCtxCmdr) {
		mCtxCmdr->ProcessCommandStatus(inCommand, outEnabled, outUsesMark, outMark, outName);
	}
}
