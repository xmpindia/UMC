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

#include "implHeaders/CustomDataHandlerRegistryImpl.h"
#include <assert.h>

#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"

namespace INT_UMC {

	bool CustomDataHandlerRegistryImpl::IsHandlerRegistered( const std::string & nameSpace, const std::string & name ) const {
		return IsHandlerRegistered( GetCombinedString( nameSpace, name ) );
		
	}

	bool CustomDataHandlerRegistryImpl::IsHandlerRegistered( const std::string & combinedName ) const {
		return mCustomDataHandlerMap.find( combinedName ) != mCustomDataHandlerMap.end();
	}

	const std::string CustomDataHandlerRegistryImpl::GetCombinedString( const std::string & nameSpace, const std::string & name ) const {
		std::string combinedString( nameSpace );
		combinedString.append( ":" ).append( name );
		return combinedString;
	}

	bool CustomDataHandlerRegistryImpl::RegisterHandler( const std::string & nameSpace, const std::string & name, const spICustomDataHandler & handler ) {
		std::string combinedString = GetCombinedString( nameSpace, name );
		if ( handler ) {
			if ( IsHandlerRegistered( combinedString ) ) return false;
			mCustomDataHandlerMap.insert( std::make_pair( combinedString, handler ) );
			std::string registeredPrefix;
			if ( !SXMPMeta::GetNamespacePrefix( nameSpace.c_str(), &registeredPrefix) ) {
				std::string prefix( "cm" );
				prefix.append( std::to_string( sPrefixCount ) );
				SXMPMeta::RegisterNamespace( nameSpace.c_str(), prefix.c_str(), &registeredPrefix );
				sPrefixCount++;
			}
			return true;
		} else {
			if ( IsHandlerRegistered( combinedString ) ) {
				mCustomDataHandlerMap.erase( combinedString );
				return true;
			}
			return false;
		}
	}

	spICustomDataHandler CustomDataHandlerRegistryImpl::GetHandler( const std::string & nameSpace, const std::string & name ) {
		std::string combinedString = GetCombinedString( nameSpace, name );
		if ( IsHandlerRegistered( combinedString ) ) {
			return mCustomDataHandlerMap.find( combinedString )->second;
		}
		return spICustomDataHandler();
	}

	spcICustomDataHandler CustomDataHandlerRegistryImpl::GetHandler( const std::string & nameSpace, const std::string & name ) const {
		return const_cast< CustomDataHandlerRegistryImpl * >( this )->GetHandler( nameSpace, name );
	}

	static CustomDataHandlerRegistryImpl * sCustomDataHandlerRegistryImplPtr( NULL );

	pICustomDataHandlerRegistry ICustomDataHandlerRegistry::CreateInstance() {
		assert( sCustomDataHandlerRegistryImplPtr == NULL );
		sCustomDataHandlerRegistryImplPtr = new CustomDataHandlerRegistryImpl();

		return sCustomDataHandlerRegistryImplPtr;
	}

	pICustomDataHandlerRegistry ICustomDataHandlerRegistry::GetInstance() {
		if ( sCustomDataHandlerRegistryImplPtr )
			return sCustomDataHandlerRegistryImplPtr;
		else
			return CreateInstance();
	}

	pcICustomDataHandlerRegistry ICustomDataHandlerRegistry::GetConstInstance() {
		return GetInstance();
	}

	void ICustomDataHandlerRegistry::DestroyInstance() {
		if ( sCustomDataHandlerRegistryImplPtr )
			delete sCustomDataHandlerRegistryImplPtr;
		sCustomDataHandlerRegistryImplPtr = NULL;
	}

}
