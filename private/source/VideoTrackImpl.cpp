// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/VideoTrackImpl.h"

namespace INT_UMC {

	VideoTrackImpl::VideoTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mTrack( CreateTrack( uniqueIDAndReferenceTracker, uniqueIDGenerator ) )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 1 ) {}

	void VideoTrackImpl::SetVideoEditRate( const EditRate & editRate ) {
		mVideoEditRate = editRate;
	}

	EditRate VideoTrackImpl::GetVideoEditRate() const {
		return mVideoEditRate;
	}

	void VideoTrackImpl::SetAudioEditRate( const EditRate & editRate ) {
		mAudioEditRate = editRate;
	}

	EditRate VideoTrackImpl::GetAudioEditRate() const {
		return mAudioEditRate;
	}

	ITrack::eTrackTypes VideoTrackImpl::GetType() const {
		return ITrack::kTrackTypeVideo;
	}

	spIClipShot VideoTrackImpl::AddClipShot() {
		return mTrack->AddClipShot();
	}

	spITransitionShot VideoTrackImpl::AddTransitionShot() {
		return mTrack->AddTransitionShot();
	}

	void VideoTrackImpl::SetName( const std::string & uniqueID ) {
		return mTrack->SetName( uniqueID );
	}

	std::string VideoTrackImpl::GetName() const {
		return mTrack->GetName();
	}

	size_t VideoTrackImpl::ShotCount() const {
		return mTrack->ShotCount();
	}

	ITrack::ShotList VideoTrackImpl::GetAllShots() {
		return mTrack->GetAllShots();
	}

	ITrack::cShotList VideoTrackImpl::GetAllShots() const {
		return const_pointer_cast< const ITrack >( mTrack )->GetAllShots();
	}

	spIShot VideoTrackImpl::GetShot( const std::string & uniqueID ) {
		return mTrack->GetShot( uniqueID );
	}

	spcIShot VideoTrackImpl::GetShot( const std::string & uniqueID ) const {
		return mTrack->GetShot( uniqueID );
	}

	size_t VideoTrackImpl::ClipShotCount() const {
		return mTrack->ClipShotCount();
	}

	ITrack::ClipShotList VideoTrackImpl::GetAllClipShots() {
		return mTrack->GetAllClipShots();
	}

	ITrack::cClipShotList VideoTrackImpl::GetAllClipShots() const {
		return const_pointer_cast< const ITrack >( mTrack )->GetAllClipShots();
	}

	spIClipShot VideoTrackImpl::GetClipShot( const std::string & uniqueID ) {
		return mTrack->GetClipShot( uniqueID );
	}

	spcIClipShot VideoTrackImpl::GetClipShot( const std::string & uniqueID ) const {
		return mTrack->GetClipShot( uniqueID );
	}

	size_t VideoTrackImpl::TransitionShotCount() const {
		return mTrack->TransitionShotCount();
	}

	ITrack::TransitionShotList VideoTrackImpl::GetAllTransitionShots() {
		return mTrack->GetAllTransitionShots();
	}

	ITrack::cTransitionShotList VideoTrackImpl::GetAllTransitionShots() const {
		return const_pointer_cast< const ITrack >( mTrack )->GetAllTransitionShots();
	}

	spITransitionShot VideoTrackImpl::GetTransitionShot( const std::string & uniqueID ) {
		return mTrack->GetTransitionShot( uniqueID );
	}

	spcITransitionShot VideoTrackImpl::GetTransitionShot( const std::string & uniqueID ) const {
		return mTrack->GetTransitionShot( uniqueID );
	}

	size_t VideoTrackImpl::RemoveAllShots() {
		return mTrack->RemoveAllShots();
	}

	size_t VideoTrackImpl::RemoveAllClipShots() {
		return mTrack->RemoveAllClipShots();
	}

	size_t VideoTrackImpl::RemoveAllTransitionShots() {
		return mTrack->RemoveAllTransitionShots();
	}

	size_t VideoTrackImpl::RemoveShot( const std::string & uniqueID ) {
		return mTrack->RemoveShot( uniqueID );
	}

	size_t VideoTrackImpl::RemoveClipShot( const std::string & uniqueID ) {
		return mTrack->RemoveClipShot( uniqueID );
	}

	size_t VideoTrackImpl::RemoveTransitionShot( const std::string & uniqueID ) {
		return mTrack->RemoveTransitionShot( uniqueID );
	}

	INode::eNodeTypes VideoTrackImpl::GetNodeType() const {
		return mTrack->GetNodeType();
	}

	const std::string & VideoTrackImpl::GetUniqueID() const {
		return mTrack->GetUniqueID();
	}

	wpcINode VideoTrackImpl::GetParentNode() const {
		return mTrack->GetParentNode();
	}

	wpINode VideoTrackImpl::GetParentNode() {
		return mTrack->GetParentNode();
	}

	spcINode VideoTrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return mTrack->GetDecendantNode( uniqueID );
	}

	spINode VideoTrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		return mTrack->GetDecendantNode( uniqueID );
	}

	spcINode VideoTrackImpl::GetChildNode( const std::string & uniqueID ) const {
		return mTrack->GetChildNode( uniqueID );
	}

	spINode VideoTrackImpl::GetChildNode( const std::string & uniqueID ) {
		return mTrack->GetChildNode( uniqueID );
	}

	INode::NodeList VideoTrackImpl::GetAllChildren() {
		return mTrack->GetAllChildren();
	}

	INode::cNodeList VideoTrackImpl::GetAllChildren() const {
		return const_pointer_cast< const ITrack >( mTrack )->GetAllChildren();
	}

	INode::NodeList VideoTrackImpl::GetAllDecendants() {
		return mTrack->GetAllDecendants();
	}

	INode::cNodeList VideoTrackImpl::GetAllDecendants() const {
		return const_pointer_cast< const ITrack >( mTrack )->GetAllDecendants();
	}

	size_t VideoTrackImpl::GetReferenceCount() const {
		return mTrack->GetReferenceCount();
	}

	pcINodeI VideoTrackImpl::GetInternalNode() const {
		return mTrack->GetInternalNode();
	}

	pINodeI VideoTrackImpl::GetInternalNode() {
		return mTrack->GetInternalNode();
	}

	bool VideoTrackImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mTrack->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	spcICustomData VideoTrackImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mTrack->GetCustomData( customDataNameSpace, customDataName );
	}

	spICustomData VideoTrackImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mTrack->GetCustomData( customDataNameSpace, customDataName );
	}

	spIVideoTrack CreateVideoTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< VideoTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}
