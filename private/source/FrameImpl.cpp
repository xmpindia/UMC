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

#include "implHeaders/FrameImpl.h"
#include "interfaces/ISource.h"
#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include "interfaces/IUMC.h"

#include "utils/Utils.h"

namespace INT_UMC {
	using AdobeXMPCommon::npos;
	FrameImpl::FrameImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, IUMCNode::kNodeTypeFrame, kFramesPair )
		, mSource( source )
		, mSourceInCount( kEditUnitInCountFromBeginning )
		, mShotInCount( kEditUnitInCountFromBeginning ) { }

	FrameImpl::FrameImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source, const spIStructureNode & node )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, IUMCNode::kNodeTypeFrame, node )
		, mSource( source )
		, mSourceInCount( kEditUnitInCountFromBeginning )
		, mShotInCount( kEditUnitInCountFromBeginning ) { }

	spISource FrameImpl::GetSource() {
		return mSource;
	}

	spcISource FrameImpl::GetSource() const {
		return mSource;
	}

	void FrameImpl::SetSourceInCount( const EditUnitInCount & sourceInCount ) {
		mSourceInCount = sourceInCount;
	}

	UMC::EditUnitInCount FrameImpl::GetSourceInCount() const {
		return mSourceInCount;
	}

	void FrameImpl::SetShotInCount( const EditUnitInCount & shotInCount ) {
		mShotInCount = shotInCount;
	}

	UMC::EditUnitInCount FrameImpl::GetShotInCount() const {
		return mShotInCount;
	}

	IUMCNode::eNodeTypes FrameImpl::GetNodeType() const {
		return IUMCNode::kNodeTypeFrame;
	}

	const std::string & FrameImpl::GetUniqueID() const {
		return NodeImpl::GetUniqueID();
	}

	std::string FrameImpl::GetParsedID() const {
		return NodeImpl::GetParsedID();
	}

	wpcIUMCNode FrameImpl::GetParentNode() const {
		return NodeImpl::GetParentNode();
	}

	wpIUMCNode FrameImpl::GetParentNode() {
		return NodeImpl::GetParentNode();
	}

	spcIUMCNode FrameImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcIUMCNode();
	}

	spIUMCNode FrameImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	spcIUMCNode FrameImpl::GetChildNode( const std::string & uniqueID ) const {
		return spIUMCNode();
	}

	spIUMCNode FrameImpl::GetChildNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	IUMCNode::NodeList FrameImpl::GetAllChildren() {
		return NodeList();
	}

	IUMCNode::cNodeList FrameImpl::GetAllChildren() const {
		return cNodeList();
	}

	IUMCNode::NodeList FrameImpl::GetAllDecendants() {
		return NodeList();
	}

	IUMCNode::cNodeList FrameImpl::GetAllDecendants() const {
		return cNodeList();
	}

	size_t FrameImpl::GetReferenceCount() const {
		return NodeImpl::GetReferenceCount();
	}

	pcIUMCNodeI FrameImpl::GetInternalNode() const {
		return this;
	}

	pIUMCNodeI FrameImpl::GetInternalNode() {
		return this;
	}

	bool FrameImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return NodeImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	spcICustomData FrameImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return NodeImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spICustomData FrameImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return NodeImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	INT_UMC::spIStructureNode FrameImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool FrameImpl::SetUniqueID( const std::string & uniqueID ) {
		return NodeImpl::SetUniqueID(  uniqueID );
	}

	bool FrameImpl::ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) {
		return false;
	}

	UMC::spIUMCNode FrameImpl::GetExternalNode() {
		return shared_from_this();
	}

	UMC::pcIUMCNode FrameImpl::GetNode() const {
		return this;
	}

	UMC::pIUMCNode FrameImpl::GetNode() {
		return this;
	}

	bool FrameImpl::ValidateXMPNode() const {
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

	void FrameImpl::SyncXMPToInternalStuff() {
		auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
		if ( source ) {
			UpdateDataFromXMPDOM( mSourceInCount, kInCountPair, source, stoi64 );
		}
		UpdateDataFromXMPDOM( mShotInCount, kInCountPair, mXMPStructureNode, stoi64 );
	}

	void FrameImpl::SyncInternalStuffToXMP() const {
		auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
		if ( !source ) {
			source = IStructureNode::CreateStructureNode( kSourcePair.first, npos, kSourcePair.second, npos );
			mXMPStructureNode->AppendNode( source );
		}
		AddOrUpdateDataToXMPDOM( mSourceInCount, kInCountPair, source, IgnoreEditUnitInCount );
		AddOrUpdateDataToXMPDOM( mSource->GetUniqueID(), kUniqueIDPair, source );
		AddOrUpdateDataToXMPDOM( mShotInCount, kInCountPair, mXMPStructureNode, IgnoreEditUnitInCount );
	}

	void FrameImpl::SetUpOnAdditionToDOM() {
		if ( !mSource ) {
			std::string userUniqueID;
			auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
			UpdateDataFromXMPDOM( userUniqueID, kUniqueIDPair, source, kEmptyString );
			std::string sourceID;
			mspUniqueIDAndReferenceTracker->GetUserUniqueID( userUniqueID, sourceID );
			if( sourceID.empty() )
				THROW_SOURCE_SHOULD_BE_CREATED_USING_BUFFER
			spIUMC umc = GetParentNode().lock()->GetParentNode().lock()->GetParentNode().lock()->GetParent< IUMC >().lock();
			mSource = umc->GetSource( sourceID );
		}
		mspUniqueIDAndReferenceTracker->AddReference( mSource->GetUniqueID() );
	}

	void FrameImpl::CleanUpOnRemovalFromDOM() {
		mspUniqueIDAndReferenceTracker->RemoveReference( mSource->GetUniqueID() );
	}

	std::string FrameImpl::Serialize() const {
		return NodeImpl::SerializeXMP();
	}

	spIFrame CreateFrame( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source, const spIStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< FrameImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, source, node );
		} else {
			return std::make_shared< FrameImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, source );
		}
	}

}
