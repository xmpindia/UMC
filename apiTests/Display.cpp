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


#include "Display.h"

namespace NS_DisplayExtension {


	std::string Display::getID() {
		return _id;
	}

	void Display::setID( const std::string & displayID ) {
		_id = displayID;
	}

	double Display::getWidth() {
		return _width;
	}

    double Display::getWidth() const{
        return _width;
    }
    
    double Display::getHeight() {
        return _height;
    }
    
    double Display::getHeight() const{
        return _height;
    }
    
    const std::string & Display::getType()
    {
        return _type;
    }
    
    const std::string & Display::getType() const{
        return _type;
    }
    
	void Display::setWidth( const double & displayWidth ) {
		_width = displayWidth;
	}
    
    void Display::setHeight(const double & displayHeight)  {
        _height = displayHeight;
    }
    
    void Display::setType(const std::string & displayType)
    {
        _type = displayType;
    }

	Display::Display()
		: _width( 50.0 ),_height(30),_type("HD") { }

}
