#ifndef IAudioTrack_h__
#define IAudioTrack_h__ 1

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

#include "interfaces/ITrack.h"
#include "baseTypes/RationalType.h"

namespace UMC {

	//!
	//! \brief This interface represents Audio Track added to an output.
	//! \details Provides all the functions to get and set various properties of the audio track.
	//!
	class IAudioTrack
		: public ITrack
	{
	public:

		//!
		//! \brief Sets audio edit rate for the audio track
		//! \param[in] editRate EditRate object.
		//!
		virtual void SetAudioEditRate( const EditRate & editRate ) = 0;

		//!
		//! \brief Gets audio edit rate for the audio track
		//! \return EditRate object.
		//!
		virtual EditRate GetAudioEditRate() const = 0;

		virtual ~IAudioTrack() = 0;
	};

	inline IAudioTrack::~IAudioTrack() {}
}
#endif  // IAudioTrack_h__
