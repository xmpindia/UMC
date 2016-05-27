// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2016 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "DisplayExtension.h"

namespace NS_DisplayExtension {

	/* Implement the Display Extension's interface*/
	void Display::SetParentNode( const wpIUMCNode & parentNode ) {
		_parent = parentNode;
	}

	wpcIUMCNode Display::GetParentNode() const {
		return _parent;
	}

	wpIUMCNode Display::GetParentNode() {
		return _parent;
	}

	std::string Display::getID() {
		return _id;
	}

	void Display::setID( const std::string & displayID ) {
		_id = displayID;
	}

	std::string Display::getName() {
		return _name;
	}

	void Display::setName( const std::string & displayName ) {
		_name = displayName;
	}

	double Display::getDiagonalSize() {
		return _diagonalSize;
	}

	void Display::setDiagonalSize( const double & displayDiagonalSize ) {
		_diagonalSize = displayDiagonalSize;
	}

	Display::Display()
		: _diagonalSize( 50.0 ) { }

	Display::~Display() {

	}

	/* Return the intended namespace for the Display Extension*/
	const std::string & Display::GetNameSpace() {
		static std::string nameSpace( "www.myns.com/" );
		return nameSpace;
	}

	/* Return the intended property name for the Display Extension*/
	const std::string & Display::GetPropertyName() {
		static std::string name( "DisplayName" );
		return name;
	}

}