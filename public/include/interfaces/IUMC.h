#ifndef IUMC_h__
#define IUMC_h__ 1

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
#include "IUMCNode.h"

namespace UMC {

	class IUMC
		: public IUMCNode
	{
	public:
		typedef std::vector< spISource >			SourceList;
		typedef std::vector< spcISource >			cSourceList;
		typedef std::vector< spIVideoSource >		VideoSourceList;
		typedef std::vector< spcIVideoSource >		cVideoSourceList;
		typedef std::vector< spIAudioSource >		AudioSourceList;
		typedef std::vector< spcIAudioSource >		cAudioSourceList;
		typedef std::vector< spIVideoFrameSource >	VideoFrameSourceList;
		typedef std::vector< spcIVideoFrameSource > cVideoFrameSourceList;
		typedef std::vector< spIImageSource >		ImageSourceList;
		typedef std::vector< spcIImageSource >		cImageSourceList;

		typedef std::vector< spIOutput > OutputList;
		typedef std::vector< spcIOutput > cOutputList;

		//!
		//! Adds a new video source to UMC
		//! \return a shared pointer to non const IVideoSource object representing the newly added video source.
		//!
		virtual spIVideoSource AddVideoSource() = 0;

		//!
		//! Adds a new audio source to UMC
		//! \return a shared pointer to non const IAudioSource object representing the newly added audio source.
		//!
		virtual spIAudioSource AddAudioSource() = 0;

		//!
		//! Creates a new video frame source using an existing video source and adds the newly created video frame source to UMC
		//! \param[in] a shared pointer to non const IVideoSource object representing the video source from which video frame source is to be created.
		//! \return a shared pointer to non const IVideoFrameSource object representing the newly added video frame source.
		//!
		virtual spIVideoFrameSource AddVideoFrameSource( const spIVideoSource & videoSource ) = 0;

		//!
		//! Adds a new image source to UMC
		//! \return a shared pointer to non const IImageSource object representing the newly added image source.
		//!
		virtual spIImageSource AddImageSource() = 0;

		//!
		//! Creates a new source from a buffer
		//! param[in] a value of type std::string indicating the buffer from which the source object is to be created
		//! \return a shared pointer to a non-const object of type ISource representing the newly created source. A parsing error will be thrown in case the parsing of the buffer fails.
		//!
		virtual spISource AddSource( const std::string & buffer ) = 0;

		//!
		//! Creates a new video source from a buffer
		//! param[in] a value of type std::string indicating the buffer from which the video source object is to be created
		//! \return a shared pointer to a non-const object of type IVideoSource representing the newly created video source. A parsing error will be thrown in case the parsing of the buffer fails.
		//!
		virtual spIVideoSource AddVideoSource( const std::string & buffer ) = 0;

		//!
		//! Creates a new audio source from a buffer
		//! param[in] a value of type std::string indicating the buffer from which the source object is to be created
		//! \return a shared pointer to a non-const object of type IAudioSource representing the newly created audio source. A parsing error will be thrown in case the parsing of the buffer fails.
		//!
		virtual spIAudioSource AddAudioSource( const std::string & buffer ) = 0;

		//!
		//! Creates a new video source from a buffer
		//! param[in] a value of type std::string indicating the buffer from which the video frame source source object is to be created
		//! \return a shared pointer to a non-const object of type IVideoFrameSource representing the newly created video frame source. A parsing error will be thrown in case the parsing of the buffer fails.
		//!
		virtual spIVideoFrameSource AddVideoFrameSource( const std::string & buffer ) = 0;

		//!
		//! Creates a new image source from a buffer
		//! param[in] a value of type std::string indicating the buffer from which the image source source object is to be created
		//! \return a shared pointer to a non-const object of type IImageSource representing the newly created image source. A parsing error will be thrown in case the parsing of the buffer fails.
		//!
		virtual spIImageSource AddImageSource( const std::string & buffer ) = 0;


		//!
		//! Adds a new audio source to UMC
		//! \return a shared pointer to non const IOutput object representing the newly added output.
		//!
		virtual spIOutput AddOutput() = 0;

		//!
		//! Adds a new audio source to UMC
		//! param[in] 
		//! \return a shared pointer to non const IOutput object representing the newly added output.
		//!
		virtual spIOutput AddOutput( const std::string & buffer ) = 0;

		//!
		//! Gets the count of sources present in the UMC
		//! \return a value of type size_t indicating the count of sources present in the UMC
		//!
		virtual size_t SourceCount() const = 0;

		//!
		//! Gets the count of video sources present in the UMC
		//! \return a value of type size_t indicating the count of video sources present in the UMC
		//!
		virtual size_t VideoSourceCount() const = 0;

		//!
		//! Gets the count of audio sources present in the UMC
		//! \return a value of type size_t indicating the count of audio sources present in the UMC
		//!
		virtual size_t AudioSourceCount() const = 0;

		//!
		//! Gets the count of video frame sources present in the UMC
		//! \return a value of type size_t indicating the count of video frame sources present in the UMC
		//!
		virtual size_t VideoFrameSourceCount() const = 0;

		//!
		//! Gets the count of image sources present in the UMC
		//! \return a value of type size_t indicating the count of image sources present in the UMC
		//!
		virtual size_t ImageSourceCount() const = 0;

		//!
		//! Gets the list of all the sources present in the UMC
		//! \return an object of type SourceList representing list of non-const objects of type ISource.
		//!
		virtual SourceList GetAllSources() = 0;

		//!
		//! Gets the list of all the sources present in the UMC
		//! \return an object of type cSourceList representing list of const objects of type ISource.
		//!
		virtual cSourceList GetAllSources() const = 0;

		//!
		//! Gets the list of all the video sources present in the UMC
		//! \return an object of type VideoSourceList representing list of non-const objects of type IVideoSource.
		//!
		virtual VideoSourceList GetAllVideoSources() = 0;

		//!
		//! Gets the list of all the video sources present in the UMC
		//! \return an object of type cVideoSourceList representing list of const objects of type IVideoSource.
		//!
		virtual cVideoSourceList GetAllVideoSources() const = 0;

		//!
		//! Gets the list of all the audio sources present in the UMC
		//! \return an object of type AudioSourceList representing list of non-const objects of type IAudioSource.
		//!
		virtual AudioSourceList GetAllAudioSources() = 0;

		//!
		//! Gets the list of all the audio sources present in the UMC
		//! \return an object of type cAudioSourceList representing list of const objects of type IAudioSource.
		//!
		virtual cAudioSourceList GetAllAudioSources() const = 0;

		//!
		//! Gets the list of all the video frame sources present in the UMC
		//! \return an object of type VideoFrameSourceList representing list of non-const objects of type IVideoFrameSource.
		//!
		virtual VideoFrameSourceList GetAllVideoFrameSources() = 0;

		//!
		//! Gets the list of all the video frame sources present in the UMC
		//! \return an object of type cVideoSourceList representing list of const objects of type IVideoFrameSource.
		//!
		virtual cVideoFrameSourceList GetAllVideoFrameSources() const = 0;

		//!
		//! Gets the list of all the image sources present in the UMC
		//! \return an object of type ImageSourceList representing list of non-const objects of type IImageSource.
		//!
		virtual ImageSourceList GetAllImageSources() = 0;

		//!
		//! Gets the list of all the image frame sources present in the UMC
		//! \return an object of type cImageSourceList representing list of const objects of type IImageSource.
		//!
		virtual cImageSourceList GetAllImageSources() const = 0;

		//!
		//! Gets the source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the source
		//! \return a shared pointer to a non-const object of type ISource. An empty shared pointer will be returned if no source is found with the particular unique id.
		//!
		virtual spISource GetSource( const std::string & uniqueID ) = 0;

		//!
		//! Gets the source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the source
		//! \return a shared pointer to a const object of type ISource. An empty shared pointer will be returned if no source is found with the particular unique id.
		//!
		virtual spcISource GetSource( const std::string & uniqueID ) const = 0;

		//!
		//! Gets the video source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the video source
		//! \return a shared pointer to a non-const object of type IVideoSource. An empty shared pointer will be returned if no video source is found with the particular unique id.
		//!
		virtual spIVideoSource GetVideoSource( const std::string & uniqueID ) = 0;

		//!
		//! Gets the video source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the video source
		//! \return a shared pointer to a const object of type IVideoSource. An empty shared pointer will be returned if no video source is found with the particular unique id.
		//!
		virtual spcIVideoSource GetVideoSource( const std::string & uniqueID ) const = 0;

		//!
		//! Gets the audio source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the audio source
		//! \return a shared pointer to a non-const object of type IAudioSource. An empty shared pointer will be returned if no audio source is found with the particular unique id.
		//!
		virtual spIAudioSource GetAudioSource( const std::string & uniqueID ) = 0;

		//!
		//! Gets the audio source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the audio source
		//! \return a shared pointer to a const object of type IAudioSource. An empty shared pointer will be returned if no audio source is found with the particular unique id.
		//!
		virtual spcIAudioSource GetAudioSource( const std::string & uniqueID ) const = 0;

		//!
		//! Gets the video frame source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the video frame source
		//! \return a shared pointer to a non-const object of type IAudioSource. An empty shared pointer will be returned if no video frame source is found with the particular unique id.
		//!
		virtual spIVideoFrameSource GetVideoFrameSource( const std::string & uniqueID ) = 0;

		//!
		//! Gets the video frame source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the audio source
		//! \return a shared pointer to a const object of type IAudioSource. An empty shared pointer will be returned if no audio source is found with the particular unique id.
		//!
		virtual spcIVideoFrameSource GetVideoFrameSource( const std::string & uniqueID ) const = 0;

		//!
		//! Gets the image source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the image source
		//! \return a shared pointer to a non-const object of type IImageSource. An empty shared pointer will be returned if no image source is found with the particular unique id.
		//!
		virtual spIImageSource GetImageSource( const std::string & uniqueID ) = 0;

		//!
		//! Gets the image source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the image source
		//! \return a shared pointer to a const object of type IImageSource. An empty shared pointer will be returned if no image source is found with the particular unique id.
		//!
		virtual spcIImageSource GetImageSource( const std::string & uniqueID ) const = 0;

		//!
		//! Removes all the sources present in the UMC
		//! \return a value of type size_t indicating the count of sources present in the UMC
		//!
		virtual size_t RemoveAllSources() = 0;

		//!
		//! Removes all the video sources present in the UMC
		//! \return a value of type size_t indicating the count of video sources present in the UMC
		//!
		virtual size_t RemoveAllVideoSources() = 0;

		//!
		//! Removes all the audio sources present in the UMC
		//! \return a value of type size_t indicating the count of audio sources present in the UMC
		//!
		virtual size_t RemoveAllAudioSources() = 0;

		//!
		//! Removes all the video frame sources present in the UMC
		//! \return a value of type size_t indicating the count of video frame sources present in the UMC
		//!
		virtual size_t RemoveAllVideoFramesSources() = 0;

		//!
		//! Removes all the image sources present in the UMC
		//! \return a value of type size_t indicating the count of image sources present in the UMC
		//!
		virtual size_t RemoveAllImageSources() = 0;

		//!
		//! Removes the source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the source
		//! \return a size_t indicating whether the source is removed successfully. 1 is returned if the removal is successful.
		//!
		virtual size_t RemoveSource( const std::string & uniqueID ) = 0;

		//!
		//! Removes the video source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the video source
		//! \return a size_t indicating whether the video source was removed successfully. 1 is returned if the removal is successful.
		//!
		virtual size_t RemoveVideoSource( const std::string & uniqueID ) = 0;

		//!
		//! Removes the audio source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the audio source
		//! \return a size_t indicating whether the audio source was removed successfully. 1 is returned if the removal is successful.
		//!
		virtual size_t RemoveAudioSource( const std::string & uniqueID ) = 0;

		//!
		//! Removes the video frame source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the video frame source
		//! \return a size_t indicating whether the video frame source was removed successfully. 1 is returned if the removal is successful.
		//!
		virtual size_t RemoveVideoFrameSource( const std::string & uniqueID ) = 0;

		//!
		//! Removes the image source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the image source
		//! \return a size_t indicating whether the image source was removed successfully. 1 is returned if the removal is successful.
		//!
		virtual size_t RemoveImageSource( const std::string & uniqueID ) = 0;

		//!
		//! Gets the count of outputs present in the UMC
		//! \return a value of type size_t indicating the outputs present in the UMC
		//!
		virtual size_t OutputCount() const = 0;

		//!
		//! Gets the list of all the outputs present in the UMC
		//! \return an object of type IOutputList representing list of non-const objects of type IOutput.
		//!
		virtual OutputList GetAllOutputs() = 0;

		//!
		//! Gets the list of all the outputs present in the UMC
		//! \return an object of type cIOutputList representing list of const objects of type IOutput.
		//!
		virtual cOutputList GetAllOutputs() const = 0;

		//!
		//! Gets the output from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the output
		//! \return a shared pointer to a non-const object of type IOutput. An empty shared pointer will be returned if no output is found with the particular unique id.
		//!
		virtual spIOutput GetOutput( const std::string & uniqueID ) = 0;
		//!
		//! Gets the image source from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the output
		//! \return a shared pointer to a const object of type IOutput. An empty shared pointer will be returned if no output is found with the particular unique id.
		//!
		virtual spcIOutput GetOutput( const std::string & uniqueID ) const = 0;

		//!
		//! Removes all the outputs present in the UMC
		//! \return a value of type size_t indicating the count of outputs present in the UMC
		//!
		virtual size_t RemoveAllOutputs() = 0;

		//!
		//! Removes the output from the UMC with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the output
		//! \return a size_t indicating whether the output was removed successfully. 1 is returned if the removal is successful.
		//!
		virtual size_t RemoveOutput( const std::string & uniqueID ) = 0;
		
		//!
		//! Removes all the outputs present in the UMC
		//! \return a value of type size_t indicating the count of outputs present in the UMC
		//!
		virtual std::string SerializeToBuffer() const = 0;

		//!
		//! Creates an empty UMC object
		//! \return a shared pointer to a non-const object of type IUMC representing the newly created UMC object
		//!
		static spIUMC CreateEmptyUMC();

		//!
		//! Creates an empty UMC object from a buffer
		//! param[in] a value of type std::string indicating the buffer from which UMC object is to be created
		//! \return a shared pointer to a non-const object of type IUMC representing the newly created UMC object. A parsing error will be thrown in case the parsing of the buffer fails.
		//!
		static spIUMC CreateUMCFromBuffer( const std::string & buffer );

		//!
		//! Registers a new custom node handler or de-registers an existing custom data handler
		//! param[in] a value of type std::string indicating the namespace of the custom data for which the custom handler is to be registered
		//! param[in] a value of type std::string indicating the name of the custom data for which the custom handler is to be registered
		//! param[in] a shared pointer to a non-const object of type ICustomDataHandler representing the custom data handler to be created. If an empty shared pointer is provided, then the existing custom data handler is de-registerd. 
		//! \return a value of type bool indicating whether the registration or the de-registration of the custom data handler was successful. 
		//!
		static bool RegisterCustomNodeHandler( const std::string & customDataNameSpace, const std::string & customDataName,
			const spICustomDataHandler & customDataHandler );

		virtual ~IUMC() = 0;
	};

	inline IUMC::~IUMC() {}
}
#endif  // IUMC_h__
