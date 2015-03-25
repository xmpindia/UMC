#ifndef SourceImpl_h__
#define SourceImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ISource.h"
#include "UMCDefines_I.h"

#include <string>

namespace INT_UMC {
	using namespace UMC;
	class SourceImpl : public ISource {
	public:
		SourceImpl( const std::string & uniqueID, eSourceTypes sourceType, const spIUMC & parent );

		virtual std::string GetUniqueID() const;

		virtual void SetClipName( const char * clipName, size_t length );
		virtual std::string GetClipName() const;

		virtual eSourceTypes GetSourceType() const;

		virtual void SetEditRate( const EditRate & editRate );
		virtual EditRate GetEditRate() const;

		virtual void SetInCount( const EditUnitInCount & inCount );
		virtual EditUnitInCount GetInCount() const;

		virtual void SetDuration( const EditUnitDuration & duration );
		virtual EditUnitDuration GetDuration() const;

		virtual void SetTimeCode( const TimeCode & timeCode );
		virtual TimeCode GetTimeCode() const;

		virtual spcIUMC GetParent() const;
		virtual spIUMC GetParent();

	protected:
		const std::string		mUniqueID;
		eSourceTypes			mSourceType;
		std::string				mClipName;
		EditRate				mEditRate;
		EditUnitInCount			mInCount;
		EditUnitDuration		mDuration;
		TimeCode				mTimeCode;
		weak_ptr< IUMC >		mwpUMC;
	};
}

#endif  // SourceImpl_h__
