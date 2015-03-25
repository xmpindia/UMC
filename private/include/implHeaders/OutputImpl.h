#ifndef OutputImpl_h__
#define OutputImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IOutput.h"
#include "UMCDefines_I.h"
#include "interfaces/ITrack.h"

#include <map>

namespace INT_UMC {
	using namespace UMC;
	class OutputImpl
		: public IOutput
		, public enable_shared_from_this< OutputImpl > {
	public:
		OutputImpl( const std::string & uniqueID, const spIUMC & parent );

		virtual std::string GetUniqueID() const;

		virtual spITrack AddVideoTrack( const char * uniqueID, size_t length );
		virtual spITrack AddAudioTrack( const char * uniqueID, size_t length );

		virtual void SetName( const char * name, size_t length );
		virtual std::string GetName() const;

		virtual void SetTitle( const char * title, size_t length );
		virtual std::string GetTitle() const;

		virtual void SetCanvasAspectRatio( const AspectRatio & canvasAspectRatio );
		virtual AspectRatio GetCanvasAspectRatio() const;

		virtual void SetImageAspectRatio( const AspectRatio & imageAspectRatio );
		virtual AspectRatio GetImageAspectRatio() const;

		virtual void SetVideoEditRate( const EditRate & videoEditRate );
		virtual EditRate GetVideoEditRate() const;

		virtual void SetAudioEditRate( const EditRate & audioEditRate );
		virtual EditRate GetAudioEditRate() const;

		virtual size_t VideoTrackCount() const;
		virtual TrackList GetVideoTracks();
		virtual cTrackList GetVideoTracks() const;
		virtual spITrack GetVideoTrack( const char * uniqueID, size_t length );
		virtual spcITrack GetVideoTrack( const char * uniqueID, size_t length ) const;

		virtual size_t AudioTrackCount() const;
		virtual TrackList GetAudioTracks();
		virtual cTrackList GetAudioTracks() const;
		virtual spITrack GetAudioTrack( const char * uniqueID, size_t length );
		virtual spcITrack GetAudioTrack( const char * uniqueID, size_t length ) const;

		virtual spcIUMC GetParent() const;
		virtual spIUMC GetParent();

	protected:
		typedef std::map< const std::string, spITrack > TrackMap;
		size_t TrackCount( const TrackMap & trackMap ) const;
		spITrack AddTrack( TrackMap & trackMap, const char * uniqueID, size_t length );
		spITrack GetTrack( const TrackMap & trackMap, const char * uniqueID, size_t length ) const;
		
	protected:
		const std::string		mUniqueID;
		std::string				mName;
		std::string				mTitle;
		AspectRatio 			mCanvasAspectRatio;
		AspectRatio 			mImageAspectRatio;
		EditRate				mVideoEditRate;
		EditRate				mAudioEditRate;

		TrackMap				mVideoTrackMap;
		TrackMap				mAudioTrackMap;

		weak_ptr< IUMC >		mwpUMC;
	};
}

#endif  // OutputImpl_h__
