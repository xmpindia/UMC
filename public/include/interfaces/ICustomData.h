#ifndef ICustomData_h__
#define ICustomData_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"

namespace UMC {

	class ICustomData {
	
	public:

		//!
		//! Set the parent node for the current node
		//! \param[in] a weak pointer to the parent node
		//!
		virtual void SetParentNode( const wpINode & parentNode ) = 0;

		//!
		//! Get the parent node for the current node
		//! \return  a weak pointer to a const object of INode indicating the parent of the current node
		//!
		virtual wpcINode GetParentNode() const = 0;

		//!
		//! Get the parent node for the current node
		//! \return  a weak pointer to a non-const object of INode indicating the parent of the current node
		//!
		virtual wpINode GetParentNode() = 0;
	};
}

#endif  // ICustomData_h__
