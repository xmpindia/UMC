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
#include "baseTypes/RationalType.h"

#include <vector>
#include <string>

namespace UMC {

	class IOutput {

	public:
		typedef std::vector< spITrack > TrackList;
		typedef std::vector< spcITrack > cTrackList;

		virtual const std::string & GetUniqueID() const = 0;
		virtual std::string GetUniqueID() = 0;

		virtual void SetName( const char * name, size_t length = npos ) = 0;
		virtual std::string GetName() const = 0;

		virtual void SetTitle( const char * title, size_t length = npos ) = 0;
		virtual std::string GetTitle() const = 0;

		virtual void SetCanvasAspectRatio( const AspectRatio & canvasAspectRatio ) = 0;
		virtual AspectRatio GetCanvasAspectRatio() const = 0;

		virtual void SetImageAspectRatio( const AspectRatio & imageAspectRatio ) = 0;
		virtual AspectRatio GetImageAspectRatio() const = 0;

		virtual void SetVideoEditRate( const EditRate & videoEditRate ) = 0;
		virtual EditRate GetVideoEditRate() const = 0;

		virtual void SetAudioEditRate( const EditRate & audioEditRate ) = 0;
		virtual EditRate GetAudioEditRate() const = 0;

		virtual TrackList GetVideoTracks() = 0;
		virtual cTrackList GetVideoTracks() const = 0;

		virtual TrackList GetAudioTracks() = 0;
		virtual cTrackList GetAudioTracks() const = 0;

		virtual spcIUMC GetParent() const = 0;
		virtual spIUMC GetParent() = 0;

		virtual ~IOutput() = 0;

	private:

	};

	inline IOutput::~IOutput() {}

};

#endif  // ISource_h__
