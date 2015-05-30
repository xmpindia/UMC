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
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCommon/Interfaces/BaseInterfaces/IConfigurable.h"

#if GENERATE_XMPCOMMON_CLIENT_LAYER_CODE

#include "XMPCommon/Utilities/TWrapperFunctions.h"
#include "XMPCommon/Interfaces/IError.h"

#include <stdlib.h>

namespace NS_XMPCOMMON {


	void IConfigurable::SetParameter( UInt64 key, bool value ) {
		NS_XMPCOMMON::CallSafeFunctionReturningVoid< IConfigurableBase, UInt64, UInt32 >(
			GetRawPointer(), &IConfigurableBase::SetParameter, key, static_cast< UInt32 >( value ) );
	}

	void IConfigurable::SetParameter( UInt64 key, UInt32 value, pcIError_base & error ) __NOTHROW__ {
		_sp->SetParameter( key, value, error );
	}

	void IConfigurable::SetParameter( UInt64 key, UInt64 value ) {
		NS_XMPCOMMON::CallSafeFunctionReturningVoid< IConfigurableBase, UInt64, UInt64 >(
			GetRawPointer(), &IConfigurableBase::SetParameter, key, value );
	}

	void IConfigurable::SetParameter( UInt64 key, UInt64 value, pcIError_base & error ) __NOTHROW__ {
		_sp->SetParameter( key, value, error );
	}

	void IConfigurable::SetParameter( UInt64 key, Int64 value ) {
		NS_XMPCOMMON::CallSafeFunctionReturningVoid< IConfigurableBase, UInt64, Int64 >(
			GetRawPointer(), &IConfigurableBase::SetParameter, key, value );
	}

	void IConfigurable::SetParameter( UInt64 key, Int64 value, pcIError_base & error ) __NOTHROW__ {
		_sp->SetParameter( key, value, error );
	}

	void IConfigurable::SetParameter( UInt64 key, double value ) {
		NS_XMPCOMMON::CallSafeFunctionReturningVoid< IConfigurableBase, UInt64, double >(
			GetRawPointer(), &IConfigurableBase::SetParameter, key, value );
	}

	void IConfigurable::SetParameter( UInt64 key, double value, pcIError_base & error ) __NOTHROW__ {
		_sp->SetParameter( key, value, error );
	}

	void IConfigurable::SetParameter( UInt64 key, char value ) {
		NS_XMPCOMMON::CallSafeFunctionReturningVoid< IConfigurableBase, UInt64, char >(
			GetRawPointer(), &IConfigurableBase::SetParameter, key, value );
	}

	void IConfigurable::SetParameter( UInt64 key, char value, pcIError_base & error ) __NOTHROW__ {
		_sp->SetParameter( key, value, error );
	}

	void IConfigurable::SetParameter( UInt64 key, const char * value ) {
		NS_XMPCOMMON::CallSafeFunctionReturningVoid< IConfigurableBase, UInt64, const char * >(
			GetRawPointer(), &IConfigurableBase::SetParameter, key, value );
	}

	void IConfigurable::SetParameter( UInt64 key, const char * value, pcIError_base & error ) __NOTHROW__ {
		_sp->SetParameter( key, value, error );
	}

	void IConfigurable::SetParameter( UInt64 key, const void * value ) {
		NS_XMPCOMMON::CallSafeFunctionReturningVoid< IConfigurableBase, UInt64, const void * >(
			GetRawPointer(), &IConfigurableBase::SetParameter, key, value );
	}

	void IConfigurable::SetParameter( UInt64 key, const void * value, pcIError_base & error ) __NOTHROW__ {
		_sp->SetParameter( key, value, error );
	}

	bool IConfigurable::RemoveParameter( UInt64 key ) {
		return NS_XMPCOMMON::CallSafeFunction< IConfigurableBase, bool, UInt32, UInt64 >(
			GetRawPointer(), &IConfigurableBase::RemoveParameter, key );
	}

	UInt32 IConfigurable::RemoveParameter( UInt64 key, pcIError_base & error ) __NOTHROW__ {
		return _sp->RemoveParameter( key, error );
	}

	bool IConfigurable::GetParameter( UInt64 key, bool & value ) const {
		UInt32 u32value = value ? 0 : 1;
		bool returnValue = NS_XMPCOMMON::CallConstSafeFunction< IConfigurableBase, bool, UInt32, UInt64, UInt32 & >(
			GetRawPointer(), &IConfigurableBase::GetParameter, key, u32value );
		value = u32value != 0 ? true : false;
		return returnValue;
	}

	UInt32 IConfigurable::GetParameter( UInt64 key, UInt32 & value, pcIError_base & error ) const __NOTHROW__ {
		return _sp->GetParameter( key, value, error );
	}

