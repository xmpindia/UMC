#ifndef ICustomDataHandler_h__
#define ICustomDataHandler_h__ 1

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
	class ICustomDataHandler {
	public:
		virtual bool BeginCustomData() = 0;
		virtual spICustomData EndCustomData() = 0;

		virtual bool BeginStructure( const std::string & structureName ) = 0;
		virtual bool EndStructure( const std::string & structureName ) = 0;

		virtual bool BeginArray( const std::string & arrayName ) = 0;
		virtual bool EndArray( const std::string & arrayName ) = 0;

		virtual bool AddKeyValuePair( const std::string & key, const std::string & value ) = 0;

		virtual bool Serialize( const spICustomData & data, const spICustomDataHandler & customDataCreator ) const = 0;

		virtual ~ICustomDataHandler() = 0;
	};

	inline ICustomDataHandler::~ICustomDataHandler() { }

}

#endif  // ICustomDataHandler_h__
