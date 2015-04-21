// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "utils/Utils.h"
#include "interfaces/INode.h"

namespace INT_UMC {
	
	//std::string & PopulateString( std::string & dest, const char * buffer, size_t lenOfBuffer ) {
	//	if ( buffer && lenOfBuffer > 0 ) {
	//		if ( lenOfBuffer == npos ) dest.assign( buffer ); else dest.assign( buffer, lenOfBuffer );
	//	} else {
	//		dest.clear();
	//	}
	//	return dest;
	//}

	size_t RemoveFromUniqueIDSet( const spUniqueIDSet & uniqueIDSet, const spcINode & nodeToRemoved ) {
		size_t count = uniqueIDSet->erase( nodeToRemoved->GetUniqueID() );
		assert( count == 1 );
		if ( count > 0 ) {
			auto decendants = nodeToRemoved->GetAllDecendants();
			auto it = decendants.begin();
			auto itEnd = decendants.end();
			for( ; it != itEnd; it++ ) {
				size_t innerCount = uniqueIDSet->erase( (*it)->GetUniqueID() );
				assert( innerCount > 0 );
				count += innerCount;
			}
		}
		return count;
	}

	//std::string GetUniqueID() {
	//	static int count = 0;
	//	static char buffer[30] = "";
	//	itoa( count, buffer, 10 );
	//	return std::string( buffer );
	//}

	size_t AddToUniqueIDSet( const spUniqueIDSet & uniqueIDSet, const std::string & uniqueID ) {
		auto pair = uniqueIDSet->insert( uniqueID );
		assert( pair.second == true );
		if ( pair.second )
			return 1;
		else
			return 0;
	}

}

namespace UMC {
	const std::string kEmptyString("");
}
