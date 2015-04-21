#ifndef UMCImpl_h__
#define UMCImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IUMC.h"
#include "UMCFwdDeclarations_I.h"
#include <map>
#include "interfaces/ISource.h"

namespace INT_UMC {

	class UMCImpl
		: public IUMC
		, public enable_shared_from_this< UMCImpl >
	{
	public:
		UMCImpl();

		virtual eNodeTypes GetNodeType() const;

		virtual const std::string & GetUniqueID() const;

		virtual spcINode GetParentNode() const;
		virtual spINode GetParentNode();

		virtual spcINode GetDecendantNode( const std::string & id ) const;
		virtual spINode GetDecendantNode( const std::string & id );

		virtual spcINode GetChildNode( const std::string & id ) const;
		virtual spINode GetChildNode( const std::string & id );

		virtual std::string SerializeToBuffer() const;

		virtual spIOutput AddOutput();
		virtual size_t OutputCount() const;

		virtual OutputList GetAllOutputs();
		virtual cOutputList GetAllOutputs() const;

		virtual spIOutput GetOutput( const std::string & uniqueID );
		virtual spcIOutput GetOutput( const std::string & uniqueID ) const;

		virtual size_t RemoveAllOutputs();
		virtual size_t RemoveOutput( const std::string & uniqueID );

		virtual spIVideoSource AddVideoSource();
		virtual spIAudioSource AddAudioSource();
		virtual spIVideoFrameSource AddVideoFrameSource( const spIVideoSource & videoSource );
		virtual spIImageSource AddImageSource();

		virtual size_t SourceCount() const;
		virtual size_t VideoSourceCount() const;
		virtual size_t AudioSourceCount() const;
		virtual size_t VideoFrameSourceCount() const;
		virtual size_t ImageSourceCount() const;

		virtual SourceList GetAllSources();
		virtual cSourceList GetAllSources() const;
		virtual VideoSourceList GetAllVideoSources();
		virtual cVideoSourceList GetAllVideoSources() const;
		virtual AudioSourceList GetAllAudioSources();
		virtual cAudioSourceList GetAllAudioSources() const;
		virtual VideoFrameSourceList GetAllVideoFrameSources();
		virtual cVideoFrameSourceList GetAllVideoFrameSources() const;
		virtual ImageSourceList GetAllImageSources();
		virtual cImageSourceList GetAllImageSources() const;

		virtual spISource GetSource( const std::string & uniqueID );
		virtual spcISource GetSource( const std::string & uniqueID ) const;
		virtual spIVideoSource GetVideoSource( const std::string & uniqueID );
		virtual spcIVideoSource GetVideoSource( const std::string & uniqueID ) const;
		virtual spIAudioSource GetAudioSource( const std::string & uniqueID );
		virtual spcIAudioSource GetAudioSource( const std::string & uniqueID ) const;
		virtual spIVideoFrameSource GetVideoFrameSource( const std::string & uniqueID );
		virtual spcIVideoFrameSource GetVideoFrameSource( const std::string & uniqueID ) const;
		virtual spIImageSource GetImageSource( const std::string & uniqueID );
		virtual spcIImageSource GetImageSource( const std::string & uniqueID ) const;

		virtual size_t RemoveAllSources();
		virtual size_t RemoveAllVideoSources();
		virtual size_t RemoveAllAudioSources();
		virtual size_t RemoveAllVideoFramesSources();
		virtual size_t RemoveAllImageSources();

		virtual size_t RemoveSource( const std::string & uniqueID );
		virtual size_t RemoveVideoSource( const std::string & uniqueID );
		virtual size_t RemoveAudioSource( const std::string & uniqueID );
		virtual size_t RemoveVideoFrameSource( const std::string & uniqueID );
		virtual size_t RemoveImageSource( const std::string & uniqueID );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		
	protected:
		typedef std::map< const std::string, spIVideoSource > VideoSourceMap;
		typedef std::map< const std::string, spIAudioSource > AudioSourceMap;
		typedef std::map< const std::string, spIVideoFrameSource > VideoFrameSourceMap;
		typedef std::map< const std::string, spIImageSource > ImageSourceMap;
		typedef std::map< const std::string, spIOutput > OutputMap;

		VideoSourceMap			mVideoSourceMap;
		AudioSourceMap			mAudioSourceMap;
		VideoFrameSourceMap		mVideoFrameSourceMap;
		ImageSourceMap			mImageSourceMap;
		OutputMap				mOutputMap;

		spUniqueIDSet			mspUniqueIDSet;
		spIUniqueIDGenerator	mspUniqueIDGenerator;
	};
}

#endif  // UMCImpl_h__
