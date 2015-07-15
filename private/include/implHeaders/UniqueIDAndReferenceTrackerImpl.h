#ifndef UniqueIDAndReferenceTrackerImpl_h__
#define UniqueIDAndReferenceTrackerImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

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
