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


#include "implHeaders/VideoTrackImpl.h"
#include "utils/UMCAndXMPMapping.h"
#include "interfaces/IClipShot.h"
#include "interfaces/ITransitionShot.h"
#include "utils/Utils.h"
#include "UMCDefines_I.h"

namespace INT_UMC {

	VideoTrackImpl::VideoTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: TrackImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, ITrack::kTrackTypeVideo, kVideoTracksPair )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 1 ) {}

	VideoTrackImpl::VideoTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
		: TrackImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, ITrack::kTrackTypeVideo, node )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 1 ) {}

	void VideoTrackImpl::SetVideoEditRate( const EditRate & editRate ) {
        if (editRate.Numerator()==0) {
            //THROW_INPUT_CANT_BE_ZERO;
            throw std::logic_error("Input can't be zero");

        }
        if (editRate.Denominator()==0) {
            THROW_INPUT_CANT_BE_ZERO;
        }

		mVideoEditRate = editRate;
	}

	EditRate VideoTrackImpl::GetVideoEditRate() const {
		return mVideoEditRate;
	}

	void VideoTrackImpl::SetAudioEditRate( const EditRate & editRate ) {
        if (editRate.Numerator()==0) {
            //THROW_INPUT_CANT_BE_ZERO;
            throw std::logic_error("Input can't be zero");

        }
        if (editRate.Denominator()==0) {
            THROW_INPUT_CANT_BE_ZERO;
        }

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

	IUMCNode::eNodeTypes VideoTrackImpl::GetNodeType() const {
		return TrackImpl::GetNodeType();
	}

	const std::string & VideoTrackImpl::GetUniqueID() const {
		return TrackImpl::GetUniqueID();
	}

	std::string VideoTrackImpl::GetParsedID() const {
		return TrackImpl::GetParsedID();
	}

	wpcIUMCNode VideoTrackImpl::GetParentNode() const {
		return TrackImpl::GetParentNode();
	}

	wpIUMCNode VideoTrackImpl::GetParentNode() {
		return TrackImpl::GetParentNode();
	}

	spcIUMCNode VideoTrackImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return TrackImpl::GetDecendantNode( uniqueID );
	}

	spIUMCNode VideoTrackImpl::GetDecendantNode( const std::string & uniqueID ) {
		return TrackImpl::GetDecendantNode( uniqueID );
	}

	spcIUMCNode VideoTrackImpl::GetChildNode( const std::string & uniqueID ) const {
		return TrackImpl::GetChildNode( uniqueID );
	}

	spIUMCNode VideoTrackImpl::GetChildNode( const std::string & uniqueID ) {
		return TrackImpl::GetChildNode( uniqueID );
	}

	IUMCNode::NodeList VideoTrackImpl::GetAllChildren() {
		return TrackImpl::GetAllChildren();
	}

	IUMCNode::cNodeList VideoTrackImpl::GetAllChildren() const {
		return TrackImpl::GetAllChildren();
	}

	IUMCNode::NodeList VideoTrackImpl::GetAllDecendants() {
		return TrackImpl::GetAllDecendants();
	}

	IUMCNode::cNodeList VideoTrackImpl::GetAllDecendants() const {
		return TrackImpl::GetAllDecendants();
	}

	size_t VideoTrackImpl::GetReferenceCount() const {
		return TrackImpl::GetReferenceCount();
	}

	std::string VideoTrackImpl::Serialize() const {
		return TrackImpl::SerializeXMP();
	}

	pcIUMCNodeI VideoTrackImpl::GetInternalNode() const {
		return this;
	}

	pIUMCNodeI VideoTrackImpl::GetInternalNode() {
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

	AdobeXMPCore::spIStructureNode VideoTrackImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool VideoTrackImpl::ValidateXMPNode() const {
		if ( TrackImpl::ValidateXMPNode() )
			return true;
		return false;
	}

	UMC::pIUMCNode VideoTrackImpl::GetNode() {
		return this;
	}

	UMC::pcIUMCNode VideoTrackImpl::GetNode() const {
		return this;
	}

	bool VideoTrackImpl::SetUniqueID( const std::string & uniqueID ) {
		return NodeImpl::SetUniqueID( uniqueID );
	}

	bool VideoTrackImpl::ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) {
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

	UMC::spIUMCNode VideoTrackImpl::GetExternalNode() {
		return shared_from_this();
	}

	UMC::spIShot VideoTrackImpl::AddShot( const std::string & buffer ) {
        if(buffer.empty())
            THROW_BUFFER_CANT_BE_EMPTY;
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
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< VideoTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		} else {
			return std::make_shared< VideoTrackImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}

}
