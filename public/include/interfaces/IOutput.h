#ifndef IOutput_h__
#define IOutput_h__ 1

/*
*  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
*  This file is licensed to you under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License. You may obtain a copy
*  of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software distributed under
*  the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
*  OF ANY KIND, either express or implied. See the License for the specific language
*  governing permissions and limitations under the License.
*
*/

#include "UMCFwdDeclarations.h"
#include "interfaces/IUMCNode.h"
#include "baseTypes/RationalType.h"

namespace UMC {

	//!
	//! \brief This interface acts as a base interface to all types of outputs of UMC.
	//! \details Provides functions to add various entities to output. It also provides functions to get and set various other properties of output nodes  
	//!
	class IOutput
		: public IUMCNode
	{

	public:
		typedef std::vector< spITrack > TrackList;
		typedef std::vector< spcITrack > cTrackList;
		typedef std::vector< spIVideoTrack > VideoTrackList;
		typedef std::vector< spcIVideoTrack > cVideoTrackList;
		typedef std::vector< spIAudioTrack > AudioTrackList;
		typedef std::vector< spcIAudioTrack > cAudioTrackList;

		//!
		//! \brief Create an empty video track and adds it to the video track list
		//! \return a shared pointer to non const IVideoTrack representing the video track after an empty video source has been added to it.
		//!
		virtual spIVideoTrack AddVideoTrack() = 0;

		//!
		//! \brief Create an empty audio track and adds it to the audio track list
		//! \return a shared pointer to non const IAudioTrack representing the video track after an empty audio source has been added to it.
		//!
		virtual spIAudioTrack AddAudioTrack() = 0;

		//!
		//! \brief Create a new video track from the provided buffer
		//! \param[in] buffer A std::string indicating the serialized form of a video track
		//! \return a shared pointer to non const IVideoTrack representing the newly added video track.
        //! \note Error is thrown in case buffer is empty
		//!
		virtual spIVideoTrack AddVideoTrack( const std::string & buffer ) = 0;

		//!
		//! \brief Create a new audio track from the provided buffer
		//! \param[in] buffer A std::string indicating the serialized form of a audio track
		//! \return a shared pointer to non const IAudioTrack representing the newly added audio track.
        //! \note Error is thrown in case buffer is empty
		//!
		virtual spIAudioTrack AddAudioTrack( const std::string & buffer ) = 0;

		//!
		//! \brief Create a new track from the provided buffer
		//! \param[in] buffer A std::string indicating the serialized form of a track
		//! \return a shared pointer to non const ITrack representing the newly added track.
        //! \note Error is thrown in case buffer is empty
		//!
		virtual spITrack AddTrack( const std::string & buffer ) = 0;

		//!
		//! \brief Set the name of the output
		//! \param[in] name std::string object containing the name of the output
		//!
		virtual void SetName( const std::string & name ) = 0;

		//!
		//! \brief Get the name of the output
		//! \return a value of type std::string containing the name of the output
		//!
		virtual std::string GetName() const = 0;

		//!
		//! \brief Set the title of the output
		//! \param[in] title std::string object containing the title of the output
		//!
		virtual void SetTitle( const std::string & title ) = 0;

		//!
		//! \brief Get the title of the output
		//! \return a value of type std::string containing the title of the output
		//!
		virtual std::string GetTitle() const = 0;

		//!
		//! \brief Set the canvas aspect ratio of the output
		//! \param[in] canvasAspectRatio AspectRatio object containing the canvas aspect ratio of the output
		//!
		virtual void SetCanvasAspectRatio( const AspectRatio & canvasAspectRatio ) = 0;

		//!
		//! \brief Get the canvas aspect ratio of the output
		//! \return a value of type AspectRatio containing the canvas aspect ratio of the output
		//!
		virtual AspectRatio GetCanvasAspectRatio() const = 0;

		//!
		//! \brief Set the image aspect ratio of the output
		//! \param[in] imageAspectRatio AspectRatio object containing the image aspect ratio of the output
		//!
		virtual void SetImageAspectRatio( const AspectRatio & imageAspectRatio ) = 0;

		//!
		//! \brief Get the image aspect ratio of the output
		//! \return a value of type AspectRatio containing the image aspect ratio of the output
		//!
		virtual AspectRatio GetImageAspectRatio() const = 0;

		//!
		//! \brief Set the video edit rate for the output
		//! \param[in] videoEditRate A value of type EditRate indicating the video edit rate for the output
		//!
		virtual void SetVideoEditRate( const EditRate & videoEditRate ) = 0;

		//!
		//! \brief Get the video edit rate for the output
		//! \return a value of type EditRate indicating the video rate for the output
		//!
		virtual EditRate GetVideoEditRate() const = 0;

		//!
		//! \brief Set the audio edit rate for the output
		//! \param[in] audioEditRate A value of type EditRate indicating the audio edit rate for the output
		//!
		virtual void SetAudioEditRate( const EditRate & audioEditRate ) = 0;

		//!
		//! \brief Get the audio edit rate for the output
		//! \return a value of type EditRate indicating the audio rate for the output
		//!
		virtual EditRate GetAudioEditRate() const = 0;
		
		//!
		//! \brief Get the track count for the output
		//! \return  a value of type size_t indicating the track count for the output
		//!
		virtual size_t	TrackCount() const = 0;

		//!
		//! \brief Get all the tracks present in the output
		//! \return  an object of type TrackList containing all the tracks present in the output
		//!
		virtual TrackList GetAllTracks() = 0;

		//!
		//! \brief Get all the tracks present in the output
		//! \return  a const object of type cTrackList containing all the tracks present in the output
		//!
		virtual cTrackList GetAllTracks() const = 0;

		//!
		//! \brief Get a track with a particular unique id from the output
		//! \param[in] uniqueID A std::string indicating the unique id of the track
		//! \return a shared pointer to non const ITrack object. An empty shared pointer is returned if the track is not found in the output
		//!
		virtual spITrack GetTrack( const std::string & uniqueID ) = 0;

		//!
		//! \brief Get a track with a particular unique id from the output
		//! \param[in] uniqueID A std::string indicating the unique id of the track
		//! \return a shared pointer to const ITrack object. An empty shared pointer is returned if the track is not found in the output
		//!
		virtual spcITrack GetTrack( const std::string & uniqueID ) const = 0;

		//!
		//! \brief Get the video track count for the output
		//! \return  a value of type size_t indicating the video track count for the output
		//!
		virtual size_t VideoTrackCount() const = 0;

		//!
		//! \brief Get all the video tracks present in the output
		//! \return  an object of type TrackList containing all the video tracks present in the output
		//!
		virtual VideoTrackList GetAllVideoTracks() = 0;

		//!
		//! \brief Get all the video tracks present in the output
		//! \return  a const object of type cVideoTrackList containing all the video tracks present in the output
		//!
		virtual cVideoTrackList GetAllVideoTracks() const = 0;

		//!
		//! \brief Get a video track with a particular unique id from the output
		//! \param[in] uniqueID A std::string indicating the unique id of the video track
		//! \return a shared pointer to non const IVideoTrack object. An empty shared pointer is returned if the video track is not found in the output
		//!
		virtual spIVideoTrack GetVideoTrack( const std::string & uniqueID ) = 0;

		//!
		//! \brief Get a video track with a particular unique id from the output
		//! \param[in] uniqueID A std::string indicating the unique id of the video track
		//! \return a shared pointer to const IVideoTrack object. An empty shared pointer is returned if the video track is not found in the output
		//!
		virtual spcIVideoTrack GetVideoTrack( const std::string & uniqueID ) const = 0;

		//!
		//! \brief Get the audio track count for the output
		//! \return  a value of type size_t indicating the audio track count for the output
		//!
		virtual size_t AudioTrackCount() const = 0;

		//!
		//! \brief Get all the audio tracks present in the output
		//! \return  an object of type AudioTrackList containing all the audio tracks present in the output
		//!
		virtual AudioTrackList GetAllAudioTracks() = 0;

		//!
		//! \brief Get all the audio tracks present in the output
		//! \return  a const object of type cAudioTrackList containing all the audio tracks present in the output
		//!
		virtual cAudioTrackList GetAllAudioTracks() const = 0;

		//!
		//! \brief Get an audio track with a particular unique id from the output
		//! \param[in] uniqueID A std::string indicating the unique id of the audio track
		//! \return a shared pointer to non const IAudioTrack object. An empty shared pointer is returned if the video track is not found in the output
		//!
		virtual spIAudioTrack GetAudioTrack( const std::string & uniqueID ) = 0;

		//!
		//! \brief Get an audio track with a particular unique id from the output
		//! \param[in] uniqueID A std::string indicating the unique id of the audio track
		//! \return a shared pointer to const IAudioTrack object. An empty shared pointer is returned if the video track is not found in the output
		//!
		virtual spcIAudioTrack GetAudioTrack( const std::string & uniqueID ) const = 0;

		//!
		//! \brief Remove all the tracks present in the output
		//! \return  a value of type size_t indicating the count of tracks present in the output before removal
		//!
		virtual size_t RemoveAllTracks() = 0;

		//!
		//! \brief Remove all the video tracks present in the output
		//! \return  a value of type size_t indicating the count of video tracks present in the output before removal
		//!
		virtual size_t RemoveAllVideoTracks() = 0;

		//!
		//! \brief Remove all the audio tracks present in the output
		//! \return  a value of type size_t indicating the count of audio tracks present in the output before removal
		//!
		virtual size_t RemoveAllAudioTracks() = 0;

		//!
		//! \brief Remove a track with a particular unique id, if present in the output
		//! \param[in] uniqueID A std::string indicating the unique id of the track
		//! \return  a value of type size_t. The value returned will be 1 if the track was successfully removed, else 0 is returned  
		//!
		virtual size_t RemoveTrack( const std::string & uniqueID ) = 0;

		//!
		//! \brief Remove a video track with a particular unique id, if present in the output
		//! \param[in] uniqueID A std::string indicating the unique id of the video track
		//! \return  a value of type size_t. The value returned will be 1 if the video track was successfully removed, else 0 is returned  
		//!
		virtual size_t RemoveVideoTrack( const std::string & uniqueID ) = 0;

		//!
		//! \brief Remove an audio track with a particular unique id, if present in the output
		//! \param[in] uniqueID A std::string indicating the unique id of the audio track
		//! \return  a value of type size_t. The value returned will be 1 if the audio track was successfully removed, else 0 is returned  
		//!
		virtual size_t RemoveAudioTrack( const std::string & uniqueID ) = 0;

		virtual ~IOutput() = 0;

	};

	inline IOutput::~IOutput() {}

};

#endif  // ISource_h__
