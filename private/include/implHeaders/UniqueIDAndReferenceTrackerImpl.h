#ifndef UniqueIDAndReferenceTrackerImpl_h__
#define UniqueIDAndReferenceTrackerImpl_h__ 1

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

#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include <map>

namespace INT_UMC {
	class UniqueIDAndReferenceTrackerImpl
		: public IUniqueIDAndReferenceTracker
	{
	public:
		virtual bool IsUniqueIDPresent( const std::string & uniqueID ) const;
		virtual bool AddUniqueID( const std::string & uniqueID );
		virtual bool RemoveUniqueID( const std::string & uniqueID );
		virtual size_t AddReference( const std::string & uniqueID );
		virtual size_t RemoveReference( const std::string & uniqueID );
		virtual size_t GetReferenceCount( const std::string & uniqueID );
		virtual bool IsReferenced( const std::string & uniqueID ) const;
		virtual bool AddUserUniqueID( const std::string & userUniqueID, const std::string & uniqueID );
		virtual bool GetUserUniqueID( const std::string & key, std::string & value, bool keyIsUserUniqueID ) const;
		virtual bool RemoveUserUniqueID( const std::string & key, bool keyIsUserUniqueID );

	protected:
		std::map< std::string, size_t >		mUniqueIDAndRefernceCountMap;
		std::map< std::string, std::string > mUserAndActualUniqueIDMap;
	};
}

#endif  // UniqueIDAndReferenceTrackerImpl_h__
