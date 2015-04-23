// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/UniqueIDGeneratorImpl.h"
#include <assert.h>
#include <cstdio>

namespace INT_UMC {

	UniqueIDGeneratorImpl::UniqueIDGeneratorImpl( const spcUniqueIDSet & uniqueIDSet )
		: mUniqueIDSet( uniqueIDSet )
		, mCurrentID( 1 ) { }

	std::string UniqueIDGeneratorImpl::GenerateUniqueID( INode::eNodeTypes nodeType ) {
		static char buffer[ 30 ] = "";
		int cx;
		cx = snprintf ( buffer, 30, "%d", mCurrentID );
		mCurrentID++;
		assert( mUniqueIDSet->find( buffer ) == mUniqueIDSet->end() );
		return std::string( buffer );
	}

	spIUniqueIDGenerator UniqueIDGeneratorImpl::CreateUniqueIDGenerator( const spcUniqueIDSet & uniqueIDSet ) {
		return std::make_shared< UniqueIDGeneratorImpl, const spcUniqueIDSet & >( uniqueIDSet );
	}

}
