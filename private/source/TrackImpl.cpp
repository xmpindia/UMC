// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/TrackImpl.h"
#include "implHeaders/ShotImpl.h"
#include "utils/Utils.h"

namespace INT_UMC {

	std::string TrackImpl::GetUniqueID() const {
		return mUniqueID;
	}


	spIShot TrackImpl::AddClipShot( const char * uniqueID, size_t length ) {
		return AddShot( uniqueID, length, IShot::kShotTypeClip );
	}

	spIShot TrackImpl::AddTransitionShot( const char * uniqueID, size_t length ) {
		return AddShot( uniqueID, length, IShot::kShotTypeTransition );
	}

	void TrackImpl::SetName( const char * name, size_t length ) {
		PopulateString( mName, name, length );
	}

	std::string TrackImpl::GetName() const {
		return mName;
	}

	void TrackImpl::SetEditRate( const EditRate & editRate ) {
		mEditRate = editRate;
	}

	EditRate TrackImpl::GetEditRate() const {
		return mEditRate;
	}

	size_t TrackImpl::ShotCount() const {
		return mShotMap.size();
	}

	ITrack::ShotList TrackImpl::GetShots() {
		ShotList list;
		auto it = mShotMap.begin();
		auto endIt = mShotMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
		}
		return list;
	}

	ITrack::cShotList TrackImpl::GetShots() const {
		cShotList list;
		auto it = mShotMap.begin();
		auto endIt = mShotMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
			}
		return list;
	}

	spcIOutput TrackImpl::GetParent() const  {
		return spcIOutput( mwpOutput );
	}

	spIOutput TrackImpl::GetParent() {
		return spIOutput( mwpOutput );
	}

	TrackImpl::TrackImpl( const std::string & uniqueID,
		const spIOutput & parent )
		: mwpOutput( parent)
		, mEditRate( 1 )
		, mUniqueID( uniqueID ) { }

	spIShot TrackImpl::AddShot( const char * uniqueID, size_t length, IShot::eShotTypes type ) {
		std::string strID;
		PopulateString( strID, uniqueID, length );
		if ( mShotMap.find( strID ) == mShotMap.end() ) {
			spIShot shot = shared_ptr< ShotImpl >( new ShotImpl( strID, type, shared_from_this() ) );
			mShotMap[ strID ] = shot;
			return shot;
		} else {
			return spIShot();
		}
	}

}
