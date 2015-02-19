// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/FrameImpl.h"

namespace INT_UMC {

	
	const std::string & FrameImpl::GetUniqueID() const  {
		return mUniqueID;
	}

	std::string FrameImpl::GetUniqueID() {
		return mUniqueID;
	}

	void FrameImpl::SetEditOffset( const UMC_Int64 & editOffset ) {
		mEditOffset = editOffset;
	}

	UMC_Int64 FrameImpl::GetEditOffset() const  {
		return mEditOffset;
	}

	spcIShot FrameImpl::GetParent() const  {
		return spcIShot( mwpShot );
	}

	spIShot FrameImpl::GetParent() {
		return spIShot( mwpShot );
	}

	FrameImpl::FrameImpl( const char * uniqueID, size_t length,
		const spIShot & parent )
		: mwpShot( parent),
		  mEditOffset( 0 )
	{
		if ( length == npos ) mUniqueID.assign( uniqueID ); else mUniqueID.assign( uniqueID, length );
	}

}
