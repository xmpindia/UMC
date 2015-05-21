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

class AddingShotsToTracksTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( AddingShotsToTracksTests );
	CPPUNIT_TEST( CountOfShots );
	CPPUNIT_TEST( ShotsContent );
	CPPUNIT_TEST_SUITE_END();


protected:
	void CountOfShots();
	void ShotsContent();

public:
	virtual void setUp();
	virtual void tearDown();

};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingShotsToTracksTests );

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

	auto clipShot1 = videoTrack1->AddClipShot();
	clipShot1->SetInCount( 10 );
	clipShot1->SetDuration( 15 );

	videoTrack1->AddClipShot();
	videoTrack1->AddClipShot();

	auto transitionShot1 = videoTrack1->AddTransitionShot();
	transitionShot1->SetInCount( 8 );
	transitionShot1->SetDuration( 3 );

	videoTrack1->AddTransitionShot();

	return sp;
}

void AddingShotsToTracksTests::CountOfShots() {
	std::cout<< "********** AddingShotsToTracksTests::CountOfShots **********"<<"\n";
	using namespace UMC;

	/*auto sp = CreateDefaultUMC();
	auto outputs = sp->GetAllOutputs();
	auto videoTracks = outputs[0]->GetAllVideoTracks();

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 5 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 3 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 2 );*/

}


void AddingShotsToTracksTests::ShotsContent() {
	std::cout<< "********** AddingShotsToTracksTests::ShotsContent **********"<<"\n";
	using namespace UMC;


}


void AddingShotsToTracksTests::setUp() {
	UMC_Initialize();
}

void AddingShotsToTracksTests::tearDown() {
	UMC_Terminate();
}


