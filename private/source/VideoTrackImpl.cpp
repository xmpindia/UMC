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

	VideoTrackImpl::VideoTrackImpl( const std::string & uniqueID, const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIOutput & parent )
		: mTrackImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator )
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

	spIShot VideoTrackImpl::AddClipShot() {
		return mTrackImpl.AddClipShot();
	}

	spIShot VideoTrackImpl::AddTransitionShot() {
		return mTrackImpl.AddTransitionShot();
	}

	void VideoTrackImpl::SetName( const std::string & uniqueID ) {
		return mTrackImpl.SetName( uniqueID );
	}

	std::string VideoTrackImpl::GetName() const {
		return mTrackImpl.GetName();
	}

	size_t VideoTrackImpl::ShotCount() const {
		return mTrackImpl.ShotCount();
	}

	ITrack::ShotList VideoTrackImpl::GetAllShots() {
		return mTrackImpl.GetAllShots();
	}

	ITrack::cShotList VideoTrackImpl::GetAllShots() const {
		return mTrackImpl.GetAllShots();
	}

	spIShot VideoTrackImpl::GetShot( const std::string & uniqueID ) {
		return mTrackImpl.GetShot( uniqueID );
	}

	spcIShot VideoTrackImpl::GetShot( const std::string & uniqueID ) const {
		return mTrackImpl.GetShot( uniqueID );
	}

	size_t VideoTrackImpl::ClipShotCount() const {
		return mTrackImpl.ClipShotCount();
	}

	ITrack::ShotList VideoTrackImpl::GetAllClipShots() {
		return mTrackImpl.GetAllClipShots();
	}

	ITrack::cShotList VideoTrackImpl::GetAllClipShots() const {
		return mTrackImpl.GetAllClipShots();
	}

	spIShot VideoTrackImpl::GetClipShot( const std::string & uniqueID ) {
		return mTrackImpl.GetClipShot( uniqueID );
	}

	spcIShot VideoTrackImpl::GetClipShot( const std::string & uniqueID ) const {
		return mTrackImpl.GetClipShot( uniqueID );
	}

	size_t VideoTrackImpl::TransitionShotCount() const {
		return mTrackImpl.TransitionShotCount();
	}

	ITrack::ShotList VideoTrackImpl::GetAllTransitionShots() {
		return mTrackImpl.GetAllTransitionShots();
	}

	ITrack::cShotList VideoTrackImpl::GetAllTransitionShots() const {
		return mTrackImpl.GetAllTransitionShots();
	}

	spIShot VideoTrackImpl::GetTransitionShot( const std::string & uniqueID ) {
		return mTrackImpl.GetTransitionShot( uniqueID );
	}

	spcIShot VideoTrackImpl::GetTransitionShot( const std::string & uniqueID ) const {
		return mTrackImpl.GetTransitionShot( uniqueID );
	}

	size_t VideoTrackImpl::RemoveAllShots() {
		return mTrackImpl.RemoveAllShots();
	}

	size_t VideoTrackImpl::RemoveAllClipShots() {
		return mTrackImpl.RemoveAllClipShots();
	}

	size_t VideoTrackImpl::RemoveAllTransitionShots() {
		return mTrackImpl.RemoveAllTransitionShots();
	}

	size_t VideoTrackImpl::RemoveShot( const std::string & uniqueID ) {
		return mTrackImpl.RemoveShot( uniqueID );
	}

	size_t VideoTrackImpl::RemoveClipShot( const std::string & uniqueID ) {
		return mTrackImpl.RemoveClipShot( uniqueID );
	}

	size_t VideoTrackImpl::RemoveTransitionShot( const std::string & uniqueID ) {
		return mTrackImpl.RemoveTransitionShot( uniqueID );
	}

	INode::eNodeTypes VideoTrackImpl::GetNodeType() const {
		return mTrackImpl.GetNodeType();
	}

	const std::string & VideoTrackImpl::GetUniqueID() const {
		return mTrackImpl.GetUniqueID();
	}

	wpcINode VideoTrackImpl::GetParentNode() const {
		return mTrackImpl.GetParentNode();
	}

	wpINode VideoTrackImpl::GetParentNode() {
		return mTrackImpl.GetParentNode();
	}

	spcINode VideoTrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return mTrackImpl.GetDecendantNode( uniqueID );
	}

	spINode VideoTrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		return mTrackImpl.GetDecendantNode( uniqueID );
	}

	spcINode VideoTrackImpl::GetChildNode( const std::string & uniqueID ) const {
		return mTrackImpl.GetChildNode( uniqueID );
	}

	spINode VideoTrackImpl::GetChildNode( const std::string & uniqueID ) {
		return mTrackImpl.GetChildNode( uniqueID );
	}

	spIVideoTrack CreateVideoTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return spIVideoTrack(); //std::make_shared< VideoTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}
