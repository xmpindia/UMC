#ifndef TWrapperFunctions_h__
#define TWrapperFunctions_h__ 1

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
// 11-26-14 ADC 1.0-a013 Added the full skeleton for IComposedAssetManager interface.
// 07-10-14 ADC 5.6-c017 Fixing issues related to Mac build.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
//
// =================================================================================================
#endif	// AdobePrivate

#include "XMPCommon/XMPCommonFwdDeclarations.h"

//! \cond XMP_INTERNAL_DOCUMENTATION
namespace NS_XMPCOMMON {

	//!
	//! Function to create Client Code Exception Raise Error on the client side.
	//! \param[in] processFatal a value of bool type indicating whether the severity of error is  process level
	//! or operation level; true for process level severity, false otherwise.
	//! \param[in] message pointer to a constant null terminated char buffer containing message. NULL pointer
	//! will be treated as empty message string.
	//! \param[in] fileName pointer to a constant null terminated char buffer containing fileName in which error
	//! originated.
	//! \param[in] lineNumber a value of #NS_XMPCOMMON::UInt32 type respresenting the lineNumber at which error
	//! originated.
	//! \param[in] paramsCount an object of type #NS_XMPCOMMON::SizeT indicating the number of parameters to be
	//! associated with the error object.
	//! \param[in] params pointer to the first location of an array of constant null terminated char buffers,
	//! where in each location stores a parameter string.
	//!
	pcIError_base CreateClientCodeExceptionError( bool processFatal, const char * message, const char * fileName,
		UInt32 lineNumber, SizeT paramsCount, const char ** params );


	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is zero.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a reference
	//! to a pointer to const #NS_XMPCOMMON::IError_base object and returning void.
	//! \note These take care of non const functions.
	//!
	template < typename className >
	void CallSafeFunctionReturningVoid( className * ptr, void (className::*Func)( pcIError_base & ) ) {
		pcIError_base error( NULL );
		(ptr->*Func)( error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is zero.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting a reference
	//! to a pointer to const #NS_XMPCOMMON::IError_base object and returning void.
	//! \note These take care of const functions.
	//!
	template < typename className >
	void CallConstSafeFunctionReturningVoid( const className * const ptr, void (className::*Func)( pcIError_base & ) const ) {
		pcIError_base error( NULL );
		(ptr->*Func)( error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is 1.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a value of type arg1Type
	//! and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning void.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \note These take care of non const functions.
	//!
	template < typename className, typename arg1Type >
	void CallSafeFunctionReturningVoid( className * ptr, void (className::*Func)( arg1Type, pcIError_base & ), arg1Type arg1Value ) {
		pcIError_base error( NULL );
		(ptr->*Func)( arg1Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is 1.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting a value of type arg1Type
	//! and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning void.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \note These take care of const functions.
	//!
	template < typename className, typename arg1Type >
	void CallConstSafeFunctionReturningVoid( const className * const ptr, void (className::*Func)( arg1Type, pcIError_base & ) const, arg1Type arg1Value ) {
		pcIError_base error( NULL );
		(ptr->*Func)( arg1Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is 2.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a value of type arg1Type
	//! and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning void.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \note These take care of non const functions.
	//!
	template < typename className, typename arg1Type, typename arg2Type >
	void CallSafeFunctionReturningVoid( className * ptr, void (className::*Func)( arg1Type, arg2Type, pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value )
	{
		pcIError_base error( NULL );
		(ptr->*Func)( arg1Value, arg2Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is 2.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to an const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting values of type arg1Type
	//!  and arg2Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning void.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \note These take care of const functions.
	//!
	template < typename className, typename arg1Type, typename arg2Type >
	void CallConstSafeFunctionReturningVoid( const className * const ptr, void (className::*Func)( arg1Type, arg2Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value )
	{
		pcIError_base error( NULL );
		(ptr->*Func)( arg1Value, arg2Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is 3.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a value of type arg1Type,
	//! arg2Type and arg3Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning
	//! void.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \note These take care of non const functions.
	//!
	template < typename className, typename arg1Type, typename arg2Type, typename arg3Type >
	void CallSafeFunctionReturningVoid( className * ptr, void (className::*Func)( arg1Type, arg2Type, arg3Type, pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value )
	{
		pcIError_base error( NULL );
		(ptr->*Func)( arg1Value, arg2Value, arg3Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is 3.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to an const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting values of type arg1Type,
	//! arg2Type and arg3Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning void.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \note These take care of const functions.
	//!
	template < typename className, typename arg1Type, typename arg2Type, typename arg3Type >
	void CallConstSafeFunctionReturningVoid( const className * const ptr, void (className::*Func)( arg1Type, arg2Type, arg3Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value )
	{
		pcIError_base error( NULL );
		(ptr->*Func)( arg1Value, arg2Value, arg3Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is 4.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a value of type arg1Type,
	//! arg2Type, arg3Type and arg4Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and
	//! returning void.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \param[in] arg4Value a value of type arg4Type.
	//! \note These take care of non const functions.
	//!
	template < typename className, typename arg1Type, typename arg2Type, typename arg3Type, typename arg4Type >
	void CallSafeFunctionReturningVoid( className * ptr,
		void (className::*Func)( arg1Type, arg2Type, arg3Type,arg4Type,  pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value, arg3Type arg4Value )
	{
		pcIError_base error( NULL );
		(ptr->*Func)( arg1Value, arg2Value, arg3Value, arg4Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is 4.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to an const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting values of type arg1Type,
	//! arg2Type, arg3Type and arg4Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning void.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \param[in] arg4Value a value of type arg4Type.
	//! \note These take care of const functions.
	//!
	template < typename className, typename arg1Type, typename arg2Type, typename arg3Type, typename arg4Type >
	void CallConstSafeFunctionReturningVoid( const className * const ptr,
		void (className::*Func)( arg1Type, arg2Type, arg3Type, arg4Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value, arg4Type arg4Value )
	{
		pcIError_base error( NULL );
		(ptr->*Func)( arg1Value, arg2Value, arg3Value, arg4Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is 5.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a value of type arg1Type,
	//! arg2Type, arg3Type, arg4Type and arg5Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and
	//! returning void.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \param[in] arg4Value a value of type arg4Type.
	//! \param[in] arg5Value a value of type arg5Type.
	//! \note These take care of non const functions.
	//!
	template < typename className, typename arg1Type, typename arg2Type, typename arg3Type, typename arg4Type, typename arg5Type >
	void CallSafeFunctionReturningVoid( className * ptr,
		void (className::*Func)( arg1Type, arg2Type, arg3Type,arg4Type, arg5Type, pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value, arg3Type arg4Value, arg5Type arg5Value )
	{
		pcIError_base error( NULL );
		(ptr->*Func)( arg1Value, arg2Value, arg3Value, arg4Value, arg5Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void and number of arguments for client exposed function is 5.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to an const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting values of type arg1Type,
	//! arg2Type, arg3Type, arg4Type and arg5Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning void.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \param[in] arg4Value a value of type arg4Type.
	//! \param[in] arg5Value a value of type arg5Type.
	//! \note These take care of const functions.
	//!
	template < typename className, typename arg1Type, typename arg2Type, typename arg3Type, typename arg4Type, typename arg5Type >
	void CallConstSafeFunctionReturningVoid( const className * const ptr,
		void (className::*Func)( arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value, arg4Type arg4Value, arg5Type arg5Value )
	{
		pcIError_base error( NULL );
		(ptr->*Func)( arg1Value, arg2Value, arg3Value, arg4Value, arg5Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 0.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a reference to a
	//! pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! These take care of non const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType >
	returnType CallSafeFunction( className * ptr, internalReturnType (className::*Func)( pcIError_base & ) ) {
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 0.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting a reference to a
	//! pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! These take care of const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType >
	returnType CallConstSafeFunction( const className * const ptr, internalReturnType (className::*Func)( pcIError_base & ) const ) {
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 1.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a value of type arg1Type
	//! and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! These take care of non const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type >
	returnType CallSafeFunction( className * ptr, internalReturnType (className::*Func)( arg1Type, pcIError_base & ), arg1Type arg1Value ) {
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 1.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting a value of type arg1Type
	//! and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! These take care of const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type >
	returnType CallConstSafeFunction( const className * const ptr, internalReturnType (className::*Func)( arg1Type, pcIError_base & ) const,
		arg1Type arg1Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 2.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a values of type arg1Type
	//! and arg2Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! These take care of non const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type, typename arg2Type >
	returnType CallSafeFunction( className * ptr, internalReturnType (className::*Func)( arg1Type, arg2Type, pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 2.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting a values of type arg1Type
	//!  and arg2Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! These take care of const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type, typename arg2Type >
	returnType CallConstSafeFunction( const className * const ptr, internalReturnType (className::*Func)( arg1Type, arg2Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 3.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a values of type arg1Type,
	//! arg2Type and arg3Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! These take care of non const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type, typename arg2Type, typename arg3Type >
	returnType CallSafeFunction( className * ptr, internalReturnType (className::*Func)( arg1Type, arg2Type, arg3Type, pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, arg3Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 3.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting a values of type arg1Type,
	//! arg2Type and arg3Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! These take care of const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type, typename arg2Type, typename arg3Type >
	returnType CallConstSafeFunction( const className * const ptr, internalReturnType (className::*Func)( arg1Type, arg2Type, arg3Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, arg3Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 4.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a values of type arg1Type,
	//! arg2Type, arg3Type and arg4Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \param[in] arg4Value a value of type arg4Type.
	//! These take care of non const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type,
		typename arg2Type, typename arg3Type, typename arg4Type >
	returnType CallSafeFunction( className * ptr,
		internalReturnType (className::*Func)( arg1Type, arg2Type, arg3Type, arg4Type, pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value, arg4Type arg4Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, arg3Value, arg4Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 4.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting a values of type arg1Type,
	//! arg2Type, arg3Type and arg4Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \param[in] arg4Value a value of type arg4Type.
	//! These take care of const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type,
		typename arg2Type, typename arg3Type, typename arg4Type >
	returnType CallConstSafeFunction( const className * const ptr,
		internalReturnType (className::*Func)( arg1Type, arg2Type, arg3Type, arg4Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value, arg4Type arg4Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, arg3Value, arg4Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 5.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a values of type arg1Type,
	//! arg2Type, arg3Type, arg4Type and arg5Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \param[in] arg4Value a value of type arg4Type.
	//! \param[in] arg5Value a value of type arg5Type.
	//! These take care of non const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type,
		typename arg2Type, typename arg3Type, typename arg4Type, typename arg5Type >
	returnType CallSafeFunction( className * ptr,
		internalReturnType (className::*Func)( arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value, arg4Type arg4Value, arg5Type arg5Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, arg3Value, arg4Value, arg5Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed
	//! function is 5.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting a values of type arg1Type,
	//! arg2Type, arg3Type, arg4Type and arg5Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning value of type internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \param[in] arg4Value a value of type arg4Type.
	//! \param[in] arg5Value a value of type arg5Type.
	//! These take care of const functions.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type,
		typename arg2Type, typename arg3Type, typename arg4Type, typename arg5Type >
	returnType CallConstSafeFunction( const className * const ptr,
		internalReturnType (className::*Func)( arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value, arg4Type arg4Value, arg5Type arg5Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, arg3Value, arg4Value, arg5Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
	#if XMP_WinBuild
		#pragma warning( push )
		#pragma warning( disable : 4800 )
	#endif
		return static_cast< returnType >( returnValue );
	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function is a shared pointer
	//! and number of arguments for client exposed function is 0.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a reference to a
	//! pointer to const #NS_XMPCOMMON::IError_base object and returning internalReturnType.
	//! These take care of non const functions.
	//!
	template < typename className, typename internalReturnType, typename sharedPointerType >
	shared_ptr< sharedPointerType > CallSafeFunctionReturningPointer( className * ptr, internalReturnType (className::*Func)( pcIError_base & ) ) {
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
		return NS_XMPCOMMON::MakeSharedPointer< sharedPointerType >( returnValue );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function is a shared pointer
	//! and number of arguments for client exposed function is 0.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting a reference to a
	//! pointer to const #NS_XMPCOMMON::IError_base object and returning internalReturnType.
	//! These take care of const functions.
	//!
	template < typename className, typename internalReturnType, typename sharedPointerType >
	shared_ptr< sharedPointerType > CallConstSafeFunctionReturningPointer( const className * const ptr, internalReturnType (className::*Func)( pcIError_base & ) const ) {
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
		return NS_XMPCOMMON::MakeSharedPointer< sharedPointerType >( returnValue );
	}


	//!
	//! template functions taking care of all the functions where return types of client exposed function is a shared pointer
	//! and number of arguments for client exposed function is 1.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a value of arg1Type
	//! and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! These take care of non const functions.
	//!
	template < typename className, typename internalReturnType, typename sharedPointerType, typename arg1Type >
	shared_ptr< sharedPointerType > CallSafeFunctionReturningPointer( className * ptr, internalReturnType (className::*Func)( arg1Type, pcIError_base & ),
		arg1Type arg1Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
		return NS_XMPCOMMON::MakeSharedPointer< sharedPointerType >( returnValue );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function is a shared pointer
	//! and number of arguments for client exposed function is 1.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to const member function of className accepting a value of arg1Type
	//! and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! These take care of const functions.
	//!
	template < typename className, typename internalReturnType, typename sharedPointerType, typename arg1Type >
	shared_ptr< sharedPointerType > CallConstSafeFunctionReturningPointer( const className * const ptr,
		internalReturnType (className::*Func)( arg1Type, pcIError_base & ) const,
		arg1Type arg1Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
		return NS_XMPCOMMON::MakeSharedPointer< sharedPointerType >( returnValue );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function is a shared pointer
	//! and number of arguments for client exposed function is 2.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a values of arg1Type
	//! and arg2Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! These take care of non const functions.
	//!
	template < typename className, typename internalReturnType, typename sharedPointerType, typename arg1Type, typename arg2Type >
	shared_ptr< sharedPointerType > CallSafeFunctionReturningPointer( className * ptr,
		internalReturnType (className::*Func)( arg1Type, arg2Type, pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
		return NS_XMPCOMMON::MakeSharedPointer< sharedPointerType >( returnValue );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function is a shared pointer
	//! and number of arguments for client exposed function is 2.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a values of arg1Type
	//! and arg2Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! These take care of const functions.
	//!
	template < typename className, typename internalReturnType, typename sharedPointerType, typename arg1Type, typename arg2Type >
	shared_ptr< sharedPointerType > CallConstSafeFunctionReturningPointer( const className * const ptr,
		internalReturnType (className::*Func)( arg1Type, arg2Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
		return NS_XMPCOMMON::MakeSharedPointer< sharedPointerType >( returnValue );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function is a shared
	//! pointer and number of arguments for client exposed function is 3.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a values of arg1Type,
	//! arg2Type and arg3Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning
	//! internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! These take care of non const functions.
	//!
	template < typename className, typename internalReturnType, typename sharedPointerType, typename arg1Type, typename arg2Type, typename arg3Type >
	shared_ptr< sharedPointerType > CallSafeFunctionReturningPointer( className * ptr,
		internalReturnType (className::*Func)( arg1Type, arg2Type, arg3Type, pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, arg3Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
		return NS_XMPCOMMON::MakeSharedPointer< sharedPointerType >( returnValue );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function is a shared
	//! pointer and number of arguments for client exposed function is 3.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a values of arg1Type,
	//! arg2Type and arg3Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and returning
	//! internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! These take care of const functions.
	//!
	template < typename className, typename internalReturnType, typename sharedPointerType, typename arg1Type, typename arg2Type, typename arg3Type >
	shared_ptr< sharedPointerType > CallConstSafeFunctionReturningPointer( const className * const ptr,
		internalReturnType (className::*Func)( arg1Type, arg2Type, arg3Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, arg3Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
		return NS_XMPCOMMON::MakeSharedPointer< sharedPointerType >( returnValue );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function is a shared
	//! pointer and number of arguments for client exposed function is 4.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr non const pointer to an object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a values of
	//! arg1Type, arg2Type, arg3Type and arg4Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base
	//! object and returning internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \param[in] arg4Value a value of type arg4Type.
	//! These take care of non const functions.
	//!
	template < typename className, typename internalReturnType, typename sharedPointerType, typename arg1Type,
		typename arg2Type, typename arg3Type, typename arg4Type >
	shared_ptr< sharedPointerType > CallSafeFunctionReturningPointer( className * ptr,
		internalReturnType (className::*Func)( arg1Type, arg2Type, arg3Type, arg4Type, pcIError_base & ),
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value, arg4Type arg4Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, arg3Value, arg4Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
		return NS_XMPCOMMON::MakeSharedPointer< sharedPointerType >( returnValue );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function is a shared
	//! pointer and number of arguments for client exposed function is 4.
	//! \details It calls the underlying DLL/library safe function and in case any error is reported back through
	//! pointer, it will make a shared pointer out of that and throws for upper functions to catch.
	//! \param[in] ptr const pointer to a const object of className itself ( most probably this pointer ).
	//! \param[in] Func function pointer to non const member function of className accepting a values of arg1Type,
	//! arg2Type, arg3Type and arg4Type and a reference to a pointer to const #NS_XMPCOMMON::IError_base object and
	//! returning internalReturnType.
	//! \param[in] arg1Value a value of type arg1Type.
	//! \param[in] arg2Value a value of type arg2Type.
	//! \param[in] arg3Value a value of type arg3Type.
	//! \param[in] arg4Value a value of type arg4Type.
	//! These take care of const functions.
	//!
	template < typename className, typename internalReturnType, typename sharedPointerType, typename arg1Type,
		typename arg2Type, typename arg3Type, typename arg4Type >
	shared_ptr< sharedPointerType > CallConstSafeFunctionReturningPointer( const className * const ptr,
		internalReturnType (className::*Func)( arg1Type, arg2Type, arg3Type, arg4Type, pcIError_base & ) const,
		arg1Type arg1Value, arg2Type arg2Value, arg3Type arg3Value, arg4Type arg4Value )
	{
		pcIError_base error( NULL );
		internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value, arg3Value, arg4Value, error );
		if ( error )
			throw NS_XMPCOMMON::MakeSharedPointer< const IError >( error );
		return NS_XMPCOMMON::MakeSharedPointer< sharedPointerType >( returnValue );
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void type and number of arguments for client exposed function is 0.
	//!
	template < typename className >
	void CallUnSafeFunctionReturningVoid( pcIError_base & error, className * ptr, void (className::*Func)() ) {
		error = NULL;
		try {
			(ptr->*Func)();
		} catch ( ... ) {
			error = CreateClientCodeExceptionError( false, "Client code has thrown some exception", __FILE__,
				__LINE__, 0, NULL );
		}
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void type and number of arguments for client exposed function is 1.
	//!
	template < typename className, typename arg1Type >
	void CallUnSafeFunctionReturningVoid( pcIError_base & error, className * ptr, void (className::*Func)( arg1Type ), arg1Type arg1Value ) {
		error = NULL;
		try {
			(ptr->*Func)( arg1Value );
		} catch ( ... ) {
			error = CreateClientCodeExceptionError( false, "Client code has thrown some exception", __FILE__,
				__LINE__, 0, NULL );
		}
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are void type and number of arguments for client exposed function is 2.
	//!
	template < typename className, typename arg1Type, typename arg2Type >
	void CallUnSafeFunctionReturningVoid( pcIError_base & error, className * ptr, void (className::*Func)( arg1Type, arg2Type ),
		arg1Type arg1Value, arg2Type arg2Value )
	{
		error = NULL;
		try {
			(ptr->*Func)( arg1Value, arg2Value );
		} catch ( ... ) {
			error = CreateClientCodeExceptionError( false, "Client code has thrown some exception", __FILE__,
				__LINE__, 0, NULL );
		}
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed function is 0.
	//!
	template < typename className, typename returnType, typename internalReturnType >
	returnType CallUnSafeFunction( pcIError_base & error, className * ptr, internalReturnType (className::*Func)() ) {
		error = NULL;
		try {
			internalReturnType returnValue = (ptr->*Func)();
			return static_cast< returnType >( returnValue );
		} catch ( ... ) {
			error = CreateClientCodeExceptionError( false, "Client code has thrown some exception", __FILE__,
				__LINE__, 0, NULL );
		}
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed function is 1.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type >
	returnType CallUnSafeFunction( pcIError_base & error, className * ptr, returnType defaultReturnValue,
		internalReturnType (className::*Func)( arg1Type ), arg1Type arg1Value ) {
		error = NULL;
		try {
			internalReturnType returnValue = (ptr->*Func)( arg1Value );
			return static_cast< returnType >( returnValue );
		} catch ( ... ) {
			error = CreateClientCodeExceptionError( false, "Client code has thrown some exception", __FILE__,
				__LINE__, 0, NULL );
		}
		return defaultReturnValue;
	}

	//!
	//! template functions taking care of all the functions where return types of client exposed function as well as
	//! DLL/library safe function are nor void type neither shared pointers and number of arguments for client exposed function is 2.
	//!
	template < typename className, typename returnType, typename internalReturnType, typename arg1Type, typename arg2Type >
	returnType CallUnSafeFunction( pcIError_base & error, className * ptr, returnType defaultReturnValue,
		internalReturnType (className::*Func)( arg1Type, arg2Type ),
		arg1Type arg1Value, arg2Type arg2Value ) {
		error = NULL;
		try {
			internalReturnType returnValue = (ptr->*Func)( arg1Value, arg2Value );
			return static_cast< returnType >( returnValue );
		} catch ( ... ) {
			error = CreateClientCodeExceptionError( false, "Client code has thrown some exception", __FILE__,
				__LINE__, 0, NULL );
		}
		return defaultReturnValue;
	}
}

//! \endcond

#endif  // TWrapperFunctions_h__
