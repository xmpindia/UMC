#ifndef UMCDefines_I_h__
#define UMCDefines_I_h__ 1

#include <stdexcept>

/*
*  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
*  This file is licensed to you under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License. You may obtain a copy
*  of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software distributed under
*  the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
*  OF ANY KIND, either express or implied. See the License for the specific language
*  governing permissions and limitations under the License.
*
*/

#include "UMCDefines.h"
#include <stdexcept>

namespace INT_UMC {
	using namespace UMC;

	static const char * kXMP_NS_UMC	= "http://ns.umc.com/xmp/1.0/UniversalMetadataContainer/";
	static const size_t kMaxsize_t = ( size_t ) -1;

	#define THROW_ID_NOT_UNIQUE throw std::bad_function_call( "id is not unique" );
	#define THROW_NODE_IS_NOT_EXPECTED_TYPE( x ) throw std::logic_error( x ## " is not of expected type" );
	#define THROW_PARENT_CANT_BE_NULL throw std::logic_error( "parent can't be null" );
	#define THROW_UNIQUE_ID_AND_REFERENCE_TRACKER_CANT_BE_NULL throw std::logic_error( "uniqueIDAndReferenceTracker can't be null" );
	#define THROW_UNIQUE_ID_GENERATOR_CANT_BE_NULL throw std::logic_error( "uniqueID generator can't be null" );
	#define THROW_NODE_IS_REFERENCED( operation ) throw std::logic_error( "can't " operation " as node is referenced somewhere in the DOM" );
	#define THROW_WRONG_FUNCTION_CALLED( operation ) throw std::bad_function_call( operation " is not supposed to be invoked" );
	#define THROW_PARSING_ERROR throw std::logic_error( "parsing error occured" );
	#define THROW_UNIQUE_ID_IS_MISSING throw std::logic_error( "validation of serialized buffer failed since uniqueID is missing" );
	#define THROW_PARSED_ID_NOT_UNIQUE throw std::logic_error( "validation of serialized buffer failed since uniqueID is already used in the DOM" );
	#define THROW_XMPSTRUCTURE_NODE_VALIDATION_FAILED( reason ) throw std::logic_error( "validation of serialized buffer failed since " reason );
}

#endif  // UMCDefines_I_h__
