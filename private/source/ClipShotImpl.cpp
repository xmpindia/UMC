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
		: mShot( CreateShot( uniqueIDAndReferenceTracker, uniqueIDGenerator ) ) {}

	const std::string & ClipShotImpl::GetUniqueID() const {
		return mShot->GetUniqueID();
	}

	IShot::eShotTypes ClipShotImpl::GetType() const {
		return IShot::kShotTypeClip;
	}

	void ClipShotImpl::SetInCount( const EditUnitInCount & inCount ) {
		mShot->SetInCount( inCount );
	}

	EditUnitInCount ClipShotImpl::GetInCount() const {
		return mShot->GetInCount();
	}

	void ClipShotImpl::SetDuration( const EditUnitDuration & duration ) {
		mShot->SetDuration( duration );
	}

	EditUnitDuration ClipShotImpl::GetDuration() const {
		return mShot->GetDuration();
	}

	spIFrame ClipShotImpl::AddFrame()
	{
		return mShot->AddFrame();
	}

	size_t ClipShotImpl::FrameCount() const {
		return mShot->FrameCount();
	}

	IShot::FrameList ClipShotImpl::GetFrames() {
		return mShot->GetFrames();
	}

	IShot::cFrameList ClipShotImpl::GetFrames() const {
		return const_pointer_cast< const IShot >( mShot )->GetFrames();
	}

	spIShotSource ClipShotImpl::AddShotSource()
	{
		return mShot->AddShotSource();
	}

	size_t ClipShotImpl::ShotSourceCount() const {
		return mShot->ShotSourceCount();
	}

	IShot::ShotSourceList ClipShotImpl::GetShotSources() {
		return mShot->GetShotSources();
	}

	IShot::cShotSourceList ClipShotImpl::GetShotSources() const {
		return const_pointer_cast< const IShot >( mShot )->GetShotSources();
	}

	spIShotSource ClipShotImpl::GetShotSource( const std::string & uniqueID ) {
		return mShot->GetShotSource( uniqueID );
	}

	spcIShotSource ClipShotImpl::GetShotSource( const std::string & uniqueID ) const {
		return const_pointer_cast< const IShot >( mShot )->GetShotSource( uniqueID );
	}

	wpcINode ClipShotImpl::GetParentNode() const {
		return mShot->GetParentNode();
	}

	wpINode ClipShotImpl::GetParentNode() {
		return mShot->GetParentNode();
	}

	INode::eNodeTypes ClipShotImpl::GetNodeType() const {
		return mShot->GetNodeType();
	}

	spcINode ClipShotImpl::GetDecendantNode( const std::string & id ) const {
		return mShot->GetDecendantNode( id );
	}

	spINode ClipShotImpl::GetDecendantNode( const std::string & id ) {
		return mShot->GetDecendantNode( id );
	}

	spcINode ClipShotImpl::GetChildNode( const std::string & id ) const {
		return mShot->GetChildNode( id );
	}

	spINode ClipShotImpl::GetChildNode( const std::string & id ) {
		return mShot->GetChildNode( id );
	}

	INode::NodeList ClipShotImpl::GetAllChildren() {
		return mShot->GetAllChildren();
	}

	INode::cNodeList ClipShotImpl::GetAllChildren() const {
		return const_pointer_cast< const IShot >( mShot )->GetAllChildren();
	}

	INode::NodeList ClipShotImpl::GetAllDecendants() {
		return mShot->GetAllDecendants();
	}

	INode::cNodeList ClipShotImpl::GetAllDecendants() const {
		return const_pointer_cast< const IShot >( mShot )->GetAllDecendants();
	}

	size_t ClipShotImpl::GetReferenceCount() const {
		return mShot->GetReferenceCount();
	}

	spICustomData ClipShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mShot->GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData ClipShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mShot->GetCustomData( customDataNameSpace, customDataName );
	}

	bool ClipShotImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mShot->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pINodeI ClipShotImpl::GetInternalNode() {
		return mShot->GetInternalNode();
	}

	pcINodeI ClipShotImpl::GetInternalNode() const {
		return mShot->GetInternalNode();
	}

	spIClipShot CreateClipShot( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< ClipShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}

