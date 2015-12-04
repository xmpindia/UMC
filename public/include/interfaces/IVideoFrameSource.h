#ifndef IVideoFrameSource_h__
#define IVideoFrameSource_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "ISource.h"

namespace UMC {

	class IVideoFrameSource
		: public ISource
	{
	public:

		//!
		//! Set the in count for the video frame source
		//! \param[in] a value of type EditUnitCount indicating the in count for the video frame source
		//!
		virtual void SetInCount( const EditUnitInCount & inCount ) = 0;

		//!
		//! Get the edit in count for the video frame source
		//! \return  a value of type EditUnitCount indicating the in count for the video frame source
		//!
		virtual EditUnitInCount GetInCount() const = 0;


		//!
		//! Get the time code for the video frame source
		//! \return a value of type TimeCode indicating the time code of the video frame source
		//!
		virtual TimeCode GetTimeCode() const = 0;

		//!
		//! Get the associated video source for the video frame source
		//! \return a shared pointer to a non-const object of type IVideoSource
		//!
		virtual spIVideoSource GetVideoSource() = 0;

		//!
		//! Get the associated video source for the video frame source
		//! \return a shared pointer to a const object of type IVideoSource
		//!
		virtual spcIVideoSource GetVideoSource() const = 0;

		virtual ~IVideoFrameSource() = 0;
	};

	inline IVideoFrameSource::~IVideoFrameSource() {}
}

#endif  // IVideoFrameSource_h__
