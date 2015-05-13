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
		: mSource( CreateSource( uniqueIDAndReferenceTracker, uniqueIDGenerator ) )
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
		mSource->SetClipName( clipName );
	}

	std::string VideoFrameSourceImpl::GetClipName() const {
		return mSource->GetClipName();
	}

	INode::eNodeTypes VideoFrameSourceImpl::GetNodeType() const {
		return mSource->GetNodeType();
	}

	const std::string & VideoFrameSourceImpl::GetUniqueID() const {
		return mSource->GetUniqueID();
	}

	spcINode VideoFrameSourceImpl::GetParentNode() const {
		return mSource->GetParentNode();
	}

	spINode VideoFrameSourceImpl::GetParentNode() {
		return mSource->GetParentNode();
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
		return NodeList();
	}

	INode::cNodeList VideoFrameSourceImpl::GetAllChildren() const {
		return cNodeList();
	}

	INode::NodeList VideoFrameSourceImpl::GetAllDecendants() {
		return NodeList();
	}

	INode::cNodeList VideoFrameSourceImpl::GetAllDecendants() const {
		return cNodeList();
	}

	size_t VideoFrameSourceImpl::GetReferenceCount() const {
		return mSource->GetReferenceCount();
	}

	spICustomData VideoFrameSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mSource->GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData VideoFrameSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mSource->GetCustomData( customDataNameSpace, customDataName );
	}

	bool VideoFrameSourceImpl::SetCustomData( const spICustomData & customData ) {
		return mSource->SetCustomData( customData );
	}

	pINodeI VideoFrameSourceImpl::GetInternalNode() {
		return this;
	}

	pcINodeI VideoFrameSourceImpl::GetInternalNode() const {
		return this;
	}

	spcIUniqueIDGenerator VideoFrameSourceImpl::GetUniqueIDGenerator() const {
		return mSource->GetInternalNode()->GetUniqueIDGenerator();
	}

	spIUniqueIDGenerator VideoFrameSourceImpl::GetUniqueIDGenerator() {
		return mSource->GetInternalNode()->GetUniqueIDGenerator();
	}

	spcIUniqueIDAndReferenceTracker VideoFrameSourceImpl::GetUniqueIDAndReferenceTracker() const {
		return mSource->GetInternalNode()->GetUniqueIDAndReferenceTracker();
	}

	spIUniqueIDAndReferenceTracker VideoFrameSourceImpl::GetUniqueIDAndReferenceTracker() {
		return mSource->GetInternalNode()->GetUniqueIDAndReferenceTracker();
	}

	void VideoFrameSourceImpl::AddToDOM( const spINode & parent ) {
		mSource->GetInternalNode()->AddToDOM( parent );
		GetUniqueIDAndReferenceTracker()->AddReference( mVideoSource->GetUniqueID() );
	}

	void VideoFrameSourceImpl::RemoveFromDOM() {
		mSource->GetInternalNode()->RemoveFromDOM();
		GetUniqueIDAndReferenceTracker()->RemoveReference( mVideoSource->GetUniqueID() );
	}

	NS_XMPCORE::spIXMPStructureNode VideoFrameSourceImpl::GetExtensionNode(bool create /*= false */) const {
		return mSource->GetInternalNode()->GetExtensionNode( create );
	}

	NS_XMPCORE::spIXMPStructureNode VideoFrameSourceImpl::GetMergedExtensionNode() const {
		return mSource->GetInternalNode()->GetMergedExtensionNode();
	}

	void VideoFrameSourceImpl::SetExtensionNode( const spIXMPStructureNode & structureNode ) {
		mSource->GetInternalNode()->SetExtensionNode( structureNode );
	}

	spIVideoFrameSource CreateVideoFrameSource( const spIVideoSource & videoSource,
		const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< VideoFrameSourceImpl >( videoSource, uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}
}
