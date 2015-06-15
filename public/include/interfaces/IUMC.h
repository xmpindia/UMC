#ifndef IUMC_h__
#define IUMC_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include "INode.h"

namespace UMC {

	class IUMC
		: public INode
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

		virtual spIVideoSource AddVideoSource() = 0;
		virtual spIAudioSource AddAudioSource() = 0;
		virtual spIVideoFrameSource AddVideoFrameSource( const spIVideoSource & videoSource ) = 0;
		virtual spIImageSource AddImageSource() = 0;

		virtual spISource AddSource( const std::string & buffer ) = 0;
		virtual spIVideoSource AddVideoSource( const std::string & buffer ) = 0;
		virtual spIAudioSource AddAudioSource( const std::string & buffer ) = 0;
		virtual spIVideoFrameSource AddVideoFrameSource( const std::string & buffer ) = 0;
		virtual spIImageSource AddImageSource( const std::string & buffer ) = 0;

		virtual spIOutput AddOutput() = 0;
		virtual spIOutput AddOutput( const std::string & buffer ) = 0;

		virtual size_t SourceCount() const = 0;
		virtual size_t VideoSourceCount() const = 0;
		virtual size_t AudioSourceCount() const = 0;
		virtual size_t VideoFrameSourceCount() const = 0;
		virtual size_t ImageSourceCount() const = 0;

		virtual SourceList GetAllSources() = 0;
		virtual cSourceList GetAllSources() const = 0;
		virtual VideoSourceList GetAllVideoSources() = 0;
		virtual cVideoSourceList GetAllVideoSources() const = 0;
		virtual AudioSourceList GetAllAudioSources() = 0;
		virtual cAudioSourceList GetAllAudioSources() const = 0;
		virtual VideoFrameSourceList GetAllVideoFrameSources() = 0;
		virtual cVideoFrameSourceList GetAllVideoFrameSources() const = 0;
		virtual ImageSourceList GetAllImageSources() = 0;
		virtual cImageSourceList GetAllImageSources() const = 0;

		virtual spISource GetSource( const std::string & uniqueID ) = 0;
		virtual spcISource GetSource( const std::string & uniqueID ) const = 0;
		virtual spIVideoSource GetVideoSource( const std::string & uniqueID ) = 0;
		virtual spcIVideoSource GetVideoSource( const std::string & uniqueID ) const = 0;
		virtual spIAudioSource GetAudioSource( const std::string & uniqueID ) = 0;
		virtual spcIAudioSource GetAudioSource( const std::string & uniqueID ) const = 0;
		virtual spIVideoFrameSource GetVideoFrameSource( const std::string & uniqueID ) = 0;
		virtual spcIVideoFrameSource GetVideoFrameSource( const std::string & uniqueID ) const = 0;
		virtual spIImageSource GetImageSource( const std::string & uniqueID ) = 0;
		virtual spcIImageSource GetImageSource( const std::string & uniqueID ) const = 0;


		virtual size_t RemoveAllSources() = 0;
		virtual size_t RemoveAllVideoSources() = 0;
		virtual size_t RemoveAllAudioSources() = 0;
		virtual size_t RemoveAllVideoFramesSources() = 0;
		virtual size_t RemoveAllImageSources() = 0;

		virtual size_t RemoveSource( const std::string & uniqueID ) = 0;
		virtual size_t RemoveVideoSource( const std::string & uniqueID ) = 0;
		virtual size_t RemoveAudioSource( const std::string & uniqueID ) = 0;
		virtual size_t RemoveVideoFrameSource( const std::string & uniqueID ) = 0;
		virtual size_t RemoveImageSource( const std::string & uniqueID ) = 0;

		virtual size_t OutputCount() const = 0;

		virtual OutputList GetAllOutputs() = 0;
		virtual cOutputList GetAllOutputs() const = 0;

		virtual spIOutput GetOutput( const std::string & uniqueID ) = 0;
		virtual spcIOutput GetOutput( const std::string & uniqueID ) const = 0;

		virtual size_t RemoveAllOutputs() = 0;
		virtual size_t RemoveOutput( const std::string & uniqueID ) = 0;
		
		virtual std::string SerializeToBuffer() const = 0;

		static spIUMC CreateEmptyUMC();
		static spIUMC CreateUMCFromBuffer( const std::string & buffer );

		static bool RegisterCustomNodeHandler( const std::string & customDataNameSpace, const std::string & customDataName,
			const spICustomDataHandler & customDataHandler );

		virtual ~IUMC() = 0;
	};

	inline IUMC::~IUMC() {}
}
#endif  // IUMC_h__
