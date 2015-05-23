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
		: mShot( CreateShot( uniqueIDAndReferenceTracker, uniqueIDGenerator ) ) {}

	const std::string & TransitionShotImpl::GetUniqueID() const {
		return mShot->GetUniqueID();
	}

	IShot::eShotTypes TransitionShotImpl::GetType() const {
		return IShot::kShotTypeTransition;
	}

	void TransitionShotImpl::SetInCount( const EditUnitInCount & inCount ) {
		mShot->SetInCount( inCount );
	}

	EditUnitInCount TransitionShotImpl::GetInCount() const {
		return mShot->GetInCount();
	}

	void TransitionShotImpl::SetDuration( const EditUnitDuration & duration ) {
		mShot->SetDuration( duration );
	}

	EditUnitDuration TransitionShotImpl::GetDuration() const {
		return mShot->GetDuration();
	}

	spIFrame TransitionShotImpl::AddFrame()
	{
		return mShot->AddFrame();
	}

	size_t TransitionShotImpl::FrameCount() const {
		return mShot->FrameCount();
	}

	IShot::FrameList TransitionShotImpl::GetFrames() {
		return mShot->GetFrames();
	}

	IShot::cFrameList TransitionShotImpl::GetFrames() const {
		return const_pointer_cast< const IShot >( mShot )->GetFrames();
	}

	spIShotSource TransitionShotImpl::AddShotSource()
	{
		return mShot->AddShotSource();
	}

	size_t TransitionShotImpl::ShotSourceCount() const {
		return mShot->ShotSourceCount();
	}

	IShot::ShotSourceList TransitionShotImpl::GetShotSources() {
		return mShot->GetShotSources();
	}

	IShot::cShotSourceList TransitionShotImpl::GetShotSources() const {
		return const_pointer_cast< const IShot >( mShot )->GetShotSources();
	}

	spIShotSource TransitionShotImpl::GetShotSource( const std::string & uniqueID ) {
		return mShot->GetShotSource( uniqueID );
	}

	spcIShotSource TransitionShotImpl::GetShotSource( const std::string & uniqueID ) const {
		return const_pointer_cast< const IShot >( mShot )->GetShotSource( uniqueID );
	}

	wpcINode TransitionShotImpl::GetParentNode() const {
		return mShot->GetParentNode();
	}

	wpINode TransitionShotImpl::GetParentNode() {
		return mShot->GetParentNode();
	}

	INode::eNodeTypes TransitionShotImpl::GetNodeType() const {
		return mShot->GetNodeType();
	}

	spcINode TransitionShotImpl::GetDecendantNode( const std::string & id ) const {
		return mShot->GetDecendantNode( id );
	}

	spINode TransitionShotImpl::GetDecendantNode( const std::string & id ) {
		return mShot->GetDecendantNode( id );
	}

	spcINode TransitionShotImpl::GetChildNode( const std::string & id ) const {
		return mShot->GetChildNode( id );
	}

	spINode TransitionShotImpl::GetChildNode( const std::string & id ) {
		return mShot->GetChildNode( id );
	}

	INode::NodeList TransitionShotImpl::GetAllChildren() {
		return mShot->GetAllChildren();
	}

	INode::cNodeList TransitionShotImpl::GetAllChildren() const {
		return const_pointer_cast< const IShot >( mShot )->GetAllChildren();
	}

	INode::NodeList TransitionShotImpl::GetAllDecendants() {
		return mShot->GetAllDecendants();
	}

	INode::cNodeList TransitionShotImpl::GetAllDecendants() const {
		return const_pointer_cast< const IShot >( mShot )->GetAllDecendants();
	}

	size_t TransitionShotImpl::GetReferenceCount() const {
		return mShot->GetReferenceCount();
	}

	spICustomData TransitionShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mShot->GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData TransitionShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mShot->GetCustomData( customDataNameSpace, customDataName );
	}

	bool TransitionShotImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mShot->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pINodeI TransitionShotImpl::GetInternalNode() {
		return mShot->GetInternalNode();
	}

	pcINodeI TransitionShotImpl::GetInternalNode() const {
		return mShot->GetInternalNode();
	}

	spITransitionShot CreateTransitionShot( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< TransitionShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}

