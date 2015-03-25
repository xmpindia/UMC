#ifndef ShotSourceImpl_h__
#define ShotSourceImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IShotSource.h"
#include "UMCDefines_I.h"

namespace INT_UMC {
	using namespace UMC;

	class ShotSourceImpl
		: public IShotSource
		, public enable_shared_from_this< ShotSourceImpl >
	{
	public:
		ShotSourceImpl( const spISource & shotSource, const spIShot & parentShot,
			const EditUnitInCount & sourceInCount = kEditUnitInCountFromBeginning,
			const EditUnitDuration sourceDuration = kEditUnitDurationTillEnd,
			const EditUnitInCount shotInCount = kEditUnitInCountFromBeginning );
	
		virtual spISource GetSource();
		virtual spcISource GetSource() const;
		
		virtual void SetSourceInCount( const EditUnitInCount & sourceInCount );
		virtual EditUnitInCount GetSourceInCount() const;

		virtual void SetSourceDuration( const EditUnitDuration & sourceDuration );
		virtual EditUnitDuration GetSourceDuration() const;

		virtual void SetShotInCount( const EditUnitInCount & shotInCount );
		virtual EditUnitInCount GetShotInCount() const;

		virtual spcIShot GetParent() const;
		virtual spIShot GetParent();

	private:
		weak_ptr< IShot >		mwpShot;
		weak_ptr< ISource >		mwpSource;
		EditUnitInCount			mSourceInCount;
		EditUnitDuration		mSourceDuration;
		EditUnitInCount			mShotInCount;
	};
}
#endif  // ShotSourceImpl_h__
