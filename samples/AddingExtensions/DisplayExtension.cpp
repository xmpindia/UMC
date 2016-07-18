/*
*  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
*  This file is licensed to you under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License. You may obtain a copy
*  of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software distributed under
*  the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
*  OF ANY KIND, either express or implied. See the License for the specific language
*  governing permissions and limitations under the License.
*
*/


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