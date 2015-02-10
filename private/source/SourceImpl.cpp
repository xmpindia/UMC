// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/SourceImpl.h"

namespace INT_UMC {


	const std::string & SourceImpl::GetUniqueID() const  {
		return mUniqueID;
	}

	std::string SourceImpl::GetUniqueID() {
		return mUniqueID;
	}

	void SourceImpl::SetClipName( const char * clipName, size_t length ) {
		if ( clipName ) {
			if ( length == npos ) mClipName.assign( clipName ); else mClipName.assign( clipName, npos );
		} else {
			mClipName.clear();
		}
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

	void SourceImpl::SetInCount( const UMC_Int64 & editUnit ) {
		mInCount = editUnit;
	}

	UMC_Int64 SourceImpl::GetInCount() const  {
		return mInCount;
	}

	void SourceImpl::SetDuration( const UMC_Uns64 & duration ) {
		mDuration = duration;
	}

	UMC_Uns64 SourceImpl::GetDuration() const  {
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

	SourceImpl::SourceImpl( const char * uniqueID, size_t length,
		eSourceTypes sourceType, const spIUMC & parent )
		: mSourceType( sourceType )
		, mwpUMC( parent)
		, mEditRate( 1 )
		, mInCount( 0 )
		, mDuration( Max_UMC_Uns64 )
		, mTimeCode( FrameRate( 0 ) )
	{
		// assert( uniqueID != NULL );
		 //assert( length != 0 );
		// assert ( parent );
		if ( length == npos ) mUniqueID.assign( uniqueID ); else mUniqueID.assign( uniqueID, length );
	}

}
