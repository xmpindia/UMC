#ifndef __XMPCommonDefines_h__
#define __XMPCommonDefines_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
// XMP_CommonDefines.h - Common Defines across all the XMP Components
// ================================================================
//
// This header defines common definitions to be used across all the XMP Components.
//
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  ADC	Amandeep Chawla
//
// mm/dd/yy who Description of changes, most recent on top.
//
// 12-30-14 ADC 5.6-c032 Adding IConfigurable Interface to XMPCommon.
// 11-19-14 ADC 1.0-a001 Framework in place for Asset Management Library.
// 08-03-14 ADC 1.0-m029 Fixing crashers on Macintosh.
// 07-10-14 ADC 5.6-c017 Fixing issues related to Mac build.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 05-19-14 ADC 1.0-m020 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 04-11-14 ADC 1.0-m019 [3739647] Find a Strategy to resolve the issues of "multiple definitions" faced
//						 by clients while integrating the new builds containing Compare and Merge.
// 03-03-14 ADC 1.0-m013 Implemented GetMergedMetadata function of ThreeWayMerge.
// 02-25-14 ADC 1.0-m010 Porting XMPCompareAndMerge to Mac Environment.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c003 Fixing crash in XMPFilesAPI test.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-18-14 ADC 1.0-m005 Fixes for problems reported by QE during the basic sanity tests
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 1.0-m002 Some changes in the common framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

// =================================================================================================
// All Platform Settings
// ===========================
#include "XMP_Environment.h"
#include "XMP_Const.h"

// =================================================================================================
// Macintosh Specific Settings
// ===========================
#if XMP_MacBuild
	#define ENABLE_XMP_COMMON_CODE 1
	#define SUPPORT_STD_ATOMIC_IMPLEMENTATION 0
	#define SUPPORT_SHARED_POINTERS_IN_TR1 0
	#define SUPPORT_SHARED_POINTERS_IN_STD 1 
	#define SUPPORT_SHARED_POINTERS_WITH_ALLOCATORS 0
	#define BAD_EXCEPTION_SUPPORT_STRINGS 0
	#define VECTOR_SUPPORT_CONST_ITERATOR_FUNCTIONS 0
	#define SUPPORT_DYNAMIC_CAST_OPTIMIZATION 0
#endif

// =================================================================================================
// IOS Specific Settings
// ===========================
#if XMP_iOSBuild
	#define ENABLE_XMP_COMMON_CODE 1
	#define SUPPORT_STD_ATOMIC_IMPLEMENTATION 0
	#define SUPPORT_SHARED_POINTERS_IN_TR1 1
	#define SUPPORT_SHARED_POINTERS_IN_STD 0
	#define SUPPORT_SHARED_POINTERS_WITH_ALLOCATORS 0
	#define BAD_EXCEPTION_SUPPORT_STRINGS 0
	#define VECTOR_SUPPORT_CONST_ITERATOR_FUNCTIONS 0
	#define SUPPORT_DYNAMIC_CAST_OPTIMIZATION 0
#endif

// =================================================================================================
// Windows Specific Settings
// =========================
#if XMP_WinBuild
	#define ENABLE_XMP_COMMON_CODE 1
	#define SUPPORT_SHARED_POINTERS_WITH_ALLOCATORS 1
	#if _MSC_VER <= 1600
		#define SUPPORT_STD_ATOMIC_IMPLEMENTATION 0
		#define SUPPORT_SHARED_POINTERS_IN_TR1 1
		#define SUPPORT_SHARED_POINTERS_IN_STD 0
	#else
		#define SUPPORT_STD_ATOMIC_IMPLEMENTATION 1
		#define SUPPORT_SHARED_POINTERS_IN_TR1 0
		#define SUPPORT_SHARED_POINTERS_IN_STD 1
	#endif
	#define BAD_EXCEPTION_SUPPORT_STRINGS 1
	#define VECTOR_SUPPORT_CONST_ITERATOR_FUNCTIONS 1
	#define SUPPORT_DYNAMIC_CAST_OPTIMIZATION 1
#endif

// =================================================================================================
// UNIX Specific Settings
// ======================
#if XMP_UNIXBuild
	#define ENABLE_XMP_COMMON_CODE 1
	#define SUPPORT_STD_ATOMIC_IMPLEMENTATION 0
	#define SUPPORT_SHARED_POINTERS_IN_TR1 0
	#define SUPPORT_SHARED_POINTERS_IN_STD 1
	#define SUPPORT_SHARED_POINTERS_WITH_ALLOCATORS 0
	#define BAD_EXCEPTION_SUPPORT_STRINGS 0
	#define VECTOR_SUPPORT_CONST_ITERATOR_FUNCTIONS 1
	#define SUPPORT_DYNAMIC_CAST_OPTIMIZATION 0
	#define SHARED_POINTERS_REQUIRE_ACCESS_TO_DESTRUCTOR 1
	#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
	#define REQ_FRIEND_CLASS_DECLARATION() template<typename _Ptr, std::_Lock_policy _Lp> friend class std::_Sp_counted_ptr;
#endif

