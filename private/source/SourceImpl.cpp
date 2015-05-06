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
		return mUniqueID;
	}

	void SourceImpl::SetClipName( const std::string & clipName ) {
		mClipName = clipName;
	}

	std::string SourceImpl::GetClipName() const  {
		return mClipName;
	}

	spcINode SourceImpl::GetParentNode() const  {
		return spcINode( mwpUMC );
	}

	spINode SourceImpl::GetParentNode() {
		return spINode( mwpUMC );
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
		return mspUniqueIDAndReferenceTracker->GetReferenceCount( mUniqueID );
	}

	void SourceImpl::RemoveFromDOM() {
		mspUniqueIDAndReferenceTracker->RemoveUniqueID( mUniqueID );
	}

	void SourceImpl::AddToDOM( const spINode & parent ) {
		mspUniqueIDAndReferenceTracker->AddUniqueID( mUniqueID );
		if ( !parent ) THROW_PARENT_CANT_BE_NULL;
		spIUMC umcParent = ConvertNode< IUMC >( parent );
		if ( !umcParent ) THROW_PARENT_CANT_BE_NULL;
		mwpUMC = umcParent;
	}

	SourceImpl::SourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mUniqueID( uniqueIDGenerator->GenerateUniqueID( INode::kNodeTypeSource ) )
		, mspUniqueIDAndReferenceTracker( uniqueIDAndReferenceTracker )
		, mspUniqueIDGenerator( uniqueIDGenerator )
	{
		if ( !mspUniqueIDAndReferenceTracker ) THROW_UNIQUE_ID_AND_REFERENCE_TRACKER_CANT_BE_NULL;
		if ( !mspUniqueIDGenerator ) THROW_UNIQUE_ID_GENERATOR_CANT_BE_NULL;
	}

}
