// Copyright �2005, 2006 Freescale Semiconductor, Inc.
// Please see the License for the specific language governing rights and
// limitations under the License.
// ===========================================================================
//	PIColorItem.h				� 1996-97 Metrowerks Inc. All rights reserved.
// ===========================================================================
//
//   Created: 08/02/96
//     $Date: 2006/01/18 01:33:20 $
//	$History: PIColorItem.h $
//	
//	*****************  Version 5  *****************
//	User: scouten      QDate: 02/21/97   Time: 11:15
//	Updated in $/Constructor/Source files/CO- Core/Property inspector
//	Improved commenting.
//	
//	*****************  Version 4  *****************
//	User: scouten      QDate: 01/24/97   Time: 17:31
//	Updated in $/Constructor/Source files/CO- Core/Property inspector
//	Fixed CR/LF problem
//	
//	*****************  Version 3  *****************
//	User: scouten      QDate: 11/26/96   Time: 17:51
//	Updated in $/Constructor/Source files/Property inspector
//	Changed resource ID allocation to avoid conflict with Display classes
//	(Eric) folder. Improved commenting.
//	
//	*****************  Version 2  *****************
//	User: scouten      QDate: 10/31/96   Time: 17:22
//	Updated in $/Constructor/Source files/Property inspector
//	Added support for attribute's enabled flag.
//	
//	*****************  Version 1   *****************
//	User: scouten      Date: 10/16/96   Time: 02:08
//	Created
//	Comment: Baseline source 15 October 1996.
//	
// ===========================================================================

#pragma once

	// Core : Property inspector
#include "PIAttributeItem.h"


// ===========================================================================
//		* Forward class declarations
// ===========================================================================

class DMRGBColorAttribute;
class SUColorPane;


// ===========================================================================
//		* PIColorItem
// ===========================================================================
//
//	PIColorItem is an attribute item for RGB color items. It presents a
//	color popup.
//
// ===========================================================================

class PIColorItem : public PIAttributeItem {

public:
							PIColorItem();
	virtual					~PIColorItem();

	// display synchronization

protected:
	virtual void			SetValueFromAttributeSelf();
	virtual void			SetValueFromDisplaySelf();
	virtual void			DisableSelf();
	virtual void			EnableSelf();

	// display configuration

	virtual void			FinishCreate();
	virtual void			SetElementSelf(DMElement* inElement);

	
	// data members

protected:
	DMRGBColorAttribute*	mAttributeRGB;			// attribute we're displaying
	SUColorPane*			mColorPane;				// RGB color popup
	
};
