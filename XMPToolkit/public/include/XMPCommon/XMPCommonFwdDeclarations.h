#ifndef __XMPCommonFwdDeclarations_h__
#define __XMPCommonFwdDeclarations_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  ADC	Amandeep Chawla
//
// mm-dd-yy who Description of changes, most recent first.
//
// 12-30-14 ADC 5.6-c032 Adding IConfigurable Interface to XMPCommon.
// 11-24-14 ADC 1.0-a008 Support for ICompositionRelationship interface.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 05-19-14 ADC 1.0-m020 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
//
// =================================================================================================
#endif	// AdobePrivate

#if !SOURCE_COMPILED
	#include "XMPCommon/XMPCommonDefines.h"
#else
	#include "XMPCommon/XMPCommonDefines_I.h"
#endif
#include "XMPCommon/Utilities/TSmartPointers.h"
#include <vector>

//!
//! Macro to include a client file through with client can control the interface versions he wants to stick with
//! if not the latest ones.
//!
#ifdef XMPCOMMON_CLIENT_HEADER
	#define QUOTEME(FILE_NAME) #FILE_NAME
	#include QUOTEME(XMPCOMMON_CLIENT_HEADER)
#endif

namespace NS_XMPCOMMON {

	using NS_XMPCOMMON::shared_ptr;

	// IError
	class IError_v1;

	typedef IError_v1									IError_base;
	typedef IError_v1 *									pIError_base;
	typedef const IError_v1 *							pcIError_base;

	typedef IError_v1									IError_latest;

	#if !SOURCE_COMPILED
		#ifndef CLIENT_IERROR_VERSION
			typedef IError_latest						IError;
		#else
			class CLIENT_IERROR_VERSION;
			typedef CLIENT_IERROR_VERSION				IError;
		#endif
	#else
		typedef NS_INT_XMPCOMMON::IError_I				IError;
	#endif
	typedef IError	*									pIError;
	typedef const IError	*							pcIError;
	typedef shared_ptr< IError >						spIError;
	typedef shared_ptr< const IError >					spcIError;

	// IUTF8String
	class IUTF8String_v1;

	typedef IUTF8String_v1								IUTF8String_base;
	typedef IUTF8String_v1 *							pIUTF8String_base;
	typedef const IUTF8String_v1 *						pcIUTF8String_base;

	typedef IUTF8String_v1								IUTF8String_latest;

#ifndef CLIENT_IUTF8STRING_VERSION
	typedef IUTF8String_latest							IUTF8String;
#else
	class CLIENT_IUTF8STRING_VERSION;
	typedef CLIENT_IUTF8STRING_VERSION					IUTF8String;
#endif
	typedef IUTF8String	*								pIUTF8String;
	typedef const IUTF8String	*						pcIUTF8String;
	typedef shared_ptr< IUTF8String >					spIUTF8String;
	typedef shared_ptr< const IUTF8String >				spcIUTF8String;

	// IClientAllocator
	class IClientAllocator_v1;

	typedef IClientAllocator_v1							IClientAllocator_base;
	typedef IClientAllocator_v1 *						pIClientAllocator_base;

	typedef IClientAllocator_v1							IClientAllocator_latest;

#ifndef CLIENT_ICLIENTALLOCATOR_VERSION
	typedef IClientAllocator_latest						IClientAllocator;
#else
	class CLIENT_ICLIENTALLOCATOR_VERSION;
	typedef CLIENT_ICLIENTALLOCATOR_VERSION				IClientAllocator;
#endif
	typedef IClientAllocator	*						pIClientAllocator;
	typedef shared_ptr< IClientAllocator >				spIClientAllocator;

	// IClientErrorNotifier
	class IClientErrorNotifier_v1;

	typedef IClientErrorNotifier_v1						IClientErrorNotifier_base;
	typedef IClientErrorNotifier_v1 *					pIClientErrorNotifier_base;

	typedef IClientErrorNotifier_v1						IClientErrorNotifier_latest;

	#ifndef CLIENT_ICLIENTERRORNOTIFIER_VERSION
		typedef IClientErrorNotifier_latest				IClientErrorNotifier;
	#else
		class CLIENT_ICLIENTERRORNOTIFIER_VERSION;
		typedef CLIENT_ICLIENTERRORNOTIFIER_VERSION		IClientErrorNotifier;
	#endif
	typedef IClientErrorNotifier	*					pIClientErrorNotifier;
	typedef shared_ptr< IClientErrorNotifier >			spIClientErrorNotifier;

	// IConfigurationManager
	class IConfigurationManager_v1;

	typedef IConfigurationManager_v1					IConfigurationManager_base;
	typedef IConfigurationManager_v1 *					pIConfigurationManager_base;

	typedef IConfigurationManager_v1					IConfigurationManager_latest;

	#ifndef CLIENT_ICONFIGURATIONMANAGER_VERSION
		typedef IConfigurationManager_latest			IConfigurationManager;
	#else
		class CLIENT_ICONFIGURATIONMANAGER_VERSION;
		typedef CLIENT_ICONFIGURATIONMANAGER_VERSION	IConfigurationManager;
	#endif
	typedef IConfigurationManager	*					pIConfigurationManager;
	typedef shared_ptr< IConfigurationManager >			spIConfigurationManager;

	// IConfigurable
	class IConfigurable_v1;

	typedef IConfigurable_v1							IConfigurable_base;
	typedef IConfigurable_v1 *							pIConfigurable_base;
	typedef const IConfigurable_v1 *					pcIConfigurable_base;

	typedef IConfigurable_v1							IConfigurable_latest;

	#if GENERATE_XMPCOMMON_CLIENT_LAYER_CODE
		#ifndef CLIENT_ICONFIGURABLE_VERSION
			#define CLIENT_ICONFIGURABLE_VERSION 1
		#endif
		class IConfigurable;
	#else
		typedef IConfigurable_latest					IConfigurable;
	#endif

	typedef IConfigurable *								pIConfigurable;
	typedef const IConfigurable *						pcIConfigurable;
	typedef shared_ptr< IConfigurable >					spIConfigurable;
	typedef shared_ptr< const IConfigurable >			spcIConfigurable;

	// typedefs for vectors and their corresponding shared pointers.
	typedef std::vector< spIUTF8String >				IUTF8StringList;
	typedef std::vector< spcIUTF8String >				cIUTF8StringList;

	typedef shared_ptr< IUTF8StringList >				spIUTF8StringList;
	typedef shared_ptr< cIUTF8StringList >				spcIUTF8StringList;

	typedef void * ( *MemAllocatorFunc )( SizeT size );
}

#endif  // __XMPCommonFwdDeclarations_h__
