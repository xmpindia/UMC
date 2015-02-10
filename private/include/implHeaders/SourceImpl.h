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
		SourceImpl( const char * uniqueID, size_t length, eSourceTypes sourceType, const spIUMC & parent );

		virtual const std::string & GetUniqueID() const;
		virtual std::string GetUniqueID();

		virtual void SetClipName( const char * clipName, size_t length );

		virtual std::string GetClipName() const;

		virtual eSourceTypes GetSourceType() const;

		virtual void SetEditRate( const EditRate & editRate );
		virtual EditRate GetEditRate() const;

		virtual void SetInCount( const UMC_Int64 & editUnit );
		virtual UMC_Int64 GetInCount() const;

		virtual void SetDuration( const UMC_Uns64 & duration );
		virtual UMC_Uns64 GetDuration() const;

		virtual void SetTimeCode( const TimeCode & timeCode );
		virtual TimeCode GetTimeCode() const;

		virtual spcIUMC GetParent() const;
		virtual spIUMC GetParent();

	protected:
		std::string				mUniqueID;
		eSourceTypes			mSourceType;
		std::string				mClipName;
		EditRate				mEditRate;
		UMC_Int64				mInCount;
		UMC_Uns64				mDuration;
		TimeCode				mTimeCode;
		weak_ptr< IUMC >		mwpUMC;
	};
}

#endif  // SourceImpl_h__
