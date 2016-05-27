// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2016 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "DisplayExtensionHandler.h"

namespace NS_DisplayExtension {

	/* Initialize the display object present in the extension handler object*/
	bool DisplayHandler::BeginCustomData() {
		_display = std::make_shared< Display >();
		return true;
	}

	/* Clear the display object present in the extension handler object*/
	spICustomData DisplayHandler::EndCustomData() {
		auto it = _display;
		_display.reset();
		return it;
	}

	/*Implement this function if the extension contains structure objects*/
	bool DisplayHandler::BeginStructure( const std::string & structureName ) {
		return false;
	}

	/*Implement this function if the extension contains structure objects*/
	bool DisplayHandler::EndStructure( const std::string & structureName ) {
		return false;
	}

	/*Implement this function if the extension contains array objects*/
	bool DisplayHandler::BeginArray( const std::string & arrayName ) {
		return false;
	}

	/*Implement this function if the extension contains array objects*/
	bool DisplayHandler::EndArray( const std::string & arrayName ) {
		return false;
	}

	/*Implement this function if the extension contains key-value pairs*/
	bool DisplayHandler::AddKeyValuePair( const std::string & key, const std::string & value ) {
		if ( key.compare( "id" ) == 0 ) {
			_display->setID( value );
			return true;
		} else if ( key.compare( "name" ) == 0 ) {
			_display->setName( value );
			return true;
		} else if ( key.compare( "diagonalSize" ) == 0 ) {
			_display->setDiagonalSize( std::stod( value ) );
			return true;
		}
		return false;
	}
	
	/*Serializing the extension*/
	bool DisplayHandler::Serialize( const spICustomData & data, const spICustomDataHandler & customDataCreator ) const {
		shared_ptr< Display > display = dynamic_pointer_cast< Display >( data );
		if ( display ) {
			if ( !customDataCreator->BeginCustomData() ) return false;
			if ( !display->getName().empty() )
				customDataCreator->AddKeyValuePair( "name", display->getName() );
			if ( !display->getID().empty() )
				customDataCreator->AddKeyValuePair( "id", display->getID() );
			if ( display->getDiagonalSize() != 0.0 )
				customDataCreator->AddKeyValuePair( "diagonalSize", std::to_string( (long double )display->getDiagonalSize() ) );
			customDataCreator->EndCustomData();
			return true;
		}
		return false;
	}

}
