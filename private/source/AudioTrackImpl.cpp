// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/AudioTrackImpl.h"
#include "utils/UMCAndXMPMapping.h"

namespace INT_UMC {

	AudioTrackImpl::AudioTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: TrackImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, ITrack::kTrackTypeAudio, kAudioTracksPair )
		, mAudioEditRate( 1 ) {}

	AudioTrackImpl::AudioTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
		: TrackImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, ITrack::kTrackTypeAudio, node )
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

	spIClipShot AudioTrackImpl::AddClipShot() {
		return TrackImpl::AddClipShot( shared_from_this() );
	}

	UMC::spIClipShot AudioTrackImpl::AddClipShot( const std::string & buffer ) {
		return TrackImpl::AddClipShot( buffer, shared_from_this() );
	}

	spITransitionShot AudioTrackImpl::AddTransitionShot() {
		return TrackImpl::AddTransitionShot( shared_from_this() );
	}

	UMC::spITransitionShot AudioTrackImpl::AddTransitionShot( const std::string & buffer ) {
		return TrackImpl::AddTransitionShot( buffer, shared_from_this() );
	}

	void AudioTrackImpl::SetName( const std::string & uniqueID ) {
		return TrackImpl::SetName( uniqueID );
	}

	std::string AudioTrackImpl::GetName() const {
		return TrackImpl::GetName();
	}

	size_t AudioTrackImpl::ShotCount() const {
		return TrackImpl::ShotCount();
	}

	ITrack::ShotList AudioTrackImpl::GetAllShots() {
		return TrackImpl::GetAllShots();
	}

	ITrack::cShotList AudioTrackImpl::GetAllShots() const {
		return TrackImpl::GetAllShots();
	}

	spIShot AudioTrackImpl::GetShot( const std::string & uniqueID ) {
		return TrackImpl::GetShot( uniqueID );
	}

	spcIShot AudioTrackImpl::GetShot( const std::string & uniqueID ) const {
		return TrackImpl::GetShot( uniqueID );
	}

	size_t AudioTrackImpl::ClipShotCount() const {
		return TrackImpl::ClipShotCount();
	}

	ITrack::ClipShotList AudioTrackImpl::GetAllClipShots() {
		return TrackImpl::GetAllClipShots();
	}

	ITrack::cClipShotList AudioTrackImpl::GetAllClipShots() const {
		return TrackImpl::GetAllClipShots();
	}

	spIClipShot AudioTrackImpl::GetClipShot( const std::string & uniqueID ) {
		return TrackImpl::GetClipShot( uniqueID );
	}

	spcIClipShot AudioTrackImpl::GetClipShot( const std::string & uniqueID ) const {
		return TrackImpl::GetClipShot( uniqueID );
	}

	size_t AudioTrackImpl::TransitionShotCount() const {
		return TrackImpl::TransitionShotCount();
	}

	ITrack::TransitionShotList AudioTrackImpl::GetAllTransitionShots() {
		return TrackImpl::GetAllTransitionShots();
	}

	ITrack::cTransitionShotList AudioTrackImpl::GetAllTransitionShots() const {
		return TrackImpl::GetAllTransitionShots();
	}

	spITransitionShot AudioTrackImpl::GetTransitionShot( const std::string & uniqueID ) {
		return TrackImpl::GetTransitionShot( uniqueID );
	}

	spcITransitionShot AudioTrackImpl::GetTransitionShot( const std::string & uniqueID ) const {
		return TrackImpl::GetTransitionShot( uniqueID );
	}

	size_t AudioTrackImpl::RemoveAllShots() {
		return TrackImpl::RemoveAllShots();
	}

	size_t AudioTrackImpl::RemoveAllClipShots() {
		return TrackImpl::RemoveAllClipShots();
	}

	size_t AudioTrackImpl::RemoveAllTransitionShots() {
		return TrackImpl::RemoveAllTransitionShots();
	}

	size_t AudioTrackImpl::RemoveShot( const std::string & uniqueID ) {
		return TrackImpl::RemoveShot( uniqueID );
	}

	size_t AudioTrackImpl::RemoveClipShot( const std::string & uniqueID ) {
		return TrackImpl::RemoveClipShot( uniqueID );
	}

	size_t AudioTrackImpl::RemoveTransitionShot( const std::string & uniqueID ) {
		return TrackImpl::RemoveTransitionShot( uniqueID );
	}

	INode::eNodeTypes AudioTrackImpl::GetNodeType() const {
		return TrackImpl::GetNodeType();
	}

	const std::string & AudioTrackImpl::GetUniqueID() const {
		return TrackImpl::GetUniqueID();
	}

	wpcINode AudioTrackImpl::GetParentNode() const {
		return TrackImpl::GetParentNode();
	}

	wpINode AudioTrackImpl::GetParentNode() {
		return TrackImpl::GetParentNode();
	}

	spcINode AudioTrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return TrackImpl::GetDecendantNode( uniqueID );
	}

	spINode AudioTrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		return TrackImpl::GetDecendantNode( uniqueID );
	}

	spcINode AudioTrackImpl::GetChildNode( const std::string & uniqueID ) const {
		return TrackImpl::GetChildNode( uniqueID );
	}

	spINode AudioTrackImpl::GetChildNode( const std::string & uniqueID ) {
		return TrackImpl::GetChildNode( uniqueID );
	}

	INode::NodeList AudioTrackImpl::GetAllChildren() {
		return TrackImpl::GetAllChildren();
	}

	INode::cNodeList AudioTrackImpl::GetAllChildren() const {
		return TrackImpl::GetAllChildren();
	}

	INode::NodeList AudioTrackImpl::GetAllDecendants() {
		return TrackImpl::GetAllDecendants();
	}

	INode::cNodeList AudioTrackImpl::GetAllDecendants() const {
		return TrackImpl::GetAllDecendants();
	}

	size_t AudioTrackImpl::GetReferenceCount() const {
		return TrackImpl::GetReferenceCount();
	}

	std::string AudioTrackImpl::Serialize() const {
		return TrackImpl::SerializeXMP();
	}

	pcINodeI AudioTrackImpl::GetInternalNode() const {
		return this;
	}

	pINodeI AudioTrackImpl::GetInternalNode() {
		return this;
	}

	void AudioTrackImpl::CleanUpOnRemovalFromDOM() { }

	void AudioTrackImpl::SetUpOnAdditionToDOM() { }

	void AudioTrackImpl::SyncInternalStuffToXMP() const {
		TrackImpl::SyncInternalStuffToXMP();
		AddOrUpdateDataToXMPDOM( mAudioEditRate, kAudioEditRatePair, mXMPStructureNode );
	}

	void AudioTrackImpl::SyncXMPToInternalStuff() {
		TrackImpl::SyncXMPToInternalStuff( shared_from_this() );
		UpdateDataFromXMPDOM( mAudioEditRate, kAudioEditRatePair, mXMPStructureNode, stou64rt );
	}

	INT_UMC::spIXMPStructureNode AudioTrackImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool AudioTrackImpl::ValidateXMPNode() const {
		if ( TrackImpl::ValidateXMPNode() )
			return true;
		return false;
	}

	UMC::pINode AudioTrackImpl::GetNode() {
		return this;
	}

	UMC::pcINode AudioTrackImpl::GetNode() const {
		return this;
	}

	UMC::spIShot AudioTrackImpl::AddShot( const std::string & buffer ) {
		return TrackImpl::AddShot( buffer, shared_from_this() );
	}

	bool AudioTrackImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return TrackImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	spcICustomData AudioTrackImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return TrackImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spICustomData AudioTrackImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return TrackImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spIAudioTrack CreateAudioTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
	{
		if ( node ) {
			auto retValue = std::make_shared< AudioTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
			retValue->SyncXMPToUMC();
			return retValue;
		} else {
			return std::make_shared< AudioTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}

}
