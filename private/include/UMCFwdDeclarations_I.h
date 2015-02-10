#ifndef UMCFwdDeclarations_I_h__
#define UMCFwdDeclarations_I_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include "UMCDefines_I.h"

namespace INT_UMC {

	// IObjectFactory_I
	class IObjectFactory_I;
	typedef IObjectFactory_I *									pIObjectFactory_I;
	typedef const IObjectFactory_I *							pcIObjectFactory_I;
	typedef shared_ptr< IObjectFactory_I >						spIObjectFactory_I;
	typedef shared_ptr< const IObjectFactory_I >				spcIObjectFactory_I;
	
};

#endif  // UMCFwdDeclarations_I_h__
