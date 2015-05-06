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

	bool SafeToRemoveElement( const spcINode & node ) {
		if ( node->GetReferenceCount() == 0  ) {
			auto list = node->GetAllChildren();
			for ( auto & element : list ) {
				if( !SafeToRemoveElement( element ) )
					return false;
			}
			return true;
		}
		return false;
	}

}

namespace UMC {
	const std::string kEmptyString("");
}
