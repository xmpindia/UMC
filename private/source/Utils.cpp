// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "utils/Utils.h"

namespace INT_UMC {
	
	std::string & PopulateString( std::string & dest, const char * buffer, size_t lenOfBuffer ) {
		if ( buffer && lenOfBuffer > 0 ) {
			if ( lenOfBuffer == npos ) dest.assign( buffer ); else dest.assign( buffer, lenOfBuffer );
		} else {
			dest.clear();
		}
		return dest;
	}

	std::string GetUniqueID() {
		static int count = 0;
		static char buffer[30] = "";
		itoa( count, buffer, 10 );
		return std::string( buffer );
	}

}
