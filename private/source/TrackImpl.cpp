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
#include "utils/Utils.h"


namespace INT_UMC {

	const std::string & TrackImpl::GetUniqueID() const {
		return mUniqueID;
	}


	spIShot TrackImpl::AddClipShot() {
		throw std::logic_error( "The method or operation is not implemented." );
		return spIShot();
	}

	spIShot TrackImpl::AddTransitionShot() {
		throw std::logic_error( "The method or operation is not implemented." );
		return spIShot();
	}

	void TrackImpl::SetName( const std::string & uniqueID ) {
		mName = uniqueID;
	}

	spIShot TrackImpl::GetShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented." );
		return spIShot();
	}

	UMC::spcIShot TrackImpl::GetShot( const std::string & uniqueID ) const {
		throw std::logic_error( "The method or operation is not implemented." );
		return spIShot();
	}

	size_t TrackImpl::ClipShotCount() const {
		throw std::logic_error( "The method or operation is not implemented." );
		return 0;
	}

	ITrack::ShotList TrackImpl::GetAllClipShots() {
		throw std::logic_error( "The method or operation is not implemented." );
		return ITrack::ShotList();
	}

	ITrack::cShotList TrackImpl::GetAllClipShots() const {
		throw std::logic_error( "The method or operation is not implemented." );
		return cShotList();
	}

	spIShot TrackImpl::GetClipShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented." );
		return spIShot();
	}

	spcIShot TrackImpl::GetClipShot( const std::string & uniqueID ) const {
		throw std::logic_error( "The method or operation is not implemented." );
		return spIShot();
	}

	size_t TrackImpl::TransitionShotCount() const {
		throw std::logic_error( "The method or operation is not implemented." );
		return 0;
	}

	ITrack::ShotList TrackImpl::GetAllTransitionShots() {
		throw std::logic_error( "The method or operation is not implemented." );
		return ShotList();
	}

	ITrack::cShotList TrackImpl::GetAllTransitionShots() const {
		throw std::logic_error( "The method or operation is not implemented." );
		return cShotList();
	}

	spIShot TrackImpl::GetTransitionShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented." );
		return spIShot();
	}

	spcIShot TrackImpl::GetTransitionShot( const std::string & uniqueID ) const {
		throw std::logic_error( "The method or operation is not implemented." );
		return spcIShot();
	}

	size_t TrackImpl::RemoveAllShots() {
		throw std::logic_error( "The method or operation is not implemented." );
		return 0;
	}

	size_t TrackImpl::RemoveAllClipShots() {
		throw std::logic_error( "The method or operation is not implemented." );
		return 0;
	}

	size_t TrackImpl::RemoveAllTransitionShots() {
		throw std::logic_error( "The method or operation is not implemented." );
		return 0;
	}

	size_t TrackImpl::RemoveShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented." );
		return 0;
	}

	size_t TrackImpl::RemoveClipShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented." );
		return 0;
	}

	size_t TrackImpl::RemoveTransitionShot( const std::string & uniqueID ) {
		throw std::logic_error( "The method or operation is not implemented." );
		return 0;
	}

	INode::eNodeTypes TrackImpl::GetNodeType() const {
		return INode::kNodeTypeTrack;
	}

	spcINode TrackImpl::GetParentNode() const {
		return spcINode( mwpOutput );
	}

	spINode TrackImpl::GetParentNode() {
		return spINode( mwpOutput );
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
		return mShotMap.size();
	}

	ITrack::ShotList TrackImpl::GetAllShots() {
		return CreateListFromMap< spIShot >( mShotMap );
	}

	ITrack::cShotList TrackImpl::GetAllShots() const {
		return CreateListFromMap< spcIShot >( mShotMap );
	}

	TrackImpl::TrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mUniqueID( uniqueIDGenerator->GenerateUniqueID( INode::kNodeTypeTrack ) )
		, mName()
		, mShotMap()
		, mspUniqueIDAndReferenceTracker( uniqueIDAndReferenceTracker )
		, mspUniqueIDGenerator( uniqueIDGenerator ) {}

	spcINode TrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return const_cast< TrackImpl * >( this )->GetDecendantNode( uniqueID );
	}

	spINode TrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		spINode node = GetChildNode( uniqueID );
		return node; /* TODO if ( node ) return node;
		node = GetDecendantFromMap< spINode >( mShotMap, uniqueID ); */
	}

	INode::NodeList TrackImpl::GetAllChildren() {
		throw std::logic_error( "The method or operation is not implemented." );
		return NodeList();
	}

	INode::cNodeList TrackImpl::GetAllChildren() const {
		throw std::logic_error( "The method or operation is not implemented." );
		return cNodeList();
	}

	INode::NodeList TrackImpl::GetAllDecendants() {
		throw std::logic_error( "The method or operation is not implemented." );
		return NodeList();
	}

	INode::cNodeList TrackImpl::GetAllDecendants() const {
		throw std::logic_error( "The method or operation is not implemented." );
		return cNodeList();
	}

	size_t TrackImpl::GetReferenceCount() const {
		return mspUniqueIDAndReferenceTracker->GetReferenceCount( mUniqueID );
	}

	void TrackImpl::RemoveFromDOM() {
		mspUniqueIDAndReferenceTracker->RemoveUniqueID( mUniqueID );
	}

	void TrackImpl::AddToDOM( const spINode & parent ) {
		mspUniqueIDAndReferenceTracker->AddUniqueID( mUniqueID );
		if ( !parent ) THROW_PARENT_CANT_BE_NULL;
		spIOutput outputParent = ConvertNode< IOutput >( parent );
		if ( !outputParent ) THROW_PARENT_CANT_BE_NULL;
		mwpOutput = outputParent;
	}

	ITrack::eTrackTypes TrackImpl::GetType() const {
		return ITrack::kTrackTypeAll;
	}

}
