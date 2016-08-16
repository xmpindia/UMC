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


#include "DisplayExtensionHandler.h"

namespace NS_DisplayExtension {

	/* Initialize the display object present in the extension handler object*/
	bool DisplayExtensionHandler::BeginCustomData() {
		_availableDisplays = std::make_shared< AvailableDisplays >();
        _currentDisplay = std::make_shared< Display >();
		return true;
	}

	/* Clear the display object present in the extension handler object*/
	spICustomData DisplayExtensionHandler::EndCustomData() {
		auto it = _availableDisplays;
		_availableDisplays.reset();
		return it;
	}

	/*Implement this function if the extension contains structure objects*/
	bool DisplayExtensionHandler::BeginStructure( const std::string & structureName ) {
		return true;
	}

	/*Implement this function if the extension contains structure objects*/
	bool DisplayExtensionHandler::EndStructure( const std::string & structureName ) {
        _availableDisplays->AddDisplay(*_currentDisplay);
        return true;
	}

	/*Implement this function if the extension contains array objects*/
	bool DisplayExtensionHandler::BeginArray( const std::string & arrayName ) {
		return true;
	}

	/*Implement this function if the extension contains array objects*/
	bool DisplayExtensionHandler::EndArray( const std::string & arrayName ) {
		return true;
	}

	/*Implement this function if the extension contains key-value pairs*/
    /*Implement this function if the extension contains key-value pairs*/
    bool DisplayExtensionHandler::AddKeyValuePair( const std::string & key, const std::string & value ) {
        if ( key.compare( "id" ) == 0 ) {
            _currentDisplay->setID( value );
            return true;
        } else if ( key.compare( "w" ) == 0 ) {
            _currentDisplay->setWidth( std::stod( value ) );
            return true;
        } else if ( key.compare( "h" ) == 0 ) {
            _currentDisplay->setHeight( std::stod( value ) );
            return true;
        } else if ( key.compare( "type" ) == 0 ) {
            _currentDisplay->setType(value);
            return true;
        } else if ( key.compare( "Device_Available" ) == 0 ) {
            _currentDisplay = std::make_shared< Display >();
            return true;
        } else if( key.compare("name") == 0){
            _availableDisplays->setName(value);
            return true;
        }

        return false;
    }
    
    const AvailableDisplays & DisplayExtensionHandler ::getAvailableDisplays() {
        return *_availableDisplays;
    }
	
	/*Serializing the extension*/
	bool DisplayExtensionHandler::Serialize( const spICustomData & data, const spICustomDataHandler & customDataCreator ) const {
		shared_ptr< AvailableDisplays > availableDisplays = dynamic_pointer_cast< AvailableDisplays >( data );
		if ( availableDisplays ) {
			if ( !customDataCreator->BeginCustomData() ) return false;
            
            
            const std::vector<Display> & displayList = availableDisplays->getDisplayList();
            customDataCreator->AddKeyValuePair("name",availableDisplays->getName());
            customDataCreator->BeginArray("Device_Available");
            Display display;
            
            for( int i = 0 ; i < displayList.size() ; i++)
            {
                customDataCreator->BeginStructure("DeviceProperties");
                
                display = displayList[i];
                customDataCreator->AddKeyValuePair("w", display.getWidth() == 0 ? std::to_string(10.0):std::to_string(display.getWidth()));
            
                customDataCreator->AddKeyValuePair("h", display.getHeight() == 0 ? std::to_string(10.0):std::to_string(display.getHeight()));
            
                customDataCreator->AddKeyValuePair("type", display.getType().empty() ? "SmartHD":display.getType());
            
                customDataCreator->EndStructure("DeviceProperties");
            
            }

            customDataCreator->EndArray("Device_Available");
            
			customDataCreator->EndCustomData();
			return true;
		}
		return false;
	}

}
