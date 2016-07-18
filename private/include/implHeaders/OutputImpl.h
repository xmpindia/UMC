#ifndef OutputImpl_h__
#define OutputImpl_h__ 1

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
#include "interfaces/IOutput.h"
#include "interfaces/ITrack.h"
#include "implHeaders/NodeImpl.h"

namespace INT_UMC {
	using namespace UMC;

	class OutputImpl
		: public IOutput
		, public NodeImpl
		, public enable_shared_from_this< OutputImpl >
	{
	public:
		OutputImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		OutputImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator,
			const spIStructureNode & xmpStructureNode );

		virtual const std::string & GetUniqueID() const;
		virtual std::string GetParsedID() const;

		virtual spITrack AddTrack( const std::string & buffer );

		virtual spIVideoTrack AddVideoTrack();
		virtual spIVideoTrack AddVideoTrack( const std::string & buffer );

		virtual spIAudioTrack AddAudioTrack();
		virtual spIAudioTrack AddAudioTrack( const std::string & buffer );

		virtual void SetName( const std::string & name );
		virtual std::string GetName() const;

		virtual void SetTitle( const std::string & title );
		virtual std::string GetTitle() const;

		virtual void SetCanvasAspectRatio( const AspectRatio & canvasAspectRatio );
		virtual AspectRatio GetCanvasAspectRatio() const;

		virtual void SetImageAspectRatio( const AspectRatio & imageAspectRatio );
		virtual AspectRatio GetImageAspectRatio() const;

		virtual void SetVideoEditRate( const EditRate & videoEditRate );
		virtual EditRate GetVideoEditRate() const;

		virtual void SetAudioEditRate( const EditRate & audioEditRate );
		virtual EditRate GetAudioEditRate() const;

		virtual size_t TrackCount() const;
		virtual TrackList GetAllTracks();
		virtual cTrackList GetAllTracks() const;
		virtual spITrack GetTrack( const std::string & uniqueID );
		virtual spcITrack GetTrack( const std::string & uniqueID ) const;

		virtual size_t VideoTrackCount() const;
		virtual VideoTrackList GetAllVideoTracks();
		virtual cVideoTrackList GetAllVideoTracks() const;
		virtual spIVideoTrack GetVideoTrack( const std::string & uniqueID );
		virtual spcIVideoTrack GetVideoTrack( const std::string & uniqueID ) const;

		virtual size_t AudioTrackCount() const;
		virtual AudioTrackList GetAllAudioTracks();
		virtual cAudioTrackList GetAllAudioTracks() const;
		virtual spIAudioTrack GetAudioTrack( const std::string & uniqueID );
		virtual spcIAudioTrack GetAudioTrack( const std::string & uniqueID ) const;

		virtual size_t RemoveAllTracks();
		virtual size_t RemoveAllVideoTracks();
		virtual size_t RemoveAllAudioTracks();
		virtual size_t RemoveTrack( const std::string & uniqueID );
		virtual size_t RemoveVideoTrack( const std::string & uniqueID );
		virtual size_t RemoveAudioTrack( const std::string & uniqueID );

		virtual eNodeTypes GetNodeType() const;

		virtual wpcIUMCNode GetParentNode() const;
		virtual wpIUMCNode GetParentNode();

		virtual spcIUMCNode GetDecendantNode( const std::string & id ) const;
		virtual spIUMCNode GetDecendantNode( const std::string & id );

		virtual spcIUMCNode GetChildNode( const std::string & id ) const;
		virtual spIUMCNode GetChildNode( const std::string & id );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual size_t GetReferenceCount() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual pIUMCNodeI GetInternalNode();
		virtual pcIUMCNodeI GetInternalNode() const;


		virtual void CleanUpOnRemovalFromDOM();
		virtual void SetUpOnAdditionToDOM();

		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff();

		virtual spIStructureNode GetXMPNode() const;

	protected:
		spIAudioTrack AddAudioTrack( const spIStructureNode & xmpStructureNode );
		spIVideoTrack AddVideoTrack( const spIStructureNode & xmpStructureNode );

		virtual bool ValidateXMPNode() const;

		virtual std::string Serialize() const;

		virtual pIUMCNode GetNode();

		virtual pcIUMCNode GetNode() const;

		virtual bool SetUniqueID( const std::string & uniqueID );
		virtual bool ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID );
		virtual spIUMCNode GetExternalNode();

		typedef std::map< const std::string, spIVideoTrack > VideoTrackMap;
		typedef std::map< const std::string, spIAudioTrack > AudioTrackMap;

		spIArrayNode					mVideoTracks;
		spIArrayNode					mAudioTracks;
		spIStructureNode				mTracks;

		std::string						mName;
		std::string						mTitle;
		AspectRatio						mCanvasAspectRatio;
		AspectRatio						mImageAspectRatio;
		EditRate						mVideoEditRate;
		EditRate						mAudioEditRate;
		VideoTrackMap					mVideoTrackMap;
		AudioTrackMap					mAudioTrackMap;
	};
}

#endif  // OutputImpl_h__
