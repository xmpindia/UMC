// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/ClipShotImpl.h"
#include "interfaces/IShotSource.h"
#include "interfaces/IFrame.h"
#include "utils/Utils.h"

namespace INT_UMC {

	ClipShotImpl::ClipShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: ShotImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator ) { }

	ClipShotImpl::ClipShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
		: ShotImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, node ) { }

	IShot::eShotTypes ClipShotImpl::GetType() const {
		return IShot::kShotTypeClip;
	}

	IUMCNode::eNodeTypes ClipShotImpl::GetNodeType() const {
		return IUMCNode::kNodeTypeShot;
	}

	const std::string & ClipShotImpl::GetUniqueID() const {
		return ShotImpl::GetUniqueID();
	}

	std::string ClipShotImpl::GetParsedID() const {
		return ShotImpl::GetParsedID();
	}

	UMC::wpcIUMCNode ClipShotImpl::GetParentNode() const {
		return ShotImpl::GetParentNode();
	}

	UMC::wpIUMCNode ClipShotImpl::GetParentNode() {
		return ShotImpl::GetParentNode();
	}

	UMC::spcIUMCNode ClipShotImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return ShotImpl::GetDecendantNode( uniqueID );
	}

	UMC::spIUMCNode ClipShotImpl::GetDecendantNode( const std::string & uniqueID ) {
		return ShotImpl::GetDecendantNode( uniqueID );
	}

	UMC::spcIUMCNode ClipShotImpl::GetChildNode( const std::string & uniqueID ) const {
		return ShotImpl::GetChildNode( uniqueID );
	}

	UMC::spIUMCNode ClipShotImpl::GetChildNode( const std::string & uniqueID ) {
		return ShotImpl::GetChildNode( uniqueID );
	}

	IUMCNode::NodeList ClipShotImpl::GetAllChildren() {
		return ShotImpl::GetAllChildren();
	}

	IUMCNode::cNodeList ClipShotImpl::GetAllChildren() const {
		return ShotImpl::GetAllChildren();
	}

	IUMCNode::NodeList ClipShotImpl::GetAllDecendants() {
		return ShotImpl::GetAllDecendants();
	}

	IUMCNode::cNodeList ClipShotImpl::GetAllDecendants() const {
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

	INT_UMC::pIUMCNodeI ClipShotImpl::GetInternalNode() {
		return this;
	}

	INT_UMC::pcIUMCNodeI ClipShotImpl::GetInternalNode() const {
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

	UMC::pIUMCNode ClipShotImpl::GetNode() {
		return this;
	}

	UMC::pcIUMCNode ClipShotImpl::GetNode() const {
		return this;
	}

	INT_UMC::spIStructureNode ClipShotImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	ClipShotImpl::~ClipShotImpl() { }

	bool ClipShotImpl::SetUniqueID( const std::string & uniqueID ) {
		return NodeImpl::SetUniqueID( uniqueID );
	}

	bool ClipShotImpl::ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) {
		switch ( childNode->GetNodeType() ) {
		case IUMCNode::kNodeTypeFrame:
		{
			spIFrame frameChild = ConvertNode< IFrame >( childNode );
			ChangeUniqueIDOfChildNode< IFrame >( mFrameMap, frameChild, newUniqueID, mFrames, shared_from_this() );
			return true;
		}
		break;

		case IUMCNode::kNodeTypeShotSource:
		{
			spIShotSource shotSourceChild = ConvertNode< IShotSource >( childNode );
			ChangeUniqueIDOfChildNode< IShotSource >( mShotSourceMap, shotSourceChild, newUniqueID, mShotSources, shared_from_this() );
			return true;
		}
		break;

		default:
			return false;
		}
		return false;
	}

	UMC::spIUMCNode ClipShotImpl::GetExternalNode() {
		return shared_from_this();
	}

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
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< ClipShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		} else {
			return std::make_shared< ClipShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}

}

