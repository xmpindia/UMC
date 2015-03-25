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

	std::string FrameImpl::GetUniqueID() const {
		return mUniqueID;
	}

	spcIShot FrameImpl::GetParent() const  {
		return spcIShot( mwpShot );
	}

	spIShot FrameImpl::GetParent() {
		return spIShot( mwpShot );
	}

	spISource FrameImpl::GetSource() {
		return spISource( mwpSource );
	}

	spcISource FrameImpl::GetSource() const {
		return spcISource( mwpSource );
	}

	void FrameImpl::SetSourceInCount( const EditUnitInCount & sourceInCount ) {
		mSourceInCount = sourceInCount;
	}

	UMC::EditUnitInCount FrameImpl::GetSourceInCount() const {
		return mSourceInCount;
	}

	void FrameImpl::SetShotInCount( const EditUnitInCount & shotInCount ) {
		mShotInCount = shotInCount;
	}

	UMC::EditUnitInCount FrameImpl::GetShotInCount() const {
		return mShotInCount;
	}

	FrameImpl::FrameImpl( const std::string & uniqueID, const spISource & frameSource,
		const spIShot & parent, const EditUnitInCount & sourceInCount,
		const EditUnitInCount & shotInCount )
		: mwpShot( parent )
		, mwpSource( frameSource )
		, mUniqueID( uniqueID )
		, mSourceInCount( sourceInCount )
		, mShotInCount( shotInCount ) { }

}
