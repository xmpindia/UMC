#ifndef SmartPointers_h__
#define SmartPointers_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

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