#ifndef REQ_FRIEND_CLASS_DECLARATION
	#define REQ_FRIEND_CLASS_DECLARATION()
#endif

#ifndef ENABLE_XMP_COMMON_CODE
	#define ENABLE_XMP_COMMON_CODE 0
#endif

#if ENABLE_XMP_COMMON_CODE
	//! \cond XMP_INTERNAL_DOCUMENTATION
	//! \cond NEVER_IN_DOCUMENTATION
	#define NS_XMPCOMMON AdobeXMPCommon
	namespace NS_XMPCOMMON {};
	//! \endcond

	#ifndef BUILDING_XMPCOMMON_LIB
		#define  BUILDING_XMPCOMMON_LIB 0
	#endif

	#ifndef SOURCE_COMPILING_XMPCOMMON_LIB
		#define SOURCE_COMPILING_XMPCOMMON_LIB 0
	#endif

	#if SOURCE_COMPILING_XMPCOMMON_LIB
		#if BUILDING_XMPCOMMON_LIB
			#error "You can't have both SOURCE_COMPILATION and BUILDING_LIB set together"
		#endif
		#define GENERATE_XMPCOMMON_CLIENT_LAYER_CODE 0
		#define GENERATE_XMPCOMMON_DLL_LAYER_CODE 0
	#endif

	#if BUILDING_XMPCOMMON_LIB
		#if SOURCE_COMPILING_XMPCOMMON_LIB
			#error "You can't have both SOURCE_COMPILATION and BUILDING_LIB set together"
		#endif
		#define GENERATE_XMPCOMMON_CLIENT_LAYER_CODE 0
		#define GENERATE_XMPCOMMON_DLL_LAYER_CODE 1
	#endif

	#ifndef GENERATE_XMPCOMMON_CLIENT_LAYER_CODE
		#define GENERATE_XMPCOMMON_CLIENT_LAYER_CODE 1
	#endif

	#ifndef GENERATE_XMPCOMMON_DLL_LAYER_CODE
		#define GENERATE_XMPCOMMON_DLL_LAYER_CODE 1
	#endif

	//TODO: @Aman to remove later on
	#if SOURCE_COMPILED
		#define BUILDING_XMPCOMMON_LIB 1
	#endif


	//!
	//! controls whether client wants to build source directly into his application/library.
	//!
	#ifndef SOURCE_COMPILED
		#define SOURCE_COMPILED 0
	#endif

	#if SOURCE_COMPILED
		#define VIRTUAL_IF_SOURCE_COMPILED virtual
		#define MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED = 0
		#define BUILDING_XMPCOMMON_LIB 1
	#else
		#define VIRTUAL_IF_SOURCE_COMPILED 
		#define MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED 
	#endif

	#define __NOTHROW__ throw()

	#define JOIN_CLASSNAME_WITH_VERSION_NUMBER_INT(x,y) x ## _v ## y
	#define JOIN_CLASSNAME_WITH_VERSION_NUMBER(x,y)  JOIN_CLASSNAME_WITH_VERSION_NUMBER_INT(x,y)
	#define BASE_CLASS(classNameWithoutVersionNumber, versionNumber) JOIN_CLASSNAME_WITH_VERSION_NUMBER(classNameWithoutVersionNumber, versionNumber)

	//! \endcond

	namespace NS_XMPCOMMON {

		typedef XMP_Int64 Int64;
		typedef XMP_Uns64 UInt64;
		typedef XMP_Int32 Int32;
		typedef XMP_Uns32 UInt32;

	#if ! XMP_64
		typedef XMP_Uns32 	NativeUInt;
		typedef XMP_Int32 	NativeInt;
	#else
		typedef XMP_Uns64 	NativeUInt;
		typedef XMP_Int64 	NativeInt;
	#endif

		typedef NativeUInt	SizeT;
	
		const SizeT kMaxSize_t = ( SizeT ) -1;
		// force an enum type to be represented in 32 bits
		static const XMP_Int32 kMaxEnumValue = Max_XMP_Int32;

		//!
		//! Indicates multi threading support required by client.
		//!
		typedef enum {
			//! Use multi threading support configured at initialization through #NS_XMPCOMMON::IConfigurationManager.
			//! By default library is not multi threaded.
			kMultiThreadingConfiguredAtInitialization						= 0,
			//! Disable multi threading support at the object level, by passing this value during creation or cloning operation (if provided).
			//! Can also be used to set no multi threading as the default behavior of multi threading support during initialization.
			kNoMultiThreading												= 1,
			//! Enable multi threading support at the object level, by passing this value during creation or cloning operation (if provided).
			//! Can also be used to set multi threading as the default behavior of multi threading support during initialization.
			kMulthiThreading												= 2,
			//! Uses the setting of the current object to be cloned. Only makes sense in case of cloning operation.
			kMultiThreadingUseClonedObjectValue								= 3,

			//! Maximum value this enum can hold, should be treated as invalid value.
			kMultithreadingMaxValue											= kMaxEnumValue
		} eMultiThreadingSupport;
	}

#endif  // ENABLE_XMP_COMMON_CODE

#endif  // __XMPCommonDefines_h__

