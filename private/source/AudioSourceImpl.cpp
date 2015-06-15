// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/AudioSourceImpl.h"
#include "XMPCore/Interfaces/IXMPStructureNode.h"
#include "utils/UMCAndXMPMapping.h"

namespace INT_UMC {

	AudioSourceImpl::AudioSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, ISource::kSourceTypeAudio )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd )
		, mAudioEditRate( 48000 )
		, mTimeCode( FrameRate( 1 ) ) {}

	AudioSourceImpl::AudioSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
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

	INode::eNodeTypes AudioSourceImpl::GetNodeType() const {
		return SourceImpl::GetNodeType();
	}

	const std::string & AudioSourceImpl::GetUniqueID() const {
		return SourceImpl::GetUniqueID();
	}

	wpcINode AudioSourceImpl::GetParentNode() const {
		return SourceImpl::GetParentNode();
	}

	wpINode AudioSourceImpl::GetParentNode() {
		return SourceImpl::GetParentNode();
	}

	spcINode AudioSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcINode();
	}

	spINode AudioSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spINode();
	}

	spcINode AudioSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spINode();
	}

	spINode AudioSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spINode();
	}

	INode::NodeList AudioSourceImpl::GetAllChildren() {
		return NodeList();
	}

	INode::cNodeList AudioSourceImpl::GetAllChildren() const {
		return cNodeList();
	}

	INode::NodeList AudioSourceImpl::GetAllDecendants() {
		return NodeList();
	}

	INode::cNodeList AudioSourceImpl::GetAllDecendants() const {
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

	pINodeI AudioSourceImpl::GetInternalNode() { return this; }

	pcINodeI AudioSourceImpl::GetInternalNode() const { return this; }

	NS_XMPCORE::spIXMPStructureNode AudioSourceImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool AudioSourceImpl::ValidateXMPNode() const {
		if ( SourceImpl::ValidateXMPNode() )
			return true;
		return false;
	}

	UMC::pINode AudioSourceImpl::GetNode() {
		return this;
	}

	UMC::pcINode AudioSourceImpl::GetNode() const {
		return this;
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
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
	{
		if ( node ) {
			auto retValue = std::make_shared< AudioSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
			retValue->SyncXMPToUMC();
			return retValue;
		}
		else {
			return std::make_shared< AudioSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}
}
