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

	AudioTrackImpl::AudioTrackImpl( const std::string & uniqueID, const spUniqueIDSet & uniqueIDSet,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIOutput & parent )
		: mTrackImpl( uniqueID, uniqueIDSet, uniqueIDGenerator, parent )
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
		return mTrackImpl.AddClipShot();
	}

	spIShot AudioTrackImpl::AddTransitionShot() {
		return mTrackImpl.AddTransitionShot();
	}

	void AudioTrackImpl::SetName( const std::string & uniqueID ) {
		return mTrackImpl.SetName( uniqueID );
	}

	std::string AudioTrackImpl::GetName() const {
		return mTrackImpl.GetName();
	}

	size_t AudioTrackImpl::ShotCount() const {
		return mTrackImpl.ShotCount();
	}

	ITrack::ShotList AudioTrackImpl::GetAllShots() {
		return mTrackImpl.GetAllShots();
	}

	ITrack::cShotList AudioTrackImpl::GetAllShots() const {
		return mTrackImpl.GetAllShots();
	}

	spIShot AudioTrackImpl::GetShot( const std::string & uniqueID ) {
		return mTrackImpl.GetShot( uniqueID );
	}

	spcIShot AudioTrackImpl::GetShot( const std::string & uniqueID ) const {
		return mTrackImpl.GetShot( uniqueID );
	}

	size_t AudioTrackImpl::ClipShotCount() const {
		return mTrackImpl.ClipShotCount();
	}

	ITrack::ShotList AudioTrackImpl::GetAllClipShots() {
		return mTrackImpl.GetAllClipShots();
	}

	ITrack::cShotList AudioTrackImpl::GetAllClipShots() const {
		return mTrackImpl.GetAllClipShots();
	}

	spIShot AudioTrackImpl::GetClipShot( const std::string & uniqueID ) {
		return mTrackImpl.GetClipShot( uniqueID );
	}

	spcIShot AudioTrackImpl::GetClipShot( const std::string & uniqueID ) const {
		return mTrackImpl.GetClipShot( uniqueID );
	}

	size_t AudioTrackImpl::TransitionShotCount() const {
		return mTrackImpl.TransitionShotCount();
	}

	ITrack::ShotList AudioTrackImpl::GetAllTransitionShots() {
		return mTrackImpl.GetAllTransitionShots();
	}

	ITrack::cShotList AudioTrackImpl::GetAllTransitionShots() const {
		return mTrackImpl.GetAllTransitionShots();
	}

	spIShot AudioTrackImpl::GetTransitionShot( const std::string & uniqueID ) {
		return mTrackImpl.GetTransitionShot( uniqueID );
	}

	spcIShot AudioTrackImpl::GetTransitionShot( const std::string & uniqueID ) const {
		return mTrackImpl.GetTransitionShot( uniqueID );
	}

	size_t AudioTrackImpl::RemoveAllShots() {
		return mTrackImpl.RemoveAllShots();
	}

	size_t AudioTrackImpl::RemoveAllClipShots() {
		return mTrackImpl.RemoveAllClipShots();
	}

	size_t AudioTrackImpl::RemoveAllTransitionShots() {
		return mTrackImpl.RemoveAllTransitionShots();
	}

	size_t AudioTrackImpl::RemoveShot( const std::string & uniqueID ) {
		return mTrackImpl.RemoveShot( uniqueID );
	}

	size_t AudioTrackImpl::RemoveClipShot( const std::string & uniqueID ) {
		return mTrackImpl.RemoveClipShot( uniqueID );
	}

	size_t AudioTrackImpl::RemoveTransitionShot( const std::string & uniqueID ) {
		return mTrackImpl.RemoveTransitionShot( uniqueID );
	}

	INode::eNodeTypes AudioTrackImpl::GetNodeType() const {
		return mTrackImpl.GetNodeType();
	}

	const std::string & AudioTrackImpl::GetUniqueID() const {
		return mTrackImpl.GetUniqueID();
	}

	spcINode AudioTrackImpl::GetParentNode() const {
		return mTrackImpl.GetParentNode();
	}

	spINode AudioTrackImpl::GetParentNode() {
		return mTrackImpl.GetParentNode();
	}

	spcINode AudioTrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return mTrackImpl.GetDecendantNode( uniqueID );
	}

	spINode AudioTrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		return mTrackImpl.GetDecendantNode( uniqueID );
	}

	spcINode AudioTrackImpl::GetChildNode( const std::string & uniqueID ) const {
		return mTrackImpl.GetChildNode( uniqueID );
	}

	spINode AudioTrackImpl::GetChildNode( const std::string & uniqueID ) {
		return mTrackImpl.GetChildNode( uniqueID );
	}

}
