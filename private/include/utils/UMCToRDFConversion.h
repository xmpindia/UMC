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

		spIXMPNode Convert( const TimeCode & timeCode );
		spIXMPNode Convert( const Unsigned64RationalType & rational, const std::string & label );
		spIXMPNode Convert( const spcISource & source );
		spIXMPNode Convert( const spcIFrame & frame );
		spIXMPNode Convert( const spcIShot & shot );
		spIXMPNode Convert( const spcIShotSource & shotSource );
		spIXMPNode Convert( const spcITrack & track );
		spIXMPNode Convert( const spcIOutput & output );
		spIXMPMetadata Convert( const spcIUMC & umc );

		std::string ConvertToString( const EditUnitInCount & inCount );
		std::string ConvertToString( const EditUnitDuration & duration );
	}
}

#endif  // UMCToRDFConversion_h__
