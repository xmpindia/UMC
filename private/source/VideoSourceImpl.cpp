// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/VideoSourceImpl.h"
#include "XMPCore/Interfaces/IXMPStructureNode.h"
#include "utils/UMCAndXMPMapping.h"

namespace INT_UMC {

	VideoSourceImpl::VideoSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, kSourceTypeVideo, kVideoSourcesPair )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 48000 )
		, mTimeCode( FrameRate( 1 ) ) {}

	VideoSourceImpl::VideoSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, kSourceTypeVideo, node )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 48000 )
		, mTimeCode( FrameRate( 1 ) ){}

	NS_XMPCORE::spIXMPStructureNode VideoSourceImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool VideoSourceImpl::ValidateXMPNode() const {
		if ( SourceImpl::ValidateXMPNode() )
			return true;
		else
			return false;
	}

	UMC::pINode VideoSourceImpl::GetNode() {
		return this;
	}

	UMC::pcINode VideoSourceImpl::GetNode() const {
		return this;
	}

	void VideoSourceImpl::SyncXMPToInternalStuff() {
		SourceImpl::SyncXMPToInternalStuff();
		UpdateDataFromXMPDOM( mInCount, kInCountPair, mXMPStructureNode, stoi64 );
		UpdateDataFromXMPDOM( mDuration, kDurationPair, mXMPStructureNode, stou64 );
		UpdateDataFromXMPDOM( mVideoEditRate, kVideoEditRatePair, mXMPStructureNode, stou64rt );
		UpdateDataFromXMPDOM( mAudioEditRate, kAudioEditRatePair, mXMPStructureNode, stou64rt );
		UpdateDataFromXMPDOM( mTimeCode, mXMPStructureNode );
	}

	void VideoSourceImpl::SyncInternalStuffToXMP() const {
		SourceImpl::SyncInternalStuffToXMP();
		AddOrUpdateDataToXMPDOM( mInCount, kInCountPair, mXMPStructureNode, IgnoreEditUnitInCount );
		AddOrUpdateDataToXMPDOM( mDuration, kDurationPair, mXMPStructureNode, IgnoreEditUnitDuration );
		AddOrUpdateDataToXMPDOM( mVideoEditRate, kVideoEditRatePair, mXMPStructureNode );
		AddOrUpdateDataToXMPDOM( mAudioEditRate, kAudioEditRatePair, mXMPStructureNode );
		AddOrUpdateDataToXMPDOM( mTimeCode, mXMPStructureNode );
	}

	void VideoSourceImpl::SetUpOnAdditionToDOM() { }

	void VideoSourceImpl::CleanUpOnRemovalFromDOM() { }

	pcINodeI VideoSourceImpl::GetInternalNode() const { return this; }

	pINodeI VideoSourceImpl::GetInternalNode() { return this; }

	bool VideoSourceImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName,
		const spICustomData & customData )
	{
		return NodeImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	spcICustomData VideoSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return NodeImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spICustomData VideoSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return NodeImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	std::string VideoSourceImpl::Serialize() const {
		return SerializeXMP();
	}

	size_t VideoSourceImpl::GetReferenceCount() const {
		return NodeImpl::GetReferenceCount();
	}

	INode::cNodeList VideoSourceImpl::GetAllDecendants() const {
		return cNodeList();
	}

	INode::NodeList VideoSourceImpl::GetAllDecendants() {
		return NodeList();
	}

	INode::cNodeList VideoSourceImpl::GetAllChildren() const {
		return cNodeList();
	}

	INode::NodeList VideoSourceImpl::GetAllChildren() {
		return NodeList();
	}

	spINode VideoSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spINode();
	}

	spcINode VideoSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spcINode();
	}

	spINode VideoSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spINode();
	}

	spcINode VideoSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcINode();
	}

	wpINode VideoSourceImpl::GetParentNode() {
		return NodeImpl::GetParentNode();
	}

	wpcINode VideoSourceImpl::GetParentNode() const {
		return NodeImpl::GetParentNode();
	}

	const std::string & VideoSourceImpl::GetUniqueID() const {
		return NodeImpl::GetUniqueID();
	}

	INode::eNodeTypes VideoSourceImpl::GetNodeType() const {
		return SourceImpl::GetNodeType();
	}

	ISource::eSourceTypes VideoSourceImpl::GetType() const {
		return ISource::kSourceTypeVideo;
	}

	std::string VideoSourceImpl::GetClipName() const {
		return SourceImpl::GetClipName();
	}

	void VideoSourceImpl::SetClipName( const std::string & clipName ) {
		SourceImpl::SetClipName( clipName );
	}

	TimeCode VideoSourceImpl::GetTimeCode() const {
		return mTimeCode;
	}

	void VideoSourceImpl::SetTimeCode( const TimeCode & timeCode ) {
		mTimeCode = timeCode;
	}

	EditUnitDuration VideoSourceImpl::GetDuration() const {
		return mDuration;
	}

	void VideoSourceImpl::SetDuration( const EditUnitDuration & duration ) {
		mDuration = duration;
	}

	EditUnitInCount VideoSourceImpl::GetInCount() const {
		return mInCount;
	}

	void VideoSourceImpl::SetInCount( const EditUnitInCount & inCount ) {
		mInCount = inCount;
	}

	EditRate VideoSourceImpl::GetAudioEditRate() const {
		return mAudioEditRate;
	}

	void VideoSourceImpl::SetAudioEditRate( const EditRate & editRate ) {
		mAudioEditRate = editRate;
	}

	EditRate VideoSourceImpl::GetVideoEditRate() const {
		return mVideoEditRate;
	}

	void VideoSourceImpl::SetVideoEditRate( const EditRate & editRate ) {
		mVideoEditRate = editRate;
	}

	spIVideoSource CreateVideoSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< VideoSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		} else {
			return std::make_shared< VideoSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}
}
