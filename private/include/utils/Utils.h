#ifndef Utils_h__
#define Utils_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations_I.h"
#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include "interfaces/INodeI.h"
#include "utils/UMCAndXMPMapping.h"

#include <vector>
#include <assert.h>

namespace INT_UMC {

	template< typename mapType >
	spINode GetDecendantFromMap( const mapType & map, const std::string & descendantID ) {
		auto it = map.begin();
		auto itEnd = map.end();
		for ( ; it != itEnd; it++ ) {
			spINode kidNode = it->second->GetDecendantNode( descendantID );
			if ( kidNode )
				return kidNode;
		}
		return spINode();
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
	void AddElementToMap( mapType & map, const mapElementType & element, const spINode & parent,
		const spIXMPArrayNode & parentXMPArrayNode = spIXMPArrayNode() ) {
		assert( element );
		const std::string & elementID = element->GetUniqueID();
		assert( map.find( elementID ) == map.end() );
		map[ elementID ] = element;
		auto internalPtr = element->GetInternalNode();
		internalPtr->AddToDOM( parent );
		spIXMPStructureNode xmpNode = internalPtr->GetXMPNode();
		if ( !xmpNode->GetParent() ) {
			parentXMPArrayNode->AppendNode( internalPtr->GetXMPNode() );
			internalPtr->SetIndex( parentXMPArrayNode->GetChildCount() );
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

	bool SafeToRemoveElement( const spcINode & node );

	template< typename mapType >
	void RemoveElementFromMap( mapType & map, typename mapType::iterator it, const spIXMPArrayNode & parentArrayNode ) {
		it->second->GetInternalNode()->RemoveFromDOM();
		// search for the entry in the array node
		pINodeI ptr = it->second->GetInternalNode();
		auto index = ptr->GetIndex();
		parentArrayNode->RemoveNode( index );
		map.erase( it );
		auto it2 = map.begin();
		auto itEnd = map.end();
		for ( ; it2 != itEnd; ++it2 ) {
			pINodeI ptr2 = it2->second->GetInternalNode();
			size_t currentIndex = ptr2->GetIndex();
			if ( currentIndex > index )
				ptr2->SetIndex( currentIndex - 1 );
		}
	}

	template< typename mapType >
	size_t TryAndRemoveElementFromMap( mapType & map, const std::string & elementID, const spIXMPArrayNode & parentNode ) {
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
	size_t ClearMap( mapType & map, const spIXMPArrayNode & arrayNode ) {
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

	NS_XMPCORE::spIXMPDOMSerializer GetSerializer( bool reset = false );
	NS_XMPCORE::spIXMPDOMParser GetParser( bool reset = false );

	void CreateEquivalentXMPNodes(
		const spIXMPStructureNode & parent, spIXMPArrayNode & arrayNode, const NamespacePropertyNamePair & arrayPair );
	
	void CreateEquivalentXMPNodes(
		const spIXMPStructureNode & parent, spIXMPArrayNode & arrayNode, const NamespacePropertyNamePair & arrayPair,
		spIXMPStructureNode & containerNode, const NamespacePropertyNamePair & containerPair );

	spIXMPArrayNode TryToGetArrayNode( const spIXMPStructureNode & parentNode, const NamespacePropertyNamePair & pair );
	spIXMPStructureNode TryToGetStructNode( const spIXMPStructureNode & parentNode, const NamespacePropertyNamePair & pair );
	spIXMPSimpleNode TryToGetSimpleNode( const spIXMPStructureNode & parentNode, const NamespacePropertyNamePair & pair );

	template < typename mapElementType, typename className >
	size_t PopulateMapFromXMPArrayNode( className * obj, mapElementType( className::*AddFuncPtr )( const spIXMPStructureNode & ),
		const spIXMPArrayNode & arrayNode )
	{
		size_t count( 0 );
		if ( arrayNode && arrayNode->GetChildCount() > 0 ) {
			for ( size_t i = 1, total = arrayNode->GetChildCount(); i <= total; ++i ) {
				try {
					spIXMPStructureNode childNode = arrayNode->GetStructureNode( i );
					spINode umcNode = ( obj->*AddFuncPtr )( childNode );
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
	size_t PopulateMapFromXMPArrayNode( className * obj, mapElementType( className::*AddFuncPtr )( const spIXMPStructureNode &, const spINode & ),
		const spIXMPArrayNode & arrayNode, const spINode & spNode )
	{
		size_t count( 0 );
		if ( arrayNode && arrayNode->GetChildCount() > 0 ) {
			for ( size_t i = 1, total = arrayNode->GetChildCount(); i <= total; ++i ) {
				try {
					spIXMPStructureNode childNode = arrayNode->GetStructureNode( i );
					spINode umcNode = ( obj->*AddFuncPtr )( childNode, spNode );
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
