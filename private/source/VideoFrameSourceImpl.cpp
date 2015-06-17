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
#include "XMPCore/Interfaces/IXMPStructureNode.h"
#include "utils/UMCAndXMPMapping.h"
#include "utils/Utils.h"
#include "interfaces/IUMC.h"

namespace INT_UMC {

	VideoFrameSourceImpl::VideoFrameSourceImpl( const spIVideoSource & videoSource,
		const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, kSourceTypeVideoFrame, kVideoFrameSourcesPair )
		, mVideoSource( videoSource )
		, mInCount( kEditUnitInCountFromBeginning )
	{
		if ( !mVideoSource ) THROW_PARENT_CANT_BE_NULL;
	}

	VideoFrameSourceImpl::VideoFrameSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, kSourceTypeVideoFrame, node )
		, mInCount( kEditUnitInCountFromBeginning ) { }

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
		SourceImpl::SetClipName( clipName );
	}

	std::string VideoFrameSourceImpl::GetClipName() const {
		return SourceImpl::GetClipName();
	}

	INode::eNodeTypes VideoFrameSourceImpl::GetNodeType() const {
		return SourceImpl::GetNodeType();
	}

	const std::string & VideoFrameSourceImpl::GetUniqueID() const {
		return SourceImpl::GetUniqueID();
	}

	wpcINode VideoFrameSourceImpl::GetParentNode() const {
		return SourceImpl::GetParentNode();
	}

	wpINode VideoFrameSourceImpl::GetParentNode() {
		return SourceImpl::GetParentNode();
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
		return SourceImpl::GetReferenceCount();
	}

	spICustomData VideoFrameSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return SourceImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData VideoFrameSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return SourceImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	bool VideoFrameSourceImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return SourceImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pINodeI VideoFrameSourceImpl::GetInternalNode() {
		return this;
	}

	pcINodeI VideoFrameSourceImpl::GetInternalNode() const {
		return this;
	}

	std::string VideoFrameSourceImpl::Serialize() const {
		return SerializeXMP();
	}

	void VideoFrameSourceImpl::CleanUpOnRemovalFromDOM() {
		mspUniqueIDAndReferenceTracker->RemoveReference( mVideoSource->GetUniqueID() );
	}

	void VideoFrameSourceImpl::SetUpOnAdditionToDOM() {
		if ( !mVideoSource ) {
			std::string userUniqueID;
			auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
			UpdateDataFromXMPDOM( userUniqueID, kUniqueIDPair, source, kEmptyString );
			std::string sourceID;
			mspUniqueIDAndReferenceTracker->GetUserUniqueID( userUniqueID, sourceID );
			spIUMC umc = GetParent< IUMC >().lock();
			mVideoSource = umc->GetVideoSource( sourceID );
		}
		mspUniqueIDAndReferenceTracker->AddReference( mVideoSource->GetUniqueID() );
	}

	void VideoFrameSourceImpl::SyncInternalStuffToXMP() const {
		SourceImpl::SyncInternalStuffToXMP();
		auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
		if ( !source ) {
			source = IXMPStructureNode::CreateStructureNode( kSourcePair.first, kSourcePair.second );
			mXMPStructureNode->AppendNode( source );
		}
		AddOrUpdateDataToXMPDOM( mVideoSource->GetUniqueID(), kUniqueIDPair, source );
		AddOrUpdateDataToXMPDOM( mInCount, kInCountPair, source, IgnoreEditUnitInCount );
	}

	void VideoFrameSourceImpl::SyncXMPToInternalStuff() {
		SourceImpl::SyncXMPToInternalStuff();
		auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
		if ( source ) {
			UpdateDataFromXMPDOM( mInCount, kInCountPair, source, stoi64 );
		}
	}

	NS_XMPCORE::spIXMPStructureNode VideoFrameSourceImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool VideoFrameSourceImpl::ValidateXMPNode() const {
		std::string userUniqueID;
		auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
		if ( !source ) return false;
		UpdateDataFromXMPDOM( userUniqueID, kUniqueIDPair, source, kEmptyString );
		if ( userUniqueID.empty() ) return false;
		std::string sourceID;
		mspUniqueIDAndReferenceTracker->GetUserUniqueID( userUniqueID, sourceID );
		if ( sourceID.empty() ) return false;
		return mspUniqueIDAndReferenceTracker->IsUniqueIDPresent( sourceID );
	}

	UMC::pcINode VideoFrameSourceImpl::GetNode() const {
		return this;
	}

	UMC::pINode VideoFrameSourceImpl::GetNode() {
		return this;
	}

	spIVideoFrameSource CreateVideoFrameSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIVideoSource & videoSource, const spIXMPStructureNode & node )
	{
		if ( node ) {
			auto retValue = std::make_shared< VideoFrameSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
			retValue->SyncXMPToUMC();
			return retValue;
		}
		else {
			return std::make_shared< VideoFrameSourceImpl >( videoSource, uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}
}
