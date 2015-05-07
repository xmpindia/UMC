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
	void AddElementToMap( mapType & map, const mapElementType & element, const spINode & parent ) {
		assert( element );
		const std::string & elementID = element->GetUniqueID();
		assert( map.find( elementID ) == map.end() );
		map[ elementID ] = element;
		element->AddToDOM( parent );
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
	void RemoveElementFromMap( mapType & map, typename mapType::iterator it ) {
		it->second->RemoveFromDOM();
		map.erase( it );
	}

	template< typename mapType >
	size_t TryAndRemoveElementFromMap( mapType & map, const std::string & elementID ) {
		auto it = map.find( elementID );
		if ( it != map.end() ) {
			if ( SafeToRemoveElement( it->second ) ) {
				RemoveElementFromMap( map, it );
				return 1;
			} else {
				// element is still referenced somewhere in the node, so can't be removed.
				THROW_NODE_IS_REFERENCED( "remove" );
				return 0;
			}
		}
		return 0;
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
	size_t ClearMap( mapType & map ) {
		size_t nCount( map.size() );
		if ( nCount > 0 ) {
			auto it = map.begin(); auto itEnd = map.end();
			for ( ; it != itEnd; ++it ) {
				it->second->RemoveFromDOM();
			}
			map.clear();
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

}
#endif  // Utils_h__
