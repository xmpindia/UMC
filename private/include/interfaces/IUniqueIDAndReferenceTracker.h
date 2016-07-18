#ifndef IUniqueIDAndReferenceTracker_h__
#define IUniqueIDAndReferenceTracker_h__ 1

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
	class IUniqueIDAndReferenceTracker {

	public:
		virtual bool IsUniqueIDPresent( const std::string & uniqueID ) const = 0;
		virtual bool AddUniqueID( const std::string & uniqueID ) = 0;
		virtual bool RemoveUniqueID( const std::string & uniqueID ) = 0;
		virtual size_t AddReference( const std::string & uniqueID ) = 0;
		virtual size_t RemoveReference( const std::string & uniqueID ) = 0;
		virtual size_t GetReferenceCount( const std::string & uniqueID ) = 0;
		virtual bool IsReferenced( const std::string & uniqueID ) const = 0;
		virtual bool AddUserUniqueID( const std::string & userUniqueID, const std::string & uniqueID ) = 0;
		virtual bool GetUserUniqueID( const std::string & key, std::string & value, bool keyIsUserUniqueID = true ) const = 0;
		virtual bool RemoveUserUniqueID( const std::string & key, bool keyIsUserUniqueID = true ) = 0;

	protected:
		virtual ~IUniqueIDAndReferenceTracker() = 0;
	};

	inline IUniqueIDAndReferenceTracker::~IUniqueIDAndReferenceTracker() {}
};

#endif  // IUniqueIDAndReferenceTracker_h__
