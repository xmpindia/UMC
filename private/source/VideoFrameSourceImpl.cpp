// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/VideoFrameSourceImpl.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IUniqueIDAndReferenceTracker.h"

namespace INT_UMC {

	VideoFrameSourceImpl::VideoFrameSourceImpl( const spIVideoSource & videoSource,
		const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mSourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator )
		, mVideoSource( videoSource )
		, mInCount( kEditUnitInCountFromBeginning )
	{
		if ( !mVideoSource ) THROW_PARENT_CANT_BE_NULL;
	}

	void VideoFrameSourceImpl::SetInCount( const EditUnitInCount & inCount ) {
		mInCount = inCount;
	}

	EditUnitInCount VideoFrameSourceImpl::GetInCount() const {
		return mInCount;
	}

	TimeCode VideoFrameSourceImpl::GetTimeCode() const {
		return mVideoSource->GetTimeCode();
	}

	spIVideoSource VideoFrameSourceImpl::GetVideoSource() {
		return mVideoSource;
	}

	spcIVideoSource VideoFrameSourceImpl::GetVideoSource() const {
		return mVideoSource;
	}

	ISource::eSourceTypes VideoFrameSourceImpl::GetType() const {
		return ISource::kSourceTypeVideoFrame;
	}

	void VideoFrameSourceImpl::SetClipName( const std::string & clipName ) {
		mSourceImpl.SetClipName( clipName );
	}

	std::string VideoFrameSourceImpl::GetClipName() const {
		return mSourceImpl.GetClipName();
	}

	INode::eNodeTypes VideoFrameSourceImpl::GetNodeType() const {
		return mSourceImpl.GetNodeType();
	}

	const std::string & VideoFrameSourceImpl::GetUniqueID() const {
		return mSourceImpl.GetUniqueID();
	}

	spcINode VideoFrameSourceImpl::GetParentNode() const {
		return mSourceImpl.GetParentNode();
	}

	spINode VideoFrameSourceImpl::GetParentNode() {
		return mSourceImpl.GetParentNode();
	}

	spcINode VideoFrameSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcINode();
	}

	spINode VideoFrameSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spINode();
	}

	spcINode VideoFrameSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spINode();
	}

	spINode VideoFrameSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spINode();
	}

	INode::NodeList VideoFrameSourceImpl::GetAllChildren() {
		return mSourceImpl.GetAllChildren();
	}

	INode::cNodeList VideoFrameSourceImpl::GetAllChildren() const {
		return mSourceImpl.GetAllChildren();
	}

	INode::NodeList VideoFrameSourceImpl::GetAllDecendants() {
		return mSourceImpl.GetAllDecendants();
	}

	INode::cNodeList VideoFrameSourceImpl::GetAllDecendants() const {
		return mSourceImpl.GetAllDecendants();
	}

	size_t VideoFrameSourceImpl::GetReferenceCount() const {
		return mSourceImpl.GetReferenceCount();
	}

	void VideoFrameSourceImpl::RemoveFromDOM() {
		mSourceImpl.RemoveFromDOM();
		mSourceImpl.mspUniqueIDAndReferenceTracker->RemoveReference( mVideoSource->GetUniqueID() );
	}

	void VideoFrameSourceImpl::AddToDOM( const spINode & parent ) {
		mSourceImpl.AddToDOM( parent );
		mSourceImpl.mspUniqueIDAndReferenceTracker->AddReference( mVideoSource->GetUniqueID() );
	}

	spIVideoFrameSource CreateVideoFrameSource( const spIVideoSource & videoSource,
		const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< VideoFrameSourceImpl >( videoSource, uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}
}
