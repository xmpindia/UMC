#ifndef ITransitionShot_h__
#define ITransitionShot_h__ 1

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

#include "interfaces/IShot.h"

namespace UMC {

	//!
	//! \brief This interface is for transition shots added to tracks in UMC
	//!
	class ITransitionShot
		: public IShot
	{
	public:
		virtual ~ITransitionShot() = 0;
	};

	inline ITransitionShot::~ITransitionShot() {}
}
#endif  // ITransitionShot_h__
