#ifndef IConfigurationManager_h__
#define IConfigurationManager_h__ 1

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
// 02-02-15 ADC 5.6-c036 Porting C++ Based APIs of XMPCore to gcc 4.8.x on Linux Platform.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 05-19-14 ADC 1.0-m020 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
//
// =================================================================================================
#endif	// AdobePrivate

#include "XMPCommon/XMPCommonFwdDeclarations.h"
#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"
#include "XMPCommon/Interfaces/IError.h"

namespace NS_XMPCOMMON {
	//!
	//! \brief Version1 of the interface that represents configuration settings controllable by the client.
	//! \details Provides functions through which client can plug in its own memory allocators, error notifiers.
	//! \attention Not Thread Safe as this functionality is generally used at the initialization phase.
	//!
	class XMP_PUBLIC IConfigurationManager_v1
		: public virtual ISharedOwnership_v1
	{
	public:
		//!
		//! Allows the client to plug in its own memory allocation procedures which will be used to allocate/deallocate memory from the heap.
		//! \param clientAllocator	[in]	a shared pointer to an object of type #NS_XMPCOMMON::IClientAllocator. Invalid shared
		//! pointer will be treated as client wants to switch to default allocator built in the library.
		//! \return a value of bool type; true means successful and false otherwise.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool RegisterClientAllocator( const spIClientAllocator & clientAllocator ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Allows the client to plug in its own error notification procedures which will be used to inform client about various warnings and errors.
		//! \param clientErrorNotifier	[in]	a shared pointer to an object of type #NS_XMPCOMMON::IClientErrorNotifier. Invalid shared
		//! pointer will be treated as client no longer wants to be notified of any warnings or errors.
		//! \return a value of bool type; true means successful and false otherwise.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool RegisterClientErrorNotifier( const spIClientErrorNotifier & clientErrorNotifier ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Allows the client to disable the support for multi threading inside the library. By default library supports multi-threading.
		//! \return a value of bool type; true means successful and false otherwise.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool DisableMultiThreading() MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

#if !SOURCE_COMPILED
	protected:
		//! \cond XMP_INTERNAL_DOCUMENTATION
		virtual UInt32 RegisterClientAllocator( pIClientAllocator_base clientAllocator, pcIError_base & error ) __NOTHROW__ = 0;
		virtual UInt32 RegisterClientErrorNotifier( pIClientErrorNotifier_base clientErrorNotifier, pcIError_base & error ) __NOTHROW__ = 0;
		virtual UInt32 DisableMultiThreading( pcIError_base & error ) __NOTHROW__ = 0;
		//! \endcond
#endif

	protected:
		//!
		//! protected virtual destructor
		//!
		virtual ~IConfigurationManager_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IConfigurationManager_v1::~IConfigurationManager_v1() __NOTHROW__ { }

};

#if !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB
//! \cond XMP_INTERNAL_DOCUMENTATION
#include "XMPCommon/Utilities/TWrapperFunctions.h"

namespace NS_XMPCOMMON {
	inline bool IConfigurationManager_v1::RegisterClientAllocator( const spIClientAllocator & clientAllocator ) {
		return NS_XMPCOMMON::CallSafeFunction< IConfigurationManager_v1, bool, UInt32, pIClientAllocator_base >(
			this, &IConfigurationManager_v1::RegisterClientAllocator, clientAllocator.get() );
	}

	inline bool IConfigurationManager_v1::RegisterClientErrorNotifier( const spIClientErrorNotifier & clientErrorNotifier ) {
		return NS_XMPCOMMON::CallSafeFunction< IConfigurationManager_v1, bool, UInt32, pIClientErrorNotifier_base >(
			this, &IConfigurationManager_v1::RegisterClientErrorNotifier, clientErrorNotifier.get() );
	}

	inline UInt32 IConfigurationManager_v1::DisableMultiThreading( pcIError_base & error ) __NOTHROW__ {
		return NS_XMPCOMMON::CallSafeFunction< IConfigurationManager_v1, bool, UInt32 >(
			this, &IConfigurationManager_v1::DisableMultiThreading );
	}
}
//! \endcond
#endif  // !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB

#endif // IConfigurationManager_h__
