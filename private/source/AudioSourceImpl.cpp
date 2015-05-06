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
		: mSourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator )
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
		mSourceImpl.SetClipName( clipName );
	}

	std::string AudioSourceImpl::GetClipName() const {
		return mSourceImpl.GetClipName();
	}

	INode::eNodeTypes AudioSourceImpl::GetNodeType() const {
		return mSourceImpl.GetNodeType();
	}

	const std::string & AudioSourceImpl::GetUniqueID() const {
		return mSourceImpl.GetUniqueID();
	}

	spcINode AudioSourceImpl::GetParentNode() const {
		return mSourceImpl.GetParentNode();
	}

	spINode AudioSourceImpl::GetParentNode() {
		return mSourceImpl.GetParentNode();
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
		return mSourceImpl.GetAllChildren();
	}

	INode::cNodeList AudioSourceImpl::GetAllChildren() const {
		return mSourceImpl.GetAllChildren();
	}

	INode::NodeList AudioSourceImpl::GetAllDecendants() {
		return mSourceImpl.GetAllDecendants();
	}

	INode::cNodeList AudioSourceImpl::GetAllDecendants() const {
		return mSourceImpl.GetAllDecendants();
	}

	size_t AudioSourceImpl::GetReferenceCount() const {
		return mSourceImpl.GetReferenceCount();
	}

	void AudioSourceImpl::RemoveFromDOM() {
		return mSourceImpl.RemoveFromDOM();
	}

	void AudioSourceImpl::AddToDOM( const spINode & parent ) {
		return mSourceImpl.AddToDOM( parent );
	}

	spIAudioSource CreateAudioSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< AudioSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}
