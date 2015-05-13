// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/AudioSourceImpl.h"

namespace INT_UMC {

	AudioSourceImpl::AudioSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mSource( CreateSource( uniqueIDAndReferenceTracker, uniqueIDGenerator ) )
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
		mSource->SetClipName( clipName );
	}

	std::string AudioSourceImpl::GetClipName() const {
		return mSource->GetClipName();
	}

	INode::eNodeTypes AudioSourceImpl::GetNodeType() const {
		return mSource->GetNodeType();
	}

	const std::string & AudioSourceImpl::GetUniqueID() const {
		return mSource->GetUniqueID();
	}

	spcINode AudioSourceImpl::GetParentNode() const {
		return mSource->GetParentNode();
	}

	spINode AudioSourceImpl::GetParentNode() {
		return mSource->GetParentNode();
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
		return mSource->GetAllChildren();
	}

	INode::cNodeList AudioSourceImpl::GetAllChildren() const {
		return const_pointer_cast< const ISource >( mSource )->GetAllChildren();
	}

	INode::NodeList AudioSourceImpl::GetAllDecendants() {
		return mSource->GetAllDecendants();
	}

	INode::cNodeList AudioSourceImpl::GetAllDecendants() const {
		return const_pointer_cast< const ISource >( mSource )->GetAllDecendants();
	}

	size_t AudioSourceImpl::GetReferenceCount() const {
		return mSource->GetReferenceCount();
	}

	spICustomData AudioSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mSource->GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData AudioSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mSource->GetCustomData( customDataNameSpace, customDataName );
	}

	bool AudioSourceImpl::SetCustomData( const spICustomData & customData ) {
		return mSource->SetCustomData( customData );
	}

	pINodeI AudioSourceImpl::GetInternalNode() {
		return mSource->GetInternalNode();
	}

	pcINodeI AudioSourceImpl::GetInternalNode() const {
		return mSource->GetInternalNode();
	}

	spIAudioSource CreateAudioSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< AudioSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}
