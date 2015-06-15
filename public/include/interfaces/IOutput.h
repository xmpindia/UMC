#ifndef IOutput_h__
#define IOutput_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include "interfaces/INode.h"
#include "baseTypes/RationalType.h"

namespace UMC {

	class IOutput
		: public INode
	{

	public:
		typedef std::vector< spITrack > TrackList;
		typedef std::vector< spcITrack > cTrackList;
		typedef std::vector< spIVideoTrack > VideoTrackList;
		typedef std::vector< spcIVideoTrack > cVideoTrackList;
		typedef std::vector< spIAudioTrack > AudioTrackList;
		typedef std::vector< spcIAudioTrack > cAudioTrackList;

		virtual spIVideoTrack AddVideoTrack() = 0;
		virtual spIAudioTrack AddAudioTrack() = 0;

		virtual spIVideoTrack AddVideoTrack( const std::string & buffer ) = 0;
		virtual spIAudioTrack AddAudioTrack( const std::string & buffer ) = 0;
		virtual spITrack AddTrack( const std::string & buffer ) = 0;

		virtual void SetName( const std::string & name ) = 0;
		virtual std::string GetName() const = 0;

		virtual void SetTitle( const std::string & title ) = 0;
		virtual std::string GetTitle() const = 0;

		virtual void SetCanvasAspectRatio( const AspectRatio & canvasAspectRatio ) = 0;
		virtual AspectRatio GetCanvasAspectRatio() const = 0;

		virtual void SetImageAspectRatio( const AspectRatio & imageAspectRatio ) = 0;
		virtual AspectRatio GetImageAspectRatio() const = 0;

		virtual void SetVideoEditRate( const EditRate & videoEditRate ) = 0;
		virtual EditRate GetVideoEditRate() const = 0;

		virtual void SetAudioEditRate( const EditRate & audioEditRate ) = 0;
		virtual EditRate GetAudioEditRate() const = 0;
		
		virtual size_t	TrackCount() const = 0;
		virtual TrackList GetAllTracks() = 0;
		virtual cTrackList GetAllTracks() const = 0;
		virtual spITrack GetTrack( const std::string & uniqueID ) = 0;
		virtual spcITrack GetTrack( const std::string & uniqueID ) const = 0;

		virtual size_t VideoTrackCount() const = 0;
		virtual VideoTrackList GetAllVideoTracks() = 0;
		virtual cVideoTrackList GetAllVideoTracks() const = 0;
		virtual spIVideoTrack GetVideoTrack( const std::string & uniqueID ) = 0;
		virtual spcIVideoTrack GetVideoTrack( const std::string & uniqueID ) const = 0;

		virtual size_t AudioTrackCount() const = 0;
		virtual AudioTrackList GetAllAudioTracks() = 0;
		virtual cAudioTrackList GetAllAudioTracks() const = 0;
		virtual spIAudioTrack GetAudioTrack( const std::string & uniqueID ) = 0;
		virtual spcIAudioTrack GetAudioTrack( const std::string & uniqueID ) const = 0;

		virtual size_t RemoveAllTracks() = 0;
		virtual size_t RemoveAllVideoTracks() = 0;
		virtual size_t RemoveAllAudioTracks() = 0;
		virtual size_t RemoveTrack( const std::string & uniqueID ) = 0;
		virtual size_t RemoveVideoTrack( const std::string & uniqueID ) = 0;
		virtual size_t RemoveAudioTrack( const std::string & uniqueID ) = 0;

		virtual ~IOutput() = 0;

	};

	inline IOutput::~IOutput() {}

};

#endif  // ISource_h__
