// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "baseTypes/TimeCode.h"
#include <sstream>
#include <iomanip>


namespace UMC {

	static void ParseSMPTETimeCode( const char * smpteTimeCode, TimeCode & timeCode ) {
		if ( smpteTimeCode ) {
			std::string str( smpteTimeCode );
			char seperator = ':';
			size_t indexOfSeperator = str.find_first_of( seperator );
			if ( indexOfSeperator == std::string::npos ) {
				seperator = ';';
				timeCode.DropFrame();
				indexOfSeperator = str.find_first_of( seperator );
			} else {
				timeCode.IsNonDropFrame();
			}
			//assert( indexOfSeperator == 1 || indexOfSeperator == 2 );
			str.assign( smpteTimeCode, indexOfSeperator );
			timeCode.Hours( atoi( str.c_str() ) );

			smpteTimeCode = smpteTimeCode + indexOfSeperator + 1;
			str.assign( smpteTimeCode );
			indexOfSeperator = str.find_first_of( seperator );
			//assert( indexOfSeperator == 1 || indexOfSeperator == 2 );
			str.assign( smpteTimeCode, indexOfSeperator );
			timeCode.Minutes( atoi( str.c_str() ) );

			smpteTimeCode = smpteTimeCode + indexOfSeperator + 1;
			str.assign( smpteTimeCode );
			indexOfSeperator = str.find_first_of( seperator );
			//assert( indexOfSeperator == 1 || indexOfSeperator == 2 );
			str.assign( smpteTimeCode, indexOfSeperator );
			timeCode.Seconds( atoi( str.c_str() ) );

			str.assign( smpteTimeCode + indexOfSeperator + 1 );
			timeCode.Frames( atoi( str.c_str() ) );
		}
	}

	static TimeCode::eStandardFrameRates ConvertToStandardFrameRate( const FrameRate & frameRate ) {
		UMC_Uns64 intFrameRate = frameRate.Numerator() / frameRate.Denominator();
		bool exactMatch = intFrameRate * frameRate.Denominator() == frameRate.Numerator();
		
		if ( exactMatch ) {
			switch ( intFrameRate ) {
				case 24:
					return TimeCode::k24Fps;
					break;

				case 25:
					return TimeCode::k25Fps;
					break;

				case 30:
					return TimeCode::k30Fps;
					break;

				case 50:
					return TimeCode::k50Fps;
					break;

				case 60:
					return TimeCode::k60Fps;
					break;
			}
		}

		double dblFrameRate = static_cast< double >( frameRate.Numerator() );
		dblFrameRate /= frameRate.Denominator();

		if ( dblFrameRate > 23.975 && dblFrameRate < 23.977 ) {
			if ( frameRate.Numerator() % 24000 == 0 && frameRate.Denominator() % 1001 == 0 &&
				frameRate.Numerator() / 24000 == frameRate.Denominator() / 1001 )
				return TimeCode::k23_976Fps;
		} else if ( dblFrameRate > 29.96 && dblFrameRate < 29.98 ) {
			if ( frameRate.Numerator() % 30000 == 0 && frameRate.Denominator() % 1001 == 0 &&
				frameRate.Numerator() / 30000 == frameRate.Denominator() / 1001 )
				return TimeCode::k29_97Fps;
		} else if ( dblFrameRate > 59.93 && dblFrameRate < 59.95 ) {
			if ( frameRate.Numerator() % 60000 == 0 && frameRate.Denominator() % 1001 == 0 &&
				frameRate.Numerator() / 60000 == frameRate.Denominator() / 1001 )
				return TimeCode::k59_94Fps;
		}

		return TimeCode::kNonStandardFrameRate;
	}

	FrameRate ConvertFromStandardFrameRate( TimeCode::eStandardFrameRates standardFrameRate ) {
		FrameRate frameRate( 1 );
		switch ( standardFrameRate ) {
			case TimeCode::k24Fps:
				frameRate.Numerator( 24 );
				break;

			case TimeCode::k25Fps:
				frameRate.Numerator( 25 );
				break;

			case TimeCode::k30Fps:
				frameRate.Numerator( 30 );
				break;

			case TimeCode::k50Fps:
				frameRate.Numerator( 50 );
				break;

			case TimeCode::k60Fps:
				frameRate.Numerator( 60 );
				break;

			case TimeCode::k23_976Fps:
				frameRate.Numerator( 24000 );
				frameRate.Denominator( 1001 );
				break;

			case TimeCode::k29_97Fps:
				frameRate.Numerator( 30000 );
				frameRate.Denominator( 1001 );
				break;

			case TimeCode::k59_94Fps:
				frameRate.Numerator( 60000 );
				frameRate.Denominator( 1001 );
				break;
		}

		return frameRate;
	}

