#ifndef DoViDisplayHandler_h__
#define DoViDisplayHandler_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2016 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ICustomDataHandler.h"
#include "DisplayExtension.h"

namespace NS_DisplayExtension {

	using namespace UMC;

	/*Implement the ICustomDataHandler interface in order to create a handler for parsing*/

	class DisplayHandler
		: public ICustomDataHandler
	{
	public:

		/* Initialize the display object present in the extension handler object*/
		virtual bool BeginCustomData();

		/* Clear the display object present in the extension handler object*/
		virtual spICustomData EndCustomData();


		/*Implement this function if the extension contains structure objects*/
		virtual bool BeginStructure( const std::string & structureName );

		/*Implement this function if the extension contains structure objects*/
		virtual bool EndStructure( const std::string & structureName );

		/*Implement this function if the extension contains array objects*/
		virtual bool BeginArray( const std::string & arrayName );


		/*Implement this function if the extension contains array objects*/
		virtual bool EndArray( const std::string & arrayName );

		/*Implement this function if the extension contains key-value pairs*/
		virtual bool AddKeyValuePair( const std::string & key, const std::string & value );

		/*Serializing the extension*/
		virtual bool Serialize( const spICustomData & data, const spICustomDataHandler & customDataCreator ) const;

	protected:

		shared_ptr< Display > _display;

	};
}

#endif  // DoViDisplayHandler_h__
