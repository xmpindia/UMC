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

	bool UniqueIDAndReferenceTrackerImpl::GetUserUniqueID( const std::string & key, std::string & value, bool keyIsUserUniqueID ) const {
		if ( keyIsUserUniqueID ) {
			auto it = mUserAndActualUniqueIDMap.find( key );
			if ( it != mUserAndActualUniqueIDMap.end() ) {
				value = it->second;
				return true;
			} else {
				return false;
			}
		} else {
			// right now doing a linear search, think about using two maps
			auto it = mUserAndActualUniqueIDMap.begin();
			auto itEnd = mUserAndActualUniqueIDMap.end();
			for( ; it != itEnd; ++it ) {
				if ( key.compare( it->second.c_str() ) == 0 ) {
					value = it->first;
					return true;
				}
			}
			return false;
		}
	}

	bool UniqueIDAndReferenceTrackerImpl::RemoveUserUniqueID( const std::string & key, bool keyIsUserUniqueID /*= true */ ) {
		if ( keyIsUserUniqueID ) {
			if ( mUserAndActualUniqueIDMap.erase( key ) > 0 )
				return true;
			return false;
		} else {
			// right now doing a linear search, think about using two maps
			auto it = mUserAndActualUniqueIDMap.begin();
			auto itEnd = mUserAndActualUniqueIDMap.end();
			for ( ; it != itEnd; ++it ) {
				if ( key.compare( it->second.c_str() ) == 0 ) {
					mUserAndActualUniqueIDMap.erase( it );
					return true;
				}
			}
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

