#ifndef __AvailableDisplays_h__
#define __AvailableDisplays_h__ 1

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

#include "interfaces/ICustomData.h"
#include "interfaces/IUMCNode.h"
#include "Display.h"

namespace NS_DisplayExtension {
	using namespace UMC;

	/*Implement the ICustomData interface in order to create an extension*/
	class AvailableDisplays
		: public UMC::ICustomData
	{
	public:
		/*The constructor for creating the AvailableDisplays extension*/
		AvailableDisplays();
		
		/*Add new display to availableDisplaysList*/
		void AddDisplay(const Display & display);

		/*Set the parent node of the AvailableDisplays */
		virtual void SetParentNode( const wpIUMCNode & parentNode );

		/*Get the parent node of the AvailableDisplays */
		virtual wpcIUMCNode GetParentNode() const;

		virtual wpIUMCNode GetParentNode();

		virtual ~AvailableDisplays();

		void setName(const std::string & name);
		
		const std::string & getName();
        
        const std::string & getName() const;

        
        const std::vector<Display> & getDisplayList();

        const std::vector<Display> & getDisplayList() const;
        
		/*Set the parent node of the AvailableDisplays */
		static const std::string & GetNameSpace();
        
		static const std::string & GetPropertyName();

	protected:
		
		wpIUMCNode			_parent;
		std::string 			_name;
        std::vector<Display> 		_availableDisplayList;
	};
}

#endif  // DoViAvailableDisplays_h__
