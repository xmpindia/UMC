// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/NodeImpl.h"
#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include "interfaces/IUniqueIDGenerator.h"
#include "interfaces/ICustomDataHandlerRegistry.h"
#include "interfaces/ICustomDataHandler.h"
#include "interfaces/ICustomData.h"

#include "XMPCore/Interfaces/IXMPStructureNode.h"
#include <assert.h>

namespace INT_UMC {

	NodeImpl::NodeImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, eNodeTypes nodeType )
		: mUniqueID( uniqueIDGenerator->GenerateUniqueID( nodeType ) )
		, mspUniqueIDAndReferenceTracker( uniqueIDAndReferenceTracker )
		, mspUniqueIDGenerator( uniqueIDGenerator )
	{
		if ( !mspUniqueIDAndReferenceTracker ) THROW_UNIQUE_ID_AND_REFERENCE_TRACKER_CANT_BE_NULL;
		if ( !mspUniqueIDGenerator ) THROW_UNIQUE_ID_GENERATOR_CANT_BE_NULL;
	}

	INode::eNodeTypes NodeImpl::GetNodeType() const {
		return INode::kNodeTypeNone;
	}

	const std::string & NodeImpl::GetUniqueID() const {
		return mUniqueID;
	}

	wpcINode NodeImpl::GetParentNode() const {
		return mwpParentNode;
	}

	wpINode NodeImpl::GetParentNode() {
		return mwpParentNode;
	}

	spcINode NodeImpl::GetDecendantNode( const std::string & ) const {
		return spcINode();
	}

	spINode NodeImpl::GetDecendantNode( const std::string & ) {
		return spINode();
	}

	spcINode NodeImpl::GetChildNode( const std::string & ) const {
		return spcINode();
	}

	spINode NodeImpl::GetChildNode( const std::string & ) {
		return spINode();
	}

	INode::NodeList NodeImpl::GetAllChildren() {
		return NodeList();
	}

	INode::cNodeList NodeImpl::GetAllChildren() const {
		return cNodeList();
	}

	INode::NodeList NodeImpl::GetAllDecendants() {
		return NodeList();
	}

	INode::cNodeList NodeImpl::GetAllDecendants() const {
		return cNodeList();
	}

	size_t NodeImpl::GetReferenceCount() const {
		return mspUniqueIDAndReferenceTracker->GetReferenceCount( mUniqueID );
	}

	static bool HandleSimpleNode( const spICustomDataHandler & handler, const spcIXMPSimpleNode & node );
	static bool HandleStructureNode( const spICustomDataHandler & handler, const spcIXMPStructureNode & node );
	static bool HandleArrayNode( const spICustomDataHandler & handler, const spcIXMPArrayNode & node );

	static bool HandleNode( const spICustomDataHandler & handler, const spcIXMPNode & node ) {
		bool retValue( false );
		switch ( node->GetNodeType() ) {
		case IXMPNode::kXMPNodeTypeSimple:
			retValue = HandleSimpleNode( handler, node->AdaptConstNodeTo< IXMPSimpleNode >( node, IXMPNode::kXMPNodeTypeSimple ) );
			break;
		case IXMPNode::kXMPNodeTypeStructure:
			retValue = HandleStructureNode( handler, IXMPNode::AdaptConstNodeTo< IXMPStructureNode >( node, IXMPNode::kXMPNodeTypeStructure ) );
			break;
		case IXMPNode::kXMPNodeTypeArray:
			retValue = HandleArrayNode( handler, IXMPNode::AdaptConstNodeTo< IXMPArrayNode >( node, IXMPNode::kXMPNodeTypeArray ) );
			break;
		}
		return retValue;
	}

	static bool HandleSimpleNode( const spICustomDataHandler & handler, const spcIXMPSimpleNode & node ) {
		return handler->AddKeyValuePair( node->GetName()->c_str(), node->GetValue()->c_str() );
	}

	static bool HandleStructureNode( const spICustomDataHandler & handler, const spcIXMPStructureNode & node ) {
		const char * name = node->GetName()->c_str();
		if ( handler->BeginStructure( name ) ) {
			auto it = node->Iterator();
			while ( it ) {
				bool retValue = HandleNode( handler, it->GetNode() );
				if ( !retValue )
					return false;
				it = it->Next();
			}
			return handler->EndStructure( name );
		}
		return false;
	}

	static bool HandleArrayNode( const spICustomDataHandler & handler, const spcIXMPArrayNode & node ) {
		const char * name = node->GetName()->c_str();
		if ( handler->BeginArray( name ) ) {
			auto it = node->Iterator();
			while ( it ) {
				bool retValue = HandleNode( handler, it->GetNode() );
				if ( !retValue )
					return false;
				it = it->Next();
			}
			return handler->EndArray( name );
		}
		return false;
	}


	static spICustomData ParseNode( const spICustomDataHandler & handler, const spcIXMPNode & node ) {
		if ( handler->BeginCustomData() ) {
			if ( HandleNode( handler, node ) )
				return handler->EndCustomData();
		}
		return spICustomData();
	}

	spICustomData NodeImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		std::string combinedString = GetCombinedString( customDataNameSpace, customDataName );
		auto it = mCustomDataMap.find( combinedString );
		if ( it != mCustomDataMap.end() )
			return it->second;
		else {
			auto handler = ICustomDataHandlerRegistry::GetInstance()->GetHandler( customDataNameSpace, customDataName );
			auto node = mExtensionNode->GetNode( customDataNameSpace.c_str(), customDataName.c_str() );
			if ( handler && node ) {
				auto returnValue = ParseNode( handler, node );
				if ( returnValue ) SetCustomData(customDataNameSpace, customDataName, returnValue );
				return returnValue;
			}
		}
		return spICustomData();
	}

	spcICustomData NodeImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return const_cast< NodeImpl * >( this )->GetCustomData( customDataNameSpace, customDataName );
	}

	bool NodeImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		if ( customData &&
			ICustomDataHandlerRegistry::GetInstance()->IsHandlerRegistered( customDataNameSpace, customDataName ) ) 
		{
			std::string combinedString = GetCombinedString( customDataNameSpace, customDataName );
			mCustomDataMap[ combinedString ] = customData;
			customData->SetParentNode( shared_from_this() );
			if ( mExtensionNode )
				mExtensionNode->RemoveNode( customDataNameSpace.c_str(), customDataName.c_str() );
			return true;
		}
		return false;
	}

	void NodeImpl::RemoveFromDOM() {
		mspUniqueIDAndReferenceTracker->RemoveUniqueID( mUniqueID );
		mwpParentNode.reset();
	}

	void NodeImpl::AddToDOM( const spINode & parent ) {
		mspUniqueIDAndReferenceTracker->AddUniqueID( mUniqueID );
		if ( !parent ) THROW_PARENT_CANT_BE_NULL;
		mwpParentNode = parent;
	}

	pINodeI NodeImpl::GetInternalNode() {
		return this;
	}

	pcINodeI NodeImpl::GetInternalNode() const {
		return this;
	}

	void NodeImpl::SetExtensionNode( const spIXMPStructureNode & structureNode ) {
		if ( structureNode )
			mExtensionNode = IXMPNode::AdaptNodeTo< IXMPStructureNode >( structureNode->Clone(), IXMPNode::kXMPNodeTypeStructure );
		else
			mExtensionNode.reset();
	}

	NS_XMPCORE::spIXMPStructureNode NodeImpl::GetExtensionNode( bool create /*= false */ ) const {
		if ( !mExtensionNode && create )
			mExtensionNode = IXMPStructureNode::CreateStructureNode( kXMP_NS_XMP, "extension" );
		return mExtensionNode;
	}

	spcIUniqueIDGenerator NodeImpl::GetUniqueIDGenerator() const {
		return mspUniqueIDGenerator;
	}

	spIUniqueIDGenerator NodeImpl::GetUniqueIDGenerator() {
		return mspUniqueIDGenerator;
	}

	NS_XMPCORE::spIXMPStructureNode NodeImpl::GetMergedExtensionNode() const {
		if ( mCustomDataMap.size() > 0 ) {
			auto node = GetExtensionNode( true );
			auto it = mCustomDataMap.begin(); auto itEnd = mCustomDataMap.end();
			for ( ; it != itEnd; ++it ) {
				std::string nameSpace, name;
				if ( GetSplitStrings( it->first, nameSpace, name ) ) {
					auto handler = ICustomDataHandlerRegistry::GetInstance()->GetHandler( nameSpace, name );
					assert(  handler );
					auto serializerHandler = CreateSerializerHandler( it->second, nameSpace, name, node );
					handler->Serialize( it->second, serializerHandler );
				}
			}
			return node;
		} else {
			return GetExtensionNode( false );
		}
	}

	std::string NodeImpl::GetCombinedString( const std::string & nameSpace, const std::string & name ) const {
		std::string combinedString( nameSpace );
		combinedString.append( ":" ).append( name );
		return combinedString;
	}

	bool NodeImpl::GetSplitStrings( const std::string & combinedString, std::string & nameSpace, std::string & name ) const {
		size_t pos = combinedString.find_last_of( ":" );
		if ( pos != std::string::npos && pos != combinedString.length() - 1 ) {
			nameSpace.assign( combinedString, 0, pos );
			name.assign( combinedString, pos + 1, std::string::npos );
			return true;
		}
		return false;
	}

	spcIUniqueIDAndReferenceTracker NodeImpl::GetUniqueIDAndReferenceTracker() const {
		return mspUniqueIDAndReferenceTracker;
	}

	spIUniqueIDAndReferenceTracker NodeImpl::GetUniqueIDAndReferenceTracker() {
		return mspUniqueIDAndReferenceTracker;
	}

	spINode CreateNode( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, INode::eNodeTypes nodeType )
	{
		return std::make_shared< NodeImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, nodeType );
	}

}
