#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"

#include "baseTypes/TimeCode.h"

class TimeCodeTests : public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( TimeCodeTests );
		CPPUNIT_TEST( ToSMPTEString );
		CPPUNIT_TEST( FromSMPTEStringNonDrop );
		CPPUNIT_TEST( FromSMPTEStringDrop );
	CPPUNIT_TEST_SUITE_END();

protected:
	void ToSMPTEString();
	void FromSMPTEStringNonDrop();
	void FromSMPTEStringDrop();

};

void TimeCodeTests::ToSMPTEString() {
	using namespace UMC;
	TimeCode tc( TimeCode::k25Fps, 4, 2, 45, 21 );
	std::string value = tc.SMPTETimecode();
	CPPUNIT_ASSERT_EQUAL( value.compare( "04:02:45:21" ), 0 );
	tc.DropFrame();
	value = tc.SMPTETimecode();
	CPPUNIT_ASSERT_EQUAL( value.compare( "04;02;45;21" ), 0 );
}

void TimeCodeTests::FromSMPTEStringNonDrop() {
	using namespace UMC;
	std::string value = "04:02:45:21";
	TimeCode tc( TimeCode::k25Fps, value.c_str() );
	CPPUNIT_ASSERT_EQUAL( tc.IsDropFrame(), false );
	CPPUNIT_ASSERT_EQUAL( tc.Hours(), ( UMC_Uns8 ) 4 );
	CPPUNIT_ASSERT_EQUAL( tc.Minutes(), ( UMC_Uns8 ) 2 );
	CPPUNIT_ASSERT_EQUAL( tc.Seconds(), ( UMC_Uns8 ) 45 );
	CPPUNIT_ASSERT_EQUAL( tc.Frames(), ( UMC_Uns64) 21 );
	CPPUNIT_ASSERT_EQUAL( tc.FrameRate().Numerator(), (UMC_Uns64) 25 );
	CPPUNIT_ASSERT_EQUAL( tc.FrameRate().Denominator(), ( UMC_Uns64 ) 1 );

}

void TimeCodeTests::FromSMPTEStringDrop() {
	using namespace UMC;
	std::string value = "08;02;35;31";
	TimeCode tc( TimeCode::k25Fps, value.c_str() );
	CPPUNIT_ASSERT_EQUAL( tc.IsDropFrame(), true );
	CPPUNIT_ASSERT_EQUAL( tc.Hours(), ( UMC_Uns8 ) 8 );
	CPPUNIT_ASSERT_EQUAL( tc.Minutes(), ( UMC_Uns8 ) 2 );
	CPPUNIT_ASSERT_EQUAL( tc.Seconds(), ( UMC_Uns8 ) 35 );
	CPPUNIT_ASSERT_EQUAL( tc.Frames(), ( UMC_Uns64 ) 31 );
	CPPUNIT_ASSERT_EQUAL( tc.FrameRate().Numerator(), ( UMC_Uns64 ) 25 );
	CPPUNIT_ASSERT_EQUAL( tc.FrameRate().Denominator(), ( UMC_Uns64 ) 1 );
}


CPPUNIT_TEST_SUITE_REGISTRATION( TimeCodeTests );
