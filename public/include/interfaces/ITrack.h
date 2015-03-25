#ifndef ITrack_h__
#define ITrack_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include "baseTypes/RationalType.h"

#include <string>
#include <vector>

namespace UMC {

	class ITrack {

	public:
		typedef std::vector< spIShot > ShotList;
		typedef std::vector< spcIShot > cShotList;

		virtual std::string GetUniqueID() const = 0;

		virtual spIShot AddClipShot( const char * uniqueID, size_t length = npos ) = 0;
		virtual spIShot AddTransitionShot( const char * uniqueID, size_t length = npos ) = 0;

		virtual void SetName( const char * outputName, size_t length = npos ) = 0;
		virtual std::string GetName() const = 0;

		virtual void SetEditRate( const EditRate & editRate ) = 0;
		virtual EditRate GetEditRate() const = 0;

		virtual size_t ShotCount() const = 0;
		virtual ShotList GetShots() = 0;
		virtual cShotList GetShots() const = 0;

		virtual spcIOutput GetParent() const = 0;
		virtual spIOutput GetParent() = 0;

		virtual ~ITrack() = 0;

	private:

	};

	inline ITrack::~ITrack() {}

};

#endif  // ITrack_h__
