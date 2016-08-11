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

class AddingShotsToTracksTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( AddingShotsToTracksTests );
	CPPUNIT_TEST( CountOfShots );
	CPPUNIT_TEST( ShotsContent );
	CPPUNIT_TEST( SerializeShots );
	CPPUNIT_TEST( ParseShots );
    CPPUNIT_TEST( RemoveShots );
	CPPUNIT_TEST_SUITE_END();


protected:
	void CountOfShots();
	void ShotsContent();
	void SerializeShots();
	void ParseShots();
    void RemoveShots();

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
#include "interfaces/IClipShot.h"
#include "interfaces/ITransitionShot.h"

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

	auto sp = CreateDefaultUMC();
	auto outputs = sp->GetAllOutputs();
	auto videoTracks = outputs[0]->GetAllVideoTracks();

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 5 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 3 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 2 );

	auto clipShot = videoTracks[0]->AddClipShot();

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 6 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 4 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 2 );

	auto transitionShot = videoTracks[0]->AddTransitionShot();
	videoTracks[0]->AddTransitionShot();

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 8 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 4 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 4 );

	videoTracks[0]->RemoveShot( clipShot->GetUniqueID() );

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 7 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 3 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 4 );

	videoTracks[0]->RemoveTransitionShot( transitionShot->GetUniqueID() );

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 6 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 3 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 3 );

	clipShot = videoTracks[0]->AddClipShot();

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 7 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 4 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 3 );

	videoTracks[0]->RemoveClipShot( clipShot->GetUniqueID() );

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 6 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 3 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 3 );


	videoTracks[0]->RemoveAllClipShots();

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 3 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 0 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 3 );

	videoTracks[0]->RemoveAllTransitionShots();

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 0 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 0 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 0 );

	videoTracks[0]->AddClipShot();
	videoTracks[0]->AddTransitionShot();

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 2 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 1 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 1 );

	videoTracks[0]->RemoveAllShots();

	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ShotCount(), (size_t) 0 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->ClipShotCount(), (size_t) 0 );
	CPPUNIT_ASSERT_EQUAL( videoTracks[0]->TransitionShotCount(), (size_t) 0 );
}


