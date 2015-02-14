// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/OutputImpl.h"
#include "implHeaders/TrackImpl.h"

namespace INT_UMC {


	const std::string & OutputImpl::GetUniqueID() const  {
		return mUniqueID;
	}

	std::string OutputImpl::GetUniqueID() {
		return mUniqueID;
	}

	spITrack OutputImpl::AddVideoTrack( const char * uniqueID, size_t length ) {
		std::string strID;
		if ( length == npos ) strID.assign( uniqueID ); else strID.assign( uniqueID, length );
		if ( mVideoTrackMap.find( strID ) == mVideoTrackMap.end() ) {
			spITrack track = spITrack( new TrackImpl( uniqueID, length, shared_from_this() ) );
			mVideoTrackMap[ strID ] = track;
			return track;
		} else {
			return spITrack();
		}
	}

	spITrack OutputImpl::AddAudioTrack( const char * uniqueID, size_t length ) {
		std::string strID;
		if ( length == npos ) strID.assign( uniqueID ); else strID.assign( uniqueID, length );
		if ( mAudioTrackMap.find( strID ) == mAudioTrackMap.end() ) {
			spITrack track = spITrack( new TrackImpl( uniqueID, length, shared_from_this() ) );
			mAudioTrackMap[ strID ] = track;
			return track;
		} else {
			return spITrack();
		}
	}

	void OutputImpl::SetName( const char * name, size_t length ) {
		if ( name ) {
			if ( length == npos ) mName.assign( name ); else mName.assign( name, npos );
		} else {
			mName.clear();
		}
	}

	std::string OutputImpl::GetName() const {
		return mName;
	}

	void OutputImpl::SetTitle( const char * title, size_t length ) {
		if ( title ) {
			if ( length == npos ) mTitle.assign( title ); else mTitle.assign( title, npos );
		} else {
			mTitle.clear();
		}
	}

	std::string OutputImpl::GetTitle() const {
		return mTitle;
	}

	void OutputImpl::SetCanvasAspectRatio( const AspectRatio & canvasAspectRatio ) {
		mCanvasAspectRatio = canvasAspectRatio;
	}

	AspectRatio OutputImpl::GetCanvasAspectRatio() const {
		return mCanvasAspectRatio;
	}

	void OutputImpl::SetImageAspectRatio( const AspectRatio & imageAspectRatio ) {
		mImageAspectRatio = imageAspectRatio;
	}

	AspectRatio OutputImpl::GetImageAspectRatio() const {
		return mImageAspectRatio;
	}

	void OutputImpl::SetVideoEditRate( const EditRate & videoEditRate ) {
		mVideoEditRate = videoEditRate;
	}

	EditRate OutputImpl::GetVideoEditRate() const {
		return mVideoEditRate;
	}

	void OutputImpl::SetAudioEditRate( const EditRate & audioEditRate ) {
		mAudioEditRate = audioEditRate;
	}

	EditRate OutputImpl::GetAudioEditRate() const {
		return mAudioEditRate;
	}


	spcIUMC OutputImpl::GetParent() const  {
		return spcIUMC( mwpUMC );
	}

	spIUMC OutputImpl::GetParent() {
		return spIUMC( mwpUMC );
	}

	size_t OutputImpl::VideoTrackCount() const {
		return mVideoTrackMap.size();
	}

	IOutput::TrackList OutputImpl::GetVideoTracks() {
		TrackList list;
		auto it = mVideoTrackMap.begin();
		auto endIt = mVideoTrackMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
		}
		return list;
	}

	IOutput::cTrackList OutputImpl::GetVideoTracks() const {
		cTrackList list;
		auto it = mVideoTrackMap.begin();
		auto endIt = mVideoTrackMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
			}
		return list;
	}

	size_t OutputImpl::AudioTrackCount() const {
		return mAudioTrackMap.size();
	}

	IOutput::TrackList OutputImpl::GetAudioTracks() {
		TrackList list;
		auto it = mAudioTrackMap.begin();
		auto endIt = mAudioTrackMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
		}
		return list;
	}

	IOutput::cTrackList OutputImpl::GetAudioTracks() const {
		cTrackList list;
		auto it = mAudioTrackMap.begin();
		auto endIt = mAudioTrackMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
			}
		return list;
	}

	OutputImpl::OutputImpl( const char * uniqueID, size_t length,
		const spIUMC & parent )
		: mwpUMC( parent)
		, mCanvasAspectRatio( 1 )
		, mImageAspectRatio( 1 )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 1 )
	{
		if ( length == npos ) mUniqueID.assign( uniqueID ); else mUniqueID.assign( uniqueID, length );
	}

}
