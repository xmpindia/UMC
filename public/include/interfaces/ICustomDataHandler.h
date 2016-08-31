#ifndef ICustomDataHandler_h__
#define ICustomDataHandler_h__ 1

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

#include "UMCFwdDeclarations.h"

namespace UMC {
	//!
	//! \brief This interface allows client to create custom extension handler.
	//! \details This interface need to be implemented , if clients want to support custom data.
	//! Clients have to implement Serialize function,in the way he/she wants to serialize custom data using customDataCreator. 
	//! Clients have to implement other functions, to support deserializing of custom data while creating the data model out of serialized data.
	//!
	class ICustomDataHandler {
	public:

		
		//!
		//! \brief Begins creating the custom data
		//! \details Clients should look to initialize their custom data in this place.
		//! \return a bool value indicating whether the creation of custom data was successful
		//!
		virtual bool BeginCustomData() = 0;

		//!
		//! \brief Ends creating the custom data
		//! \details Clients should look to destroy their custom data in this place.
		//! \return a shared pointer to a non-const object of type ICustomData indicating the custom data that was created
		//!
		virtual spICustomData EndCustomData() = 0;

		//!
		//! \brief Begins creating a structure property within the custom data
		//! \details Clients should look to create a new structure property in this place.
		//! \param[in] structureName A value of type std::string indicating the name of the structure property to be created
		//! \return a bool value indicating whether the creation of the structure property was begun successful
		//!
		virtual bool BeginStructure( const std::string & structureName ) = 0;

		//!
		//! \brief Ends creating a new structure property within the custom data
		//! \details Clients should look to end creation of a new structure property in this place.
		//! \param[in] structureName A value of type std::string indicating the name of the structure property whose creation is to be completed
		//! \return a bool value indicating whether the creation of the structure property was completed successful
		//!
		virtual bool EndStructure( const std::string & structureName ) = 0;

		//!
		//! \brief Begins creating an array property within the custom data
		//! \details Clients should look to create a new array property in this place.
		//! \param[in] arrayName A value of type std::string indicating the name of the array property to be created
		//! \return a bool value indicating whether the creation of the array property was begun successful
		//!
		virtual bool BeginArray( const std::string & arrayName ) = 0;

		//!
		//! \brief Ends creating a new array property within the custom data
		//! \details Clients should look to end creation of a new array property in this place.
		//! \param[in] arrayName A value of type std::string indicating the name of the array property whose creation is to be completed
		//! \return a bool value indicating whether the creation of the array property was completed successful
		//!
		virtual bool EndArray( const std::string & arrayName ) = 0;

		//!
		//! \brief Adds key-value pairs within the custom data
		//! \details Clients should look to add key-value pair in this place.
		//! \param[in] key A value of type std::string indicating the key to be added to the custom data
		//! \param[in] value A value of type std::string indicating the value to be added to the custom data
		//! \return a bool value indicating whether the addition of key-value pair was successful
		//!
		virtual bool AddKeyValuePair( const std::string & key, const std::string & value ) = 0;

		//!
		//! \brief Serializes the custom data to XMP
		//! \details Clients should write their code to create the entire custom data here
		//! \param[in] data A shared pointer to a non-const object of type ICustomData
		//! \param[in] customDataCreator A shared pointer to a non-const object of type ICustomDataHandler
		//! \return a bool value indicating whether the serialization of the custom data was successful
		//!
		virtual bool Serialize( const spICustomData & data, const spICustomDataHandler & customDataCreator ) const = 0;

		virtual ~ICustomDataHandler() = 0;
	};

	inline ICustomDataHandler::~ICustomDataHandler() { }

}

#endif  // ICustomDataHandler_h__
