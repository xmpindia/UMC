#ifndef IAudioTrack_h__
#define IAudioTrack_h__ 1

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

	class IAudioTrack
		: public ITrack
	{
	public:

		//!
		//! Sets audio edit rate for the audio track
		//! \param[in] EditRate object.
		//!
		virtual void SetAudioEditRate( const EditRate & editRate ) = 0;

		//!
		//! Gets audio edit rate for the audio track
		//! \return EditRate object.
		//!
		virtual EditRate GetAudioEditRate() const = 0;

		virtual ~IAudioTrack() = 0;
	};

	inline IAudioTrack::~IAudioTrack() {}
}
#endif  // IAudioTrack_h__
