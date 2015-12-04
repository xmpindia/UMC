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

		//!
		//! Generate a unique id based on the node type
		//! param[in] a value of type INode::eNodeTypes indicating the type of the node for which the unique id is to be generated
		//! \return a value of type std::string indicating the generated unique id
		//!
		virtual std::string GenerateUniqueID( INode::eNodeTypes nodeType ) = 0;
	};
}

#endif  // IUniqueIDGenerator_h__
