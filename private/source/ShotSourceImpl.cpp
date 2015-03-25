// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/ShotSourceImpl.h"
#include "interfaces/ISource.h"

namespace INT_UMC {
	
	ShotSourceImpl::ShotSourceImpl( const spISource & shotSource, const spIShot & parentShot,
		const EditUnitInCount & sourceInCount, const EditUnitDuration sourceDuration,
		const EditUnitInCount shotInCount )
		: mwpShot( parentShot )
		, mwpSource( shotSource )
		, mSourceInCount( sourceInCount )
		, mSourceDuration( sourceDuration )
		, mShotInCount( shotInCount ) { }

	spcISource ShotSourceImpl::GetSource() const {
		return spcISource( mwpSource );
	}

	spISource ShotSourceImpl::GetSource() {
		return spISource( mwpSource );
	}

	void ShotSourceImpl::SetSourceInCount( const EditUnitInCount & sourceInCount ) {
		mSourceInCount = sourceInCount;
	}

	UMC::EditUnitInCount ShotSourceImpl::GetSourceInCount() const {
		return mSourceInCount;
	}

	void ShotSourceImpl::SetSourceDuration( const EditUnitDuration & sourceDuration ) {
		mSourceDuration = sourceDuration;
	}

	UMC::EditUnitDuration ShotSourceImpl::GetSourceDuration() const {
		return mSourceDuration;
	}

	void ShotSourceImpl::SetShotInCount( const EditUnitInCount & shotInCount ) {
		mShotInCount = shotInCount;
	}

	UMC::EditUnitInCount ShotSourceImpl::GetShotInCount() const {
		return mShotInCount;
	}

	spIShot ShotSourceImpl::GetParent() {
		return spIShot( mwpShot );
	}

	spcIShot ShotSourceImpl::GetParent() const {
		return spcIShot( mwpShot );
	}

}
