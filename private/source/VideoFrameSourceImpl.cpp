/*
*  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
*  This file is licensed to you under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License. You may obtain a copy
*  of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software distributed under
*  the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
*  OF ANY KIND, either express or implied. See the License for the specific language
*  governing permissions and limitations under the License.
*
*/


#include "implHeaders/VideoFrameSourceImpl.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include "XMPCore/Interfaces/IStructureNode.h"
#include "utils/UMCAndXMPMapping.h"
#include "utils/Utils.h"
#include "interfaces/IUMC.h"

namespace INT_UMC {


	using AdobeXMPCommon::npos;
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
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
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

	IUMCNode::eNodeTypes VideoFrameSourceImpl::GetNodeType() const {
		return SourceImpl::GetNodeType();
	}

	const std::string & VideoFrameSourceImpl::GetUniqueID() const {
		return SourceImpl::GetUniqueID();
	}

	std::string VideoFrameSourceImpl::GetParsedID() const {
		return SourceImpl::GetParsedID();
	}

	wpcIUMCNode VideoFrameSourceImpl::GetParentNode() const {
		return SourceImpl::GetParentNode();
	}

	wpIUMCNode VideoFrameSourceImpl::GetParentNode() {
		return SourceImpl::GetParentNode();
	}

	spcIUMCNode VideoFrameSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcIUMCNode();
	}

	spIUMCNode VideoFrameSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	spcIUMCNode VideoFrameSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spIUMCNode();
	}

	spIUMCNode VideoFrameSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	IUMCNode::NodeList VideoFrameSourceImpl::GetAllChildren() {
		return NodeList();
	}

	IUMCNode::cNodeList VideoFrameSourceImpl::GetAllChildren() const {
		return cNodeList();
	}

	IUMCNode::NodeList VideoFrameSourceImpl::GetAllDecendants() {
		return NodeList();
	}

	IUMCNode::cNodeList VideoFrameSourceImpl::GetAllDecendants() const {
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

	pIUMCNodeI VideoFrameSourceImpl::GetInternalNode() {
		return this;
	}

	pcIUMCNodeI VideoFrameSourceImpl::GetInternalNode() const {
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
			source = IStructureNode::CreateStructureNode( kSourcePair.first, npos, kSourcePair.second, npos );
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

	AdobeXMPCore::spIStructureNode VideoFrameSourceImpl::GetXMPNode() const {
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

	UMC::pcIUMCNode VideoFrameSourceImpl::GetNode() const {
		return this;
	}

	UMC::pIUMCNode VideoFrameSourceImpl::GetNode() {
		return this;
	}

	UMC::spIUMCNode VideoFrameSourceImpl::GetExternalNode() {
		return shared_from_this();
	}

	bool VideoFrameSourceImpl::ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) {
		return false;
	}

	bool VideoFrameSourceImpl::SetUniqueID( const std::string & uniqueID ) {
		return NodeImpl::SetUniqueID( uniqueID );
	}

	spIVideoFrameSource CreateVideoFrameSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIVideoSource & videoSource, const spIStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< VideoFrameSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		}
		else {
			return std::make_shared< VideoFrameSourceImpl >( videoSource, uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}
}
