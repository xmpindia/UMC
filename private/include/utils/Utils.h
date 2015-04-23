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
#include <vector>
#include <assert.h>

namespace INT_UMC {

	size_t RemoveFromUniqueIDSet( const spUniqueIDSet & uniqueIDSet, const spcINode & nodeToRemoved );
	size_t AddToUniqueIDSet( const spUniqueIDSet & uniqueIDSet, const std::string & uniqueID );

	template< typename mapElementType, typename mapType >
	mapElementType GetDecendantFromMap( const mapType & map, const std::string & descendantID ) {
		auto it = map.begin();
		auto itEnd = map.end();
		for ( ; it != itEnd; it++ ) {
			auto kidNode = it->second->GetDecendantNode( descendantID );
			if ( kidNode )
				return kidNode;
		}
		return mapElementType();
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

	template< typename mapElementType, typename mapType >
	void AddElementToMap( mapType & map, const std::string & elementID,
		const mapElementType & element, const spUniqueIDSet & uniqueIDSet ) {
		assert( element );
		assert( map.find( elementID ) == map.end() );
		map[ elementID ] = element;
		AddToUniqueIDSet( uniqueIDSet, elementID );
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

	template< typename mapType >
	size_t RemoveElementFromMap( mapType & map, const std::string & elementID,
		const spUniqueIDSet & uniqueIDSet )
	{
		auto it = map.find( elementID );
		if ( it != map.end() ) {
			assert( uniqueIDSet->find( elementID ) != uniqueIDSet->end() );
			size_t entriesRemoved = RemoveFromUniqueIDSet( uniqueIDSet, it->second );
			assert( entriesRemoved >= 1 );
			map.erase( it );
			return 1;
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
	size_t ClearMap( mapType & map, spUniqueIDSet & uniqueIDSet ) {
		size_t nCount( 0 );
		if ( map.size() == 0 )
			return 0;
		auto elements = CreateListFromMap< typename mapType::mapped_type, mapType >( map );
		auto it = elements.begin();
		auto itEnd = elements.end();
		while ( it != itEnd ) {
			RemoveElementFromMap( map, ( *it )->GetUniqueID(), uniqueIDSet );
			nCount++;
			it++;
		}
		assert( map.size() == 0 );
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
