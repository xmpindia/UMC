// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/AudioTrackImpl.h"

namespace INT_UMC {

	AudioTrackImpl::AudioTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mTrack( CreateTrack( uniqueIDAndReferenceTracker, uniqueIDGenerator ) )
		, mAudioEditRate( 1 ) {}

	void AudioTrackImpl::SetAudioEditRate( const EditRate & editRate ) {
		mAudioEditRate = editRate;
	}

	EditRate AudioTrackImpl::GetAudioEditRate() const {
		return mAudioEditRate;
	}

	ITrack::eTrackTypes AudioTrackImpl::GetType() const {
		return ITrack::kTrackTypeAudio;
	}

	spIShot AudioTrackImpl::AddClipShot() {
		return mTrack->AddClipShot();
	}

	spIShot AudioTrackImpl::AddTransitionShot() {
		return mTrack->AddTransitionShot();
	}

	void AudioTrackImpl::SetName( const std::string & uniqueID ) {
		return mTrack->SetName( uniqueID );
	}

	std::string AudioTrackImpl::GetName() const {
		return mTrack->GetName();
	}

	size_t AudioTrackImpl::ShotCount() const {
		return mTrack->ShotCount();
	}

	ITrack::ShotList AudioTrackImpl::GetAllShots() {
		return mTrack->GetAllShots();
	}

	ITrack::cShotList AudioTrackImpl::GetAllShots() const {
		return const_pointer_cast< const ITrack >( mTrack )->GetAllShots();
	}

	spIShot AudioTrackImpl::GetShot( const std::string & uniqueID ) {
		return mTrack->GetShot( uniqueID );
	}

	spcIShot AudioTrackImpl::GetShot( const std::string & uniqueID ) const {
		return mTrack->GetShot( uniqueID );
	}

	size_t AudioTrackImpl::ClipShotCount() const {
		return mTrack->ClipShotCount();
	}

	ITrack::ShotList AudioTrackImpl::GetAllClipShots() {
		return mTrack->GetAllClipShots();
	}

	ITrack::cShotList AudioTrackImpl::GetAllClipShots() const {
		return const_pointer_cast< const ITrack >( mTrack )->GetAllClipShots();
	}

	spIShot AudioTrackImpl::GetClipShot( const std::string & uniqueID ) {
		return mTrack->GetClipShot( uniqueID );
	}

	spcIShot AudioTrackImpl::GetClipShot( const std::string & uniqueID ) const {
		return mTrack->GetClipShot( uniqueID );
	}

	size_t AudioTrackImpl::TransitionShotCount() const {
		return mTrack->TransitionShotCount();
	}

	ITrack::ShotList AudioTrackImpl::GetAllTransitionShots() {
		return mTrack->GetAllTransitionShots();
	}

	ITrack::cShotList AudioTrackImpl::GetAllTransitionShots() const {
		return const_pointer_cast< const ITrack >( mTrack )->GetAllTransitionShots();
	}

	spIShot AudioTrackImpl::GetTransitionShot( const std::string & uniqueID ) {
		return mTrack->GetTransitionShot( uniqueID );
	}

	spcIShot AudioTrackImpl::GetTransitionShot( const std::string & uniqueID ) const {
		return mTrack->GetTransitionShot( uniqueID );
	}

	size_t AudioTrackImpl::RemoveAllShots() {
		return mTrack->RemoveAllShots();
	}

	size_t AudioTrackImpl::RemoveAllClipShots() {
		return mTrack->RemoveAllClipShots();
	}

	size_t AudioTrackImpl::RemoveAllTransitionShots() {
		return mTrack->RemoveAllTransitionShots();
	}

	size_t AudioTrackImpl::RemoveShot( const std::string & uniqueID ) {
		return mTrack->RemoveShot( uniqueID );
	}

	size_t AudioTrackImpl::RemoveClipShot( const std::string & uniqueID ) {
		return mTrack->RemoveClipShot( uniqueID );
	}

	size_t AudioTrackImpl::RemoveTransitionShot( const std::string & uniqueID ) {
		return mTrack->RemoveTransitionShot( uniqueID );
	}




	INode::eNodeTypes AudioTrackImpl::GetNodeType() const {
		return mTrack->GetNodeType();
	}

	const std::string & AudioTrackImpl::GetUniqueID() const {
		return mTrack->GetUniqueID();
	}

	wpcINode AudioTrackImpl::GetParentNode() const {
		return mTrack->GetParentNode();
	}

	wpINode AudioTrackImpl::GetParentNode() {
		return mTrack->GetParentNode();
	}

	spcINode AudioTrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return mTrack->GetDecendantNode( uniqueID );
	}

	spINode AudioTrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		return mTrack->GetDecendantNode( uniqueID );
	}

	spcINode AudioTrackImpl::GetChildNode( const std::string & uniqueID ) const {
		return mTrack->GetChildNode( uniqueID );
	}

	spINode AudioTrackImpl::GetChildNode( const std::string & uniqueID ) {
		return mTrack->GetChildNode( uniqueID );
	}

	INode::NodeList AudioTrackImpl::GetAllChildren() {
		return mTrack->GetAllChildren();
	}

	INode::cNodeList AudioTrackImpl::GetAllChildren() const {
		return const_pointer_cast< const ITrack >( mTrack )->GetAllChildren();
	}

	INode::NodeList AudioTrackImpl::GetAllDecendants() {
		return mTrack->GetAllDecendants();
	}

	INode::cNodeList AudioTrackImpl::GetAllDecendants() const {
		return const_pointer_cast< const ITrack >( mTrack )->GetAllDecendants();
	}

	size_t AudioTrackImpl::GetReferenceCount() const {
		return mTrack->GetReferenceCount();
	}

	pcINodeI AudioTrackImpl::GetInternalNode() const {
		return mTrack->GetInternalNode();
	}

	pINodeI AudioTrackImpl::GetInternalNode() {
		return mTrack->GetInternalNode();
	}

	bool AudioTrackImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mTrack->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	spcICustomData AudioTrackImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mTrack->GetCustomData( customDataNameSpace, customDataName );
	}

	spICustomData AudioTrackImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mTrack->GetCustomData( customDataNameSpace, customDataName );
	}





	spIAudioTrack CreateAudioTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
	const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< AudioTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}
