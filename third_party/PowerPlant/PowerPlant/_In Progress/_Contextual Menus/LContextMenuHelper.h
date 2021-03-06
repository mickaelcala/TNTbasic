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
 *	Class Name:			LContextMenuHelper
 *
 *	Change History:
 *
 *	Who     	Date	    Description
 * ---------------------------------------------------------------------------
 *	RLA		06-Jan-2006		Original Code (AContextMenu.h)
 *	RLA		27-Sep-2006		Adapted for contribution to open-powerplant
 */

#ifndef	_H_LContextMenuHelper
#define	_H_LContextMenuHelper
#pragma once

#include			<LMenu.h>
#include			<LCommander.h>
#include			<LString.h>
#include			<UAppleEventsMgr.h>

#if PP_Uses_Pragma_Import
#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	LContextMenuHelper	:	public	LMenu	{
public:
							LContextMenuHelper ( LCommander * inCtxCmdr = nil );
							
							LContextMenuHelper (
								ResIDT						inMENUid,
								LCommander *				inCtxCmdr = nil );

	virtual					~LContextMenuHelper ( void );
	
			void			SetContextCommander ( LCommander * inCtxCmdr )
								{
									mCtxCmdr = dynamic_cast<LCommander*>(inCtxCmdr);
								}
			
			void			SetContextPane ( LPane * inCtxPane )
								{
									mCtxPane = dynamic_cast<LPane*>(inCtxPane);
								}
			
			void			SpecifyHelpString ( ConstStringPtr inHelpString ) 
								{ 
									mHelpStr.Assign(inHelpString); 
								}
			
			void			SpecifyHelpType ( UInt32 inHelpType ) { mHelpType = inHelpType; }
	
			void			AppendMenuCommand (
								ConstStringPtr				inMenuString,
								CommandT					inCommand );
			
			void			AppendMenuCommand (
							   const char *					inMenuString,
							   CommandT						inCommand );
			
			void			AppendMenuCommand (
								ResIDT						inStringResID,
								SInt16						inStringIndex,
								CommandT					inCommand );
			
			void			AppendMenuCommandList ( ResIDT inMenuID );
			
			void			AppendMenuSeparator ( void );
			
	virtual	CommandT		TrackMenu ( 
								Point						inGlobalPt,
								bool						inExecuteCommand = true );
	
protected:
	StAEDescriptor		mSelection;
	LCommander *		mCtxCmdr;
	LPane *				mCtxPane;
	LStr255				mHelpStr;
	UInt32				mHelpType;
	
	virtual	bool			IsHelpAvailable ( void ) const { return false; }
	
	virtual void			ShowHelp ( void ) {}
	
	virtual void			GetContext ( void );
	
	virtual void			PreCMSelect ( Point /* inGlobalPt */ ) {}
	
	virtual void			PostCMSelect ( Point /* inGlobalPt */ ) {}
	
	virtual	void			PrepareMenuItems ( void );
	
	virtual void			FinalizeMenu ( void );
	
	virtual	void			CheckCommandStatus (
								CommandT					inCommand,
								Boolean &					outEnabled,
								Boolean &					outUsesMark,
								UInt16 &					outMark,
								Str255						outName );
	
private:									// unimplemented methods
							LContextMenuHelper ( const LContextMenuHelper &	inOriginal );

	LContextMenuHelper &	operator = ( const LContextMenuHelper &	inOriginal );
			
			bool			operator == ( const LContextMenuHelper & inObject );
};

PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
#pragma import reset
#endif

#endif
