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


#include "implHeaders/UniqueIDGeneratorImpl.h"
#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include <assert.h>
#include <cstdio>

namespace INT_UMC {

	UniqueIDGeneratorImpl::UniqueIDGeneratorImpl( const spcIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker )
		: mUniqueIDAndReferenceTracker( uniqueIDAndReferenceTracker )
		, mCurrentID( 0 ) { }

	std::string UniqueIDGeneratorImpl::GenerateUniqueID( IUMCNode::eNodeTypes nodeType ) {
		static char buffer[ 32 ] = "";
		do {
	#if UMC_UNIXBuild || UMC_MacBuild
		snprintf ( buffer, 32, "%d", mCurrentID );
	#elif UMC_WinBuild
		sprintf_s( buffer, 32, "%d", mCurrentID );
	#else
		#error "Missing implementation for the platform"
	#endif
		mCurrentID++;
		} while( mUniqueIDAndReferenceTracker->IsUniqueIDPresent( buffer ) );
		assert( !mUniqueIDAndReferenceTracker->IsUniqueIDPresent( buffer ) );
		return std::string( buffer );
	}

	spIUniqueIDGenerator CreateUniqueIDGenerator( const spcIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker ) {
		return std::make_shared< UniqueIDGeneratorImpl, const spcIUniqueIDAndReferenceTracker & >( uniqueIDAndReferenceTracker );
	}

}
