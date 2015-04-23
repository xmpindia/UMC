#ifndef UMCFwdDeclarations_I_h__
#define UMCFwdDeclarations_I_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include "UMCDefines_I.h"

#include <set>
#include <string>

namespace INT_UMC {
	using namespace UMC;

	typedef std::set< std::string >					UniqueIDSet;
	typedef shared_ptr< UniqueIDSet >				spUniqueIDSet;
	typedef shared_ptr< const UniqueIDSet >			spcUniqueIDSet;
};

#endif  // UMCFwdDeclarations_I_h__