	bool IConfigurable::GetParameter( UInt64 key, UInt64 & value ) const {
		return NS_XMPCOMMON::CallConstSafeFunction< IConfigurableBase, bool, UInt32, UInt64, UInt64 & >(
			GetRawPointer(), &IConfigurableBase::GetParameter, key, value );
	}

	UInt32 IConfigurable::GetParameter( UInt64 key, UInt64 & value, pcIError_base & error ) const __NOTHROW__ {
		return _sp->GetParameter( key, value, error );
	}

	bool IConfigurable::GetParameter( UInt64 key, Int64 & value ) const {
		return NS_XMPCOMMON::CallConstSafeFunction< IConfigurableBase, bool, UInt32, UInt64, Int64 & >(
			GetRawPointer(), &IConfigurableBase::GetParameter, key, value );
	}

	UInt32 IConfigurable::GetParameter( UInt64 key, Int64 & value, pcIError_base & error ) const __NOTHROW__ {
		return _sp->GetParameter( key, value, error );
	}

	bool IConfigurable::GetParameter( UInt64 key, double & value ) const {
		return NS_XMPCOMMON::CallConstSafeFunction< IConfigurableBase, bool, UInt32, UInt64, double & >(
			GetRawPointer(), &IConfigurableBase::GetParameter, key, value );
	}

	UInt32 IConfigurable::GetParameter( UInt64 key, double & value, pcIError_base & error ) const __NOTHROW__ {
		return _sp->GetParameter( key, value, error );
	}

	bool IConfigurable::GetParameter( UInt64 key, char & value ) const {
		return NS_XMPCOMMON::CallConstSafeFunction< IConfigurableBase, bool, UInt32, UInt64, char & >(
			GetRawPointer(), &IConfigurableBase::GetParameter, key, value );
	}

	UInt32 IConfigurable::GetParameter( UInt64 key, char & value, pcIError_base & error ) const __NOTHROW__ {
		return _sp->GetParameter( key, value, error );
	}

	bool IConfigurable::GetParameter( UInt64 key, const char * & value ) const {
		return NS_XMPCOMMON::CallConstSafeFunction< IConfigurableBase, bool, UInt32, UInt64, const char * & >(
			GetRawPointer(), &IConfigurableBase::GetParameter, key, value );
	}

	UInt32 IConfigurable::GetParameter( UInt64 key, const char * & value, pcIError_base & error ) const __NOTHROW__ {
		return _sp->GetParameter( key, value, error );
	}

	bool IConfigurable::GetParameter( UInt64 key, const void * & value ) const {
		return NS_XMPCOMMON::CallConstSafeFunction< IConfigurableBase, bool, UInt32, UInt64, const void * & >(
			GetRawPointer(), &IConfigurableBase::GetParameter, key, value );
	}

	UInt32 IConfigurable::GetParameter( UInt64 key, const void * & value, pcIError_base & error ) const __NOTHROW__ {
		return _sp->GetParameter( key, value, error );
	}

	std::vector< UInt64 > IConfigurable::GetAllParameters() const {
		SizeT nElements = _sp->Size();
		std::vector< UInt64 > vec;
		vec.reserve( nElements );
		UInt64 * array = ( UInt64 * ) malloc( nElements * sizeof ( UInt64 ) );
		_sp->GetAllParameters( array, nElements );
		for ( SizeT i = 0; i < nElements; i++ )
			vec.push_back( array[i] );
		return vec;
	}

	void IConfigurable::GetAllParameters( UInt64 * array, SizeT count ) const __NOTHROW__ {
		return _sp->GetAllParameters( array , count );
	}

	IConfigurable_v1::eParameterValueType IConfigurable::GetParameterValueType( UInt64 key ) const {
		return NS_XMPCOMMON::CallConstSafeFunction< IConfigurableBase, eParameterValueType, UInt32, UInt64 >(
			GetRawPointer(), &IConfigurableBase::GetParameterValueType, key );
	}

	UInt32 IConfigurable::GetParameterValueType( UInt64 key, pcIError_base & error ) const __NOTHROW__ {
		return _sp->GetParameterValueType( key, error );
	}

}

#endif  // GENERATE_XMPCOMMON_CLIENT_LAYER_CODE

namespace NS_XMPCOMMON {

	UInt64 IConfigurable_v1::ConvertCharBufferToUInt64( const char * key ) {
		UInt64 keyAsUInt64 = 0;
		if ( key ) {
			for ( int i = 0; i < 8 && key[ i ] != '\0'; i++ ) {
				keyAsUInt64 = keyAsUInt64 << 8;
				keyAsUInt64 += ( unsigned char ) key[ i ];
				}
			}
		return keyAsUInt64;
		}	
}
