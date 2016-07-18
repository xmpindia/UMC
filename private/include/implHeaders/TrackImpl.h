#ifndef TrackImpl_h__
#define TrackImpl_h__ 1

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

#include "interfaces/ITrack.h"
#include "implHeaders/NodeImpl.h"

namespace INT_UMC {
	using namespace UMC;

	class TrackImpl
		: public NodeImpl
	{
	public:
		TrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, ITrack::eTrackTypes trackType, const NamespacePropertyNamePair & pair );

		TrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, ITrack::eTrackTypes trackType,
			const spIStructureNode & xmpStructureNode );

		IUMCNode::eNodeTypes GetNodeType() const;

		void CleanUpOnRemovalFromDOM();
		void SetUpOnAdditionToDOM();

		void SyncInternalStuffToXMP() const;
		void SyncXMPToInternalStuff( const spIUMCNode & node );

		spIClipShot AddClipShot( const spIUMCNode & node );
		spITransitionShot AddTransitionShot( const spIUMCNode & node );

		spIShot AddShot( const std::string & buffer, const spIUMCNode & node );
		spIClipShot AddClipShot( const std::string & buffer, const spIUMCNode & node );
		spITransitionShot AddTransitionShot( const std::string & buffer, const spIUMCNode & node );

		void SetName( const std::string & name );
		std::string GetName() const;

		size_t ShotCount() const;
		ITrack::ShotList GetAllShots();
		ITrack::cShotList GetAllShots() const;
		spIShot GetShot( const std::string & uniqueID );
		spcIShot GetShot( const std::string & uniqueID ) const;

		size_t ClipShotCount() const;
		ITrack::ClipShotList GetAllClipShots();
		ITrack::cClipShotList GetAllClipShots() const;
		spIClipShot GetClipShot( const std::string & uniqueID );
		spcIClipShot GetClipShot( const std::string & uniqueID ) const;

		size_t TransitionShotCount() const;
		ITrack::TransitionShotList GetAllTransitionShots();
		ITrack::cTransitionShotList GetAllTransitionShots() const;
		spITransitionShot GetTransitionShot( const std::string & uniqueID );
		spcITransitionShot GetTransitionShot( const std::string & uniqueID ) const;

		size_t RemoveAllShots();
		size_t RemoveAllClipShots();
		size_t RemoveAllTransitionShots();

		size_t RemoveShot( const std::string & uniqueID );
		size_t RemoveClipShot( const std::string & uniqueID );
		size_t RemoveTransitionShot( const std::string & uniqueID );

		spcIUMCNode GetDecendantNode( const std::string & uniqueID ) const;
		spIUMCNode GetDecendantNode( const std::string & uniqueID );

		spcIUMCNode GetChildNode( const std::string & uniqueID ) const;
		spIUMCNode GetChildNode( const std::string & uniqueID );

		IUMCNode::NodeList GetAllChildren();
		IUMCNode::cNodeList GetAllChildren() const;

		IUMCNode::NodeList GetAllDecendants();
		IUMCNode::cNodeList GetAllDecendants() const;

	protected:
		spIClipShot AddClipShot( const spIStructureNode & node, const spIUMCNode & node2 );
		spITransitionShot AddTransitionShot( const spIStructureNode & node, const spIUMCNode & node2 );

		bool ValidateXMPNode() const = 0;

		typedef std::map< const std::string, spIClipShot >			ClipShotMap;
		typedef std::map< const std::string, spITransitionShot >	TransitionShotMap;

		spIStructureNode				mShots;
		spIArrayNode					mClipShots;
		spIArrayNode					mTransitionShots;

		std::string						mName;
		ClipShotMap						mClipShotMap;
		TransitionShotMap				mTransitionShotMap;
	};
}

#endif  // TrackImpl_h__
