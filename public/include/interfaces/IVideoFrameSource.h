#ifndef IVideoFrameSource_h__
#define IVideoFrameSource_h__ 1

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
