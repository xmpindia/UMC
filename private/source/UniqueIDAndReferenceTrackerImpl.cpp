// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/UniqueIDAndReferenceTrackerImpl.h"

namespace INT_UMC {

	bool UniqueIDAndReferenceTrackerImpl::IsUniqueIDPresent( const std::string & uniqueID ) const {
		if ( mUniqueIDAndRefernceCountMap.find( uniqueID ) != mUniqueIDAndRefernceCountMap.end() )
			return true;
		return false;
	}

	bool UniqueIDAndReferenceTrackerImpl::AddUniqueID( const std::string & uniqueID ) {
		auto retVal = mUniqueIDAndRefernceCountMap.insert( std::make_pair( uniqueID, (size_t) 0 ) );
		return retVal.second;
	}

	bool UniqueIDAndReferenceTrackerImpl::RemoveUniqueID( const std::string & uniqueID ) {
		return mUniqueIDAndRefernceCountMap.erase( uniqueID ) > 0 ? true : false;
	}

	size_t UniqueIDAndReferenceTrackerImpl::AddReference( const std::string & uniqueID ) {
		auto it = mUniqueIDAndRefernceCountMap.find( uniqueID );
		if ( it != mUniqueIDAndRefernceCountMap.end() ) {
			it->second++;
			return it->second;
		}
		else {
			return kMaxsize_t;
		}
	}

	size_t UniqueIDAndReferenceTrackerImpl::RemoveReference( const std::string & uniqueID ) {
		auto it = mUniqueIDAndRefernceCountMap.find( uniqueID );
		if ( it != mUniqueIDAndRefernceCountMap.end() ) {
			if ( it->second > 0 ) {
				it->second--;
				return it->second;
			} else {
				return kMaxsize_t;
			}
		} else {
			return kMaxsize_t;
		}
	}

	size_t UniqueIDAndReferenceTrackerImpl::GetReferenceCount( const std::string & uniqueID ) {
		auto it = mUniqueIDAndRefernceCountMap.find( uniqueID );
		if ( it != mUniqueIDAndRefernceCountMap.end() ) {
			return it->second;
		} else {
			return kMaxsize_t;
		}
	}

	bool UniqueIDAndReferenceTrackerImpl::IsReferenced( const std::string & uniqueID ) const {
		auto it = mUniqueIDAndRefernceCountMap.find( uniqueID );
		if ( it != mUniqueIDAndRefernceCountMap.end() ) {
			return it->second > 0;
		} else {
			return false;
		}
	}

	bool UniqueIDAndReferenceTrackerImpl::GetUserUniqueID( const std::string & userUniqueID, std::string & uniqueID ) const {
		auto it = mUserAndActualUniqueIDMap.find ( userUniqueID );
		if ( it != mUserAndActualUniqueIDMap.end() ) {
			uniqueID = it->second;
			return true;
		} else {
			return false;
		}
	}

	bool UniqueIDAndReferenceTrackerImpl::AddUserUniqueID( const std::string & userUniqueID, const std::string & uniqueID ) {
		auto retVal = mUserAndActualUniqueIDMap.insert( std::make_pair( userUniqueID, uniqueID ) );
		return retVal.second;
	}

	spIUniqueIDAndReferenceTracker CreateUniqueIDAndReferenceTracker() {
		return std::make_shared< UniqueIDAndReferenceTrackerImpl >();
	}

}

