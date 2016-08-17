#ifndef ICustomData_h__
#define ICustomData_h__ 1

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

#include "UMCFwdDeclarations.h"

namespace UMC {

	//!
    //! \brief Interface for CustomData.
    //! \details This interface need to be implemented by all client's custom data classes to support custom data.
    //!

	class ICustomData {
	
	public:

		//!
		//! \brief Set the parent node for the current node
		//! \param[in] parentNode A weak pointer to the parent node
		//!
		virtual void SetParentNode( const wpIUMCNode & parentNode ) = 0;

		//!
		//! \brief Get the parent node for the current node
		//! \return a weak pointer to a const object of IUMCNode indicating the parent of the current node
		//!
		virtual wpcIUMCNode GetParentNode() const = 0;

		//!
		//! \brief Get the parent node for the current node
		//! \return  a weak pointer to a non-const object of IUMCNode indicating the parent of the current node
		//!
		virtual wpIUMCNode GetParentNode() = 0;
	};
}

#endif  // ICustomData_h__
