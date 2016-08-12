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


#include "AvailableDisplays.h"

namespace NS_DisplayExtension {

    AvailableDisplays::AvailableDisplays(){
    }
    
	/* Implement the AvailableDisplays Extension's interface*/
	void AvailableDisplays::SetParentNode( const wpIUMCNode & parentNode ) {
		_parent = parentNode;
	}

	wpcIUMCNode AvailableDisplays::GetParentNode() const {
		return _parent;
	}

	wpIUMCNode AvailableDisplays::GetParentNode() {
		return _parent;
	}

	AvailableDisplays::~AvailableDisplays() {
		_availableDisplayList.clear();
	}

	void AvailableDisplays::AddDisplay(const Display & display) {
        _availableDisplayList.push_back(display);
	}

    const std::vector<Display> & AvailableDisplays::getDisplayList(){
        return _availableDisplayList;
    }

    const std::vector<Display> & AvailableDisplays::getDisplayList() const{
        return _availableDisplayList;
    }
    
	void AvailableDisplays::setName(const std::string & name){
		_name = name;
	}
	const std::string & AvailableDisplays::getName(){
		return _name;
	}

    const std::string & AvailableDisplays::getName() const{
        return _name;
    }
	/* Return the intended namespace for the AvailableDisplays Extension*/
	const std::string & AvailableDisplays::GetNameSpace() {
		static std::string nameSpace( "www.myns.com/" );
		return nameSpace;
	}

	/* Return the intended property name for the AvailableDisplays Extension*/
	const std::string & AvailableDisplays::GetPropertyName() {
		static std::string name( "AvailableDisplaysName" );
		return name;
	}

}
