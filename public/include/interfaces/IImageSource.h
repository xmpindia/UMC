#ifndef IImageSource_h__
#define IImageSource_h__ 1

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

#include "interfaces/ISource.h"

namespace UMC {

	//!
	//! \brief This interface represents Image Source of UMC.
	//! \details Provides all the functions to get and set various properties of the image source.
	//!
	class IImageSource
		: public ISource
	{
	public:
		virtual ~IImageSource() = 0;
	};

	inline IImageSource::~IImageSource() {}
}

#endif  // IImageSource_h__
