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
		: mSource( CreateSource( uniqueIDAndReferenceTracker, uniqueIDGenerator ) )
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
		mSource->SetClipName( clipName );
	}

	std::string VideoSourceImpl::GetClipName() const {
		return mSource->GetClipName();
	}

	INode::eNodeTypes VideoSourceImpl::GetNodeType() const {
		return mSource->GetNodeType();
	}

	const std::string & VideoSourceImpl::GetUniqueID() const {
		return mSource->GetUniqueID();
	}

	spcINode VideoSourceImpl::GetParentNode() const {
		return mSource->GetParentNode();
	}

	spINode VideoSourceImpl::GetParentNode() {
		return mSource->GetParentNode();
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
		return mSource->GetAllChildren();
	}

	INode::cNodeList VideoSourceImpl::GetAllChildren() const {
		return const_pointer_cast< const ISource >( mSource )->GetAllChildren();
	}

	INode::NodeList VideoSourceImpl::GetAllDecendants() {
		return mSource->GetAllDecendants();
	}

	INode::cNodeList VideoSourceImpl::GetAllDecendants() const {
		return const_pointer_cast< const ISource >( mSource )->GetAllDecendants();
	}

	size_t VideoSourceImpl::GetReferenceCount() const {
		return mSource->GetReferenceCount();
	}

	pcINodeI VideoSourceImpl::GetInternalNode() const {
		return mSource->GetInternalNode();
	}

	pINodeI VideoSourceImpl::GetInternalNode() {
		return mSource->GetInternalNode();
	}

	bool VideoSourceImpl::SetCustomData( const spICustomData & customData ) {
		return mSource->SetCustomData( customData );
	}

	spcICustomData VideoSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mSource->GetCustomData( customDataNameSpace, customDataName );
	}

	spICustomData VideoSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mSource->GetCustomData( customDataNameSpace, customDataName );
	}

	spIVideoSource CreateVideoSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< VideoSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}
}
