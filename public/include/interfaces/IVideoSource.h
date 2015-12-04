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

		//!
		//! Set the video edit rate for the video source
		//! \param[in] a value of type EditRate indicating the video edit rate for the video source
		//!
		virtual void SetVideoEditRate( const EditRate & editRate ) = 0;

		//!
		//! Get the video edit rate for the video source
		//! \return a value of type EditRate indicating the video rate for the video source
		//!
		virtual EditRate GetVideoEditRate() const = 0;

		//!
		//! Set the audio edit rate for the video source
		//! \param[in] a value of type EditRate indicating the audio edit rate for the video source
		//!
		virtual void SetAudioEditRate( const EditRate & editRate ) = 0;

		//!
		//! Get the audio edit rate for the video source
		//! \return a value of type EditRate indicating the audio rate for the video source
		//!
		virtual EditRate GetAudioEditRate() const = 0;

		//!
		//! Get the edit in count for the video source
		//! \return  a value of type EditUnitCount indicating the in count for the video source
		//!
		virtual void SetInCount( const EditUnitInCount & inCount ) = 0;

		//!
		//! Set the in count for the video source
		//! \param[in] a value of type EditUnitDuration indicating the in count of the video source
		//!
		virtual EditUnitInCount GetInCount() const = 0;

		//!
		//! Set the duration for the video source
		//! \param[in] a value of type EditUnitDuration indicating the duration of the video source
		//!
		virtual void SetDuration( const EditUnitDuration & duration ) = 0;

		//!
		//! Get the duration for the video source
		//! \return a value of type EditUnitDuration indicating the duration of the video source 
		//!
		virtual EditUnitDuration GetDuration() const = 0;

		//!
		//! Set the time code for the video source
		//! \param[in] a value of type TimeCode indicating the time code of the video source
		//!
		virtual void SetTimeCode( const TimeCode & timeCode ) = 0;

		//!
		//! Get the time code for the video source
		//! \return a value of type TimeCode indicating the time code of the video source
		//!
		virtual TimeCode GetTimeCode() const = 0;

		virtual ~IVideoSource() = 0;

	};

	inline IVideoSource::~IVideoSource() {}

}

#endif  // IVideoSource_h__
