#ifndef IVideoTrack_h__
#define IVideoTrack_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ITrack.h"
#include "baseTypes/RationalType.h"

namespace UMC {

	class IVideoTrack
		: public ITrack
	{
	public:
		virtual void SetVideoEditRate( const EditRate & editRate ) = 0;
		virtual EditRate GetVideoEditRate() const = 0;

		virtual void SetAudioEditRate( const EditRate & editRate ) = 0;
		virtual EditRate GetAudioEditRate() const = 0;

		virtual ~IVideoTrack() = 0;
	};

	inline IVideoTrack::~IVideoTrack() {}
}
#endif  // IVideoTrack_h__
