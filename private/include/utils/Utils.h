#ifndef Utils_h__
#define Utils_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCDefines_I.h"

namespace INT_UMC {
	std::string & PopulateString( std::string & dest, const char * buffer, size_t lenOfBuffer );
	std::string GetUniqueID();
}
#endif  // Utils_h__
