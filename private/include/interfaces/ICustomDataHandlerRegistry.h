#ifndef ICustomDataHandlerRegistry_h__
#define ICustomDataHandlerRegistry_h__ 1

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

#include "UMCFwdDeclarations_I.h"

namespace INT_UMC {
	using namespace UMC;

	class ICustomDataHandlerRegistry {
	public:
		virtual bool IsHandlerRegistered( const std::string & nameSpace, const std::string & name ) const = 0;

		virtual bool RegisterHandler( const std::string & nameSpace, const std::string & name, const spICustomDataHandler & handler ) = 0;

		virtual spICustomDataHandler GetHandler( const std::string & nameSpace, const std::string & name ) = 0;
		virtual spcICustomDataHandler GetHandler( const std::string & nameSpace, const std::string & name ) const = 0;

		static pICustomDataHandlerRegistry GetInstance();
		static pcICustomDataHandlerRegistry GetConstInstance();

		static pICustomDataHandlerRegistry CreateInstance();
		static void DestroyInstance();

		virtual ~ICustomDataHandlerRegistry() = 0;

	};

	inline ICustomDataHandlerRegistry::~ICustomDataHandlerRegistry() { }

}
#endif  // ICustomDataHandlerRegistry_h__
