#ifndef IAudioSource_h__
#define IAudioSource_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include "ISource.h"

namespace UMC {

	class IAudioSource
		: public ISource
	{

	public:

		virtual void SetAudioEditRate( const EditRate & editRate ) = 0;
		virtual EditRate GetAudioEditRate() const = 0;

		virtual void SetInCount( const EditUnitInCount & inCount ) = 0;
		virtual EditUnitInCount GetInCount() const = 0;

		virtual void SetDuration( const EditUnitDuration & duration ) = 0;
		virtual EditUnitDuration GetDuration() const = 0;

		virtual void SetTimeCode( const TimeCode & timeCode ) = 0;
		virtual TimeCode GetTimeCode() const = 0;

		virtual ~IAudioSource() = 0;

	};

	inline IAudioSource::~IAudioSource() {}

}

#endif  // IAudioSource_h__
