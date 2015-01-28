#ifndef __IError_h__
#define __IError_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
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
// mm/dd/yy who Description of changes, most recent on top.
//
// 12-30-14 ADC 5.6-c032 Adding IConfigurable Interface to XMPCommon.
// 12-07-14 ADC 1.0-a041 Refactored Part Classes and Adding support for IAssetArtboardPart.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 05-19-14 ADC 1.0-m020 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCommon/XMPCommonFwdDeclarations.h"
#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

#if !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB
	#include "XMPCommon/Interfaces/IUTF8String.h"
#endif

namespace NS_XMPCOMMON {

	//!
	//! \brief Version1 of the interface that represents an error/warning encountered during processing.
	//! \details Provides all the functions to get required information regarding error scenario.
	//! \attention Do Not support Multi-threading at object level.
	//! \attention Multi-threading not required since clients will only be provided const objects.
	//!
	class XMP_PUBLIC IError_v1
		: public virtual ISharedOwnership_v1
	{
	public:
		//!
		//! Indicates various types of errors.
		//!
		typedef enum {
			//! Recovery is possible, client can choose to ignore and let library continue with the best possible way.
			kSeverityWarning						= 0,
			//! Recovery is not possible, an exception of type #NS_XMPCOMMON::spcIError will be thrown aborting the API call.
			kSeverityOperationFatal					= 1,
			//! Recovery is not possible, an exception of type #NS_XMPCOMMON::spcIError will be thrown,
			//! the entire process should be aborted.
			kSeverityProcessFatal					= 2,

			// Add new severities here

			//! Maximum value this enum can hold, should be treated as invalid value.
			kSeverityMaxValue						= kMaxEnumValue
		} eErrorSeverity;

		//!
		//! Indicates various types of error domains.
		//!
		typedef enum {
			//! Indicates error related to general conditions.
			kDomainGeneral							= 0,
			//! Indicates error related to memory allocation-deallocation conditions.
			kDomainMemoryManagement					= 1,
			//! Indicates error related to configurable APIs.
			kDomainConfigurable						= 2,

			//! Indicates error related to XMP Data Model Management.
			kDomainXMPDataModel						= 100,
			//! Indicates error related to XMP Parsing.
			kDomainXMPParser						= 101,
			//! Indicates error related to XMP Serializing.
			kDomainXMPSerializer					= 102,

			//! Indicates error related to dealing with XMP in various file formats.
			kDomainXMPFiles							= 200,

			//! Indicates error related to Conflict Identification Domain.
			kDomainConflictIdentification			= 400,

			//! Indicates error related to Conflict Resolution Domain.
			kDomainConflictResolution				= 500,

			//! Indicates error related to Asset Management Domain.
			kDomainAssetManagement					= 600,

			//! Maximum value this enum can hold, should be treated as invalid value.
			kDomainMaxValue							= kMaxEnumValue
		} eErrorDomain;

		//!
		//! Indicates various types of error codes within General Domain.
		//!
		typedef enum {
			//! Indicates that parameters passed to function are not as expected.
			kGeneralCodeParametersNotAsExpected				= 0,
			//! Indicates that version expected by client is not available in the library.
			kGeneralCodeVersionUnavailable					= 1,
			//! Indicates that some assertion has failed.
			kGeneralCodeAssertionFailure					= 2,
			//! Indicates logic failure.
			kGeneralCodeLogicalError						= 3,
			//! Indicates index provided is out of bounds.
			kGeneralCodeIndexOutOfBounds					= 4,
			//! Indicates an internal failure.
			kGeneralCodeInternalFailure						= 5,
			//! Indicates a call to deprecated function.
			kGeneralCodeDeprecatedFunctionCall				= 6,
			//! Indicates an external failure.
			kGeneralCodeExternalFailure						= 7,
			//! Indicates an unknown failure.
			kGeneralCodeUnknownFailure						= 8,
			//! Indicates an error due to User Abort.
			kGeneralCodeUserAbort							= 9,

			//! Indicates that client code has thrown some exception.
			kGeneralCodeClientThrownExceptionCaught			= 100,
			//! Indicates that standard exception has occurred.
			kGeneralCodeStandardException					= 101,

			//! Indicates that some unknown exception has occurred.
			kGeneralCodeUnknownExceptionCaught				= 200,

			//! Indicates that functionality is not yet implemented.
			kGeneralCodeNotImplemented						= 10000,

			//! Maximum value this enum can hold, should be treated as invalid value.
			kGeneralCodeMaxValue							= kMaxEnumValue
		} eGeneralErrorCode;

		//!
		//! Indicates various types of error codes within Memory Management domain.
		//!
		typedef enum {
			//! Indicates that allocation has failed.
			kMemoryManagementCodeAllocationFailure			= 0,

			//! Maximum value this enum can hold, should be treated as invalid value.
			kMemoryManagementMaxValue						= kMaxEnumValue
		} eMemoryManagementErrorCode;

		typedef UInt32 eErrorCode;

		//!
		//! Get the error code.
		//! \return an object of type #eErrorCode indicating the error code.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED eErrorCode GetCode() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the error domain.
		//! \return an object of type #eErrorDomain indicating the error domain.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED eErrorDomain GetDomain() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Get the error severity.
		//! \return an object of type #eErrorSeverity indicating the severity of error.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED eErrorSeverity GetSeverity() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! \brief Get the error message.
		//! \details Error message contains a descriptive string, for debugging use only. It must not be shown to users
		//! in a final product. It is written for developers, not users, and never localized.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String object containing message string.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetMessage() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! \brief Get the location of the error origin.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String object containing location as like file name
		//! and line number.
		//! \note for debugging use only.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetLocation() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! \brief Get the value of a parameter at a particular index.
		//! \details Based on each error condition various parameters are stored along with the error object. Clients can 
		//! one by one get access to each parameter that can be later used for debugging.
		//! \param index		[in]		a value of #NS_XMPCOMMON::SizeT indicating the index of the parameter client is
		//! interested in retrieving.
		//! \return a shared pointer to const #NS_XMPCOMMON::IUTF8String object containing some string.
		//! \attention throws #NS_XMPCOMMON::spcIError in case index is out of bounds.
		//! \note for debugging use only.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetParameter( SizeT index ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! \brief Get the count of parameters.
		//! \return an object of type #NS_XMPCOMMON::SizeT containing the count of paramaters associated with the error object.
		//!
		virtual SizeT GetParametersCount() const __NOTHROW__ = 0;

		//!
		//! Creates an error object which encapsulates the error generated by client during call back operations.
		//! \param errDomain	[in]		a value of #eErrorDomain indicating the error domain.
		//! \param errCode		[in]		a value of #eErrorCode indicating the error code.
		//! \param errSeverity	[in]		a value of #eErrorSeverity indicating the severity of the error.
		//! \param message		[in]		pointer to a constant null terminated char buffer containing message. NULL pointer
		//! will be treated as empty message string.
		//! \param fileName		[in]		pointer to a constant null terminated char buffer containing fileName in which error
		//! originated.
		//! \param lineNumber	[in]		a value of #NS_XMPCOMMON::UInt32 type respresenting the lineNumber at which error
		//! originated.
		//! \param paramsCount	[in]		an object of type #NS_XMPCOMMON::SizeT indicating the number of parameters to be
		//! associated with the error object.
		//! \param parameters	[in]		pointer to the first location of an array of constant null terminated char buffers,
		//! where in each location stores a parameter string.
		//! \return a pointer to a const object of #NS_XMPCOMMON::IError_base.
		//! \attention the returned pointer is allocated on heap by the module so client is responsible for its release. They
		//! should call ReleaseSharedOwnership once they no longer need this object.
		//! 
		static pcIError_base CreateClientInitiatedError( eErrorDomain errDomain, eErrorCode errCode, eErrorSeverity errSeverity,
			const char * message, const char * fileName, UInt32 lineNumber, SizeT paramsCount = 0, const char ** parameters = NULL );

#if !SOURCE_COMPILED
	//! \cond XMP_INTERNAL_DOCUMENTATION
	protected:
		virtual UInt32 GetCode( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 GetDomain( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 GetSeverity( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pcIUTF8String_base GetMessage( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pcIUTF8String_base GetLocation( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pcIUTF8String_base GetParameter( SizeT index, pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond
#endif  // !SOURCE_COMPILED

	protected:
		//!
		//! protected virtual destructor
		//!
		virtual ~IError_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IError_v1::~IError_v1() __NOTHROW__ { }

}

namespace NS_XMPCOMMON {

	inline void ThrowError( IError_base::eErrorDomain domain, IError_base::eErrorCode code, bool processFatal, const char * message,
		const char * fileName, UInt32 lineNumber, SizeT paramsCount, const char ** params)
	{
		pcIError_base errPtr = IError_base::CreateClientInitiatedError( domain, code,
			processFatal ? IError_base::kSeverityProcessFatal : IError_base::kSeverityOperationFatal,
			message, fileName, lineNumber, paramsCount, params );

		if ( errPtr ) {
			spcIError sp = MakeSharedPointer< const IError >( errPtr );
			throw sp;
		} else {
			throw std::bad_exception();
		}
	}

	inline void ThrowNULLPointerError( bool processFatal, const char * message, const char * fileName, UInt32 lineNumber,
		SizeT paramsCount, const char ** params )
	{
		ThrowError( IError_base::kDomainGeneral, IError_base::kGeneralCodeParametersNotAsExpected, processFatal,
			message, fileName, lineNumber, paramsCount, params );
	}

	inline void ThrowVersionNotAvailableError( bool processFatal, const char * message, const char * fileName,
		UInt32 lineNumber, SizeT paramsCount, const char ** params )
	{
		ThrowError( IError_base::kDomainGeneral, IError_base::kGeneralCodeVersionUnavailable, processFatal,
			message, fileName, lineNumber, paramsCount, params );
	}

	inline pcIError_base CreateClientCodeExceptionError( bool processFatal, const char * message, const char * fileName,
		UInt32 lineNumber, SizeT paramsCount, const char ** params )
	{
		return IError_base::CreateClientInitiatedError( IError_base::kDomainGeneral,
			IError_base::kGeneralCodeClientThrownExceptionCaught,
			processFatal ? IError_base::kSeverityProcessFatal : IError_base::kSeverityOperationFatal,
			message, fileName, lineNumber, paramsCount, params );
	}

}

#if !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB
#include "XMPCommon/Utilities/TWrapperFunctions.h"

//! \cond XMP_INTERNAL_DOCUMENTATION
namespace NS_XMPCOMMON {
	inline IError_base::eErrorCode IError_v1::GetCode() const {
		return NS_XMPCOMMON::CallConstSafeFunction< IError_v1, IError_base::eErrorCode, UInt32 >( this, &IError_v1::GetCode );
	}

	inline IError_base::eErrorDomain IError_v1::GetDomain() const {
		return NS_XMPCOMMON::CallConstSafeFunction< IError_v1, IError_base::eErrorDomain, UInt32 >( this, &IError_v1::GetDomain );
	}

	inline IError_base::eErrorSeverity IError_v1::GetSeverity() const {
		return NS_XMPCOMMON::CallConstSafeFunction< IError_v1, IError_base::eErrorSeverity, UInt32 >( this, &IError_v1::GetSeverity );
	}

	inline spcIUTF8String IError_v1::GetMessage() const {
		return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IError_v1, pcIUTF8String_base, const IUTF8String >( this, &IError_v1::GetMessage );
	}

	inline spcIUTF8String IError_v1::GetLocation() const {
		return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IError_v1, pcIUTF8String_base, const IUTF8String >( this, &IError_v1::GetLocation );
	}

	inline spcIUTF8String IError_v1::GetParameter( SizeT index ) const {
		return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IError_v1, pcIUTF8String_base, const IUTF8String, SizeT >( this, &IError_v1::GetParameter, index );
	}

}
//! \endcond
#endif  // !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB


#if SOURCE_COMPILED
//! \cond XMP_INTERNAL_DOCUMENTATION
#include "XMPCommon/Interfaces/IError_I.h"
//! \endcond
#endif

#endif  // __IError_h__
