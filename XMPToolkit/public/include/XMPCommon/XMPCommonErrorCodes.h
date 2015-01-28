#ifndef XMPCommonErrorCodes_h__
#define XMPCommonErrorCodes_h__ 1

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

#include "XMPCommon/XMPCommonDefines.h"

namespace NS_XMPCOMMON {

	//!
	//! Indicates various types of error codes within Configurable domain.
	//!
	typedef enum {
		//! Indicates that key is not supported by the object.
		kConfigurableCodeKeyNotSupported			= 0,
		//! Indicates different type of value provided than the one supported for a key.
		kConfigurableCodeValueTypeNotSupported		= 1,
		//! Indicates that different value type is previously stored for a key.
		kConfigurableCodePreviousTypeDifferent		= 2,
		//! Indicates the type of value stored for a key is different than what client is asking for.
		kConfigurableCodeValueTypeMismatch			= 3,

		//! Maximum value this enum can hold, should be treated as invalid value.
		kConfigurableCodeMaxValue					= kMaxEnumValue
	} eConfigurableErrorCode;
}

#endif  // XMPCommonErrorCodes_h__
