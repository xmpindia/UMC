// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/CustomDataHandlerImpl.h"
#include "interfaces/ICustomData.h"
#include "XMPCore/Interfaces/IXMPArrayNode.h"
#include "XMPCore/Interfaces/IXMPStructureNode.h"
#include "XMPCore/Interfaces/IXMPSimpleNode.h"
#include "XMPCore/Interfaces/IXMPCoreObjectFactory.h"
#include <assert.h>

namespace INT_UMC {

	CustomDataHandlerImpl::CustomDataHandlerImpl( const spcICustomData & customData, const std::string & customDataNameSpace,
		const std::string & customDataName, const spIXMPStructureNode & baseNode )
		: mNameSpace( customDataNameSpace )
		, mBaseNode( baseNode )
	{
		spIXMPStructureNode node = IXMPStructureNode::CreateStructureNode( mNameSpace.c_str(), customDataName.c_str() );
		mParents.push( Parent( node ) );
	}

	bool CustomDataHandlerImpl::BeginCustomData() {
		return true;
	}

	spICustomData CustomDataHandlerImpl::EndCustomData() {
		assert( mParents.size() == 1 );
		mBaseNode->InsertNode( mParents.top().mStructNode );
		mParents.pop();
		return spICustomData();
	}

	bool CustomDataHandlerImpl::BeginStructure( const std::string & structureName ) {
		spIXMPStructureNode node = IXMPStructureNode::CreateStructureNode( mNameSpace.c_str(), structureName.c_str() );
		mParents.push( Parent( node ) );
		return true;
	}

	bool CustomDataHandlerImpl::EndStructure( const std::string & structureName ) {
		assert( mParents.top().mIsArray == false );
		assert( structureName.compare( mParents.top().mStructNode->GetName()->c_str() ) == 0 );
		assert( mParents.size() > 1 );

		auto node = mParents.top().mStructNode;
		mParents.pop();
		if ( mParents.top().mIsArray )
			mParents.top().mArrayNode->AppendNode( node );
		else
			mParents.top().mStructNode->AppendNode( node );
		return true;
	}

	bool CustomDataHandlerImpl::BeginArray( const std::string & arrayName ) {
		spIXMPArrayNode node = IXMPArrayNode::CreateUnorderedArrayNode( mNameSpace.c_str(), arrayName.c_str() );
		mParents.push( Parent( node ) );
		return true;
	}

	bool CustomDataHandlerImpl::EndArray( const std::string & arrayName ) {
		assert( mParents.top().mIsArray == true );
		assert( arrayName.compare( mParents.top().mArrayNode->GetName()->c_str() ) == 0 );
		assert( mParents.size() > 1 );

		auto node = mParents.top().mArrayNode;
		mParents.pop();
		if ( mParents.top().mIsArray )
			mParents.top().mArrayNode->AppendNode( node );
		else
			mParents.top().mStructNode->AppendNode( node );
		return true;
	}

	bool CustomDataHandlerImpl::AddKeyValuePair( const std::string & key, const std::string & value ) {
		if ( mParents.top().mIsArray )
			mParents.top().mArrayNode->AppendNode( IXMPSimpleNode::CreateSimpleNode( mNameSpace.c_str(), key.c_str(), value.c_str() ) );
		else
			mParents.top().mStructNode->AppendNode( IXMPSimpleNode::CreateSimpleNode( mNameSpace.c_str(), key.c_str(), value.c_str() ) );
		return true;
	}

	bool CustomDataHandlerImpl::Serialize( const spICustomData & data, const spICustomDataHandler & customDataCreator ) const {
		return false;
	}

	CustomDataHandlerImpl::Parent::Parent( const spIXMPStructureNode & structureNode )
		: mStructNode( structureNode )
		, mIsArray( false ) { }

	CustomDataHandlerImpl::Parent::Parent( const spIXMPArrayNode & arrayNode )
		: mArrayNode( arrayNode )
		, mIsArray( true ) { }

	spICustomDataHandler CreateSerializerHandler( const spcICustomData & customData, const std::string & customDataNameSpace,
		const std::string & customDataName, const spIXMPStructureNode & baseNode )
	{
		return std::make_shared< CustomDataHandlerImpl >( customData, customDataNameSpace, customDataName, baseNode );
	}
}

