#ifndef DoviDisplayHandler_h__
#define DoviDisplayHandler_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ICustomDataHandler.h"
#include "DoviDisplay.h"

namespace DoVi {
	using namespace UMC;

	class DisplayHandler
		: public ICustomDataHandler
	{
	public:
		virtual bool BeginCustomData();
		virtual spICustomData EndCustomData();

		virtual bool BeginStructure( const std::string & structureName );
		virtual bool EndStructure( const std::string & structureName );

		virtual bool BeginArray( const std::string & arrayName );
		virtual bool EndArray( const std::string & arrayName );

		virtual bool AddKeyValuePair( const std::string & key, const std::string & value );

		virtual bool Serialize( const spICustomData & data, const spICustomDataHandler & customDataCreator ) const;

	protected:
		shared_ptr< Display > _display;

	};
}

#endif  // DoviDisplayHandler_h__
