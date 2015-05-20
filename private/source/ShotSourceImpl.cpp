// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/ShotSourceImpl.h"
#include "interfaces/ISource.h"

namespace INT_UMC {
	
	ShotSourceImpl::ShotSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator )
		: mNode( CreateNode( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeShotSource ) )
		, mSourceInCount( kEditUnitInCountFromBeginning )
		, mSourceDuration( kEditUnitDurationTillEnd )
		, mShotInCount( kEditUnitInCountFromBeginning ) { }


	void ShotSourceImpl::SetSourceInCount( const EditUnitInCount & sourceInCount ) {
		mSourceInCount = sourceInCount;
	}

	UMC::EditUnitInCount ShotSourceImpl::GetSourceInCount() const {
		return mSourceInCount;
	}

	void ShotSourceImpl::SetSourceDuration( const EditUnitDuration & sourceDuration ) {
		mSourceDuration = sourceDuration;
	}

	UMC::EditUnitDuration ShotSourceImpl::GetSourceDuration() const {
		return mSourceDuration;
	}

	void ShotSourceImpl::SetShotInCount( const EditUnitInCount & shotInCount ) {
		mShotInCount = shotInCount;
	}

	UMC::EditUnitInCount ShotSourceImpl::GetShotInCount() const {
		return mShotInCount;
	}




	// INODEI

	INode::eNodeTypes ShotSourceImpl::GetNodeType() const {
		return mNode->GetNodeType();
	}

	const std::string & ShotSourceImpl::GetUniqueID() const {
		return mNode->GetUniqueID();
	}

	wpcINode ShotSourceImpl::GetParentNode() const {
		return mNode->GetParentNode();
	}

	wpINode ShotSourceImpl::GetParentNode() {
		return mNode->GetParentNode();
	}

	spcINode ShotSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcINode();
	}

	spINode ShotSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spINode();
	}

	spcINode ShotSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spINode();
	}

	spINode ShotSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spINode();
	}

	INode::NodeList ShotSourceImpl::GetAllChildren() {
		return mNode->GetAllChildren();
	}

	INode::cNodeList ShotSourceImpl::GetAllChildren() const {
		cNodeList list;
		return list;
	}

	INode::NodeList ShotSourceImpl::GetAllDecendants() {
		return mNode->GetAllDecendants();
	}

	INode::cNodeList ShotSourceImpl::GetAllDecendants() const {
		cNodeList list;
		return list;
	}

	size_t ShotSourceImpl::GetReferenceCount() const {
		return mNode->GetReferenceCount();
	}

	void ShotSourceImpl::RemoveFromDOM() {
		mNode->GetInternalNode()->RemoveFromDOM();
	}

	void ShotSourceImpl::AddToDOM( const spINode & parent ) {
		mNode->GetInternalNode()->AddToDOM( parent );
	}

	pcINodeI ShotSourceImpl::GetInternalNode() const {
		return mNode->GetInternalNode();
	}

	pINodeI ShotSourceImpl::GetInternalNode() {
		return mNode->GetInternalNode();
	}

	bool ShotSourceImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mNode->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	spcICustomData ShotSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}

	spICustomData ShotSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}



	void ShotSourceImpl::SetExtensionNode( const spIXMPStructureNode & structureNode ) {
		mNode->GetInternalNode()->SetExtensionNode( structureNode );
	}

	NS_XMPCORE::spIXMPStructureNode ShotSourceImpl::GetExtensionNode(bool create /*= false */) const {
		return mNode->GetInternalNode()->GetExtensionNode( create );
	}

	NS_XMPCORE::spIXMPStructureNode ShotSourceImpl::GetMergedExtensionNode() const {
		return mNode->GetInternalNode()->GetMergedExtensionNode();
	}

	spIUniqueIDAndReferenceTracker ShotSourceImpl::GetUniqueIDAndReferenceTracker() {
		return mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker();
	}

	spcIUniqueIDAndReferenceTracker ShotSourceImpl::GetUniqueIDAndReferenceTracker() const {
		return mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker();
	}

	spIUniqueIDGenerator ShotSourceImpl::GetUniqueIDGenerator() {
		return mNode->GetInternalNode()->GetUniqueIDGenerator();
	}

	spcIUniqueIDGenerator ShotSourceImpl::GetUniqueIDGenerator() const {
		return mNode->GetInternalNode()->GetUniqueIDGenerator();
	}







	spIShotSource CreateShotSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< ShotSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}
