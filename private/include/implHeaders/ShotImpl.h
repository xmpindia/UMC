#ifndef ShotImpl_h__
#define ShotImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IShot.h"
#include "UMCDefines_I.h"
#include "interfaces/IFrame.h"
#include "interfaces/ISource.h"

#include <string>
#include <map>

namespace INT_UMC {
	using namespace UMC;
	class ShotImpl
		: public IShot
		, public enable_shared_from_this< ShotImpl >
	{
	public:
		ShotImpl( const std::string & uniqueID, eShotTypes type, const spITrack & parent );

		virtual std::string GetUniqueID() const;

		virtual eShotTypes GetType() const ;

		virtual void SetInCount( const EditUnitInCount & inCount );
		virtual EditUnitInCount GetInCount() const;

		virtual void SetDuration( const EditUnitDuration & duration );
		virtual EditUnitDuration GetDuration() const;

		virtual spIFrame AddFrame( const spISource & frameSource, const char * uniqueID,
			size_t lengthOfID, const EditUnitInCount & sourceInCount, const EditUnitInCount shotInCount );

		virtual size_t FrameCount() const;
		virtual FrameList GetFrames();
		virtual cFrameList GetFrames() const;
		virtual spIFrame GetFrame( const char * uniqueID, size_t length );

		virtual spIShotSource AddShotSource( const spISource & shotSource,
			const EditUnitInCount & sourceInCount, const EditUnitDuration sourceDuration,
			const EditUnitInCount shotInCount );

		virtual size_t ShotSourceCount() const;
		virtual ShotSourceList GetShotSources();
		virtual cShotSourceList GetShotSources() const;

		virtual spcITrack GetParent() const;
		virtual spITrack GetParent();

	protected:
		typedef std::map< const std::string, spIFrame > FrameMap;
		typedef std::map< const std::string, spIShotSource > ShotSourceMap;

		std::string				mUniqueID;
		eShotTypes				mShotType;
		EditUnitInCount			mInCount;
		EditUnitDuration		mDuration;
		weak_ptr< ITrack >		mwpTrack;
		FrameMap				mFrameMap;
		ShotSourceMap			mShotSourceMap;
	};
}

#endif  // ShotImpl_h__
