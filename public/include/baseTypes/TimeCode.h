#ifndef TimeCode_h__
#define TimeCode_h__ 1

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

#include "baseTypes/RationalType.h"
#include <string>

namespace UMC {

	class TimeCode {
	public:
		typedef enum {
			k24Fps			= 0,
			k25Fps			= 1,
			k30Fps			= 2,
			k50Fps			= 3,
			k60Fps			= 4,
			k23_976Fps		= 5,
			k29_97Fps		= 6,
			k59_94Fps		= 7,

			kNonStandardFrameRate = Max_UMC_Int32
		} eStandardFrameRates;

		TimeCode( const FrameRate & frameRate, UMC_Uns8 hours = 0, UMC_Uns8 minutes = 0,
			UMC_Uns8 seconds = 0, UMC_Uns64 frames = 0, bool isDropFrame = false
		);

		TimeCode( eStandardFrameRates standardFrameRate, UMC_Uns8 hours = 0, UMC_Uns8 minutes = 0,
			UMC_Uns8 seconds = 0, UMC_Uns64 frames = 0, bool isDropFrame = false );

		TimeCode( const UMC::FrameRate & frameRate, const char * smpteTimeCode );
		TimeCode( eStandardFrameRates standardFrameRate, const char * smpteTimeCode );

		void DropFrame() { mIsDropFrame = true; }
		void NonDropFrame() { mIsDropFrame = false; }
		bool IsDropFrame() const { return mIsDropFrame; }
		bool IsNonDropFrame() const { return !mIsDropFrame; }

		void FrameRate( const UMC::FrameRate & frameRate );
		UMC::FrameRate FrameRate() const { return mFrameRate; }

		void StandardFrameRate( eStandardFrameRates standardFrameRate );
		eStandardFrameRates StandardFrameRate() const { return mStandardFrameRate; }

		void Hours( const UMC_Uns8 & hours ) { /*assert( hours < 24 );*/ mHours = hours; }
		UMC_Uns8 Hours() const { return mHours; }

		void Minutes( const UMC_Uns8 & minutes ) { /*assert( minutes < 60);*/ mMinutes = minutes; }
		UMC_Uns8 Minutes() const { return mMinutes; }

		void Seconds( const UMC_Uns8 & seconds ) { /*assert( seconds < 60 );*/ mSeconds = seconds; }
		UMC_Uns8 Seconds() const { return mSeconds; }

		void Frames( const UMC_Uns64 & frames ) { /*assert( mFrames < mFrameRate.Numerator() / mFrameRate.Denominator() );*/ mFrames = frames; }
		UMC_Uns64 Frames() const { return mFrames; }

		void SMPTETimecode( const char * smpteTimeCode );

		std::string SMPTETimecode() const;

		bool operator == ( const TimeCode & right ) const {
			return ( mFrameRate == right.mFrameRate &&
				mIsDropFrame == right.mIsDropFrame &&
				mHours == right.mHours &&
				mMinutes == right.mMinutes &&
				mSeconds == right.mSeconds &&
				mFrames == right.mFrames &&
				mStandardFrameRate == right.mStandardFrameRate
				);
		}

	protected:
		UMC::FrameRate			mFrameRate;
		bool					mIsDropFrame;
		UMC_Uns8				mHours;
		UMC_Uns8				mMinutes;
		UMC_Uns8				mSeconds;
		UMC_Uns64				mFrames;
		eStandardFrameRates		mStandardFrameRate;
	};


	inline std::ostream& operator <<( std::ostream& os, const TimeCode& tc )
	{
		os << tc.SMPTETimecode();
		return os;
	}
}
#endif  // TimeCode_h__
