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

namespace INT_UMC {
	
	const std::string & ShotImpl::GetUniqueID() const  {
		return mUniqueID;
	}

	std::string ShotImpl::GetUniqueID() {
		return mUniqueID;
	}

	void ShotImpl::SetType( eShotTypes type ) {
		mShotType = type;
	}

	IShot::eShotTypes ShotImpl::GetType() const {
		return mShotType;
	}

	void ShotImpl::SetIn( const UMC_Int64 & editUnit ) {
		mIn = editUnit;
	}

	UMC_Int64 ShotImpl::GetIn() const  {
		return mIn;
	}

	void ShotImpl::SetDuration( const UMC_Uns64 & duration ) {
		mDuration = duration;
	}

	UMC_Uns64 ShotImpl::GetDuration() const  {
		return mDuration;
	}

	spIFrame ShotImpl::AddFrame( const char * uniqueID, size_t length ) {
		std::string strID;
		if ( length == npos ) strID.assign( uniqueID ); else strID.assign( uniqueID, length );
		if ( mFrameMap.find( strID ) == mFrameMap.end() ) {
			spIFrame frame = shared_ptr< IFrame >( new FrameImpl( uniqueID, length, shared_from_this() ) );
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

	ShotImpl::ShotImpl( const char * uniqueID, size_t length, eShotTypes type, 
		const spITrack & parent )
		: mwpTrack( parent ),
		  mShotType( type ),
		  mIn( 0 ),
		  mDuration( Max_UMC_Uns64 )
	{
		if ( length == npos ) mUniqueID.assign( uniqueID ); else mUniqueID.assign( uniqueID, length );
	}

}
