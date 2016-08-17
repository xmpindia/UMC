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

#include "implHeaders/TrackImpl.h"
#include "interfaces/IClipShot.h"
#include "interfaces/ITransitionShot.h"
#include "interfaces/IUniqueIDGenerator.h"

#include "utils/Utils.h"
#include "utils/UMCAndXMPMapping.h"

#include "XMPCore/Interfaces/IStructureNode.h"


namespace INT_UMC {

	TrackImpl::TrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, ITrack::eTrackTypes trackType, const NamespacePropertyNamePair & pair )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, IUMCNode::kNodeTypeTrack, pair ) { }

	TrackImpl::TrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, ITrack::eTrackTypes trackType,
		const spIStructureNode & xmpStructureNode )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, IUMCNode::kNodeTypeTrack, xmpStructureNode ) { }

	IUMCNode::eNodeTypes TrackImpl::GetNodeType() const {
		return IUMCNode::kNodeTypeTrack;
	}

	void TrackImpl::CleanUpOnRemovalFromDOM() {
		ClearMap( mClipShotMap, mClipShots );
		ClearMap( mTransitionShotMap, mTransitionShots );
	}

	void TrackImpl::SetUpOnAdditionToDOM() { }

	void TrackImpl::SyncInternalStuffToXMP() const {
		AddOrUpdateDataToXMPDOM( mName, kNamePair, mXMPStructureNode );

		CallSyncUMCToXMPOnMapElements( mClipShotMap );
		CallSyncUMCToXMPOnMapElements( mTransitionShotMap );
	}

	void TrackImpl::SyncXMPToInternalStuff( const spIUMCNode & node ) {
		mShots = TryToGetStructNode( mXMPStructureNode, kShotsPair );
		if ( mShots ) {
			mClipShots = TryToGetArrayNode( mShots, kClipShotsPair );
			mTransitionShots = TryToGetArrayNode( mShots, kTransitionShotsPair );
		}

		UpdateDataFromXMPDOM( mName, kNamePair, mXMPStructureNode, kEmptyString );

		PopulateMapFromXMPArrayNode< spIClipShot, TrackImpl >( this, &TrackImpl::AddClipShot, mClipShots, node );
		PopulateMapFromXMPArrayNode< spITransitionShot, TrackImpl >( this, &TrackImpl::AddTransitionShot, mTransitionShots, node );
	}

	UMC::spIShot TrackImpl::AddShot( const std::string & buffer, const spIUMCNode & node2 ) {
        if(buffer.empty())
            THROW_BUFFER_CANT_BE_EMPTY;
        
		spIStructureNode parentNode = ParseRDF( buffer );
		const NamespacePropertyNamePair * pairs[2] = { &kClipShotsPair, &kTransitionShotsPair };
		size_t matchedIndex = GetMatchingIndexForActualNode( parentNode, &pairs[ 0 ], ( size_t ) 2 );

		switch ( matchedIndex ) {
		case 0:
			return AddClipShot( parentNode, node2 );
		case 1:
			return AddTransitionShot( parentNode, node2 );
		default:
			THROW_PARSING_ERROR;
		}
		return spIShot();
		
	}

	UMC::spIClipShot TrackImpl::AddClipShot( const spIUMCNode & node ) {
		spIClipShot shot = CreateClipShot( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator );
		CreateEquivalentXMPNodes( mXMPStructureNode, mClipShots, kClipShotsPair, mShots, kShotsPair );
		AddElementToMap( mClipShotMap, shot, node, mClipShots );
		return shot;
	}

	UMC::spIClipShot TrackImpl::AddClipShot( const std::string & buffer, const spIUMCNode & node ) {
        if(buffer.empty())
            THROW_BUFFER_CANT_BE_EMPTY;
		spIStructureNode xmpNode = ParseRDF( buffer );
		return AddClipShot( xmpNode, node );
	}

	UMC::spIClipShot TrackImpl::AddClipShot( const spIStructureNode & node, const spIUMCNode & node2 ) {
		auto actualNode = TryToGetActualNode( node, kClipShotsPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIClipShot shot = CreateClipShot( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, actualNode );
		CreateEquivalentXMPNodes( mXMPStructureNode, mClipShots, kClipShotsPair, mShots, kShotsPair );
		AddElementToMap( mClipShotMap, shot, node2, mClipShots );
		shot->GetInternalNode()->SyncXMPToUMC();
		return shot;
	}

	UMC::spITransitionShot TrackImpl::AddTransitionShot( const spIUMCNode & node ) {
		spITransitionShot shot = CreateTransitionShot( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator );
		CreateEquivalentXMPNodes( mXMPStructureNode, mTransitionShots, kTransitionShotsPair, mShots, kShotsPair );
		AddElementToMap( mTransitionShotMap, shot, node, mTransitionShots );
		return shot;
	}

	UMC::spITransitionShot TrackImpl::AddTransitionShot( const std::string & buffer, const spIUMCNode & node ) {
        if(buffer.empty())
            THROW_BUFFER_CANT_BE_EMPTY;
        
		spIStructureNode xmpNode = ParseRDF( buffer );
		return AddTransitionShot( xmpNode, node );
	}

	UMC::spITransitionShot TrackImpl::AddTransitionShot( const spIStructureNode & node, const spIUMCNode & node2 ) {
		auto actualNode = TryToGetActualNode( node, kTransitionShotsPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spITransitionShot shot = CreateTransitionShot( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, actualNode );
		CreateEquivalentXMPNodes( mXMPStructureNode, mTransitionShots, kTransitionShotsPair, mShots, kShotsPair );
		AddElementToMap( mTransitionShotMap, shot, node2, mTransitionShots );
		shot->GetInternalNode()->SyncXMPToUMC();
		return shot;
	}

	bool TrackImpl::ValidateXMPNode() const {
		return true;
	}

	void TrackImpl::SetName( const std::string & name ) {
		mName = name;
	}

	std::string TrackImpl::GetName() const {
		return mName;
	}

	size_t TrackImpl::ShotCount() const {
		return mClipShotMap.size() + mTransitionShotMap.size();
	}

	ITrack::ShotList TrackImpl::GetAllShots() {
		ITrack::ShotList list;
		AppendToListFromMap< spIShot, ClipShotMap >( list, mClipShotMap );
		AppendToListFromMap< spIShot, TransitionShotMap >( list, mTransitionShotMap );
		return list;

	}

	ITrack::cShotList TrackImpl::GetAllShots() const {
		ITrack::cShotList list;
		AppendToListFromMap< spcIShot, ClipShotMap >( list, mClipShotMap );
		AppendToListFromMap< spcIShot, TransitionShotMap >( list, mTransitionShotMap );
		return list;
	}

	UMC::spIShot TrackImpl::GetShot( const std::string & uniqueID ) {
		spIShot shot = GetClipShot( uniqueID );
		if ( shot ) return shot;
		shot = GetTransitionShot( uniqueID );
		return shot;
	}

	UMC::spcIShot TrackImpl::GetShot( const std::string & uniqueID ) const {
		return const_cast< TrackImpl *>( this )->GetShot( uniqueID );
	}

	size_t TrackImpl::ClipShotCount() const {
		return mClipShotMap.size();
	}

	ITrack::ClipShotList TrackImpl::GetAllClipShots() {
		return CreateListFromMap< spIClipShot >( mClipShotMap );
	}

	ITrack::cClipShotList TrackImpl::GetAllClipShots() const {
		return CreateListFromMap< spcIClipShot >( mClipShotMap );
	}

	UMC::spIClipShot TrackImpl::GetClipShot( const std::string & uniqueID ) {
		return GetElementFromMap< spIClipShot >( mClipShotMap, uniqueID );
	}

	UMC::spcIClipShot TrackImpl::GetClipShot( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIClipShot >( mClipShotMap, uniqueID );
	}

	size_t TrackImpl::TransitionShotCount() const {
		return mTransitionShotMap.size();
	}

	ITrack::TransitionShotList TrackImpl::GetAllTransitionShots() {
		return CreateListFromMap< spITransitionShot >( mTransitionShotMap );
	}

	ITrack::cTransitionShotList TrackImpl::GetAllTransitionShots() const {
		return CreateListFromMap< spcITransitionShot >( mTransitionShotMap );
	}

	UMC::spITransitionShot TrackImpl::GetTransitionShot( const std::string & uniqueID ) {
		return GetElementFromMap< spITransitionShot >( mTransitionShotMap, uniqueID );
	}

	UMC::spcITransitionShot TrackImpl::GetTransitionShot( const std::string & uniqueID ) const {
		return GetElementFromMap< spcITransitionShot >( mTransitionShotMap, uniqueID );
	}

	size_t TrackImpl::RemoveAllShots() {
		bool safeToClear( false );
		safeToClear = SafeToClearMap( mClipShotMap );
		if ( safeToClear ) SafeToClearMap( mTransitionShotMap ); else THROW_NODE_IS_REFERENCED("remove" );
		if ( safeToClear ) {
			size_t expectedCount = ShotCount();
			size_t count( 0 );
			count += ClearMap( mClipShotMap, mClipShots );
			count += ClearMap( mTransitionShotMap,mTransitionShots );
			assert( expectedCount == count );
			return count;
		} else {
			THROW_NODE_IS_REFERENCED( "remove" );
		}
		return 0;
	}

	size_t TrackImpl::RemoveAllClipShots() {
		if ( SafeToClearMap( mClipShotMap ) ) {
			return ClearMap( mClipShotMap, mClipShots );
		} else {
			THROW_NODE_IS_REFERENCED( "remove" );
		}
		return 0;
	}

	size_t TrackImpl::RemoveAllTransitionShots() {
		if ( SafeToClearMap( mTransitionShotMap ) ) {
			return ClearMap( mTransitionShotMap,mTransitionShots );
		} else {
			THROW_NODE_IS_REFERENCED( "remove" );
		}
		return 0;
	}

	size_t TrackImpl::RemoveShot( const std::string & uniqueID ) {
		size_t count = TryAndRemoveElementFromMap( mClipShotMap, uniqueID, mClipShots );
		if ( count > 0 ) return count;
		count = TryAndRemoveElementFromMap( mTransitionShotMap, uniqueID, mTransitionShots );
		return count;
	}

	size_t TrackImpl::RemoveClipShot( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mClipShotMap, uniqueID, mClipShots );
	}

	size_t TrackImpl::RemoveTransitionShot( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mTransitionShotMap, uniqueID, mTransitionShots );
	}

	UMC::spcIUMCNode TrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return const_cast< TrackImpl * >( this )->GetDecendantNode( uniqueID );
	}

	UMC::spIUMCNode TrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		auto node = GetChildNode( uniqueID );
		if ( node ) return node;
		node = GetDecendantFromMap( mClipShotMap, uniqueID );
		if ( node ) return node;
		node = GetDecendantFromMap( mTransitionShotMap, uniqueID );
		return node;
	}

	UMC::spcIUMCNode TrackImpl::GetChildNode( const std::string & uniqueID ) const {
		return GetShot( uniqueID );
	}

	UMC::spIUMCNode TrackImpl::GetChildNode( const std::string & uniqueID ) {
		return GetShot( uniqueID );
	}

	IUMCNode::NodeList TrackImpl::GetAllChildren() {
		IUMCNode::NodeList list;
		AppendToListFromMap< spIUMCNode, ClipShotMap >( list, mClipShotMap );
		AppendToListFromMap< spIUMCNode, TransitionShotMap >( list, mTransitionShotMap );
		return list;
	}

	IUMCNode::cNodeList TrackImpl::GetAllChildren() const {
		IUMCNode::cNodeList list;
		AppendToListFromMap< spcIUMCNode, ClipShotMap >( list, mClipShotMap );
		AppendToListFromMap< spcIUMCNode, TransitionShotMap >( list, mTransitionShotMap );
		return list;
	}

	IUMCNode::NodeList TrackImpl::GetAllDecendants() {
		IUMCNode::NodeList list;
		AppendDecendantsFromMapToList< spIUMCNode >( list, mClipShotMap );
		AppendDecendantsFromMapToList< spIUMCNode >( list, mTransitionShotMap );
		return list;
	}

	IUMCNode::cNodeList TrackImpl::GetAllDecendants() const {
		IUMCNode::cNodeList list;
		AppendDecendantsFromMapToList< spcIUMCNode >( list, mClipShotMap );
		AppendDecendantsFromMapToList< spcIUMCNode >( list, mTransitionShotMap );
		return list;
	}

}
