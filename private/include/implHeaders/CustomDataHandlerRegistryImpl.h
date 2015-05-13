#ifndef CustomDataHandlerRegistryImpl_h__
#define CustomDataHandlerRegistryImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ICustomDataHandlerRegistry.h"
#include <string>
#include <map>

namespace INT_UMC {
	class CustomDataHandlerRegistryImpl 
		: public ICustomDataHandlerRegistry
	{
	public:
		virtual bool IsHandlerRegistered( const std::string & nameSpace, const std::string & name ) const;
		virtual bool RegisterHandler( const std::string & nameSpace, const std::string & name, const spICustomDataHandler & handler );
		virtual spICustomDataHandler GetHandler( const std::string & nameSpace, const std::string & name );
		virtual spcICustomDataHandler GetHandler( const std::string & nameSpace, const std::string & name ) const;

		bool IsHandlerRegistered( const std::string & combinedName ) const;
		const std::string GetCombinedString( const std::string & nameSpace, const std::string & name ) const;

	protected:
		std::map< std::string, spICustomDataHandler >		mCustomDataHandlerMap;

	};
}

#endif  // CustomDataHandlerRegistryImpl_h__
