#ifndef DoViDisplayHandler_h__
#define DoViDisplayHandler_h__ 1

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
