// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"
#include "TestUtils.h"

class SetUniqueIDTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( SetUniqueIDTests );
		CPPUNIT_TEST( ReferenceCountPreserved );
		CPPUNIT_TEST( ParsedIDPreserved );
	CPPUNIT_TEST_SUITE_END();

protected:
	void ReferenceCountPreserved();
	void ParsedIDPreserved();

public:
	virtual void setUp();
	virtual void tearDown();

};

CPPUNIT_TEST_SUITE_REGISTRATION( SetUniqueIDTests );

#include "interfaces/IUMC.h"
#include "interfaces/IOutput.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/ITrack.h"
#include "interfaces/IVideoTrack.h"
#include "interfaces/IAudioTrack.h"
#include "interfaces/IShot.h"
#include "interfaces/IShotSource.h"
#include "interfaces/IClipShot.h"
#include "interfaces/ITransitionShot.h"
#include "interfaces/IFrame.h"

static UMC::spIUMC CreateDefaultUMC() {
	using namespace UMC;

	spIUMC sp = IUMC::CreateEmptyUMC();
	auto output1 = sp->AddOutput();
	auto source1 = sp->AddVideoSource();
	source1->SetClipName( "source 1" );
	auto source2 = sp->AddVideoSource();
	source2->SetClipName( "source 2" );
	auto videoTrack1 = output1->AddVideoTrack();

	auto clipShot1 = videoTrack1->AddClipShot();
	clipShot1->SetInCount( 10 );
	clipShot1->SetDuration( 15 );

	auto shotSource1 = clipShot1->AddShotSource( source1 );
	auto transitionShot1 = videoTrack1->AddTransitionShot();
	auto shotSource2 = transitionShot1->AddShotSource( source1 );
	auto shotSource3 = transitionShot1->AddShotSource( source2 );
	return sp;
}

void SetUniqueIDTests::ReferenceCountPreserved() {
	std::cout << "********** SetUniqueIDTests::ReferenceCountPreserved **********" << "\n";
	using namespace UMC;

	auto sp = CreateDefaultUMC();
	auto videoSourceNode = sp->GetVideoSource( "2" );
	CPPUNIT_ASSERT_EQUAL( videoSourceNode->GetReferenceCount(), ( size_t )2 );

	CPPUNIT_ASSERT_EQUAL( videoSourceNode->SetUniqueID( "video2" ), true );
	CPPUNIT_ASSERT_EQUAL( videoSourceNode->GetReferenceCount(), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( videoSourceNode->GetUniqueID().compare( "video2" ), 0 );
}

void SetUniqueIDTests::setUp() {
	UMC_Initialize();
}

void SetUniqueIDTests::tearDown() {
	UMC_Terminate();
}

void SetUniqueIDTests::ParsedIDPreserved() {
	std::cout << "********** SetUniqueIDTests::ParsedIDPreserved **********" << "\n";
	using namespace UMC;

	auto temp = CreateDefaultUMC();
	auto sp = IUMC::CreateUMCFromBuffer( temp->Serialize() );
	std::cout<<temp->Serialize();
	std::cout<<sp->Serialize();

	auto videoSourceNode = sp->GetVideoSource( "2" );
	CPPUNIT_ASSERT_EQUAL( videoSourceNode->GetReferenceCount(), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( videoSourceNode->GetParsedID().compare("2"), 0 );
}

