// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/TrackImpl.h"
#include "implHeaders/ShotImpl.h"
#include "interfaces/IOutput.h"
#include "interfaces/IUniqueIDGenerator.h"
#include "interfaces/IUMC.h"

#include "utils/Utils.h"

namespace INT_UMC {

	const std::string & TrackImpl::GetUniqueID() const {
		return mNode->GetUniqueID();
	}

	spIClipShot TrackImpl::AddClipShot() {
		spIClipShot shot = CreateClipShot( GetUniqueIDAndReferenceTracker(), GetUniqueIDGenerator() );
		AddElementToMap( mClipShotMap, shot, shared_from_this() );
		return shot;
	}

	spITransitionShot TrackImpl::AddTransitionShot() {
		spITransitionShot shot = CreateTransitionShot( GetUniqueIDAndReferenceTracker(), GetUniqueIDGenerator() );
		AddElementToMap( mTransitionShotMap, shot, shared_from_this() );
		return shot;
	}

	void TrackImpl::SetName( const std::string & uniqueID ) {
		mName = uniqueID;
	}

	spIShot TrackImpl::GetShot( const std::string & uniqueID ) {
		spIShot shot = GetClipShot( uniqueID );
		if ( shot ) return shot;
		shot = GetTransitionShot( uniqueID );
		return shot;
	}

	spcIShot TrackImpl::GetShot( const std::string & uniqueID ) const {
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

	spIClipShot TrackImpl::GetClipShot( const std::string & uniqueID ) {
		return GetElementFromMap< spIClipShot >( mClipShotMap, uniqueID );
	}

	spcIClipShot TrackImpl::GetClipShot( const std::string & uniqueID ) const {
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

	spITransitionShot TrackImpl::GetTransitionShot( const std::string & uniqueID ) {
		return GetElementFromMap< spITransitionShot >( mTransitionShotMap, uniqueID );
	}

	spcITransitionShot TrackImpl::GetTransitionShot( const std::string & uniqueID ) const {
		return GetElementFromMap< spcITransitionShot >( mTransitionShotMap, uniqueID );
	}

	size_t TrackImpl::RemoveAllShots() {
		bool safeToClear( false );
		safeToClear = SafeToClearMap( mClipShotMap );
		if ( safeToClear ) SafeToClearMap( mTransitionShotMap ); else return 0;
		if ( safeToClear ) {
			size_t expectedCount = ShotCount();
			size_t count( 0 );
			count += ClearMap( mClipShotMap );
			count += ClearMap( mTransitionShotMap );
			assert( expectedCount == count );
			return count;
		}
		return 0;
	}

	size_t TrackImpl::RemoveAllClipShots() {
		if ( SafeToClearMap( mClipShotMap ) ) {
			return ClearMap( mClipShotMap );
		}
		return 0;
	}

	size_t TrackImpl::RemoveAllTransitionShots() {
		if ( SafeToClearMap( mTransitionShotMap ) ) {
			return ClearMap( mTransitionShotMap );
		}
		return 0;
	}

	size_t TrackImpl::RemoveShot( const std::string & uniqueID ) {
		size_t count = RemoveClipShot( uniqueID );
		if ( count > 0 ) return count;
		count = RemoveTransitionShot( uniqueID );
		return count;
	}

	size_t TrackImpl::RemoveClipShot( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mClipShotMap, uniqueID );
	}

	size_t TrackImpl::RemoveTransitionShot( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mTransitionShotMap, uniqueID );
	}

	// INODEI

	INode::eNodeTypes TrackImpl::GetNodeType() const {
		return INode::kNodeTypeTrack;
	}

	wpcINode TrackImpl::GetParentNode() const {
		return mNode->GetParentNode();
	}

	wpINode TrackImpl::GetParentNode() {
		return mNode->GetParentNode();
	}

	spcINode TrackImpl::GetChildNode( const std::string & uniqueID ) const {
		return const_cast< TrackImpl * >( this )->GetChildNode( uniqueID );
	}

	spINode TrackImpl::GetChildNode( const std::string & uniqueID ) {
		return GetShot( uniqueID );
	}

	std::string TrackImpl::GetName() const {
		return mName;
	}

	size_t TrackImpl::ShotCount() const {
		return mClipShotMap.size() + mTransitionShotMap.size();
	}

