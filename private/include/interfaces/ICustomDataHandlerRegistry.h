#ifndef ICustomDataHandlerRegistry_h__
#define ICustomDataHandlerRegistry_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations_I.h"

namespace INT_UMC {
	using namespace UMC;

	class ICustomDataHandlerRegistry {
	public:
		virtual bool IsHandlerRegistered( const std::string & nameSpace, const std::string & name ) const = 0;

		virtual bool RegisterHandler( const std::string & nameSpace, const std::string & name, const spICustomDataHandler & handler ) = 0;

		virtual spICustomDataHandler GetHandler( const std::string & nameSpace, const std::string & name ) = 0;
		virtual spcICustomDataHandler GetHandler( const std::string & nameSpace, const std::string & name ) const = 0;

		static pICustomDataHandlerRegistry GetInstance();
		static pcICustomDataHandlerRegistry GetConstInstance();

		static pICustomDataHandlerRegistry CreateInstance();
		static void DestroyInstance();

		virtual ~ICustomDataHandlerRegistry() = 0;

	};

	inline ICustomDataHandlerRegistry::~ICustomDataHandlerRegistry() { }

}
#endif  // ICustomDataHandlerRegistry_h__
