#ifndef IUniqueIDGenerator_h__
#define IUniqueIDGenerator_h__ 1

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


#include <UMCFwdDeclarations.h>
#include "interfaces/IUMCNode.h"

namespace UMC {
	class IUniqueIDGenerator {
	public:

		//!
		//! Generate a unique id based on the node type
		//! param[in] a value of type IUMCNode::eNodeTypes indicating the type of the node for which the unique id is to be generated
		//! \return a value of type std::string indicating the generated unique id
		//!
		virtual std::string GenerateUniqueID( IUMCNode::eNodeTypes nodeType ) = 0;
	};
}

#endif  // IUniqueIDGenerator_h__
