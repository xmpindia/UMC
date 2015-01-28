#ifndef IConfigurable_h__
#define IConfigurable_h__ 1

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

#include "XMPCommon/XMPCommonFwdDeclarations.h"

namespace NS_XMPCOMMON {
	using namespace NS_XMPCOMMON;

	//!
	//! \brief Version1 of the interface that allows to attach various key-value parameters to the
	//! underlying object.
	//! \details Key is an unsigned 64-bit integer value which can be a char buffer of eight
	//! characters also.
	//! \note For all value types except user data ( const void * ) or char buffer
	//! ( const char * ) a copy is made and is stored, so the scope is maintained
	//! internally. But for user data ( const void * ) or char buffer ( const
	//! char * ) its clients responsibility to make sure these pointers remain
	//! valid through out the life span of the object or objects derived from it.
	//! \attention Multi threading is supported by the derived object if required.
	//!
	class XMP_PUBLIC IConfigurable_v1
	{
	public:

		//!
		//! Indicates various types of parameter values.
		//!
		typedef enum {
			//! Parameter value type is boolean.
			kParameterValueTypeBool					= 0,
			//! Parameter value type is unsigned 64 bit integer.
			kParameterValueTypeUInt64				= 1,
			//! Parameter value type is signed 64 bit integer.
			kParameterValueTypeInt64				= 2,
			//! Parameter value type is character.
			kParameterValueTypeChar					= 3,
			//! Parameter value type is double.
			kParameterValueTypeDouble				= 4,
			//! Parameter value type is char buffer.
			kParameterValueTypeConstCharBuffer		= 5,
			//! Parameter value type is user data ( pointer to const void ).
			kParameterValueTypeConstVoidPtr			= 6,

			//! Maximum value this enum can hold, should be treated as invalid value.
			kParameterValueTypeMaxValue				= kMaxEnumValue
		} eParameterValueType;

		//! @{
		//!
		//! Add/Change a value of a parameter.
		//! \param[in] key an unsigned 64 bit integer value indicating the key.
		//! \param[in] value new value of the parameter.
		//! \attention Error is thrown in case
		//!		- the previous type of value associated with key is of different type.
		//!		- the type of value associated with key is not as expected.
		//!
		virtual void SetParameter( UInt64 key, bool value ) = 0;
		virtual void SetParameter( UInt64 key, UInt64 value ) = 0;
		virtual void SetParameter( UInt64 key, Int64 value ) = 0;
		virtual void SetParameter( UInt64 key, double value ) = 0;
		virtual void SetParameter( UInt64 key, char value ) = 0;
		virtual void SetParameter( UInt64 key, const char * value ) = 0;
		virtual void SetParameter( UInt64 key, const void * value ) = 0;
		//! @}

		//!
		//! Removes a particular parameter if present.
		//! \param[in] key an unsigned 64 bit integer value indicating the key.
		//! \return true in case key was present and is deleted.
		//! \attention Error is thrown in case
		//!		- key is a must have for the underlying object.
		//!
		virtual bool RemoveParameter( UInt64 key ) = 0;

		//! {@
		//!
		//! Get the value of a parameter if present.
		//! \param[in] key an unsigned 64 bit integer value indicating the key.
		//! \param[out] value the value of the parameter.
		//! \return false if no such parameter is present, otherwise true.
		//! \attention Error is thrown in case the type of the parameter is not
		//! the one client is asking for.
		//!
		virtual bool GetParameter( UInt64 key, bool & value ) const = 0;
		virtual bool GetParameter( UInt64 key, UInt64 & value ) const = 0;
		virtual bool GetParameter( UInt64 key, Int64 & value ) const = 0;
		virtual bool GetParameter( UInt64 key, double & value ) const = 0;
		virtual bool GetParameter( UInt64 key, char & value ) const = 0;
		virtual bool GetParameter( UInt64 key, const char * & value ) const = 0;
		virtual bool GetParameter( UInt64 key, const void * & value ) const = 0;
		//! @}

		//!
		//! Get all the keys of the parameters associated with the object.
		//! \detail provide a std::vector containing the keys of all the parameters associated with the object.
		//! \return a std::vector of unsigned 64 bit integers.
		//!
		virtual std::vector< UInt64 > GetAllParameters() const = 0;

		//!
		//! Get the number of parameters associated with the object.
		//!
		virtual SizeT Size() const = 0;

		//!
		//! Get the value type of a particular parameter.
		//! \param[in] key an unsigned 64 bit integer value indicating the key.
		//! \return a value of type eParameterValueType indicating the type of value the parameter is supposed to hold.
		//! \note return kParameterValueTypeMaxValue in case no such key is associated with the object.
		//!
		virtual eParameterValueType GetParameterValueType( UInt64 key ) const = 0;

		//!
		//! Utility function to convert character buffer ( maximum of 8 characters ) to UInt64 representation.
		//! \param[in] key a pointer to const char buffer, maximum characters used are 8 provided there is no
		//! null character present in the buffer between 1st to 8 characters, otherwise characters upto NULL
		//! character (excluding NULL) are read.
		//! \return a 64-bit unsigned integer representing the first 8 characters of the character buffer.
		//! \note return 0 in case key is NULL.
		//!
		static UInt64 ConvertCharBufferToUInt64( const char * key );

