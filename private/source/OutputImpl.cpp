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
#include "utils/Utils.h"

namespace INT_UMC {

	std::string OutputImpl::GetUniqueID() const {
		return mUniqueID;
	}

	spITrack OutputImpl::AddTrack( TrackMap & trackMap, const char * uniqueID, size_t length ) {
		std::string strID;
		PopulateString( strID, uniqueID, length );
		if ( trackMap.find( strID ) == trackMap.end() ) {
			spITrack track = shared_ptr< TrackImpl >( new TrackImpl( strID, shared_from_this() ) );
			trackMap[ strID ] = track;
			return track;
		}
		return spITrack();
	}

	spITrack OutputImpl::GetTrack( const TrackMap & trackMap, const char * uniqueID, size_t length ) const {
		std::string strID;
		PopulateString( strID, uniqueID, length );
		auto it = trackMap.find( strID );
		if ( it == trackMap.end() ) {
			return spITrack();
		} else {
			return it->second;
		}
	}

	spITrack OutputImpl::AddVideoTrack( const char * uniqueID, size_t length ) {
		return AddTrack( mVideoTrackMap, uniqueID, length );
	}

	spITrack OutputImpl::AddAudioTrack( const char * uniqueID, size_t length ) {
		return AddTrack( mAudioTrackMap, uniqueID, length );
	}

	void OutputImpl::SetName( const char * name, size_t length ) {
		PopulateString( mName, name, length );
	}

	std::string OutputImpl::GetName() const {
		return mName;
	}

	void OutputImpl::SetTitle( const char * title, size_t length ) {
		PopulateString( mTitle, title, length );
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


	spcITrack OutputImpl::GetAudioTrack( const char * uniqueID, size_t length ) const {
		return GetTrack( mAudioTrackMap, uniqueID, length );
	}

	spITrack OutputImpl::GetAudioTrack( const char * uniqueID, size_t length ) {
		return GetTrack( mAudioTrackMap, uniqueID, length );
	}

	spcIUMC OutputImpl::GetParent() const  {
		return spcIUMC( mwpUMC );
	}

	spIUMC OutputImpl::GetParent() {
		return spIUMC( mwpUMC );
	}

	size_t OutputImpl::TrackCount( const TrackMap & trackMap ) const {
		return trackMap.size();
	}

	size_t OutputImpl::VideoTrackCount() const {
		return TrackCount( mVideoTrackMap );
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

	spcITrack OutputImpl::GetVideoTrack( const char * uniqueID, size_t length ) const {
		return GetTrack( mVideoTrackMap, uniqueID, length );
	}

	spITrack OutputImpl::GetVideoTrack( const char * uniqueID, size_t length ) {
		return GetTrack( mVideoTrackMap, uniqueID, length );
	}

	size_t OutputImpl::AudioTrackCount() const {
		return TrackCount( mAudioTrackMap );
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

	OutputImpl::OutputImpl( const std::string & uniqueID,const spIUMC & parent )
		: mwpUMC( parent)
		, mCanvasAspectRatio( 1 )
		, mImageAspectRatio( 1 )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 1 )
		, mUniqueID( uniqueID ) { }

}
