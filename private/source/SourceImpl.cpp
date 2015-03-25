// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/SourceImpl.h"
#include "utils/Utils.h"

namespace INT_UMC {

	std::string SourceImpl::GetUniqueID() const {
		return mUniqueID;
	}

	void SourceImpl::SetClipName( const char * clipName, size_t length ) {
		PopulateString( mClipName, clipName, length );
	}

	std::string SourceImpl::GetClipName() const  {
		return mClipName;
	}

	ISource::eSourceTypes SourceImpl::GetSourceType() const {
		return mSourceType;
	}

	void SourceImpl::SetEditRate( const EditRate & editRate ) {
		mEditRate = editRate;
	}

	EditRate SourceImpl::GetEditRate() const {
		return mEditRate;
	}

	void SourceImpl::SetInCount( const EditUnitInCount & editUnit ) {
		mInCount = editUnit;
	}

	EditUnitInCount SourceImpl::GetInCount() const {
		return mInCount;
	}

	void SourceImpl::SetDuration( const EditUnitDuration & duration ) {
		mDuration = duration;
	}

	EditUnitDuration SourceImpl::GetDuration() const {
		return mDuration;
	}

	void SourceImpl::SetTimeCode( const TimeCode & timeCode ) {
		mTimeCode = timeCode;
	}

	TimeCode SourceImpl::GetTimeCode() const  {
		return mTimeCode;
	}

	spcIUMC SourceImpl::GetParent() const  {
		return spcIUMC( mwpUMC );
	}

	spIUMC SourceImpl::GetParent() {
		return spIUMC( mwpUMC );
	}

	SourceImpl::SourceImpl( const std::string & uniqueID,
		eSourceTypes sourceType, const spIUMC & parent )
		: mUniqueID( uniqueID )
		, mSourceType( sourceType )
		, mwpUMC( parent)
		, mEditRate( 1 )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd )
		, mTimeCode( FrameRate( 0 ) )
	{
		// assert ( parent );
	}

}
