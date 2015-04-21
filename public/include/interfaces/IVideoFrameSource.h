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
		virtual void SetInCount( const EditUnitInCount & inCount ) = 0;
		virtual EditUnitInCount GetInCount() const = 0;

		virtual TimeCode GetTimeCode() const = 0;

		virtual spIVideoSource GetVideoSource() = 0;
		virtual spcIVideoSource GetVideoSource() const = 0;

		virtual ~IVideoFrameSource() = 0;
	};

	inline IVideoFrameSource::~IVideoFrameSource() {}
}

#endif  // IVideoFrameSource_h__