	ITrack::ShotList TrackImpl::GetAllShots() {
		ShotList list;
		AppendToListFromMap< spIShot, ClipShotMap >( list, mClipShotMap );
		AppendToListFromMap< spIShot, TransitionShotMap >( list, mTransitionShotMap );
		return list;
	}

	ITrack::cShotList TrackImpl::GetAllShots() const {
		cShotList list;
		AppendToListFromMap< spcIShot, ClipShotMap >( list, mClipShotMap );
		AppendToListFromMap< spcIShot, TransitionShotMap >( list, mTransitionShotMap );
		return list;
	}

	TrackImpl::TrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mNode( CreateNode( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeTrack ) )
		, mName()
		, mClipShotMap()
		, mTransitionShotMap() { }

	spcINode TrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return const_cast< TrackImpl * >( this )->GetDecendantNode( uniqueID );
	}

	spINode TrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		auto node = GetChildNode( uniqueID );
		if ( node ) return node;
		node = GetDecendantFromMap( mClipShotMap, uniqueID );
		if ( node ) return node;
		node = GetDecendantFromMap( mTransitionShotMap, uniqueID );
		return node;
	}

	INode::NodeList TrackImpl::GetAllChildren() {
		NodeList list;
		AppendToListFromMap< spINode, ClipShotMap >( list, mClipShotMap );
		AppendToListFromMap< spINode, TransitionShotMap >( list, mTransitionShotMap );
		return list;
	}

	INode::cNodeList TrackImpl::GetAllChildren() const {
		cNodeList list;
		AppendToListFromMap< spcINode, ClipShotMap >( list, mClipShotMap );
		AppendToListFromMap< spcINode, TransitionShotMap >( list, mTransitionShotMap );
		return list;
	}

	INode::NodeList TrackImpl::GetAllDecendants() {
		NodeList list;
		AppendDecendantsFromMapToList< spINode >( list, mClipShotMap );
		AppendDecendantsFromMapToList< spINode >( list, mTransitionShotMap );
		return list;
	}

	INode::cNodeList TrackImpl::GetAllDecendants() const {
		cNodeList list;
		AppendDecendantsFromMapToList< spcINode >( list, mClipShotMap );
		AppendDecendantsFromMapToList< spcINode >( list, mTransitionShotMap );
		return list;
	}

	size_t TrackImpl::GetReferenceCount() const {
		return mNode->GetReferenceCount();
	}

	void TrackImpl::RemoveFromDOM() {
		ClearMap( mClipShotMap );
		ClearMap( mTransitionShotMap );
		mNode->GetInternalNode()->RemoveFromDOM();
	}

	void TrackImpl::AddToDOM( const spINode & parent ) {
		mNode->GetInternalNode()->AddToDOM( parent );
	}

	spICustomData TrackImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData TrackImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}

	bool TrackImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mNode->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pINodeI TrackImpl::GetInternalNode() {
		return this;
	}

	pcINodeI TrackImpl::GetInternalNode() const {
		return this;
	}

	void TrackImpl::SetExtensionNode( const spIXMPStructureNode & structureNode ) {
		return mNode->GetInternalNode()->SetExtensionNode( structureNode );
	}

	NS_XMPCORE::spIXMPStructureNode TrackImpl::GetExtensionNode(bool create /*= false */) const {
		return mNode->GetInternalNode()->GetExtensionNode( create );
	}

	NS_XMPCORE::spIXMPStructureNode TrackImpl::GetMergedExtensionNode() const {
		return mNode->GetInternalNode()->GetMergedExtensionNode();
	}

	spIUniqueIDAndReferenceTracker TrackImpl::GetUniqueIDAndReferenceTracker() {
		return mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker();
	}

	spcIUniqueIDAndReferenceTracker TrackImpl::GetUniqueIDAndReferenceTracker() const {
		return mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker();
	}

	spIUniqueIDGenerator TrackImpl::GetUniqueIDGenerator() {
		return mNode->GetInternalNode()->GetUniqueIDGenerator();
	}

	spcIUniqueIDGenerator TrackImpl::GetUniqueIDGenerator() const {
		return mNode->GetInternalNode()->GetUniqueIDGenerator();
	}

	ITrack::eTrackTypes TrackImpl::GetType() const {
		return ITrack::kTrackTypeAll;
	}

	spITrack CreateTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< TrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}
