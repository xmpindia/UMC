// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/FrameImpl.h"

namespace INT_UMC {
	spISource FrameImpl::GetSource() {
		return spISource( mwpSource );
	}

	spcISource FrameImpl::GetSource() const {
		return spcISource( mwpSource );
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

	// INODEI

	const std::string & FrameImpl::GetUniqueID() const {
		return mNode->GetUniqueID();
	}

	INode::eNodeTypes FrameImpl::GetNodeType() const {
		return mNode->GetNodeType();
	}

	wpcINode FrameImpl::GetParentNode() const {
		return mNode->GetParentNode();
	}

	wpINode FrameImpl::GetParentNode() {
		return mNode->GetParentNode();
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
		return mNode->GetAllChildren();
	}

	INode::cNodeList FrameImpl::GetAllChildren() const {
		cNodeList list;
		return list;
	}

	INode::NodeList FrameImpl::GetAllDecendants() {
		return mNode->GetAllDecendants();
	}

	INode::cNodeList FrameImpl::GetAllDecendants() const {
		cNodeList list;
		return list;
	}

	size_t FrameImpl::GetReferenceCount() const {
		return mNode->GetReferenceCount();
	}

	void FrameImpl::RemoveFromDOM() {
		mNode->GetInternalNode()->RemoveFromDOM();
	}

	void FrameImpl::AddToDOM( const spINode & parent ) {
		mNode->GetInternalNode()->AddToDOM( parent );
	}

	pcINodeI FrameImpl::GetInternalNode() const {
		return mNode->GetInternalNode();
	}

	pINodeI FrameImpl::GetInternalNode() {
		return mNode->GetInternalNode();
	}

	bool FrameImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mNode->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	spcICustomData FrameImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}

	spICustomData FrameImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}


	void FrameImpl::SetExtensionNode( const spIXMPStructureNode & structureNode ) {
		mNode->GetInternalNode()->SetExtensionNode( structureNode );
	}

	NS_XMPCORE::spIXMPStructureNode FrameImpl::GetExtensionNode(bool create /*= false */) const {
		return mNode->GetInternalNode()->GetExtensionNode( create );
	}

	NS_XMPCORE::spIXMPStructureNode FrameImpl::GetMergedExtensionNode() const {
		return mNode->GetInternalNode()->GetMergedExtensionNode();
	}

	spIUniqueIDAndReferenceTracker FrameImpl::GetUniqueIDAndReferenceTracker() {
		return mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker();
	}

	spcIUniqueIDAndReferenceTracker FrameImpl::GetUniqueIDAndReferenceTracker() const {
		return mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker();
	}

	spIUniqueIDGenerator FrameImpl::GetUniqueIDGenerator() {
		return mNode->GetInternalNode()->GetUniqueIDGenerator();
	}

	spcIUniqueIDGenerator FrameImpl::GetUniqueIDGenerator() const {
		return mNode->GetInternalNode()->GetUniqueIDGenerator();
	}

	FrameImpl::FrameImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source )
	    : mNode( CreateNode( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeFrame ) )
	    , mwpSource( source )
		, mSourceInCount( kEditUnitInCountFromBeginning )
		, mShotInCount( kEditUnitInCountFromBeginning ) { }

	spIFrame CreateFrame( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source )
	{
		return std::make_shared< FrameImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, source );
	}

}
