#ifndef IVideoSource_h__
#define IVideoSource_h__ 1

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

	class IVideoSource
		: public ISource
	{

	public:

		virtual void SetVideoEditRate( const EditRate & editRate ) = 0;
		virtual EditRate GetVideoEditRate() const = 0;

		virtual void SetAudioEditRate( const EditRate & editRate ) = 0;
		virtual EditRate GetAudioEditRate() const = 0;

		virtual void SetInCount( const EditUnitInCount & inCount ) = 0;
		virtual EditUnitInCount GetInCount() const = 0;

		virtual void SetDuration( const EditUnitDuration & duration ) = 0;
		virtual EditUnitDuration GetDuration() const = 0;

		virtual void SetTimeCode( const TimeCode & timeCode ) = 0;
		virtual TimeCode GetTimeCode() const = 0;

		virtual ~IVideoSource() = 0;

	};

	inline IVideoSource::~IVideoSource() {}

}

#endif  // IVideoSource_h__
