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
		: TrackImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, ITrack::kTrackTypeVideo )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 1 ) {}

	VideoTrackImpl::VideoTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
		: TrackImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, ITrack::kTrackTypeVideo, node )
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
		return TrackImpl::AddClipShot( shared_from_this() );
	}

	UMC::spIClipShot VideoTrackImpl::AddClipShot( const std::string & buffer ) {
		return TrackImpl::AddClipShot( buffer, shared_from_this() );
	}

	spITransitionShot VideoTrackImpl::AddTransitionShot() {
		return TrackImpl::AddTransitionShot( shared_from_this() );
	}

	UMC::spITransitionShot VideoTrackImpl::AddTransitionShot( const std::string & buffer ) {
		return TrackImpl::AddTransitionShot( buffer, shared_from_this() );
	}

	void VideoTrackImpl::SetName( const std::string & uniqueID ) {
		return TrackImpl::SetName( uniqueID );
	}

	std::string VideoTrackImpl::GetName() const {
		return TrackImpl::GetName();
	}

	size_t VideoTrackImpl::ShotCount() const {
		return TrackImpl::ShotCount();
	}

	ITrack::ShotList VideoTrackImpl::GetAllShots() {
		return TrackImpl::GetAllShots();
	}

	ITrack::cShotList VideoTrackImpl::GetAllShots() const {
		return TrackImpl::GetAllShots();
	}

	spIShot VideoTrackImpl::GetShot( const std::string & uniqueID ) {
		return TrackImpl::GetShot( uniqueID );
	}

	spcIShot VideoTrackImpl::GetShot( const std::string & uniqueID ) const {
		return TrackImpl::GetShot( uniqueID );
	}

	size_t VideoTrackImpl::ClipShotCount() const {
		return TrackImpl::ClipShotCount();
	}

	ITrack::ClipShotList VideoTrackImpl::GetAllClipShots() {
		return TrackImpl::GetAllClipShots();
	}

	ITrack::cClipShotList VideoTrackImpl::GetAllClipShots() const {
		return TrackImpl::GetAllClipShots();
	}

	spIClipShot VideoTrackImpl::GetClipShot( const std::string & uniqueID ) {
		return TrackImpl::GetClipShot( uniqueID );
	}

	spcIClipShot VideoTrackImpl::GetClipShot( const std::string & uniqueID ) const {
		return TrackImpl::GetClipShot( uniqueID );
	}

	size_t VideoTrackImpl::TransitionShotCount() const {
		return TrackImpl::TransitionShotCount();
	}

	ITrack::TransitionShotList VideoTrackImpl::GetAllTransitionShots() {
		return TrackImpl::GetAllTransitionShots();
	}

	ITrack::cTransitionShotList VideoTrackImpl::GetAllTransitionShots() const {
		return TrackImpl::GetAllTransitionShots();
	}

	spITransitionShot VideoTrackImpl::GetTransitionShot( const std::string & uniqueID ) {
		return TrackImpl::GetTransitionShot( uniqueID );
	}

	spcITransitionShot VideoTrackImpl::GetTransitionShot( const std::string & uniqueID ) const {
		return TrackImpl::GetTransitionShot( uniqueID );
	}

	size_t VideoTrackImpl::RemoveAllShots() {
		return TrackImpl::RemoveAllShots();
	}

	size_t VideoTrackImpl::RemoveAllClipShots() {
		return TrackImpl::RemoveAllClipShots();
	}

	size_t VideoTrackImpl::RemoveAllTransitionShots() {
		return TrackImpl::RemoveAllTransitionShots();
	}

	size_t VideoTrackImpl::RemoveShot( const std::string & uniqueID ) {
		return TrackImpl::RemoveShot( uniqueID );
	}

	size_t VideoTrackImpl::RemoveClipShot( const std::string & uniqueID ) {
		return TrackImpl::RemoveClipShot( uniqueID );
	}

	size_t VideoTrackImpl::RemoveTransitionShot( const std::string & uniqueID ) {
		return TrackImpl::RemoveTransitionShot( uniqueID );
	}

	INode::eNodeTypes VideoTrackImpl::GetNodeType() const {
		return TrackImpl::GetNodeType();
	}

	const std::string & VideoTrackImpl::GetUniqueID() const {
		return TrackImpl::GetUniqueID();
	}

	wpcINode VideoTrackImpl::GetParentNode() const {
		return TrackImpl::GetParentNode();
	}

	wpINode VideoTrackImpl::GetParentNode() {
		return TrackImpl::GetParentNode();
	}

	spcINode VideoTrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return TrackImpl::GetDecendantNode( uniqueID );
	}

	spINode VideoTrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		return TrackImpl::GetDecendantNode( uniqueID );
	}

	spcINode VideoTrackImpl::GetChildNode( const std::string & uniqueID ) const {
		return TrackImpl::GetChildNode( uniqueID );
	}

	spINode VideoTrackImpl::GetChildNode( const std::string & uniqueID ) {
		return TrackImpl::GetChildNode( uniqueID );
	}

	INode::NodeList VideoTrackImpl::GetAllChildren() {
		return TrackImpl::GetAllChildren();
	}

	INode::cNodeList VideoTrackImpl::GetAllChildren() const {
		return TrackImpl::GetAllChildren();
	}

	INode::NodeList VideoTrackImpl::GetAllDecendants() {
		return TrackImpl::GetAllDecendants();
	}

	INode::cNodeList VideoTrackImpl::GetAllDecendants() const {
		return TrackImpl::GetAllDecendants();
	}

	size_t VideoTrackImpl::GetReferenceCount() const {
		return TrackImpl::GetReferenceCount();
	}

	std::string VideoTrackImpl::Serialize() const {
		return TrackImpl::SerializeXMP();
	}

	pcINodeI VideoTrackImpl::GetInternalNode() const {
		return this;
	}

	pINodeI VideoTrackImpl::GetInternalNode() {
		return this;
	}

	void VideoTrackImpl::CleanUpOnRemovalFromDOM() {
		TrackImpl::CleanUpOnRemovalFromDOM();
	}

	void VideoTrackImpl::SetUpOnAdditionToDOM() {
		TrackImpl::SetUpOnAdditionToDOM();
	}

	void VideoTrackImpl::SyncInternalStuffToXMP() const {
		TrackImpl::SyncInternalStuffToXMP();
		AddOrUpdateDataToXMPDOM( mVideoEditRate, kVideoEditRatePair, mXMPStructureNode );
		AddOrUpdateDataToXMPDOM( mAudioEditRate, kAudioEditRatePair, mXMPStructureNode );
	}

	void VideoTrackImpl::SyncXMPToInternalStuff() {
		TrackImpl::SyncXMPToInternalStuff( shared_from_this() );
		UpdateDataFromXMPDOM( mVideoEditRate, kVideoEditRatePair, mXMPStructureNode, stou64rt );
		UpdateDataFromXMPDOM( mAudioEditRate, kAudioEditRatePair, mXMPStructureNode, stou64rt );
	}

	NS_XMPCORE::spIXMPStructureNode VideoTrackImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool VideoTrackImpl::ValidateXMPNode() const {
		if ( TrackImpl::ValidateXMPNode() )
			return true;
		return false;
	}

	UMC::pINode VideoTrackImpl::GetNode() {
		return this;
	}

	UMC::pcINode VideoTrackImpl::GetNode() const {
		return this;
	}

	UMC::spIShot VideoTrackImpl::AddShot( const std::string & buffer ) {
		return TrackImpl::AddShot( buffer, shared_from_this() );
	}

	bool VideoTrackImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return TrackImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	spcICustomData VideoTrackImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return TrackImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spICustomData VideoTrackImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return TrackImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spIVideoTrack CreateVideoTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
	{
		if ( node ) {
			auto retValue = std::make_shared< VideoTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
			retValue->SyncXMPToUMC();
			return retValue;
		} else {
			return std::make_shared< VideoTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}

}
