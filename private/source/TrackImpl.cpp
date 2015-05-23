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
		throw std::logic_error( "The method or operation is not implemented.2" );
		return spIShot();
	}

	spcIShot TrackImpl::GetShot( const std::string & uniqueID ) const {
		throw std::logic_error( "The method or operation is not implemented.3" );
		return spIShot();
	}

	size_t TrackImpl::ClipShotCount() const {
		throw std::logic_error( "The method or operation is not implemented.4" );
		return 0;
	}

	ITrack::ShotList TrackImpl::GetAllClipShots() {
		throw std::logic_error( "The method or operation is not implemented.5" );
		return ITrack::ShotList();
	}

	ITrack::cShotList TrackImpl::GetAllClipShots() const {
		throw std::logic_error( "The method or operation is not implemented.6" );
		return cShotList();
	}

	spIShot TrackImpl::GetClipShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented.7" );
		return spIShot();
	}

	spcIShot TrackImpl::GetClipShot( const std::string & uniqueID ) const {
		throw std::logic_error( "The method or operation is not implemented.8" );
		return spIShot();
	}

	size_t TrackImpl::TransitionShotCount() const {
		throw std::logic_error( "The method or operation is not implemented9." );
		return 0;
	}

	ITrack::ShotList TrackImpl::GetAllTransitionShots() {
		throw std::logic_error( "The method or operation is not implemented10." );
		return ShotList();
	}

	ITrack::cShotList TrackImpl::GetAllTransitionShots() const {
		throw std::logic_error( "The method or operation is not implemented11." );
		return cShotList();
	}

	spIShot TrackImpl::GetTransitionShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented12." );
		return spIShot();
	}

	spcIShot TrackImpl::GetTransitionShot( const std::string & uniqueID ) const {
		throw std::logic_error( "The method or operation is not implemented13." );
		return spcIShot();
	}

	size_t TrackImpl::RemoveAllShots() {
		throw std::logic_error( "The method or operation is not implemented14." );
		return 0;
	}

	size_t TrackImpl::RemoveAllClipShots() {
		throw std::logic_error( "The method or operation is not implemented15." );
		return 0;
	}

	size_t TrackImpl::RemoveAllTransitionShots() {
		throw std::logic_error( "The method or operation is not implemented16." );
		return 0;
	}

	size_t TrackImpl::RemoveShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented17." );
		return 0;
	}

	size_t TrackImpl::RemoveClipShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented18." );
		return 0;
	}

	size_t TrackImpl::RemoveTransitionShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented.19" );
		return 0;
	}

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
		spINode node;/*TODO = GetElementFromMap< spINode > ( mShotMap, uniqueID ); */
		return node;
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
		spINode node = GetChildNode( uniqueID );
		return node; /* TODO if ( node ) return node;
		node = GetDecendantFromMap< spINode >( mShotMap, uniqueID ); */
	}

	INode::NodeList TrackImpl::GetAllChildren() {
		throw std::logic_error( "The method or operation is not implemented.20" );
		return NodeList();
	}

	INode::cNodeList TrackImpl::GetAllChildren() const {
		//throw std::logic_error( "The method or operation is not implemented.21" );
		return cNodeList();
	}

	INode::NodeList TrackImpl::GetAllDecendants() {
		throw std::logic_error( "The method or operation is not implemented.22" );
		return NodeList();
	}

	INode::cNodeList TrackImpl::GetAllDecendants() const {
		throw std::logic_error( "The method or operation is not implemented.23" );
		return cNodeList();
	}

	size_t TrackImpl::GetReferenceCount() const {
		return mNode->GetReferenceCount();
	}

	void TrackImpl::RemoveFromDOM() {
		//ClearMap( mShotMap );
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