	protected:
		//! \cond XMP_INTERNAL_DOCUMENTATION
		// all safe functions
		virtual void SetParameter( UInt64 key, UInt32 value, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void SetParameter( UInt64 key, UInt64 value, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void SetParameter( UInt64 key, Int64 value, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void SetParameter( UInt64 key, double value, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void SetParameter( UInt64 key, char value, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void SetParameter( UInt64 key, const char * value, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void SetParameter( UInt64 key, const void * value, pcIError_base & error ) __NOTHROW__ = 0;
		virtual UInt32 RemoveParameter( UInt64 key, pcIError_base & error ) __NOTHROW__ = 0;
		virtual UInt32 GetParameter( UInt64 key, UInt32 & value, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 GetParameter( UInt64 key, UInt64 & value, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 GetParameter( UInt64 key, Int64 & value, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 GetParameter( UInt64 key, double & value, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 GetParameter( UInt64 key, char & value, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 GetParameter( UInt64 key, const char * & value, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 GetParameter( UInt64 key, const void * & value, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual void GetAllParameters( UInt64 * array, SizeT count ) const __NOTHROW__ = 0;
		virtual UInt32 GetParameterValueType( UInt64 key, pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IConfigurable_v1() __NOTHROW__ = 0;
		
		REQ_FRIEND_CLASS_DECLARATION();

	#if GENERATE_XMPCOMMON_CLIENT_LAYER_CODE
		friend class IConfigurable;
	#endif
	
	};

	inline IConfigurable_v1::~IConfigurable_v1() __NOTHROW__ { }

#if GENERATE_XMPCOMMON_CLIENT_LAYER_CODE
	typedef BASE_CLASS( IConfigurable, CLIENT_ICONFIGURABLE_VERSION ) IConfigurableBase;

	class IConfigurable : public virtual IConfigurableBase {
	//! \cond XMP_INTERNAL_DOCUMENTATION
	public:
		typedef IConfigurableBase *											pIConfigurableBase;
		typedef const IConfigurableBase *									pcIConfigurableBase;
		typedef shared_ptr< IConfigurableBase >								spIConfigurableBase;
		typedef shared_ptr< const IConfigurableBase >						spcIConfigurableBase;

	public:
		IConfigurable( const spIConfigurableBase & sp ) : _sp( sp ) {}
		IConfigurable( const spcIConfigurableBase & csp ) : _sp( const_pointer_cast< IConfigurableBase > ( csp ) ) {}

		virtual void SetParameter( UInt64 key, bool value );
		virtual void SetParameter( UInt64 key, UInt32 value, pcIError_base & error ) __NOTHROW__;
		virtual void SetParameter( UInt64 key, UInt64 value );
		virtual void SetParameter( UInt64 key, UInt64 value, pcIError_base & error ) __NOTHROW__;
		virtual void SetParameter( UInt64 key, Int64 value );
		virtual void SetParameter( UInt64 key, Int64 value, pcIError_base & error ) __NOTHROW__;
		virtual void SetParameter( UInt64 key, double value );
		virtual void SetParameter( UInt64 key, double value, pcIError_base & error ) __NOTHROW__;
		virtual void SetParameter( UInt64 key, char value );
		virtual void SetParameter( UInt64 key, char value, pcIError_base & error ) __NOTHROW__;
		virtual void SetParameter( UInt64 key, const char * value );
		virtual void SetParameter( UInt64 key, const char * value, pcIError_base & error ) __NOTHROW__;
		virtual void SetParameter( UInt64 key, const void * value );
		virtual void SetParameter( UInt64 key, const void * value, pcIError_base & error ) __NOTHROW__;
		virtual bool RemoveParameter( UInt64 key );
		virtual UInt32 RemoveParameter( UInt64 key, pcIError_base & error ) __NOTHROW__;
		virtual bool GetParameter( UInt64 key, bool & value ) const;
		virtual UInt32 GetParameter( UInt64 key, UInt32 & value, pcIError_base & error ) const __NOTHROW__;
		virtual bool GetParameter( UInt64 key, UInt64 & value ) const;
		virtual UInt32 GetParameter( UInt64 key, UInt64 & value, pcIError_base & error ) const __NOTHROW__;
		virtual bool GetParameter( UInt64 key, Int64 & value ) const;
		virtual UInt32 GetParameter( UInt64 key, Int64 & value, pcIError_base & error ) const __NOTHROW__;
		virtual bool GetParameter( UInt64 key, double & value ) const;
		virtual UInt32 GetParameter( UInt64 key, double & value, pcIError_base & error ) const __NOTHROW__;
		virtual bool GetParameter( UInt64 key, char & value ) const;
		virtual UInt32 GetParameter( UInt64 key, char & value, pcIError_base & error ) const __NOTHROW__;
		virtual bool GetParameter( UInt64 key, const char * & value ) const;
		virtual UInt32 GetParameter( UInt64 key, const char * & value, pcIError_base & error ) const __NOTHROW__;
		virtual bool GetParameter( UInt64 key, const void * & value ) const;
		virtual UInt32 GetParameter( UInt64 key, const void * & value, pcIError_base & error ) const __NOTHROW__;
		virtual std::vector< UInt64 > GetAllParameters() const;
		virtual void GetAllParameters( UInt64 * array, SizeT count ) const __NOTHROW__ = 0;
		virtual eParameterValueType GetParameterValueType( UInt64 key ) const = 0;
		virtual UInt32 GetParameterValueType( UInt64 key, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual ~IConfigurable() __NOTHROW__ = 0;

		pcIConfigurableBase GetRawPointer() const { return _sp.get(); }
		pIConfigurableBase GetRawPointer() { return _sp.get(); }

	private:
		spIConfigurableBase					_sp;

	//! \endcond
	};

	inline IConfigurable::~IConfigurable() __NOTHROW__ { }

#endif  // GENERATE_XMPCOMMON_CLIENT_LAYER_CODE
}

#endif  // IConfigurable_h__
