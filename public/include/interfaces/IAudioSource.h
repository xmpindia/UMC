#ifndef IAudioSource_h__
#define IAudioSource_h__ 1

/*
*  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
*  This file is licensed to you under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License. You may obtain a copy
*  of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software distributed under
*  the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
*  OF ANY KIND, either express or implied. See the License for the specific language
*  governing permissions and limitations under the License.
*
*/


#include "UMCFwdDeclarations.h"
#include "ISource.h"

namespace UMC {

	class IAudioSource
		: public ISource
	{

	public:

		//!
		//! Set the audio edit rate for the audio source
		//! \param[in] a value of type EditRate indicating the audio edit rate for the audio source
		//!
		virtual void SetAudioEditRate( const EditRate & editRate ) = 0;

		//!
		//! Get the audio edit rate for the audio source
		//! \return a value of type EditRate indicating the audio edit rate for the audio source
		//!
		virtual EditRate GetAudioEditRate() const = 0;

		//!
		//! Set the edit in count for the audio source
		//! \param[in] a value of type EditUnitCount indicating the in count for the audio source
		//!
		virtual void SetInCount( const EditUnitInCount & inCount ) = 0;

		//!
		//! Get the edit in count for the audio source
		//! \return  a value of type EditUnitCount indicating the in count for the audio source
		//!
		virtual EditUnitInCount GetInCount() const = 0;

		//!
		//! Set the duration for the audio source
		//! \param[in] a value of type EditUnitDuration indicating the duration of the audio source
		//!
		virtual void SetDuration( const EditUnitDuration & duration ) = 0;

		//!
		//! Get the duration for the audio source
		//! \return a value of type EditUnitDuration indicating the duration of the audio source 
		//!
		virtual EditUnitDuration GetDuration() const = 0;

		//!
		//! Set the time code for the audio source
		//! \param[in] a value of type TimeCode indicating the time code of the audio source
		//!
		virtual void SetTimeCode( const TimeCode & timeCode ) = 0;


		//!
		//! Get the time code for the audio source
		//! \return a value of type TimeCode indicating the time code of the audio source
		//!
		virtual TimeCode GetTimeCode() const = 0;

		virtual ~IAudioSource() = 0;

	};

	inline IAudioSource::~IAudioSource() {}

}

#endif  // IAudioSource_h__
