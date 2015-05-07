#ifndef UMCDefines_I_h__
#define UMCDefines_I_h__ 1

#include <stdexcept>

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCDefines.h"
#include <stdexcept>

namespace INT_UMC {
	using namespace UMC;

	static const char * kXMP_NS_UMC	= "http://ns.umc.com/xmp/1.0/UniversalMetadataContainer/";
	static const size_t kMaxsize_t = ( size_t ) -1;

	#define THROW_ID_NOT_UNIQUE throw std::bad_function_call( "id is not unique" );
	#define THROW_NODE_IS_NOT_EXPECTED_TYPE( x ) throw std::bad_exception( x ## " is not of expected type" );
	#define THROW_PARENT_CANT_BE_NULL throw std::logic_error( "parent can't be null" );
	#define THROW_UNIQUE_ID_AND_REFERENCE_TRACKER_CANT_BE_NULL throw std::logic_error( "uniqueIDAndReferenceTracker can't be null" );
	#define THROW_UNIQUE_ID_GENERATOR_CANT_BE_NULL throw std::logic_error( "uniqueID generator can't be null" );
	#define THROW_NODE_IS_REFERENCED( operation ) throw std::logic_error( "can't " operation " as node is referenced somewhere in the DOM" );
}

#endif  // UMCDefines_I_h__
