/*
*  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
*  This file is licensed to you under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License. You may obtain a copy
*  of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software distributed under
*  the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
*  OF ANY KIND, either express or implied. See the License for the specific language
*  governing permissions and limitations under the License.
*
*/


#include "implHeaders/AudioTrackImpl.h"
#include "utils/UMCAndXMPMapping.h"
#include "interfaces/IClipShot.h"
#include "interfaces/ITransitionShot.h"
#include "utils/Utils.h"

namespace INT_UMC {

	AudioTrackImpl::AudioTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: TrackImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, ITrack::kTrackTypeAudio, kAudioTracksPair )
		, mAudioEditRate( 1 ) {}

	AudioTrackImpl::AudioTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
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

	IUMCNode::eNodeTypes AudioTrackImpl::GetNodeType() const {
		return TrackImpl::GetNodeType();
	}

	const std::string & AudioTrackImpl::GetUniqueID() const {
		return TrackImpl::GetUniqueID();
	}

	std::string AudioTrackImpl::GetParsedID() const {
		return GetParsedID();
	}

	wpcIUMCNode AudioTrackImpl::GetParentNode() const {
		return TrackImpl::GetParentNode();
	}

	wpIUMCNode AudioTrackImpl::GetParentNode() {
		return TrackImpl::GetParentNode();
	}

	spcIUMCNode AudioTrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return TrackImpl::GetDecendantNode( uniqueID );
	}

	spIUMCNode AudioTrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		return TrackImpl::GetDecendantNode( uniqueID );
	}

	spcIUMCNode AudioTrackImpl::GetChildNode( const std::string & uniqueID ) const {
		return TrackImpl::GetChildNode( uniqueID );
	}

	spIUMCNode AudioTrackImpl::GetChildNode( const std::string & uniqueID ) {
		return TrackImpl::GetChildNode( uniqueID );
	}

	IUMCNode::NodeList AudioTrackImpl::GetAllChildren() {
		return TrackImpl::GetAllChildren();
	}

	IUMCNode::cNodeList AudioTrackImpl::GetAllChildren() const {
		return TrackImpl::GetAllChildren();
	}

	IUMCNode::NodeList AudioTrackImpl::GetAllDecendants() {
		return TrackImpl::GetAllDecendants();
	}

	IUMCNode::cNodeList AudioTrackImpl::GetAllDecendants() const {
		return TrackImpl::GetAllDecendants();
	}

	size_t AudioTrackImpl::GetReferenceCount() const {
		return TrackImpl::GetReferenceCount();
	}

	std::string AudioTrackImpl::Serialize() const {
		return TrackImpl::SerializeXMP();
	}

	pcIUMCNodeI AudioTrackImpl::GetInternalNode() const {
		return this;
	}

	pIUMCNodeI AudioTrackImpl::GetInternalNode() {
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

	INT_UMC::spIStructureNode AudioTrackImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool AudioTrackImpl::ValidateXMPNode() const {
		if ( TrackImpl::ValidateXMPNode() )
			return true;
		return false;
	}

	UMC::pIUMCNode AudioTrackImpl::GetNode() {
		return this;
	}

	UMC::pcIUMCNode AudioTrackImpl::GetNode() const {
		return this;
	}

	bool AudioTrackImpl::SetUniqueID( const std::string & uniqueID ) {
		return NodeImpl::SetUniqueID( uniqueID );
	}

	bool AudioTrackImpl::ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) {
		switch ( childNode->GetNodeType() ) {
		case IUMCNode::kNodeTypeShot:
		{
			spIShot shotChild = ConvertNode< IShot >( childNode );
			switch ( shotChild->GetType() ) {

			case IShot::kShotTypeClip:
				ChangeUniqueIDOfChildNode< IClipShot >( mClipShotMap, shotChild, newUniqueID, mClipShots, shared_from_this() );
				return true;
				break;

			case IShot::kShotTypeTransition:
				ChangeUniqueIDOfChildNode< ITransitionShot >( mTransitionShotMap, shotChild, newUniqueID, mTransitionShots, shared_from_this() );
				return true;
				break;

			default:
				return false;
			}
		}
		break;

		default:
			return false;
		}
		return false;
	}

	UMC::spIUMCNode AudioTrackImpl::GetExternalNode() {
		return shared_from_this();
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
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< AudioTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		} else {
			return std::make_shared< AudioTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}

}
