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

namespace INT_UMC {

	
	const std::string & TrackImpl::GetUniqueID() const  {
		return mUniqueID;
	}

	std::string TrackImpl::GetUniqueID() {
		return mUniqueID;
	}

	spIShot TrackImpl::AddShot( const char * uniqueID, size_t length ) {
		std::string strID;
		if ( length == npos ) strID.assign( uniqueID ); else strID.assign( uniqueID, length );
		if ( mShotMap.find( strID ) == mShotMap.end() ) {
			spIShot shot = shared_ptr< IShot >( new ShotImpl( uniqueID, length, shared_from_this() ) );
			mShotMap[ strID ] = shot;
			return shot;
		} else {
			return spIShot();
		}
	}

	void TrackImpl::SetName( const char * name, size_t length ) {
		if ( name ) {
			if ( length == npos ) mName.assign( name ); else mName.assign( name, npos );
		} else {
			mName.clear();
		}
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

	TrackImpl::TrackImpl( const char * uniqueID, size_t length,
		const spIOutput & parent )
		: mwpOutput( parent)
		, mEditRate( 1 )
	{
		if ( length == npos ) mUniqueID.assign( uniqueID ); else mUniqueID.assign( uniqueID, length );
	}

}
