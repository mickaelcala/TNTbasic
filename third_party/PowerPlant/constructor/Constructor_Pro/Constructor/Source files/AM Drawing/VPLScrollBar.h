// Copyright ?2005, 2006 Freescale Semiconductor, Inc.
// Please see the License for the specific language governing rights and
// limitations under the License.
// ===========================================================================
//	VPLScrollBar.h					?1997 Metrowerks Inc. All rights reserved.
// ===========================================================================

#pragma once

#include "VPLControlPane.h"
#include "LScrollBar.h"

class VPLScrollBar : public VPLControlPane {

public:
	static VEDrawingAgent*	CreateAgent()
									{ return new VPLScrollBar; }

							VPLScrollBar() { }
	virtual					~VPLScrollBar() { }

	virtual LPane*			CreateFromStream(
									LStream			*inStream)
								{
									return new LScrollBar(inStream);
								}
};
