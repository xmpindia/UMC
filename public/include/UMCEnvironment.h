#ifndef UMCEnvironment_h__
#define UMCEnvironment_h__ 1

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

// =================================================================================================
// Determine the Platform
// ======================

// One of MAC_ENV, WIN_ENV, UNIX_ENV or IOS_ENV must be defined by the client. Since some other code
// requires these to be defined without values, they are only used here to define UMC-specific
// macros with 0 or 1 values.

#if defined ( MAC_ENV )

	#if 0	// ! maybe someday - ! MAC_ENV
		#error "MAC_ENV must be defined so that \"#if MAC_ENV\" is true"
	#endif

	#if defined ( WIN_ENV ) || defined ( UNIX_ENV ) || defined ( IOS_ENV )
		#error "UMC environment error - must define only one of MAC_ENV, WIN_ENV, UNIX_ENV or IOS_ENV"
	#endif

	#define UMC_MacBuild  1
	#define UMC_WinBuild  0
	#define UMC_UNIXBuild 0
	#define UMC_iOSBuild  0

#elif defined ( WIN_ENV )

	#if 0	// ! maybe someday - ! WIN_ENV
		#error "WIN_ENV must be defined so that \"#if WIN_ENV\" is true"
	#endif

	#if defined ( MAC_ENV ) || defined ( UNIX_ENV ) || defined ( IOS_ENV )
		#error "UMC environment error - must define only one of MAC_ENV, WIN_ENV, UNIX_ENV or IOS_ENV"
	#endif

	#define UMC_MacBuild  0
	#define UMC_WinBuild  1
	#define UMC_UNIXBuild 0
	#define UMC_iOSBuild  0

#elif defined ( UNIX_ENV )

	#if 0	// ! maybe someday - ! UNIX_ENV
		#error "UNIX_ENV must be defined so that \"#if UNIX_ENV\" is true"
	#endif

	#if defined ( MAC_ENV ) || defined ( WIN_ENV ) || defined ( IOS_ENV )
		#error "UMC environment error - must define only one of MAC_ENV, WIN_ENV, UNIX_ENV or IOS_ENV"
	#endif

	#define UMC_MacBuild  0
	#define UMC_WinBuild  0
	#define UMC_UNIXBuild 1
	#define UMC_iOSBuild  0

#elif defined ( IOS_ENV )

	#if 0	// ! maybe someday - ! IOS_ENV
		#error "IOS_ENV must be defined so that \"#if IOS_ENV\" is true"
	#endif

	#if defined ( MAC_ENV ) || defined ( WIN_ENV ) || defined ( UNIX_ENV )
		#error "UMC environment error - must define only one of MAC_ENV, WIN_ENV, UNIX_ENV or IOS_ENV"
	#endif

	#define UMC_MacBuild  0
	#define UMC_WinBuild  0
	#define UMC_UNIXBuild 0
	#define UMC_iOSBuild  1

#else

	#error "UMC environment error - must define one of MAC_ENV, WIN_ENV, UNIX_ENV or IOS_ENV"

#endif

// =================================================================================================
// Common Macros
// =============

#if defined ( DEBUG )
	#if defined ( NDEBUG )
		#error "UMC environment error - both DEBUG and NDEBUG are defined"
	#endif
	#define UMC_DebugBuild 1
#endif

#if defined ( NDEBUG )
	#define UMC_DebugBuild 0
#endif

#ifndef UMC_DebugBuild
	#define UMC_DebugBuild 0
#endif

#ifndef UMC_64
	#if _WIN64 || defined(_LP64)
		#define UMC_64 1
	#else
		#define UMC_64 0
	#endif
#endif

// =================================================================================================
// Macintosh Specific Settings
// ===========================
#if (UMC_MacBuild)
	#define UMC_HELPER_DLL_IMPORT __attribute__((visibility("default")))
	#define UMC_HELPER_DLL_EXPORT __attribute__((visibility("default")))
	#define UMC_HELPER_DLL_PRIVATE __attribute__((visibility("hidden")))
#endif

// =================================================================================================
// Windows Specific Settings
// =========================
#if (UMC_WinBuild)
	#define UMC_HELPER_DLL_IMPORT
	#define UMC_HELPER_DLL_EXPORT
	#define UMC_HELPER_DLL_PRIVATE
#endif

// =================================================================================================
// UNIX Specific Settings
// ======================
#if (UMC_UNIXBuild)
	#define UMC_HELPER_DLL_IMPORT
	#define UMC_HELPER_DLL_EXPORT
	#define UMC_HELPER_DLL_PRIVATE
#endif

// =================================================================================================
// IOS Specific Settings
// ===========================
#if (UMC_iOSBuild)
	#include <TargetConditionals.h>
	#if (TARGET_CPU_ARM)
		#define UMC_IOS_ARM 1
	#else
		#define UMC_IOS_ARM 0
	#endif
	#define UMC_HELPER_DLL_IMPORT __attribute__((visibility("default")))
	#define UMC_HELPER_DLL_EXPORT __attribute__((visibility("default")))
	#define UMC_HELPER_DLL_PRIVATE __attribute__((visibility("hidden")))
#endif

// =================================================================================================

#if (UMC_DynamicBuild)
	#define UMC_PUBLIC UMC_HELPER_DLL_EXPORT
	#define UMC_PRIVATE UMC_HELPER_DLL_PRIVATE
#elif (UMC_StaticBuild)
	#define UMC_PUBLIC
	#define UMC_PRIVATE
#else
	#define UMC_PUBLIC UMC_HELPER_DLL_IMPORT
	#define UMC_PRIVATE UMC_HELPER_DLL_PRIVATE
#endif

#endif // UMCEnvironment_h__
