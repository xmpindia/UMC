// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/SourceImpl.h"

#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include "interfaces/IUniqueIDGenerator.h"
#include "interfaces/IUMC.h"

namespace INT_UMC {

	const std::string & SourceImpl::GetUniqueID() const {
		return mNode->GetUniqueID();
	}

	void SourceImpl::SetClipName( const std::string & clipName ) {
		mClipName = clipName;
	}

	std::string SourceImpl::GetClipName() const  {
		return mClipName;
	}

	spcINode SourceImpl::GetParentNode() const  {
		return mNode->GetParentNode();
	}

	spINode SourceImpl::GetParentNode() {
		return mNode->GetParentNode();
	}

	spcINode SourceImpl::GetDecendantNode( const std::string & id ) const {
		return spcINode();
	}

	spINode SourceImpl::GetDecendantNode( const std::string & id ) {
		return spINode();
	}

	spcINode SourceImpl::GetChildNode( const std::string & id ) const {
		return spcINode();
	}

	spINode SourceImpl::GetChildNode( const std::string & id ) {
		return spINode();
	}

	INode::NodeList SourceImpl::GetAllChildren() {
		return NodeList();
	}

	INode::cNodeList SourceImpl::GetAllChildren() const {
		return cNodeList();
	}

	INode::NodeList SourceImpl::GetAllDecendants() {
		return NodeList();
	}

	INode::cNodeList SourceImpl::GetAllDecendants() const {
		return cNodeList();
	}

	size_t SourceImpl::GetReferenceCount() const {
		return mNode->GetReferenceCount();
	}

	spICustomData SourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData SourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}

	bool SourceImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mNode->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pINodeI SourceImpl::GetInternalNode() {
		return mNode->GetInternalNode();
	}

	pcINodeI SourceImpl::GetInternalNode() const {
		return mNode->GetInternalNode();
	}

	SourceImpl::SourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mNode( CreateNode( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeSource ) ){ }

	spISource CreateSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< SourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}
}
