// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/TransitionShotImpl.h"

namespace INT_UMC {

	TransitionShotImpl::TransitionShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: ShotImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator ) { }

	TransitionShotImpl::TransitionShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
		: ShotImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, node ) { }

	IShot::eShotTypes TransitionShotImpl::GetType() const {
		return IShot::kShotTypeClip;
	}

	INode::eNodeTypes TransitionShotImpl::GetNodeType() const {
		return INode::kNodeTypeShot;
	}

	const std::string & TransitionShotImpl::GetUniqueID() const {
		return ShotImpl::GetUniqueID();
	}

	UMC::wpcINode TransitionShotImpl::GetParentNode() const {
		return ShotImpl::GetParentNode();
	}

	UMC::wpINode TransitionShotImpl::GetParentNode() {
		return ShotImpl::GetParentNode();
	}

	UMC::spcINode TransitionShotImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return ShotImpl::GetDecendantNode( uniqueID );
	}

	UMC::spINode TransitionShotImpl::GetDecendantNode( const std::string & uniqueID ) {
		return ShotImpl::GetDecendantNode( uniqueID );
	}

	UMC::spcINode TransitionShotImpl::GetChildNode( const std::string & uniqueID ) const {
		return ShotImpl::GetChildNode( uniqueID );
	}

	UMC::spINode TransitionShotImpl::GetChildNode( const std::string & uniqueID ) {
		return ShotImpl::GetChildNode( uniqueID );
	}

	INode::NodeList TransitionShotImpl::GetAllChildren() {
		return ShotImpl::GetAllChildren();
	}

	INode::cNodeList TransitionShotImpl::GetAllChildren() const {
		return ShotImpl::GetAllChildren();
	}

	INode::NodeList TransitionShotImpl::GetAllDecendants() {
		return ShotImpl::GetAllDecendants();
	}

	INode::cNodeList TransitionShotImpl::GetAllDecendants() const {
		return ShotImpl::GetAllDecendants();
	}

	size_t TransitionShotImpl::GetReferenceCount() const {
		return ShotImpl::GetReferenceCount();
	}

	std::string TransitionShotImpl::Serialize() const {
		return ShotImpl::SerializeXMP();
	}

	UMC::spICustomData TransitionShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return ShotImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	UMC::spcICustomData TransitionShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return ShotImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	bool TransitionShotImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return ShotImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	INT_UMC::pINodeI TransitionShotImpl::GetInternalNode() {
		return this;
	}

	INT_UMC::pcINodeI TransitionShotImpl::GetInternalNode() const {
		return this;
	}

	void TransitionShotImpl::CleanUpOnRemovalFromDOM() {
		ShotImpl::CleanUpOnRemovalFromDOM();
	}

	void TransitionShotImpl::SetUpOnAdditionToDOM() {
		ShotImpl::SetUpOnAdditionToDOM();
	}

	void TransitionShotImpl::SyncXMPToInternalStuff() {
		ShotImpl::SyncXMPToInternalStuff( shared_from_this() );
	}

	void TransitionShotImpl::SyncInternalStuffToXMP() const {
		ShotImpl::SyncInternalStuffToXMP();
	}

	UMC::pINode TransitionShotImpl::GetNode() {
		return this;
	}

	UMC::pcINode TransitionShotImpl::GetNode() const {
		return this;
	}

	INT_UMC::spIXMPStructureNode TransitionShotImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	TransitionShotImpl::~TransitionShotImpl() { }

	size_t TransitionShotImpl::RemoveShotSource( const std::string & uniqueID ) {
		return ShotImpl::RemoveShotSource( uniqueID );
	}

	size_t TransitionShotImpl::RemoveFrame( const std::string & uniqueID ) {
		return ShotImpl::RemoveFrame( uniqueID );
	}

	size_t TransitionShotImpl::RemoveAllFrames() {
		return ShotImpl::RemoveAllFrames();
	}

	size_t TransitionShotImpl::RemoveAllShotSources() {
		return ShotImpl::RemoveAllShotSources();
	}

	UMC::spcIShotSource TransitionShotImpl::GetShotSource( const std::string & uniqueID ) const {
		return ShotImpl::GetShotSource( uniqueID );
	}

	UMC::spIShotSource TransitionShotImpl::GetShotSource( const std::string & uniqueID ) {
		return ShotImpl::GetShotSource( uniqueID );
	}

	IShot::cShotSourceList TransitionShotImpl::GetAllShotSources() const {
		return ShotImpl::GetAllShotSources();
	}

	IShot::ShotSourceList TransitionShotImpl::GetAllShotSources() {
		return ShotImpl::GetAllShotSources();
	}

	size_t TransitionShotImpl::ShotSourceCount() const {
		return ShotImpl::ShotSourceCount();
	}

	UMC::spcIFrame TransitionShotImpl::GetFrame( const std::string & uniqueID ) const {
		return ShotImpl::GetFrame( uniqueID );
	}

	UMC::spIFrame TransitionShotImpl::GetFrame( const std::string & uniqueID ) {
		return ShotImpl::GetFrame( uniqueID );
	}

	IShot::cFrameList TransitionShotImpl::GetAllFrames() const {
		return ShotImpl::GetAllFrames();
	}

	IShot::FrameList TransitionShotImpl::GetAllFrames() {
		return ShotImpl::GetAllFrames();
	}

	size_t TransitionShotImpl::FrameCount() const {
		return ShotImpl::FrameCount();
	}

	UMC::spIShotSource TransitionShotImpl::AddShotSource( const std::string & buffer ) {
		return ShotImpl::AddShotSource( buffer, shared_from_this() );
	}

	UMC::spIShotSource TransitionShotImpl::AddShotSource( const spISource & source ) {
		return ShotImpl::AddShotSource( source, shared_from_this() );
	}

	UMC::spIFrame TransitionShotImpl::AddFrame( const std::string & buffer ) {
		return ShotImpl::AddFrame( buffer, shared_from_this() );
	}

	UMC::spIFrame TransitionShotImpl::AddFrame( const spISource & source ) {
		return ShotImpl::AddFrame( source, shared_from_this() );
	}

	UMC::EditUnitDuration TransitionShotImpl::GetDuration() const {
		return ShotImpl::GetDuration();
	}

	void TransitionShotImpl::SetDuration( const EditUnitDuration & duration ) {
		return ShotImpl::SetDuration( duration );
	}

	UMC::EditUnitInCount TransitionShotImpl::GetInCount() const {
		return ShotImpl::GetInCount();
	}

	void TransitionShotImpl::SetInCount( const EditUnitInCount & inCount ) {
		return ShotImpl::SetInCount( inCount );
	}

	spITransitionShot CreateTransitionShot( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
	{
		if ( node ) {
			auto retValue = std::make_shared< TransitionShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
			retValue->SyncXMPToUMC();
			return retValue;
		} else {
			return std::make_shared< TransitionShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}

}

