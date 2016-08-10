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


#include "implHeaders/NodeImpl.h"
#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include "interfaces/IUniqueIDGenerator.h"
#include "interfaces/ICustomDataHandlerRegistry.h"
#include "interfaces/ICustomDataHandler.h"
#include "interfaces/ICustomData.h"
#include "utils/UMCAndXMPMapping.h"
#include "utils/Utils.h"

#include "XMPCore/Interfaces/IStructureNode.h"
#include "XMPCore/Interfaces/IMetadata.h"
#include "XMPCore/Interfaces/ICoreObjectFactory.h"
#include "XMPCore/Interfaces/INode.h"
#include "XMPCore/Interfaces/INodeIterator.h"
#include "XMPCommon/Interfaces/IUTF8String.h"
#include <assert.h>

namespace INT_UMC {

	using AdobeXMPCommon::npos;
	NodeImpl::NodeImpl()
		: mXMPStructureNode( IMetadata::CreateMetadata() )
		, mIndex( size_t(-1) ) { }

	NodeImpl::NodeImpl( const spIStructureNode & structureNode )
		: mXMPStructureNode( structureNode )
		, mIndex( size_t(-1) ) { }
	
	NodeImpl::NodeImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, IUMCNode::eNodeTypes nodeType,
		const NamespacePropertyNamePair & namespacePropertyNamePair )
		: mXMPStructureNode( IStructureNode::CreateStructureNode( namespacePropertyNamePair.first, npos, namespacePropertyNamePair.second, npos ) )
		, mIndex( size_t(-1) ) 
	{
		Init( uniqueIDAndReferenceTracker, uniqueIDGenerator, nodeType );
	}

	NodeImpl::NodeImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, IUMCNode::eNodeTypes nodeType,
		const spIStructureNode & xmpStructureNode )
		: mXMPStructureNode( xmpStructureNode )
		, mIndex( size_t(-1) ) 
	{
		Init( uniqueIDAndReferenceTracker, uniqueIDGenerator, nodeType );
	}

	void NodeImpl::Init( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, IUMCNode::eNodeTypes nodeType )
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

	wpcIUMCNode NodeImpl::GetParentNode() const {
		return mwpParentNode;
	}

	wpIUMCNode NodeImpl::GetParentNode() {
		return mwpParentNode;
	}

	size_t NodeImpl::GetReferenceCount() const {
		return mspUniqueIDAndReferenceTracker->GetReferenceCount( mUniqueID );
	}

	static bool HandleSimpleNode( const spICustomDataHandler & handler, const spcISimpleNode & node );
	static bool HandleStructureNode( const spICustomDataHandler & handler, const spcIStructureNode & node );
	static bool HandleArrayNode( const spICustomDataHandler & handler, const spcIArrayNode & node );

	static bool HandleNode( const spICustomDataHandler & handler, const spcINode & node ) {
		bool retValue( false );
		switch ( node->GetNodeType() ) {
		case INode::kNTSimple:
			retValue = HandleSimpleNode( handler, node->ConvertToSimpleNode() );
			break;
		case INode::kNTStructure:
			retValue = HandleStructureNode( handler, node->ConvertToStructureNode() );
			break;
		case INode::kNTArray:
			retValue = HandleArrayNode( handler, node->ConvertToArrayNode()) ;
			break;
		}
		return retValue;
	}

	static bool HandleCustomDataNode( const spICustomDataHandler & handler, const spcIStructureNode & node ) {
		auto it = node->Iterator();
		while ( it ) {
			bool retValue = HandleNode( handler, it->GetNode() );
			if ( !retValue )
				return false;
			it = it->Next();
		}
		return true;
	}

	static bool HandleSimpleNode( const spICustomDataHandler & handler, const spcISimpleNode & node ) {
		return handler->AddKeyValuePair(node->GetName()->c_str(), node->GetValue()->c_str());
	}

	static bool HandleStructureNode( const spICustomDataHandler & handler, const spcIStructureNode & node ) {
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

	static bool HandleArrayNode( const spICustomDataHandler & handler, const spcIArrayNode & node ) {
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


	static spICustomData ParseNode( const spICustomDataHandler & handler, const spcIStructureNode & node ) {
		if ( handler->BeginCustomData() ) {
			if ( HandleCustomDataNode( handler, node ) )
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
			auto node = mExtensionNode != nullptr ? mExtensionNode->GetStructureNode( customDataNameSpace.c_str(), npos, customDataName.c_str(), npos ): nullptr;
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
				mExtensionNode->RemoveNode( customDataNameSpace.c_str(), npos, customDataName.c_str(), npos );
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

	void NodeImpl::AddToDOM( const spIUMCNode & parent ) {
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
			mExtensionNode = IStructureNode::CreateStructureNode( kExtensionPair.first, npos, kExtensionPair.second, npos );
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

	std::string NodeImpl::GetParsedID() const {
		std::string parsedID;
		mspUniqueIDAndReferenceTracker->GetUserUniqueID( mUniqueID, parsedID, false );
		return parsedID;
	}

	bool NodeImpl::SetUniqueID( const std::string & newUniqueID ) {
		if ( newUniqueID.length() == 0 )
			return false;
		if ( mUniqueID.compare( newUniqueID ) == 0 )
			return true;
		if ( mspUniqueIDAndReferenceTracker->IsUniqueIDPresent( newUniqueID) )
			return false;
		size_t referenceCount = mspUniqueIDAndReferenceTracker->GetReferenceCount( mUniqueID );
		std::string oldUniqueID = mUniqueID;
		std::string userUniqueID = GetParsedID();
		spIUMCNode parentNode = mwpParentNode.lock();
		if ( parentNode && parentNode->GetInternalNode()->ChangeChildUniqueID( GetExternalNode(), newUniqueID ) ) {
			mspUniqueIDAndReferenceTracker->RemoveUniqueID( oldUniqueID );
			mspUniqueIDAndReferenceTracker->AddUniqueID( newUniqueID );
			for( size_t i = 0; i < referenceCount; ++i ) {
				mspUniqueIDAndReferenceTracker->AddReference( newUniqueID );
			}
			if ( userUniqueID.length() > 0 ) {
				mspUniqueIDAndReferenceTracker->RemoveUserUniqueID( userUniqueID );
				mspUniqueIDAndReferenceTracker->AddUserUniqueID( userUniqueID, newUniqueID );
			}
		}
		return true;
	}

	void NodeImpl::ChangeUniqueID( const std::string & newUniqueID ) {
		mUniqueID = newUniqueID;
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
			if ( !mspUniqueIDAndReferenceTracker->AddUserUniqueID( oldUniqueID->c_str(), mUniqueID ) )
				THROW_PARSED_ID_NOT_UNIQUE;
			SetUniqueID( oldUniqueID->c_str() );
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
