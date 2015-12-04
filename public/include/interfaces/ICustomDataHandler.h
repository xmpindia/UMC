#ifndef ICustomDataHandler_h__
#define ICustomDataHandler_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"

namespace UMC {
	class ICustomDataHandler {
	public:

		
		//!
		//! Begins creating the custom data
		//! Clients should look to initialize their custom data in this place.
		//! \return a bool value indicating whether the creation of custom data was successful
		//!
		virtual bool BeginCustomData() = 0;

		//!
		//! Ends creating the custom data
		//! Clients should look to destroy their custom data in this place.
		//! \return a shared pointer to a non-const object of type ICustomData indicating the custom data that was created
		//!
		virtual spICustomData EndCustomData() = 0;

		//!
		//! Begins creating a structure property within the custom data
		//! Clients should look to create a new structure property in this place.
		//! \param[in] a value of type std::string indicating the name of the structure property to be created
		//! \return a bool value indicating whether the creation of the structure property was begun successful
		//!
		virtual bool BeginStructure( const std::string & structureName ) = 0;

		//!
		//! Ends creating a new structure property within the custom data
		//! Clients should look to end creation of a new structure property in this place.
		//! \param[in] a value of type std::string indicating the name of the structure property whose creation is to be completed
		//! \return a bool value indicating whether the creation of the structure property was completed successful
		//!
		virtual bool EndStructure( const std::string & structureName ) = 0;

		//!
		//! Begins creating an array property within the custom data
		//! Clients should look to create a new array property in this place.
		//! \param[in] a value of type std::string indicating the name of the array property to be created
		//! \return a bool value indicating whether the creation of the array property was begun successful
		//!
		virtual bool BeginArray( const std::string & arrayName ) = 0;

		//!
		//! Ends creating a new array property within the custom data
		//! Clients should look to end creation of a new array property in this place.
		//! \param[in] a value of type std::string indicating the name of the array property whose creation is to be completed
		//! \return a bool value indicating whether the creation of the array property was completed successful
		//!
		virtual bool EndArray( const std::string & arrayName ) = 0;

		//!
		//! Adds key-value pairs within the custom data
		//! Clients should look to add key-value pair in this place.
		//! \param[in] a value of type std::string indicating the key to be added to the custom data
		//! \param[in] a value of type std::string indicating the value to be added to the custom data
		//! \return a bool value indicating whether the addition of key-value pair was successful
		//!
		virtual bool AddKeyValuePair( const std::string & key, const std::string & value ) = 0;

		//!
		//! Serializes the custom data to XMP
		//! Clients should write their code to create the entire custom data here
		//! \param[in] a shared pointer to a non-const object of type ICustomData
		//! \param[in] a shared pointer to a non-const object of type ICustomDataHandler
		//! \return a bool value indicating whether the serialization of the custom data was successful
		//!
		virtual bool Serialize( const spICustomData & data, const spICustomDataHandler & customDataCreator ) const = 0;

		virtual ~ICustomDataHandler() = 0;
	};

	inline ICustomDataHandler::~ICustomDataHandler() { }

}

#endif  // ICustomDataHandler_h__
