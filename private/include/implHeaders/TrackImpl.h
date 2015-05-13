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
#include "interfaces/IShot.h"
#include "interfaces/INodeI.h"

#include <string>
#include <map>

namespace INT_UMC {
	using namespace UMC;

	class TrackImpl
		: public ITrack
		, public INodeI
	{
	public:
		TrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		const std::string & GetUniqueID() const;

		virtual eTrackTypes GetType() const;

		virtual spIShot AddClipShot();
		virtual spIShot AddTransitionShot();

		virtual void SetName( const std::string & uniqueID );
		virtual std::string GetName() const;

		virtual size_t ShotCount() const;
		virtual size_t ClipShotCount() const;
		virtual size_t TransitionShotCount() const;

		virtual ShotList GetAllShots();
		virtual cShotList GetAllShots() const;
		virtual ShotList GetAllClipShots();
		virtual cShotList GetAllClipShots() const;
		virtual ShotList GetAllTransitionShots();
		virtual cShotList GetAllTransitionShots() const;

		virtual spIShot GetShot( const std::string & uniqueID );
		virtual spcIShot GetShot( const std::string & uniqueID ) const;
		virtual spIShot GetClipShot( const std::string & uniqueID );
		virtual spcIShot GetClipShot( const std::string & uniqueID ) const;
		virtual spIShot GetTransitionShot( const std::string & uniqueID );
		virtual spcIShot GetTransitionShot( const std::string & uniqueID ) const;

		virtual size_t RemoveAllShots();
		virtual size_t RemoveAllClipShots();
		virtual size_t RemoveAllTransitionShots();

		virtual size_t RemoveShot( const std::string & uniqueID );
		virtual size_t RemoveClipShot( const std::string & uniqueID );
		virtual size_t RemoveTransitionShot( const std::string & uniqueID );

		virtual eNodeTypes GetNodeType() const;

		virtual spcINode GetParentNode() const;
		virtual spINode GetParentNode();

		virtual spcINode GetChildNode( const std::string & uniqueID ) const;
		virtual spINode GetChildNode( const std::string & uniqueID );

		virtual spcINode GetDecendantNode( const std::string & uniqueID ) const;
		virtual spINode GetDecendantNode( const std::string & uniqueID );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual size_t GetReferenceCount() const;

		virtual void RemoveFromDOM();
		virtual void AddToDOM( const spINode & parent );

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual pINodeI GetInternalNode();
		virtual pcINodeI GetInternalNode() const;

		virtual void SetExtensionNode( const spIXMPStructureNode & structureNode );

		virtual spIXMPStructureNode GetExtensionNode(bool create = false) const;
		virtual spIXMPStructureNode GetMergedExtensionNode() const;

		virtual spIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker();
		virtual spcIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() const;

		virtual spIUniqueIDGenerator GetUniqueIDGenerator();
		virtual spcIUniqueIDGenerator GetUniqueIDGenerator() const;

	protected:

		typedef std::map< const std::string, spIShot > ShotMap;

		spINode							mNode;

		std::string						mName;
		ShotMap							mShotMap;
	};
}

#endif  // TrackImpl_h__
