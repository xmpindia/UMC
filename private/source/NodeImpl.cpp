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
#include "utils/UMCAndXMPMapping.h"
#include "utils/Utils.h"

#include "XMPCore/Interfaces/IXMPStructureNode.h"
#include "XMPCore/Interfaces/IXMPCoreObjectFactory.h"
#include <assert.h>

namespace INT_UMC {

	NodeImpl::NodeImpl()
		: mXMPStructureNode( IXMPMetadata::CreateMetadata() )
		, mIndex( size_t(-1) ) { }

	NodeImpl::NodeImpl( const spIXMPStructureNode & structureNode )
		: mXMPStructureNode( structureNode )
		, mIndex( size_t(-1) ) { }
	
	NodeImpl::NodeImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, INode::eNodeTypes nodeType,
		const NamespacePropertyNamePair & namespacePropertyNamePair )
		: mXMPStructureNode( IXMPStructureNode::CreateStructureNode( namespacePropertyNamePair.first, namespacePropertyNamePair.second ) )
		, mIndex( size_t(-1) ) 
	{
		Init( uniqueIDAndReferenceTracker, uniqueIDGenerator, nodeType );
	}

	NodeImpl::NodeImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, INode::eNodeTypes nodeType,
		const spIXMPStructureNode & xmpStructureNode )
		: mXMPStructureNode( xmpStructureNode )
		, mIndex( size_t(-1) ) 
	{
		Init( uniqueIDAndReferenceTracker, uniqueIDGenerator, nodeType );
	}

	void NodeImpl::Init( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, INode::eNodeTypes nodeType )
	{
		if ( !uniqueIDAndReferenceTracker ) THROW_UNIQUE_ID_AND_REFERENCE_TRACKER_CANT_BE_NULL;
		if ( !uniqueIDGenerator ) THROW_UNIQUE_ID_GENERATOR_CANT_BE_NULL;
		mspUniqueIDAndReferenceTracker = uniqueIDAndReferenceTracker;
		mspUniqueIDGenerator = uniqueIDGenerator;
		mUniqueID = mspUniqueIDGenerator->GenerateUniqueID( nodeType );
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
				mCustomDataMap[ combinedString ] = returnValue;
				returnValue->SetParentNode( mwpParentNode.lock() );
				return returnValue;
			}
		}
		return spICustomData();
	}

	spcICustomData NodeImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return const_cast< NodeImpl * >( this )->GetCustomData( customDataNameSpace, customDataName );
	}

	bool NodeImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData )
	{
		if ( customData ) {
			auto handler = ICustomDataHandlerRegistry::GetInstance()->GetHandler( customDataNameSpace, customDataName );
			if ( handler ) {
				CreateExtensionNodeIfRequired();
				std::string combinedString = GetCombinedString( customDataNameSpace, customDataName );
				mCustomDataMap[ combinedString ] = customData;
				customData->SetParentNode( mwpParentNode.lock() );
				mExtensionNode->RemoveNode( customDataNameSpace.c_str(), customDataName.c_str() );
				auto serializerHandler = CreateSerializerHandler( customData, customDataNameSpace, customDataName, mExtensionNode );
				handler->Serialize( customData, serializerHandler );
				return true;
			}
		}
		return false;
	}

	void NodeImpl::RemoveFromDOM() {
		CleanUpOnRemovalFromDOM();
		mspUniqueIDAndReferenceTracker->RemoveUniqueID( mUniqueID );
		mwpParentNode.reset();
	}

	void NodeImpl::AddToDOM( const spINode & parent ) {
		mspUniqueIDAndReferenceTracker->AddUniqueID( mUniqueID );
		if ( !parent ) THROW_PARENT_CANT_BE_NULL;
		mwpParentNode = parent;
		SetUpOnAdditionToDOM();
	}

	spcIUniqueIDGenerator NodeImpl::GetUniqueIDGenerator() const {
		return mspUniqueIDGenerator;
	}

	spIUniqueIDGenerator NodeImpl::GetUniqueIDGenerator() {
		return mspUniqueIDGenerator;
	}

	NodeImpl::~NodeImpl() { }

	void NodeImpl::CreateExtensionNodeIfRequired() {
		if ( !mExtensionNode ) {
			mExtensionNode = IXMPStructureNode::CreateStructureNode( kExtensionPair.first, kExtensionPair.second );
			mXMPStructureNode->AppendNode( mExtensionNode );
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

	void NodeImpl::SetIndex( size_t index ) {
		mIndex = index;
	}

	size_t NodeImpl::GetIndex() const {
		return mIndex;
	}

	void NodeImpl::SyncUMCToXMP() const {
		AddOrUpdateDataToXMPDOM( mUniqueID, kUniqueIDPair, mXMPStructureNode );
		SyncInternalStuffToXMP();
	}

	void NodeImpl::SyncXMPToUMC() {
		mExtensionNode = TryToGetStructNode( mXMPStructureNode, kExtensionPair );
		auto uniqueIDNode = TryToGetSimpleNode( mXMPStructureNode, kUniqueIDPair );
		if ( uniqueIDNode ) {
			auto oldUniqueID = uniqueIDNode->GetValue();
			mspUniqueIDAndReferenceTracker->AddUserUniqueID( oldUniqueID->c_str(), mUniqueID );
		} else {
			THROW_UNIQUE_ID_IS_MISSING;
		}
		if ( ValidateXMPNode() )
			SyncXMPToInternalStuff();
		else
			THROW_XMPSTRUCTURE_NODE_VALIDATION_FAILED( "unknown reason" );
	}

	spcIUniqueIDAndReferenceTracker NodeImpl::GetUniqueIDAndReferenceTracker() const {
		return mspUniqueIDAndReferenceTracker;
	}

	spIUniqueIDAndReferenceTracker NodeImpl::GetUniqueIDAndReferenceTracker() {
		return mspUniqueIDAndReferenceTracker;
	}

}
