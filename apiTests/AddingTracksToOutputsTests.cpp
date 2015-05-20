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

class AddingTracksToOuputsTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( AddingTracksToOuputsTests );
	CPPUNIT_TEST( CountOfTracks );
	CPPUNIT_TEST_SUITE_END();


protected:
	void CountOfTracks();

public:
	virtual void setUp();
	virtual void tearDown();

	};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingTracksToOuputsTests );

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

static UMC::spIUMC CreateDefaultUMC() {
	using namespace UMC;
	spIUMC sp = IUMC::CreateEmptyUMC();
	auto output1 = sp->AddOutput();
	auto videoTrack1 = output1->AddVideoTrack();
	videoTrack1->SetName( "videoTrack1" );
	videoTrack1->SetVideoEditRate( EditRate( 24000, 1001 ) );
	videoTrack1->SetAudioEditRate( 48000 );
	output1->AddVideoTrack();
	output1->AddVideoTrack();

	auto audioTrack1 = output1->AddAudioTrack();
	audioTrack1->SetName( "audioTrack1" );
	audioTrack1->SetAudioEditRate( 44000 );
	auto audioTrack2 = output1->AddAudioTrack();
	audioTrack2->SetName( "audioTrack2" );
	output1->AddAudioTrack();
	output1->AddAudioTrack();
	
	return sp;
}

void AddingTracksToOuputsTests::CountOfTracks() {
	std::cout<< "********** AddingTracksToOuputsTests::CountOfTracks **********"<<"\n";
	using namespace UMC;

	auto sp = CreateDefaultUMC();
	/*auto outputs = sp->GetAllOutputs();
	auto videoTracks = outputs[0]->GetAllVideoTracks();

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetName(), std::string( "videoTrack1" ) );*/
}

void AddingTracksToOuputsTests::setUp() {
	UMC_Initialize();
}

void AddingTracksToOuputsTests::tearDown() {
	UMC_Terminate();
}


