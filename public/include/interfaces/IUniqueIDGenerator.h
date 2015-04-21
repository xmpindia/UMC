#ifndef IUniqueIDGenerator_h__
#define IUniqueIDGenerator_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include <UMCFwdDeclarations.h>
#include "interfaces/INode.h"

namespace UMC {
	class IUniqueIDGenerator {
	public:
		virtual std::string GenerateUniqueID( INode::eNodeTypes nodeType ) = 0;
	};
}

#endif  // IUniqueIDGenerator_h__
