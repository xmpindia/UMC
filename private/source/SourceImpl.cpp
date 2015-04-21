// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/SourceImpl.h"
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

	SourceImpl::SourceImpl( const std::string & uniqueID, const spUniqueIDSet & uniqueIDSet,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIUMC & parent )
		: mUniqueID( uniqueID )
		, mwpUMC( parent )
		, mspUniqueIDSet( uniqueIDSet )
		, mspUniqueIDGenerator( uniqueIDGenerator )
	{
		if ( !parent ) THROW_PARENT_CANT_BE_NULL;
		if ( !mspUniqueIDSet ) THROW_UNIQUE_ID_MAP_CANT_BE_NULL;
		if ( !mspUniqueIDGenerator ) THROW_UNIQUE_ID_GENERATOR_CANT_BE_NULL;
	}

}