	TimeCode::TimeCode( const UMC::FrameRate & frameRate, const char * smpteTimeCode )
		: mFrameRate( frameRate )
		, mIsDropFrame( false )
		, mHours( 0 )
		, mMinutes( 0 )
		, mSeconds( 0 )
		, mFrames( 0 )
		, mStandardFrameRate( ConvertToStandardFrameRate( frameRate ) )
	{
		ParseSMPTETimeCode( smpteTimeCode, *this );
	}

	TimeCode::TimeCode( eStandardFrameRates standardFrameRate, const char * smpteTimeCode )
		: mFrameRate( ConvertFromStandardFrameRate( standardFrameRate ) )
		, mIsDropFrame( false )
		, mHours( 0 )
		, mMinutes( 0 )
		, mSeconds( 0 )
		, mFrames( 0 )
		, mStandardFrameRate( standardFrameRate )
	{
		ParseSMPTETimeCode( smpteTimeCode, *this );
	}

	TimeCode::TimeCode( const UMC::FrameRate & frameRate, UMC_Uns8 hours /*= 0*/, UMC_Uns8 minutes /*= 0*/,
		UMC_Uns8 seconds /*= 0*/, UMC_Uns64 frames /*= 0*/, bool isDropFrame /*= false */ )
		: mFrameRate( frameRate )
		, mHours( hours )
		, mMinutes( minutes )
		, mSeconds( seconds )
		, mFrames( frames )
		, mIsDropFrame( isDropFrame )
		, mStandardFrameRate( ConvertToStandardFrameRate( frameRate ) )
	{
		/*assert( frames < frameRate.Numerator() / frameRate.Denominator() );
				assert( seconds < 59 );
				assert( minutes < 59 );
				assert( hours < 23 );*/
	}

	TimeCode::TimeCode( eStandardFrameRates standardFrameRate, UMC_Uns8 hours /*= 0*/,
		UMC_Uns8 minutes /*= 0*/, UMC_Uns8 seconds /*= 0*/, UMC_Uns64 frames /*= 0*/,
		bool isDropFrame /*= false */ )
		: mFrameRate( ConvertFromStandardFrameRate( standardFrameRate ) )
		, mHours( hours )
		, mMinutes( minutes )
		, mSeconds( seconds )
		, mFrames( frames )
		, mIsDropFrame( isDropFrame )
		, mStandardFrameRate( standardFrameRate )
	{
		/*assert( frames < mFrameRate.Numerator() / mFrameRate.Denominator() );
		assert( seconds < 59 );
		assert( minutes < 59 );
		assert( hours < 23 );*/
	}

	std::string TimeCode::SMPTETimecode() const {
		char seperator = ':';
		if ( mIsDropFrame )
			seperator = ';';

		std::stringstream buf;
		buf<<std::right<<std::setfill('0')<<std::setw(2)<<(UMC_Uns64) mHours;
		buf<<seperator;
		buf << std::right << std::setfill( '0' ) << std::setw( 2 ) <<(UMC_Uns64) mMinutes;
		buf << seperator;
		buf << std::right << std::setfill( '0' ) << std::setw( 2 ) <<(UMC_Uns64) mSeconds;
		buf << seperator;
		buf << std::right << std::setfill( '0' ) << std::setw( 2 ) << mFrames;

		return buf.str();

	}

	void TimeCode::FrameRate( const UMC::FrameRate & frameRate ) {
		mFrameRate = frameRate;
		mStandardFrameRate = ConvertToStandardFrameRate( frameRate );
		/*assert( mFrames < mFrameRate.Numerator() / mFrameRate.Denominator() ); */
	}

	void TimeCode::StandardFrameRate( eStandardFrameRates standardFrameRate ) {
		mStandardFrameRate = standardFrameRate;
		mFrameRate = ConvertFromStandardFrameRate( standardFrameRate );
	}



}
