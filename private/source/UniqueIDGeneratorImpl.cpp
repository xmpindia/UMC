// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


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
