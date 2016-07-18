#ifndef UMCDefines_h__
#define UMCDefines_h__ 1

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

#include "UMCEnvironment.h"

#include <stddef.h>
#include <string>

#if UMC_MacBuild | UMC_iOSBuild
	#include <stdint.h>
#elif UMC_UNIXBuild
	#include <inttypes.h>
#endif

namespace UMC {
#if UMC_MacBuild | UMC_iOSBuild

	typedef int8_t   UMC_Int8;
	typedef int16_t  UMC_Int16;
	typedef int32_t  UMC_Int32;
	typedef int64_t  UMC_Int64;

	typedef uint8_t  UMC_Uns8;
	typedef uint16_t UMC_Uns16;
	typedef uint32_t UMC_Uns32;
	typedef uint64_t UMC_Uns64;

#elif UMC_WinBuild

	typedef signed char UMC_Int8;
	typedef signed short UMC_Int16;
	typedef signed long UMC_Int32;
	typedef signed long long UMC_Int64;

	typedef unsigned char UMC_Uns8;
	typedef unsigned short UMC_Uns16;
	typedef unsigned long UMC_Uns32;
	typedef unsigned long long UMC_Uns64;

#elif UMC_UNIXBuild

	#if ! UMC_64

		typedef signed char UMC_Int8;
		typedef signed short UMC_Int16;
		typedef signed long UMC_Int32;
		typedef signed long long UMC_Int64;

		typedef unsigned char UMC_Uns8;
		typedef unsigned short UMC_Uns16;
		typedef unsigned long UMC_Uns32;
		typedef unsigned long long UMC_Uns64;

	#else

		typedef signed char UMC_Int8;
		typedef signed short UMC_Int16;
		typedef signed int UMC_Int32;
		typedef signed long long UMC_Int64;

		typedef unsigned char UMC_Uns8;
		typedef unsigned short UMC_Uns16;
		typedef unsigned int UMC_Uns32;
		typedef unsigned long long UMC_Uns64;

	#endif
#endif

	static const UMC_Uns8 Min_UMC_Uns8 = ( ( UMC_Uns8 ) 0x00 );
	static const UMC_Uns8 Max_UMC_Uns8 = ( ( UMC_Uns8 ) 0xFF );
	static const UMC_Uns16 Min_UMC_Uns16 = ( ( UMC_Uns16 ) 0x00 );
	static const UMC_Uns16 Max_UMC_Uns16 = ( ( UMC_Uns16 ) 0xFFFF );
	static const UMC_Uns32 Min_UMC_Uns32 = ( ( UMC_Uns32 ) 0x00 );
	static const UMC_Uns32 Max_UMC_Uns32 = ( ( UMC_Uns32 ) 0xFFFFFFFF );
	static const UMC_Uns64 Min_UMC_Uns64 = ( ( UMC_Uns64 ) 0x00 );
	static const UMC_Uns64 Max_UMC_Uns64 = ( ( UMC_Uns64 ) 0xFFFFFFFFFFFFFFFFLL );

	static const UMC_Int8 Min_UMC_Int8 = ( ( UMC_Int8 ) 0x80 );
	static const UMC_Int8 Max_UMC_Int8 = ( ( UMC_Int8 ) 0x7F );
	static const UMC_Int16 Min_UMC_Int16 = ( ( UMC_Int16 ) 0x8000 );
	static const UMC_Int16 Max_UMC_Int16 = ( ( UMC_Int16 ) 0x7FFF );
	static const UMC_Int32 Min_UMC_Int32 = ( ( UMC_Int32 ) 0x80000000 );
	static const UMC_Int32 Max_UMC_Int32 = ( ( UMC_Int32 ) 0x7FFFFFFF );
	static const UMC_Int64 Min_UMC_Int64 = ( ( UMC_Int64 ) 0x8000000000000000LL );
	static const UMC_Int64 Max_UMC_Int64 = ( ( UMC_Int64 ) 0x7FFFFFFFFFFFFFFFLL );

	typedef UMC_Int64 EditUnitInCount;
	typedef UMC_Uns64 EditUnitDuration;

	static const EditUnitInCount kEditUnitInCountFromBeginning = 0;
	static const EditUnitDuration kEditUnitDurationTillEnd = Max_UMC_Uns64;

	static const size_t npos = std::string::npos;

}

extern "C" void UMC_Initialize();
extern "C" void UMC_Terminate();

#endif // UMCDefines_h__
