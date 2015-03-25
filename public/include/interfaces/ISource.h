#ifndef ISource_h__
#define ISource_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"

#include "baseTypes/TimeCode.h"

#include <string>

namespace UMC {

	class ISource {

	public:
		typedef enum {
			kSourceTypeVideo		= 0,
			kSourceTypeAudio		= 1,
			kSourceTypeFrame	= 2
		} eSourceTypes;

		virtual std::string GetUniqueID() const = 0;

		virtual void SetClipName( const char * clipName, size_t length = npos ) = 0;
		virtual std::string GetClipName() const = 0;

		virtual eSourceTypes GetSourceType() const = 0;

		virtual void SetEditRate( const EditRate & editRate ) = 0;
		virtual EditRate GetEditRate() const = 0;

		virtual void SetInCount( const EditUnitInCount & inCount ) = 0; 
		virtual EditUnitInCount GetInCount() const = 0;

		virtual void SetDuration( const EditUnitDuration & duration ) = 0;
		virtual EditUnitDuration GetDuration() const = 0;

		virtual void SetTimeCode( const TimeCode & timeCode ) = 0;
		virtual TimeCode GetTimeCode() const = 0;

		virtual spcIUMC GetParent() const = 0;
		virtual spIUMC GetParent() = 0;

		virtual ~ISource() = 0;

	private:

	};

	inline ISource::~ISource() {}

};

#endif  // ISource_h__
