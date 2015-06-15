// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/FrameImpl.h"
#include "interfaces/ISource.h"
#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include "interfaces/IUMC.h"

#include "utils/Utils.h"

namespace INT_UMC {

	FrameImpl::FrameImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeFrame, kFramesPair )
		, mSource( source )
		, mSourceInCount( kEditUnitInCountFromBeginning )
		, mShotInCount( kEditUnitInCountFromBeginning ) { }

	FrameImpl::FrameImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source, const spIXMPStructureNode & node )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeFrame, node )
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

	INode::eNodeTypes FrameImpl::GetNodeType() const {
		return INode::kNodeTypeFrame;
	}

	const std::string & FrameImpl::GetUniqueID() const {
		return NodeImpl::GetUniqueID();
	}

	wpcINode FrameImpl::GetParentNode() const {
		return NodeImpl::GetParentNode();
	}

	wpINode FrameImpl::GetParentNode() {
		return NodeImpl::GetParentNode();
	}

	spcINode FrameImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcINode();
	}

	spINode FrameImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spINode();
	}

	spcINode FrameImpl::GetChildNode( const std::string & uniqueID ) const {
		return spINode();
	}

	spINode FrameImpl::GetChildNode( const std::string & uniqueID ) {
		return spINode();
	}

	INode::NodeList FrameImpl::GetAllChildren() {
		return NodeList();
	}

	INode::cNodeList FrameImpl::GetAllChildren() const {
		return cNodeList();
	}

	INode::NodeList FrameImpl::GetAllDecendants() {
		return NodeList();
	}

	INode::cNodeList FrameImpl::GetAllDecendants() const {
		return cNodeList();
	}

	size_t FrameImpl::GetReferenceCount() const {
		return NodeImpl::GetReferenceCount();
	}

	pcINodeI FrameImpl::GetInternalNode() const {
		return this;
	}

	pINodeI FrameImpl::GetInternalNode() {
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

	INT_UMC::spIXMPStructureNode FrameImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	UMC::pcINode FrameImpl::GetNode() const {
		return this;
	}

	UMC::pINode FrameImpl::GetNode() {
		return this;
	}

	bool FrameImpl::ValidateXMPNode() const {
		std::string userUniqueID;
		auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
		if ( source ) return false;
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
			source = IXMPStructureNode::CreateStructureNode( kSourcePair.first, kSourcePair.second );
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
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source, const spIXMPStructureNode & node )
	{
		if ( node ) {
			auto retValue = std::make_shared< FrameImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, source, node );
			retValue->SyncXMPToUMC();
			return retValue;
		} else {
			return std::make_shared< FrameImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, source );
		}
	}

}
