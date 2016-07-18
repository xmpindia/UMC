#ifndef AudioTrackImpl_h__
#define AudioTrackImpl_h__ 1

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

#include "interfaces/IAudioTrack.h"
#include "implHeaders/TrackImpl.h"
#include "UMCFwdDeclarations_I.h"

namespace INT_UMC {
	class AudioTrackImpl
		: public IAudioTrack
		, public TrackImpl
		, public enable_shared_from_this < AudioTrackImpl >
	{
	public:
		AudioTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		AudioTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node );

		virtual ~AudioTrackImpl() {}

		virtual void SetAudioEditRate( const EditRate & editRate );
		virtual EditRate GetAudioEditRate() const;

		virtual eTrackTypes GetType() const;

		virtual spIShot AddShot( const std::string & buffer );

		virtual spIClipShot AddClipShot();
		virtual spIClipShot AddClipShot( const std::string & buffer );

		virtual spITransitionShot AddTransitionShot();
		virtual spITransitionShot AddTransitionShot( const std::string & buffer );

		virtual void SetName( const std::string & uniqueID );
		virtual std::string GetName() const;

		virtual size_t ShotCount() const;
		virtual ShotList GetAllShots();
		virtual cShotList GetAllShots() const;
		virtual spIShot GetShot( const std::string & uniqueID );
		virtual spcIShot GetShot( const std::string & uniqueID ) const;

		virtual size_t ClipShotCount() const;
		virtual ClipShotList GetAllClipShots();
		virtual cClipShotList GetAllClipShots() const;
		virtual spIClipShot GetClipShot( const std::string & uniqueID );
		virtual spcIClipShot GetClipShot( const std::string & uniqueID ) const;

		virtual size_t TransitionShotCount() const;
		virtual TransitionShotList GetAllTransitionShots();
		virtual cTransitionShotList GetAllTransitionShots() const;
		virtual spITransitionShot GetTransitionShot( const std::string & uniqueID );
		virtual spcITransitionShot GetTransitionShot( const std::string & uniqueID ) const;

		virtual size_t RemoveAllShots();
		virtual size_t RemoveAllClipShots();
		virtual size_t RemoveAllTransitionShots();

		virtual size_t RemoveShot( const std::string & uniqueID );
		virtual size_t RemoveClipShot( const std::string & uniqueID );
		virtual size_t RemoveTransitionShot( const std::string & uniqueID );

		virtual eNodeTypes GetNodeType() const;

		virtual const std::string & GetUniqueID() const;
		virtual std::string GetParsedID() const;

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual wpcIUMCNode GetParentNode() const;
		virtual wpIUMCNode GetParentNode();

		virtual spcIUMCNode GetDecendantNode( const std::string & uniqueID ) const;
		virtual spIUMCNode GetDecendantNode( const std::string & uniqueID );

		virtual spcIUMCNode GetChildNode( const std::string & uniqueID ) const;
		virtual spIUMCNode GetChildNode( const std::string & uniqueID );

		virtual size_t GetReferenceCount() const;

		virtual std::string Serialize() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual INT_UMC::pIUMCNodeI GetInternalNode();
		virtual INT_UMC::pcIUMCNodeI GetInternalNode() const;

		virtual void CleanUpOnRemovalFromDOM();
		virtual void SetUpOnAdditionToDOM();

		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff();

		virtual spIStructureNode GetXMPNode() const;

	protected:
		virtual bool ValidateXMPNode() const;

		virtual pIUMCNode GetNode();

		virtual pcIUMCNode GetNode() const;

		virtual bool SetUniqueID( const std::string & uniqueID );
		virtual bool ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID );
		virtual spIUMCNode GetExternalNode();

		EditRate				mAudioEditRate;
	};
}

#endif  // AudioTrackImpl_h__