void AddingShotsToTracksTests::ShotsContent() {
	std::cout<< "********** AddingShotsToTracksTests::ShotsContent **********"<<"\n";
	using namespace UMC;

	auto sp = CreateDefaultUMC();
	auto outputs = sp->GetAllOutputs();
	auto videoTracks = outputs[0]->GetAllVideoTracks();
	auto shots = videoTracks[0]->GetAllShots();
    CPPUNIT_ASSERT_EQUAL(shots.size(), (size_t)5 );

	CPPUNIT_ASSERT_EQUAL( shots[0]->GetInCount(), (EditUnitInCount) 10 );
	CPPUNIT_ASSERT_EQUAL( shots[0]->GetDuration(), (EditUnitDuration) 15 );
    
    shots[0]->SetUniqueID("sh1");
    auto shot1=videoTracks[0]->GetShot("sh1");
    
    CPPUNIT_ASSERT_EQUAL( shot1->GetInCount(), (EditUnitInCount) 10 );
    CPPUNIT_ASSERT_EQUAL( shot1->GetDuration(), (EditUnitDuration) 15 );
    
    auto clipShot1=videoTracks[0]->GetClipShot("sh1");
    
    CPPUNIT_ASSERT_EQUAL( clipShot1->GetInCount(), (EditUnitInCount) 10 );
    CPPUNIT_ASSERT_EQUAL( clipShot1->GetDuration(), (EditUnitDuration) 15 );


	CPPUNIT_ASSERT_EQUAL( shots[1]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( shots[1]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );

	CPPUNIT_ASSERT_EQUAL( shots[2]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( shots[2]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );

	CPPUNIT_ASSERT_EQUAL( shots[3]->GetInCount(), (EditUnitInCount) 8 );
	CPPUNIT_ASSERT_EQUAL( shots[3]->GetDuration(), (EditUnitDuration) 3 );
    
    shots[3]->SetUniqueID("sh2");
    auto transitionShot1=videoTracks[0]->GetShot("sh2");
    
    CPPUNIT_ASSERT_EQUAL( transitionShot1->GetInCount(), (EditUnitInCount) 8 );
    CPPUNIT_ASSERT_EQUAL( transitionShot1->GetDuration(), (EditUnitDuration) 3 );

	CPPUNIT_ASSERT_EQUAL( shots[4]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( shots[4]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );
    
    
    auto shot2=videoTracks[0]->GetShot("notAvailable");
    if(shot2.get()==NULL)
        CPPUNIT_ASSERT(true);
    else
        CPPUNIT_ASSERT(false);
    
    auto clipShot2=videoTracks[0]->GetShot("notAvailable");
    if(clipShot2.get()==NULL)
        CPPUNIT_ASSERT(true);
    else
        CPPUNIT_ASSERT(false);
    
    auto transitionShot2=videoTracks[0]->GetShot("notAvailable");
    if(transitionShot2.get()==NULL)
        CPPUNIT_ASSERT(true);
    else
        CPPUNIT_ASSERT(false);
    
    videoTracks[0]->RemoveAllShots();
    
    auto allClipShots = videoTracks[0]->GetAllClipShots();
    auto allTransitionShots = videoTracks[0]->GetAllTransitionShots();
    auto allShots= videoTracks[0]->GetAllShots();
    
    CPPUNIT_ASSERT_EQUAL(allClipShots.size(), (size_t)0 );
    CPPUNIT_ASSERT_EQUAL(allTransitionShots.size(), (size_t)0 );
    CPPUNIT_ASSERT_EQUAL(allShots.size(), (size_t)0 );
    
    //error scenarios
    auto output2 = sp->AddOutput();
    auto videoTrack1 = output2->AddVideoTrack();
    auto audioTrack1 = output2->AddAudioTrack();
    auto clip2=videoTrack1->AddClipShot();
    
    /*
    try {
        clip2->SetDuration( -4 );
        CPPUNIT_ASSERT(false);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    */
    auto clip3=videoTrack1->AddTransitionShot();
    
    /*
    try {
        clip3->SetDuration( -10 );
        CPPUNIT_ASSERT(false);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    */
    try {
        audioTrack1->GetClipShot(NULL);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    try {
        audioTrack1->GetTransitionShot(NULL);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    try {
        audioTrack1->GetShot(NULL);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    
}

void AddingShotsToTracksTests::SerializeShots()
{
	std::cout<< "********** AddingShotsToTracksTests::SerializeShots **********"<<"\n";
	auto sp = CreateDefaultUMC();

	using namespace TestUtils;
	std::string result = ReadTextFileIntoString( Join( GetMaterialDir(), "AddingShots.xml" ) );
	CPPUNIT_ASSERT_EQUAL( sp->SerializeToBuffer(), result );
}

void AddingShotsToTracksTests::ParseShots()
{
	std::cout<< "********** AddingShotsToTracksTests::ParseShots **********"<<"\n";
	using namespace TestUtils;
	using namespace UMC;
	auto sp = IUMC::CreateUMCFromBuffer( ReadTextFileIntoString( Join( GetMaterialDir(), "AddingShots.xml" ) ) );

	auto outputs = sp->GetAllOutputs();
	auto videoTracks = outputs[0]->GetAllVideoTracks();
	auto shots = videoTracks[0]->GetAllShots();

	CPPUNIT_ASSERT_EQUAL( shots[0]->GetInCount(), (EditUnitInCount) 10 );
	CPPUNIT_ASSERT_EQUAL( shots[0]->GetDuration(), (EditUnitDuration) 15 );

	CPPUNIT_ASSERT_EQUAL( shots[1]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( shots[1]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );

	CPPUNIT_ASSERT_EQUAL( shots[2]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( shots[2]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );

	CPPUNIT_ASSERT_EQUAL( shots[3]->GetInCount(), (EditUnitInCount) 8 );
	CPPUNIT_ASSERT_EQUAL( shots[3]->GetDuration(), (EditUnitDuration) 3 );

	CPPUNIT_ASSERT_EQUAL( shots[4]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( shots[4]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );
    
    spIUMC sp2 = IUMC::CreateEmptyUMC();
    auto output1 = sp2->AddOutput();
    auto videoTrack1=output1->AddVideoTrack();
    
    //checking for Empty string as input
    try {
        videoTrack1->AddShot("");
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    try {
        videoTrack1->AddClipShot("");
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    
    try {
        videoTrack1->AddTransitionShot("");
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    
    //checking for NULL as input
    try {
        videoTrack1->AddShot(NULL);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    try {
        videoTrack1->AddClipShot(NULL);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    
    try {
        videoTrack1->AddTransitionShot(NULL);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    auto audioTrack1=output1->AddAudioTrack();
    audioTrack1->AddShot(ReadTextFileIntoString( Join( GetMaterialDir(), "ShotBuffer.xml" )));
    auto shots1=audioTrack1->GetAllShots();
    
    CPPUNIT_ASSERT_EQUAL( shots1[0]->GetInCount(), (EditUnitInCount) 10 );
    CPPUNIT_ASSERT_EQUAL( shots1[0]->GetDuration(), (EditUnitDuration) 15 );
    
    CPPUNIT_ASSERT_EQUAL( shots1[1]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( shots1[1]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );
    
    CPPUNIT_ASSERT_EQUAL( shots1[2]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( shots1[2]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );
    
    CPPUNIT_ASSERT_EQUAL( shots1[3]->GetInCount(), (EditUnitInCount) 8 );
    CPPUNIT_ASSERT_EQUAL( shots1[3]->GetDuration(), (EditUnitDuration) 3 );
    
    CPPUNIT_ASSERT_EQUAL( shots1[4]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( shots1[4]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );
    
    auto audioTrack2=output1->AddAudioTrack();
    audioTrack2->AddShot(ReadTextFileIntoString( Join( GetMaterialDir(), "ClipShotBuffer.xml" )));
    auto shots2=audioTrack2->GetAllClipShots();
    
    CPPUNIT_ASSERT_EQUAL( shots2[0]->GetInCount(), (EditUnitInCount) 10 );
    CPPUNIT_ASSERT_EQUAL( shots2[0]->GetDuration(), (EditUnitDuration) 15 );
    
    CPPUNIT_ASSERT_EQUAL( shots2[1]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( shots2[1]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );
    
    CPPUNIT_ASSERT_EQUAL( shots2[2]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( shots2[2]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );
    
    auto audioTrack3=output1->AddAudioTrack();
    audioTrack3->AddShot(ReadTextFileIntoString( Join( GetMaterialDir(), "TransitionShotBuffer.xml" )));
    auto shots3=audioTrack2->GetAllTransitionShots();
    
    CPPUNIT_ASSERT_EQUAL( shots3[0]->GetInCount(), (EditUnitInCount) 8 );
    CPPUNIT_ASSERT_EQUAL( shots3[0]->GetDuration(), (EditUnitDuration) 3 );
    
    CPPUNIT_ASSERT_EQUAL( shots3[1]->GetInCount(), (EditUnitInCount) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( shots3[1]->GetDuration(), (EditUnitDuration) kEditUnitDurationTillEnd );

    
    

}

void AddingShotsToTracksTests::RemoveShots() {
    
    auto sp = CreateDefaultUMC();
    auto outputs=sp->AddOutput();
    auto audioTrack=outputs->AddAudioTrack();
    
    auto sp2= CreateDefaultUMC();
    auto outputs2=sp->GetAllOutputs();
    auto videoTracks2 = outputs2[0]->GetAllVideoTracks();
    
    //error scenarios with NULL
    
    try {
        audioTrack->RemoveShot(NULL);
        CPPUNIT_ASSERT(false);
        
    } catch(std::logic_error){
        
        CPPUNIT_ASSERT(true);
        
    }
    
    try {
        audioTrack->RemoveTransitionShot(NULL);
        CPPUNIT_ASSERT(false);
        
    } catch(std::logic_error){
        
        CPPUNIT_ASSERT(true);
        
    }
    
    try {
        audioTrack->RemoveClipShot(NULL);
        CPPUNIT_ASSERT(false);
        
    } catch(std::logic_error){
        
        CPPUNIT_ASSERT(true);
        
    }
    
    //
    
    audioTrack->RemoveAllShots();
    
    try {
        audioTrack->RemoveAllClipShots();
        CPPUNIT_ASSERT(true);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(false);
    }
    
    try {
        audioTrack->RemoveAllTransitionShots();
        CPPUNIT_ASSERT(true);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(false);
    }
    
    videoTracks2[0]->RemoveShot( "notAvailable" );
    
    CPPUNIT_ASSERT_EQUAL( videoTracks2[0]->ShotCount(), (size_t) 6 );
    CPPUNIT_ASSERT_EQUAL( videoTracks2[0]->ClipShotCount(), (size_t) 3 );
    CPPUNIT_ASSERT_EQUAL( videoTracks2[0]->TransitionShotCount(), (size_t) 3 );
    
    videoTracks2[0]->RemoveClipShot( "notAvailable" );
    
    CPPUNIT_ASSERT_EQUAL( videoTracks2[0]->ShotCount(), (size_t) 6 );
    CPPUNIT_ASSERT_EQUAL( videoTracks2[0]->ClipShotCount(), (size_t) 3 );
    CPPUNIT_ASSERT_EQUAL( videoTracks2[0]->TransitionShotCount(), (size_t) 3 );
    
    videoTracks2[0]->RemoveTransitionShot( "notAvailable" );
    
    CPPUNIT_ASSERT_EQUAL( videoTracks2[0]->ShotCount(), (size_t) 6 );
    CPPUNIT_ASSERT_EQUAL( videoTracks2[0]->ClipShotCount(), (size_t) 3 );
    CPPUNIT_ASSERT_EQUAL( videoTracks2[0]->TransitionShotCount(), (size_t) 3 );
    
}


void AddingShotsToTracksTests::setUp() {
	UMC_Initialize();
}

void AddingShotsToTracksTests::tearDown() {
	UMC_Terminate();
}


