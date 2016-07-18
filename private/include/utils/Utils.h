#ifndef Utils_h__
#define Utils_h__ 1

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

#include "UMCFwdDeclarations_I.h"
#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include "interfaces/IUMCNodeI.h"
#include "utils/UMCAndXMPMapping.h"
#include "XMPCore/Interfaces/IArrayNode.h"
#include "XMPCore/Interfaces/IStructureNode.h"

#include <vector>
#include <assert.h>

namespace INT_UMC {

	template< typename mapType >
	spIUMCNode GetDecendantFromMap( const mapType & map, const std::string & descendantID ) {
		auto it = map.begin();
		auto itEnd = map.end();
		for ( ; it != itEnd; it++ ) {
			spIUMCNode kidNode = it->second->GetDecendantNode( descendantID );
			if ( kidNode )
				return kidNode;
		}
		return spIUMCNode();
	}

	template< typename mapElementType, typename mapType >
	void AppendDecendantsFromMapToList( std::vector< mapElementType >& list, const mapType & map ) {
		auto it = map.begin();
		auto endIt = map.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
			auto decendantList = it->second->GetAllDecendants();
			auto innerIt = decendantList.begin();
			auto innerItEnd = decendantList.end();
			for ( ; innerIt != innerItEnd; innerIt++ ) {
				list.push_back( *innerIt );
			}
		}
	}

	template< typename mapType, typename mapElementType >
	void AddElementToMap( mapType & map, const mapElementType & element, const spIUMCNode & parent,
		const spIArrayNode & parentXMPArrayNode = spIArrayNode() ) {
		assert( element );
		const std::string & elementID = element->GetUniqueID();
		assert( map.find( elementID ) == map.end() );
		map[ elementID ] = element;
		auto internalPtr = element->GetInternalNode();
		internalPtr->AddToDOM( parent );
		spIStructureNode xmpNode = internalPtr->GetXMPNode();
		if ( !xmpNode->GetParent() ) {
			parentXMPArrayNode->AppendNode( internalPtr->GetXMPNode() );
			internalPtr->SetIndex( parentXMPArrayNode->ChildCount() );
		}
		assert( map.find( elementID ) != map.end() );
	}

	template< typename mapElementType, typename mapType >
	mapElementType GetElementFromMap( const mapType & map, const std::string & elementID ) {
		auto it = map.find( elementID );
		if ( it != map.end() ) {
			return it->second;
		}
		return mapElementType();
	}

	bool SafeToRemoveElement( const spcIUMCNode & node );

	template< typename mapType >
	void RemoveElementFromMap( mapType & map, typename mapType::iterator it, const spIArrayNode & parentArrayNode ) {
		it->second->GetInternalNode()->RemoveFromDOM();
		// search for the entry in the array node
		pIUMCNodeI ptr = it->second->GetInternalNode();
		auto index = ptr->GetIndex();
		parentArrayNode->RemoveNodeAtIndex( index );
		map.erase( it );
		auto it2 = map.begin();
		auto itEnd = map.end();
		for ( ; it2 != itEnd; ++it2 ) {
			pIUMCNodeI ptr2 = it2->second->GetInternalNode();
			size_t currentIndex = ptr2->GetIndex();
			if ( currentIndex > index )
				ptr2->SetIndex( currentIndex - 1 );
		}
	}

	template< typename mapElementType, typename mapType >
	void ChangeUniqueIDOfChildNode( mapType & map, const spIUMCNode & node, const std::string & newUniqueID,
		const spIArrayNode & parentArrayNode, const spIUMCNode & parentNode )
	{
		auto childNode = ConvertNode< mapElementType >( node );
		map.erase( node->GetUniqueID() );
		childNode->GetInternalNode()->ChangeUniqueID( newUniqueID );
		map[ newUniqueID ] = childNode;
	}

	template< typename mapType >
	size_t TryAndRemoveElementFromMap( mapType & map, const std::string & elementID, const spIArrayNode & parentNode ) {
		auto it = map.find( elementID );
		if ( it != map.end() ) {
			if ( SafeToRemoveElement( it->second ) ) {
				RemoveElementFromMap( map, it, parentNode );
				return 1;
			} else {
				// element is still referenced somewhere in the node, so can't be removed.
				THROW_NODE_IS_REFERENCED( "remove" );
				return 0;
			}
		}
		return 0;
	}

	template< typename MapType >
	void CallSyncUMCToXMPOnMapElements( const MapType & map ) {
		auto it = map.begin();
		auto endIt = map.end();
		for ( ; it != endIt; it++ ) {
			it->second->GetInternalNode()->SyncUMCToXMP();
		}
	}

	template< typename OutputListElementType, typename MapType >
	void AppendToListFromMap( std::vector< OutputListElementType > & list, const MapType & map ) {
		auto it = map.begin();
		auto endIt = map.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
		}
	}

	template< typename OutputListElementType, typename MapType >
	std::vector< OutputListElementType > CreateListFromMap( const MapType & map ) {
		std::vector< OutputListElementType > list;
		AppendToListFromMap( list, map );
		return list;
	}

	template< typename mapType >
	bool SafeToClearMap( const mapType & map ) {
		auto it = map.begin();
		auto itEnd = map.end();
		for ( ; it != itEnd; it++ ) {
			if ( !SafeToRemoveElement( it->second ) )
				return false;
			}
		return true;
	}

	template< typename mapType >
	size_t ClearMap( mapType & map, const spIArrayNode & arrayNode ) {
		size_t nCount( map.size() );
		if ( nCount > 0 ) {
			auto it = map.begin(); auto itEnd = map.end();
			for ( ; it != itEnd; ++it ) {
				it->second->GetInternalNode()->RemoveFromDOM();
			}
			map.clear();
			arrayNode->Clear();
		}
		return nCount;
	}

	template< typename OutputListElementType, typename MapType,
		typename OutputListRequiredType, OutputListRequiredType allType >
	std::vector< OutputListElementType > CreateSelectedListFromMap( const MapType & map,
		OutputListRequiredType requiredType )
	{
		std::vector< OutputListElementType > list;
		auto it = map.begin();
		auto endIt = map.end();
		for ( ; it != endIt; it++ ) {
			switch ( requiredType ) {
			case allType:
				list.push_back( it->second );
				break;

			default:
				if ( it->second->GetType() == requiredType )
					list.push_back( it->second );
				break;
			}
		}
		return list;
	}

	AdobeXMPCore::spIDOMSerializer GetSerializer( bool reset = false );
	AdobeXMPCore::spIDOMParser GetParser( bool reset = false );

	void CreateEquivalentXMPNodes(
		const spIStructureNode & parent, spIArrayNode & arrayNode, const NamespacePropertyNamePair & arrayPair );
	
	void CreateEquivalentXMPNodes(
		const spIStructureNode & parent, spIArrayNode & arrayNode, const NamespacePropertyNamePair & arrayPair,
		spIStructureNode & containerNode, const NamespacePropertyNamePair & containerPair );

	spIArrayNode TryToGetArrayNode( const spIStructureNode & parentNode, const NamespacePropertyNamePair & pair );
	spIStructureNode TryToGetStructNode( const spIStructureNode & parentNode, const NamespacePropertyNamePair & pair );
	spISimpleNode TryToGetSimpleNode( const spIStructureNode & parentNode, const NamespacePropertyNamePair & pair );

	template < typename mapElementType, typename className >
	size_t PopulateMapFromXMPArrayNode( className * obj, mapElementType( className::*AddFuncPtr )( const spIStructureNode & ),
		const spIArrayNode & arrayNode )
	{
		size_t count( 0 );
		if ( arrayNode && arrayNode->ChildCount() > 0 ) {
			for ( size_t i = 1, total = arrayNode->ChildCount(); i <= total; ++i ) {
				try {
					spIStructureNode childNode = arrayNode->GetStructureNodeAtIndex( i );
					spIUMCNode umcNode = ( obj->*AddFuncPtr )( childNode );
					if ( umcNode ) {
						count++;
						umcNode->GetInternalNode()->SetIndex( i );
					}
				} catch ( ... ) {}
			}
		}
		return count;
	}

	template < typename mapElementType, typename className >
	size_t PopulateMapFromXMPArrayNode( className * obj, mapElementType( className::*AddFuncPtr )( const spIStructureNode &, const spIUMCNode & ),
		const spIArrayNode & arrayNode, const spIUMCNode & spNode )
	{
		size_t count( 0 );
		if ( arrayNode && arrayNode->ChildCount() > 0 ) {
			for ( size_t i = 1, total = arrayNode->ChildCount(); i <= total; ++i ) {
				try {
					spIStructureNode childNode = arrayNode->GetStructureNodeAtIndex( i );
					spIUMCNode umcNode = ( obj->*AddFuncPtr )( childNode, spNode );
					if ( umcNode ) {
						count++;
						umcNode->GetInternalNode()->SetIndex( i );
					}
				} catch ( ... ) {}
			}
		}
		return count;
	}
}
#endif  // Utils_h__
