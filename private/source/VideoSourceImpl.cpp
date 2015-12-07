// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/VideoSourceImpl.h"
#include "XMPCore/Interfaces/IStructureNode.h"
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
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, kSourceTypeVideo, node )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 48000 )
		, mTimeCode( FrameRate( 1 ) ){}

	AdobeXMPCore::spIStructureNode VideoSourceImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool VideoSourceImpl::ValidateXMPNode() const {
		if ( SourceImpl::ValidateXMPNode() )
			return true;
		else
			return false;
	}

	UMC::pIUMCNode VideoSourceImpl::GetNode() {
		return this;
	}

	UMC::pcIUMCNode VideoSourceImpl::GetNode() const {
		return this;
	}

	bool VideoSourceImpl::SetUniqueID( const std::string & uniqueID ) {
		return NodeImpl::SetUniqueID( uniqueID );
	}


	bool VideoSourceImpl::ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) {
		return false;
	}

	UMC::spIUMCNode VideoSourceImpl::GetExternalNode() {
		return shared_from_this();
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

	pcIUMCNodeI VideoSourceImpl::GetInternalNode() const { return this; }

	pIUMCNodeI VideoSourceImpl::GetInternalNode() { return this; }

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

	IUMCNode::cNodeList VideoSourceImpl::GetAllDecendants() const {
		return cNodeList();
	}

	IUMCNode::NodeList VideoSourceImpl::GetAllDecendants() {
		return NodeList();
	}

	IUMCNode::cNodeList VideoSourceImpl::GetAllChildren() const {
		return cNodeList();
	}

	IUMCNode::NodeList VideoSourceImpl::GetAllChildren() {
		return NodeList();
	}

	spIUMCNode VideoSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	spcIUMCNode VideoSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spcIUMCNode();
	}

	spIUMCNode VideoSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	spcIUMCNode VideoSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcIUMCNode();
	}

	wpIUMCNode VideoSourceImpl::GetParentNode() {
		return NodeImpl::GetParentNode();
	}

	wpcIUMCNode VideoSourceImpl::GetParentNode() const {
		return NodeImpl::GetParentNode();
	}

	const std::string & VideoSourceImpl::GetUniqueID() const {
		return NodeImpl::GetUniqueID();
	}

	std::string VideoSourceImpl::GetParsedID() const {
		return NodeImpl::GetParsedID();
	}

	IUMCNode::eNodeTypes VideoSourceImpl::GetNodeType() const {
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
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< VideoSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		} else {
			return std::make_shared< VideoSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}
}
