#ifndef TrackImpl_h__
#define TrackImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ITrack.h"
#include "implHeaders/NodeImpl.h"

namespace INT_UMC {
	using namespace UMC;

	class TrackImpl
		: public NodeImpl
	{
	public:
		TrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, ITrack::eTrackTypes trackType );

		TrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, ITrack::eTrackTypes trackType,
			const spIXMPStructureNode & xmpStructureNode );

		INode::eNodeTypes GetNodeType() const;

		void CleanUpOnRemovalFromDOM();
		void SetUpOnAdditionToDOM();

		void SyncInternalStuffToXMP() const;
		void SyncXMPToInternalStuff( const spINode & node );

		spIClipShot AddClipShot( const spINode & node );
		spITransitionShot AddTransitionShot( const spINode & node );

		spIShot AddShot( const std::string & buffer, const spINode & node );
		spIClipShot AddClipShot( const std::string & buffer, const spINode & node );
		spITransitionShot AddTransitionShot( const std::string & buffer, const spINode & node );

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

		spcINode GetDecendantNode( const std::string & uniqueID ) const;
		spINode GetDecendantNode( const std::string & uniqueID );

		spcINode GetChildNode( const std::string & uniqueID ) const;
		spINode GetChildNode( const std::string & uniqueID );

		INode::NodeList GetAllChildren();
		INode::cNodeList GetAllChildren() const;

		INode::NodeList GetAllDecendants();
		INode::cNodeList GetAllDecendants() const;

	protected:
		spIClipShot AddClipShot( const spIXMPStructureNode & node, const spINode & node2 );
		spITransitionShot AddTransitionShot( const spIXMPStructureNode & node, const spINode & node2 );

		bool ValidateXMPNode() const = 0;

		typedef std::map< const std::string, spIClipShot >			ClipShotMap;
		typedef std::map< const std::string, spITransitionShot >	TransitionShotMap;

		spIXMPStructureNode				mShots;
		spIXMPArrayNode					mClipShots;
		spIXMPArrayNode					mTransitionShots;

		std::string						mName;
		ClipShotMap						mClipShotMap;
		TransitionShotMap				mTransitionShotMap;
	};
}

#endif  // TrackImpl_h__
