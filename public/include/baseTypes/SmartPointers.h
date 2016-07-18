#ifndef SmartPointers_h__
#define SmartPointers_h__ 1

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

#include "UMCDefines.h"

#if UMC_WinBuild || UMC_UNIXBuild
	#include <memory>
	#define SMART_PTR_NAMESPACE std
#elif UMC_MacBuild || UMC_iOSBuild
	#include <memory>
	#define SMART_PTR_NAMESPACE std
#else
	#error "location of shared pointer stuff is unknown"
#endif

namespace UMC {
	using SMART_PTR_NAMESPACE::shared_ptr;
	using SMART_PTR_NAMESPACE::weak_ptr;
	using SMART_PTR_NAMESPACE::dynamic_pointer_cast;
	using SMART_PTR_NAMESPACE::static_pointer_cast;
	using SMART_PTR_NAMESPACE::const_pointer_cast;
	using SMART_PTR_NAMESPACE::bad_weak_ptr;
	using SMART_PTR_NAMESPACE::enable_shared_from_this;
}
#endif  // SmartPointers_h__
