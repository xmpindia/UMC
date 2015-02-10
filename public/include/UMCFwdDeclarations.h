#ifndef UMCFwdDeclarations_h__
#define UMCFwdDeclarations_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "UMCDefines.h"
#include "baseTypes/SmartPointers.h"

namespace UMC {

	// ISource
	class ISource;
	typedef ISource *								pISource;
	typedef const ISource *							pcISource;
	typedef shared_ptr< ISource >					spISource;
	typedef shared_ptr< const ISource >				spcISource;

	// IUMC
	class IUMC;
	typedef IUMC *									pIUMC;
	typedef const IUMC *							pcIUMC;
	typedef shared_ptr< IUMC >						spIUMC;
	typedef shared_ptr< const IUMC >				spcIUMC;
	
};

#endif  // UMCFwdDeclarations_h__
