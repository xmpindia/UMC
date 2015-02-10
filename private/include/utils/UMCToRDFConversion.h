#ifndef UMCToRDFConversion_h__
#define UMCToRDFConversion_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations_I.h"
#include "baseTypes/RationalType.h"
#include "baseTypes/TimeCode.h"

#include "XMPCore/XMPCoreFwdDeclarations.h"

namespace INT_UMC {

	namespace UMCToRDFConversion {
		using namespace NS_XMPCORE;
		using namespace UMC;

		spIXMPMetadata Convert( const spcIUMC & umc );
		spIXMPNode Convert( const spcISource & source );
		spIXMPNode Convert( const FrameRate & frameRate );
		spIXMPNode Convert( const TimeCode & timeCode );

	}
}

#endif  // UMCToRDFConversion_h__
