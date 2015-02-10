#ifndef RationalType_h__
#define RationalType_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCDefines.h"

namespace UMC {

	template < typename BaseType >
	class TRationalType {
	public:
		TRationalType( const BaseType & numerator, const BaseType & denominator = 1 )
			: mNumerator( numerator )
			, mDenominator( denominator ) { /* assert( denominator != 0 );*/ }

		TRationalType ( const TRationalType & source )
			: mNumerator( source.mNumerator )
			, mDenominator( source.mDenominator ) { }

		TRationalType & operator = ( const TRationalType & right ) {
			mNumerator = right.mNumerator;
			mDenominator = right.mDenominator;
			return *this;
		}

		void Numerator( const BaseType & value ) { mNumerator = value; }
		void Denominator( const BaseType & value ) { /* assert( denominator != 0 ); */ mDenominator = value; }

		BaseType Numerator() const { return mNumerator; }
		BaseType Denominator() const { return mDenominator; }

	protected:
		BaseType		mNumerator;
		BaseType		mDenominator;
	};

	typedef TRationalType< UMC_Uns64 > Unsigned64RationalType;
	typedef TRationalType< UMC_Int64 > Signed64RationalType;

	typedef Unsigned64RationalType EditRate;
	typedef Unsigned64RationalType FrameRate;

}

#endif  // RationalType_h__
