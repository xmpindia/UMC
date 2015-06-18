// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/ClipShotImpl.h"

namespace INT_UMC {

	ClipShotImpl::ClipShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: ShotImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator ) { }

	ClipShotImpl::ClipShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
		: ShotImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, node ) { }

	IShot::eShotTypes ClipShotImpl::GetType() const {
		return IShot::kShotTypeClip;
	}

	INode::eNodeTypes ClipShotImpl::GetNodeType() const {
		return INode::kNodeTypeShot;
	}

	const std::string & ClipShotImpl::GetUniqueID() const {
		return ShotImpl::GetUniqueID();
	}

	UMC::wpcINode ClipShotImpl::GetParentNode() const {
		return ShotImpl::GetParentNode();
	}

	UMC::wpINode ClipShotImpl::GetParentNode() {
		return ShotImpl::GetParentNode();
	}

	UMC::spcINode ClipShotImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return ShotImpl::GetDecendantNode( uniqueID );
	}

	UMC::spINode ClipShotImpl::GetDecendantNode( const std::string & uniqueID ) {
		return ShotImpl::GetDecendantNode( uniqueID );
	}

	UMC::spcINode ClipShotImpl::GetChildNode( const std::string & uniqueID ) const {
		return ShotImpl::GetChildNode( uniqueID );
	}

	UMC::spINode ClipShotImpl::GetChildNode( const std::string & uniqueID ) {
		return ShotImpl::GetChildNode( uniqueID );
	}

	INode::NodeList ClipShotImpl::GetAllChildren() {
		return ShotImpl::GetAllChildren();
	}

	INode::cNodeList ClipShotImpl::GetAllChildren() const {
		return ShotImpl::GetAllChildren();
	}

	INode::NodeList ClipShotImpl::GetAllDecendants() {
		return ShotImpl::GetAllDecendants();
	}

	INode::cNodeList ClipShotImpl::GetAllDecendants() const {
		return ShotImpl::GetAllDecendants();
	}

	size_t ClipShotImpl::GetReferenceCount() const {
		return ShotImpl::GetReferenceCount();
	}

	std::string ClipShotImpl::Serialize() const {
		return ShotImpl::SerializeXMP();
	}

	UMC::spICustomData ClipShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return ShotImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	UMC::spcICustomData ClipShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return ShotImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	bool ClipShotImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return ShotImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	INT_UMC::pINodeI ClipShotImpl::GetInternalNode() {
		return this;
	}

	INT_UMC::pcINodeI ClipShotImpl::GetInternalNode() const {
		return this;
	}

	void ClipShotImpl::CleanUpOnRemovalFromDOM() {
		ShotImpl::CleanUpOnRemovalFromDOM();
	}

	void ClipShotImpl::SetUpOnAdditionToDOM() {
		ShotImpl::SetUpOnAdditionToDOM();
	}

	void ClipShotImpl::SyncXMPToInternalStuff() {
		ShotImpl::SyncXMPToInternalStuff( shared_from_this() );
	}

	void ClipShotImpl::SyncInternalStuffToXMP() const {
		ShotImpl::SyncInternalStuffToXMP();
	}

	UMC::pINode ClipShotImpl::GetNode() {
		return this;
	}

	UMC::pcINode ClipShotImpl::GetNode() const {
		return this;
	}

	INT_UMC::spIXMPStructureNode ClipShotImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	ClipShotImpl::~ClipShotImpl() { }

	size_t ClipShotImpl::RemoveShotSource( const std::string & uniqueID ) {
		return ShotImpl::RemoveShotSource( uniqueID );
	}

	size_t ClipShotImpl::RemoveFrame( const std::string & uniqueID ) {
		return ShotImpl::RemoveFrame( uniqueID );
	}

	size_t ClipShotImpl::RemoveAllFrames() {
		return ShotImpl::RemoveAllFrames();
	}

	size_t ClipShotImpl::RemoveAllShotSources() {
		return ShotImpl::RemoveAllFrames();
	}

	UMC::spcIShotSource ClipShotImpl::GetShotSource( const std::string & uniqueID ) const {
		return ShotImpl::GetShotSource( uniqueID );
	}

	UMC::spIShotSource ClipShotImpl::GetShotSource( const std::string & uniqueID ) {
		return ShotImpl::GetShotSource( uniqueID );
	}

	IShot::cShotSourceList ClipShotImpl::GetAllShotSources() const {
		return ShotImpl::GetAllShotSources();
	}

	IShot::ShotSourceList ClipShotImpl::GetAllShotSources() {
		return ShotImpl::GetAllShotSources();
	}

	size_t ClipShotImpl::ShotSourceCount() const {
		return ShotImpl::ShotSourceCount();
	}

	UMC::spcIFrame ClipShotImpl::GetFrame( const std::string & uniqueID ) const {
		return ShotImpl::GetFrame( uniqueID );
	}

	UMC::spIFrame ClipShotImpl::GetFrame( const std::string & uniqueID ) {
		return ShotImpl::GetFrame( uniqueID );
	}

	IShot::cFrameList ClipShotImpl::GetAllFrames() const {
		return ShotImpl::GetAllFrames();
	}

	IShot::FrameList ClipShotImpl::GetAllFrames() {
		return ShotImpl::GetAllFrames();
	}

	size_t ClipShotImpl::FrameCount() const {
		return ShotImpl::FrameCount();
	}

	UMC::spIShotSource ClipShotImpl::AddShotSource( const std::string & buffer ) {
		return ShotImpl::AddShotSource( buffer, shared_from_this() );
	}

	UMC::spIShotSource ClipShotImpl::AddShotSource( const spISource & source ) {
		return ShotImpl::AddShotSource( source, shared_from_this() );
	}

	UMC::spIFrame ClipShotImpl::AddFrame( const std::string & buffer ) {
		return ShotImpl::AddFrame( buffer, shared_from_this() );
	}

	UMC::spIFrame ClipShotImpl::AddFrame( const spISource & source ) {
		return ShotImpl::AddFrame( source, shared_from_this() );
	}

	UMC::EditUnitDuration ClipShotImpl::GetDuration() const {
		return ShotImpl::GetDuration();
	}

	void ClipShotImpl::SetDuration( const EditUnitDuration & duration ) {
		return ShotImpl::SetDuration( duration );
	}

	UMC::EditUnitInCount ClipShotImpl::GetInCount() const {
		return ShotImpl::GetInCount();
	}

	void ClipShotImpl::SetInCount( const EditUnitInCount & inCount ) {
		return ShotImpl::SetInCount( inCount );
	}


	spIClipShot CreateClipShot( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< ClipShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		} else {
			return std::make_shared< ClipShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}

}

