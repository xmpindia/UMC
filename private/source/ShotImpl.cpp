// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/ShotImpl.h"
#include "implHeaders/FrameImpl.h"
#include "implHeaders/ShotSourceImpl.h"
#include "utils/Utils.h"

namespace INT_UMC {

	std::string ShotImpl::GetUniqueID() const {
		return mUniqueID;
	}

	IShot::eShotTypes ShotImpl::GetType() const {
		return mShotType;
	}

	void ShotImpl::SetInCount( const EditUnitInCount & inCount ) {
		mInCount = inCount;
	}

	EditUnitInCount ShotImpl::GetInCount() const {
		return mInCount;
	}

	void ShotImpl::SetDuration( const EditUnitDuration & duration ) {
		mDuration = duration;
	}

	EditUnitDuration ShotImpl::GetDuration() const {
		return mDuration;
	}

	spIFrame ShotImpl::AddFrame( const spISource & frameSource, const char * uniqueID,
		size_t lengthOfID, const EditUnitInCount & sourceInCount,
		const EditUnitInCount shotInCount )
	{
		std::string strID( uniqueID);
		if ( mFrameMap.find( strID ) == mFrameMap.end() ) {
			spIFrame frame = shared_ptr< FrameImpl >( new FrameImpl( strID, frameSource,
				shared_from_this(), sourceInCount, shotInCount ) );
			mFrameMap[ strID ] = frame;
			return frame;
		} else {
			return spIFrame();
		}
	}

	size_t ShotImpl::FrameCount() const {
		return mFrameMap.size();
	}

	IShot::FrameList ShotImpl::GetFrames() {
		FrameList list;
		auto it = mFrameMap.begin();
		auto endIt = mFrameMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
		}
		return list;
	}

	IShot::cFrameList ShotImpl::GetFrames() const {
		cFrameList list;
		auto it = mFrameMap.begin();
		auto endIt = mFrameMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
		}
		return list;
	}

	spcITrack ShotImpl::GetParent() const  {
		return spcITrack( mwpTrack );
	}

	spITrack ShotImpl::GetParent() {
		return spITrack( mwpTrack );
	}

	spIShotSource ShotImpl::AddShotSource( const spISource & source,
		const EditUnitInCount & sourceInCount, const EditUnitDuration sourceDuration,
		const EditUnitInCount shotInCount )
	{
		std::string strID( GetUniqueID() );
		if ( mShotSourceMap.find( strID ) == mShotSourceMap.end() ) {
			auto shotSource = shared_ptr< ShotSourceImpl >( new ShotSourceImpl( source,
				shared_from_this(), sourceInCount, sourceDuration, shotInCount ) );
			mShotSourceMap[ strID ] = shotSource;
			return shotSource;
		} else {
			return spIShotSource();
		}
	}

	size_t ShotImpl::ShotSourceCount() const {
		return mShotSourceMap.size();
	}

	IShot::ShotSourceList ShotImpl::GetShotSources() {
		ShotSourceList list;
		auto it = mShotSourceMap.begin();
		auto endIt = mShotSourceMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
		}
		return list;
	}

	IShot::cShotSourceList ShotImpl::GetShotSources() const {
		cShotSourceList list;
		auto it = mShotSourceMap.begin();
		auto endIt = mShotSourceMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
		}
		return list;
	}

	ShotImpl::ShotImpl( const std::string & uniqueID, eShotTypes type, const spITrack & parent )
		: mwpTrack( parent )
		, mUniqueID( uniqueID )
		, mShotType( type )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd ) { }

	spIFrame ShotImpl::GetFrame( const char * uniqueID, size_t length ) {
		return spIFrame();
	}
}

