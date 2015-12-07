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
#include "XMPCore/Interfaces/IArrayNode.h"
#include "XMPCore/Interfaces/IStructureNode.h"
#include "XMPCore/Interfaces/ISimpleNode.h"
#include "XMPCore/Interfaces/ICoreObjectFactory.h"
#include "XMPCommon/Interfaces/IUTF8String.h"
#include <assert.h>

namespace INT_UMC {

	CustomDataHandlerImpl::CustomDataHandlerImpl( const spcICustomData & customData, const std::string & customDataNameSpace,
		const std::string & customDataName, const spIStructureNode & baseNode )
		: mNameSpace( customDataNameSpace )
		, mBaseNode( baseNode )
	{
		spIStructureNode node = IStructureNode::CreateStructureNode( mNameSpace.c_str(), mNameSpace.length(), customDataName.c_str(), customDataName.length() );
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
		spIStructureNode node = IStructureNode::CreateStructureNode( mNameSpace.c_str(), mNameSpace.length(), structureName.c_str(), structureName.length() );
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
		spIArrayNode node = IArrayNode::CreateUnorderedArrayNode( mNameSpace.c_str(), mNameSpace.length(), arrayName.c_str(), arrayName.length() );
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
			mParents.top().mArrayNode->AppendNode( ISimpleNode::CreateSimpleNode( mNameSpace.c_str(), mNameSpace.length(), key.c_str(), key.length(), value.c_str(), value.length() ) );
		else
			mParents.top().mStructNode->AppendNode( ISimpleNode::CreateSimpleNode( mNameSpace.c_str(), mNameSpace.length(), key.c_str(), key.length(), value.c_str(), value.length() ) );
		return true;
	}

	bool CustomDataHandlerImpl::Serialize( const spICustomData & data, const spICustomDataHandler & customDataCreator ) const {
		return false;
	}

	CustomDataHandlerImpl::Parent::Parent( const spIStructureNode & structureNode )
		: mStructNode( structureNode )
		, mIsArray( false ) { }

	CustomDataHandlerImpl::Parent::Parent( const spIArrayNode & arrayNode )
		: mArrayNode( arrayNode )
		, mIsArray( true ) { }

	spICustomDataHandler CreateSerializerHandler( const spcICustomData & customData, const std::string & customDataNameSpace,
		const std::string & customDataName, const spIStructureNode & baseNode )
	{
		return std::make_shared< CustomDataHandlerImpl >( customData, customDataNameSpace, customDataName, baseNode );
	}
}

