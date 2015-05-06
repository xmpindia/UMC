// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/VideoSourceImpl.h"

namespace INT_UMC {

	VideoSourceImpl::VideoSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mSourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 48000 )
		, mTimeCode( FrameRate( 1 ) ){}

	void VideoSourceImpl::SetVideoEditRate( const EditRate & editRate ) {
		mVideoEditRate = editRate;
	}

	EditRate VideoSourceImpl::GetVideoEditRate() const {
		return mVideoEditRate;
	}

	void VideoSourceImpl::SetAudioEditRate( const EditRate & editRate ) {
		mAudioEditRate = editRate;
	}

	EditRate VideoSourceImpl::GetAudioEditRate() const {
		return mAudioEditRate;
	}

	void VideoSourceImpl::SetInCount( const EditUnitInCount & inCount ) {
		mInCount = inCount;
	}

	EditUnitInCount VideoSourceImpl::GetInCount() const {
		return mInCount;
	}

	void VideoSourceImpl::SetDuration( const EditUnitDuration & duration ) {
		mDuration = duration;
	}

	EditUnitDuration VideoSourceImpl::GetDuration() const {
		return mDuration;
	}

	void VideoSourceImpl::SetTimeCode( const TimeCode & timeCode ) {
		mTimeCode = timeCode;
	}

	UMC::TimeCode VideoSourceImpl::GetTimeCode() const {
		return mTimeCode;
	}

	ISource::eSourceTypes VideoSourceImpl::GetType() const {
		return ISource::kSourceTypeVideo;
	}
	void VideoSourceImpl::SetClipName( const std::string & clipName ) {
		mSourceImpl.SetClipName( clipName );
	}

	std::string VideoSourceImpl::GetClipName() const {
		return mSourceImpl.GetClipName();
	}

	INode::eNodeTypes VideoSourceImpl::GetNodeType() const {
		return mSourceImpl.GetNodeType();
	}

	const std::string & VideoSourceImpl::GetUniqueID() const {
		return mSourceImpl.GetUniqueID();
	}

	spcINode VideoSourceImpl::GetParentNode() const {
		return mSourceImpl.GetParentNode();
	}

	spINode VideoSourceImpl::GetParentNode() {
		return mSourceImpl.GetParentNode();
	}

	spcINode VideoSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcINode();
	}

	spINode VideoSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spINode();
	}

	spcINode VideoSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spINode();
	}

	spINode VideoSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spINode();
	}

	INode::NodeList VideoSourceImpl::GetAllChildren() {
		return mSourceImpl.GetAllChildren();
	}

	INode::cNodeList VideoSourceImpl::GetAllChildren() const {
		return mSourceImpl.GetAllChildren();
	}

	INode::NodeList VideoSourceImpl::GetAllDecendants() {
		return mSourceImpl.GetAllDecendants();
	}

	INode::cNodeList VideoSourceImpl::GetAllDecendants() const {
		return mSourceImpl.GetAllDecendants();
	}

	size_t VideoSourceImpl::GetReferenceCount() const {
		return mSourceImpl.GetReferenceCount();
	}

	void VideoSourceImpl::RemoveFromDOM() {
		return mSourceImpl.RemoveFromDOM();
	}

	void VideoSourceImpl::AddToDOM( const spINode & parent ) {
		return mSourceImpl.AddToDOM( parent );
	}

	spIVideoSource CreateVideoSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< VideoSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}
}
