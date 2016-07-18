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


#include "implHeaders/AudioSourceImpl.h"
#include "XMPCore/Interfaces/IStructureNode.h"
#include "utils/UMCAndXMPMapping.h"

namespace INT_UMC {

	AudioSourceImpl::AudioSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, ISource::kSourceTypeAudio, kAudioSourcesPair )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd )
		, mAudioEditRate( 48000 )
		, mTimeCode( FrameRate( 1 ) ) {}

	AudioSourceImpl::AudioSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, ISource::kSourceTypeAudio, node )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd )
		, mAudioEditRate( 48000 )
		, mTimeCode( FrameRate( 1 ) ) {}

	void AudioSourceImpl::SetAudioEditRate( const EditRate & editRate ) {
		mAudioEditRate = editRate;
	}

	EditRate AudioSourceImpl::GetAudioEditRate() const {
		return mAudioEditRate;
	}

	void AudioSourceImpl::SetInCount( const EditUnitInCount & inCount ) {
		mInCount = inCount;
	}

	EditUnitInCount AudioSourceImpl::GetInCount() const {
		return mInCount;
	}

	void AudioSourceImpl::SetDuration( const EditUnitDuration & duration ) {
		mDuration = duration;
	}

	EditUnitDuration AudioSourceImpl::GetDuration() const {
		return mDuration;
	}

	void AudioSourceImpl::SetTimeCode( const TimeCode & timeCode ) {
		mTimeCode = timeCode;
	}

	TimeCode AudioSourceImpl::GetTimeCode() const {
		return mTimeCode;
	}

	ISource::eSourceTypes AudioSourceImpl::GetType() const {
		return ISource::kSourceTypeAudio;
	}

	void AudioSourceImpl::SetClipName( const std::string & clipName ) {
		SourceImpl::SetClipName( clipName );
	}

	std::string AudioSourceImpl::GetClipName() const {
		return SourceImpl::GetClipName();
	}

	IUMCNode::eNodeTypes AudioSourceImpl::GetNodeType() const {
		return SourceImpl::GetNodeType();
	}

	const std::string & AudioSourceImpl::GetUniqueID() const {
		return SourceImpl::GetUniqueID();
	}

	wpcIUMCNode AudioSourceImpl::GetParentNode() const {
		return SourceImpl::GetParentNode();
	}

	wpIUMCNode AudioSourceImpl::GetParentNode() {
		return SourceImpl::GetParentNode();
	}

	spcIUMCNode AudioSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcIUMCNode();
	}

	spIUMCNode AudioSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	spcIUMCNode AudioSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spIUMCNode();
	}

	spIUMCNode AudioSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	IUMCNode::NodeList AudioSourceImpl::GetAllChildren() {
		return NodeList();
	}

	IUMCNode::cNodeList AudioSourceImpl::GetAllChildren() const {
		return cNodeList();
	}

	IUMCNode::NodeList AudioSourceImpl::GetAllDecendants() {
		return NodeList();
	}

	IUMCNode::cNodeList AudioSourceImpl::GetAllDecendants() const {
		return cNodeList();
	}

	size_t AudioSourceImpl::GetReferenceCount() const {
		return SourceImpl::GetReferenceCount();
	}

	spICustomData AudioSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return SourceImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData AudioSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return SourceImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	bool AudioSourceImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return SourceImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pIUMCNodeI AudioSourceImpl::GetInternalNode() { return this; }

	pcIUMCNodeI AudioSourceImpl::GetInternalNode() const { return this; }

	AdobeXMPCore::spIStructureNode AudioSourceImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool AudioSourceImpl::ValidateXMPNode() const {
		if ( SourceImpl::ValidateXMPNode() )
			return true;
		return false;
	}

	UMC::pIUMCNode AudioSourceImpl::GetNode() {
		return this;
	}

	UMC::pcIUMCNode AudioSourceImpl::GetNode() const {
		return this;
	}

	bool AudioSourceImpl::ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) {
		return false;
	}

	spIUMCNode AudioSourceImpl::GetExternalNode() {
		return shared_from_this();
	}

	bool AudioSourceImpl::SetUniqueID( const std::string & uniqueID ) {
		return NodeImpl::SetUniqueID( uniqueID );
	}

	std::string AudioSourceImpl::GetParsedID() const {
		return SourceImpl::GetParsedID();
	}

	void AudioSourceImpl::SyncXMPToInternalStuff() {
		SourceImpl::SyncXMPToInternalStuff();
		UpdateDataFromXMPDOM( mInCount, kInCountPair, mXMPStructureNode, stoi64 );
		UpdateDataFromXMPDOM( mDuration, kDurationPair, mXMPStructureNode, stou64 );
		UpdateDataFromXMPDOM( mAudioEditRate, kAudioEditRatePair, mXMPStructureNode, stou64rt );
		UpdateDataFromXMPDOM( mTimeCode, mXMPStructureNode );
	}

	void AudioSourceImpl::SyncInternalStuffToXMP() const {
		SourceImpl::SyncInternalStuffToXMP();
		AddOrUpdateDataToXMPDOM( mInCount, kInCountPair, mXMPStructureNode, IgnoreEditUnitInCount );
		AddOrUpdateDataToXMPDOM( mDuration, kDurationPair, mXMPStructureNode, IgnoreEditUnitDuration );
		AddOrUpdateDataToXMPDOM( mAudioEditRate, kAudioEditRatePair, mXMPStructureNode );
		AddOrUpdateDataToXMPDOM( mTimeCode, mXMPStructureNode );
	}

	void AudioSourceImpl::SetUpOnAdditionToDOM() { }

	void AudioSourceImpl::CleanUpOnRemovalFromDOM() { }

	std::string AudioSourceImpl::Serialize() const {
		return SerializeXMP();
	}

	spIAudioSource CreateAudioSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< AudioSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		}
		else {
			return std::make_shared< AudioSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}
}
