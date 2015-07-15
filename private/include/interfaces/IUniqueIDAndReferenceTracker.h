#ifndef IUniqueIDAndReferenceTracker_h__
#define IUniqueIDAndReferenceTracker_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

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
