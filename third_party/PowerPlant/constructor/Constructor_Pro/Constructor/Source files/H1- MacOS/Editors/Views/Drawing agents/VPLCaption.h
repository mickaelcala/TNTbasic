// Copyright ?2005, 2006 Freescale Semiconductor, Inc.
// Please see the License for the specific language governing rights and
// limitations under the License.
// ===========================================================================
//	VPLCaption.h				? 1996-97 Metrowerks Inc. All rights reserved.
// ===========================================================================
//
//   Created: 11/15/96
//     $Date: 2006/01/18 01:33:58 $
//  $History: VPLCaption.h $
//	
//	*****************  Version 3  *****************
//	User: scouten      QDate: 02/18/97   Time: 19:55
//	Updated in $/Constructor/Source files/H1- MacOS/Editors/Views/Drawing agents
//	Improved commenting.
//	
//	*****************  Version 2  *****************
//	User: scouten      QDate: 01/24/97   Time: 17:45
//	Updated in $/Constructor/Source files/H1- MacOS/Editors/Views/Drawing agents
//	Fixed CR/LF problem
//	
//	*****************  Version 1  *****************
//	User: scouten      QDate: 11/17/96   Time: 11:24
//	Created in $/Constructor/Source files/Editors/Views/PowerPlant/Drawing agents
//	Added drawing agent.
//	
// ===========================================================================

#pragma once

	// MacOS : Editors : Views : Drawing agents
#include "VPLPane.h"


// ===========================================================================
//		* VPLCaption
// ===========================================================================
//	Drawing agent for the PowerPlant class LCaption.

class VPLCaption : public VPLPane {

public:
	static VEDrawingAgent*	CreateAgent()
									{ return new VPLCaption; }

							VPLCaption() {}
	virtual					~VPLCaption() {}

	virtual LPane*			CreateFromStream(LStream* inStream)
									{ return new LCaption(inStream); }

protected:
	virtual void			ValueChangedSelf(
									FourCharCode		inAttributeKey,
									DMAttribute*		inAttribute);

};
