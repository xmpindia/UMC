#ifndef UMCImpl_h__
#define UMCImpl_h__ 1

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
#include "interfaces/IUMC.h"
#include "UMCFwdDeclarations_I.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"
#include "implHeaders/NodeImpl.h"

#include <map>

namespace INT_UMC {

	using namespace AdobeXMPCore;

	class UMCImpl
		: public IUMC
		, public NodeImpl
		, public enable_shared_from_this< UMCImpl >
	{
	public:
		UMCImpl();
		UMCImpl( const spIStructureNode & metadata );

		virtual spIVideoSource AddVideoSource();
		virtual spIVideoSource AddVideoSource( const std::string & buffer );

		virtual spIAudioSource AddAudioSource();
		virtual spIAudioSource AddAudioSource( const std::string & buffer );

		virtual spIVideoFrameSource AddVideoFrameSource( const spIVideoSource & videoSource );
		virtual spIVideoFrameSource AddVideoFrameSource( const std::string & buffer );

		virtual spIImageSource AddImageSource();
		virtual spIImageSource AddImageSource( const std::string & buffer );

		virtual spISource AddSource( const std::string & buffer );

		virtual spIOutput AddOutput();
		virtual spIOutput AddOutput( const std::string & buffer );

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

		virtual size_t OutputCount() const;

		virtual OutputList GetAllOutputs();
		virtual cOutputList GetAllOutputs() const;

		virtual spIOutput GetOutput( const std::string & uniqueID );
		virtual spcIOutput GetOutput( const std::string & uniqueID ) const;

		virtual size_t RemoveAllOutputs();

		virtual size_t RemoveOutput( const std::string & uniqueID );

		virtual std::string SerializeToBuffer() const;

		virtual eNodeTypes GetNodeType() const;

		virtual spcIUMCNode GetDecendantNode( const std::string & uniqueID ) const;
		virtual spIUMCNode GetDecendantNode( const std::string & uniqueID );

		virtual spcIUMCNode GetChildNode( const std::string & uniqueID ) const;
		virtual spIUMCNode GetChildNode( const std::string & uniqueID );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual INT_UMC::pIUMCNodeI GetInternalNode();
		virtual INT_UMC::pcIUMCNodeI GetInternalNode() const;

		virtual void CleanUpOnRemovalFromDOM();
		virtual void SetUpOnAdditionToDOM();

		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff();

		virtual spIStructureNode GetXMPNode() const;

		virtual const std::string & GetUniqueID() const;
		virtual std::string GetParsedID() const;

		virtual wpcIUMCNode GetParentNode() const;
		virtual wpIUMCNode GetParentNode();

		virtual size_t GetReferenceCount() const;

		virtual std::string Serialize() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

	protected:
		spIVideoSource AddVideoSource( const spIStructureNode & node );
		spIAudioSource AddAudioSource( const spIStructureNode & node );
		spIImageSource AddImageSource( const spIStructureNode & node );
		spIVideoFrameSource AddVideoFrameSource( const spIStructureNode & node );

		spIOutput AddOutput( const spIStructureNode & node );

		virtual bool ValidateXMPNode() const;

		virtual pIUMCNode GetNode();

		virtual pcIUMCNode GetNode() const;

		virtual bool SetUniqueID( const std::string & uniqueID );
		virtual bool ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID );

		virtual spIUMCNode GetExternalNode();

		typedef std::map< const std::string, spIVideoSource > VideoSourceMap;
		typedef std::map< const std::string, spIAudioSource > AudioSourceMap;
		typedef std::map< const std::string, spIVideoFrameSource > VideoFrameSourceMap;
		typedef std::map< const std::string, spIImageSource > ImageSourceMap;
		typedef std::map< const std::string, spIOutput > OutputMap;

		spIArrayNode					mOutputs;
		spIStructureNode				mSources;
		spIArrayNode					mVideoSources;
		spIArrayNode					mAudioSources;
		spIArrayNode					mVideoFrameSources;
		spIArrayNode					mImageSources;

		VideoSourceMap					mVideoSourceMap;
		AudioSourceMap					mAudioSourceMap;
		VideoFrameSourceMap				mVideoFrameSourceMap;
		ImageSourceMap					mImageSourceMap;
		OutputMap						mOutputMap;
	};
}

#endif  // UMCImpl_h__
