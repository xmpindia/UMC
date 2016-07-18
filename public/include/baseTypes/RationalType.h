#ifndef RationalType_h__
#define RationalType_h__ 1

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

		bool operator == ( const TRationalType & right ) const {
			return ( ( mNumerator * right.mDenominator ) == ( mDenominator * right.mNumerator ) );
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
	typedef Unsigned64RationalType AspectRatio;

	inline std::ostream& operator <<( std::ostream& os, const Unsigned64RationalType& rt )
	{
		os << rt.Numerator() << '/' << rt.Denominator();
		return os;
	}
}

#endif  // RationalType_h__




