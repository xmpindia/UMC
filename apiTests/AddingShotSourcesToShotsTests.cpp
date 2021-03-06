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

class AddingShotSourcesToShotsTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( AddingShotSourcesToShotsTests );
	CPPUNIT_TEST( CountOfShotSources );
	CPPUNIT_TEST( ShotSourcesContent );
	CPPUNIT_TEST( SerializeShotSources );
	CPPUNIT_TEST( ParseShotSources );
    CPPUNIT_TEST( RemoveShotSources );
	CPPUNIT_TEST_SUITE_END();

protected:
	void CountOfShotSources();
	void ShotSourcesContent();
	void SerializeShotSources();
	void ParseShotSources();
    void RemoveShotSources();

public:
	virtual void setUp();
	virtual void tearDown();

};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingShotSourcesToShotsTests );

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
    shotSource1->SetShotInCount(10);
    shotSource1->SetSourceInCount(12);
    shotSource1->SetSourceDuration(4);
	auto transitionShot1 = videoTrack1->AddTransitionShot();
	auto shotSource2 = transitionShot1->AddShotSource( source1 );
	auto shotSource3 = transitionShot1->AddShotSource( source2 );
    //std::cout<<shotSource1->Serialize();
    
	return sp;
}

void AddingShotSourcesToShotsTests::CountOfShotSources() {
	std::cout<< "********** AddingShotSourcesToShotsTests::CountOfShotSources **********"<<"\n";
	using namespace UMC;

	auto sp = CreateDefaultUMC();
	auto sources = sp->GetAllSources();
	auto outputs = sp->GetAllOutputs();
	auto tracks = outputs[0]->GetAllTracks();
	auto shots = tracks[0]->GetAllShots();

	CPPUNIT_ASSERT_EQUAL( sp ? true : false, true );
	CPPUNIT_ASSERT_EQUAL( shots[0]->ShotSourceCount(), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( shots[1]->ShotSourceCount(), ( size_t ) 2 );

	auto shotSource = shots[0]->AddShotSource( sources[1] );

	CPPUNIT_ASSERT_EQUAL( shots[0]->ShotSourceCount(), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( shots[1]->ShotSourceCount(), ( size_t ) 2 );

	shots[0]->RemoveShotSource( shotSource->GetUniqueID() );

	CPPUNIT_ASSERT_EQUAL( shots[0]->ShotSourceCount(), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( shots[1]->ShotSourceCount(), ( size_t ) 2 );

	shots[0]->RemoveShotSource( shotSource->GetUniqueID() );

	CPPUNIT_ASSERT_EQUAL( shots[0]->ShotSourceCount(), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( shots[1]->ShotSourceCount(), ( size_t ) 2 );

	shots[0]->RemoveShotSource( shots[0]->GetAllShotSources()[0]->GetUniqueID() );

	CPPUNIT_ASSERT_EQUAL( shots[0]->ShotSourceCount(), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( shots[1]->ShotSourceCount(), ( size_t ) 2 );

	shots[0]->RemoveAllShotSources();

	CPPUNIT_ASSERT_EQUAL( shots[0]->ShotSourceCount(), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( shots[1]->ShotSourceCount(), ( size_t ) 2 );

	shots[1]->RemoveAllShotSources();

	CPPUNIT_ASSERT_EQUAL( shots[0]->ShotSourceCount(), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( shots[1]->ShotSourceCount(), ( size_t ) 0 );

	printf("DONE AddingShotSourcesToShotsTests::CountOfShotSources \n");
}


void AddingShotSourcesToShotsTests::ShotSourcesContent() {
	std::cout<< "********** AddingShotSourcesToShotsTests::ShotSourcesContent **********"<<"\n";
	using namespace UMC;

	auto sp = CreateDefaultUMC();

	auto outputs = sp->GetAllOutputs();
	auto tracks = outputs[0]->GetAllTracks();
	auto shots = tracks[0]->GetAllShots();
	auto shotSources = shots[0]->GetAllShotSources();
	auto source = shotSources[0]->GetSource();
    
    CPPUNIT_ASSERT_EQUAL(shotSources[0]->GetShotInCount(), ( EditUnitInCount ) 10);
    CPPUNIT_ASSERT_EQUAL(shotSources[0]->GetSourceInCount(), (EditUnitInCount) 12);
    CPPUNIT_ASSERT_EQUAL(shotSources[0]->GetSourceDuration(), (EditUnitDuration) 4);

	CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
	CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );
    
    auto vsource = dynamic_pointer_cast< const IVideoSource >( source );
    
    CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
    CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
    
    shotSources[0]->SetUniqueID("shSource1");
    auto shotSource1=shots[0]->GetShotSource("shSource1");
    
    CPPUNIT_ASSERT_EQUAL(shotSource1->GetShotInCount(), ( EditUnitInCount ) 10);
    CPPUNIT_ASSERT_EQUAL(shotSource1->GetSourceInCount(), (EditUnitInCount) 12);
    CPPUNIT_ASSERT_EQUAL(shotSource1->GetSourceDuration(), (EditUnitDuration) 4);
    
    auto source1=shotSource1->GetSource();
    CPPUNIT_ASSERT_EQUAL( source1->GetClipName(), std::string( "source 1" ) );
    CPPUNIT_ASSERT_EQUAL( source1->GetType(), ISource::kSourceTypeVideo );

	shotSources = shots[1]->GetAllShotSources();
	source = shotSources[0]->GetSource();

	CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
	CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );

	vsource = dynamic_pointer_cast< const IVideoSource >( source );

	CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
	CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );

	source = shotSources[1]->GetSource();

	CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 2" ) );
	CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );

	vsource = dynamic_pointer_cast< const IVideoSource >( source );

	CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
	CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
    
    auto shotSource2=shots[0]->GetShotSource("notAvailable");
    if(shotSource2.get()==NULL)
        CPPUNIT_ASSERT(true);
    else
        CPPUNIT_ASSERT(false);
    
    shots[0]->RemoveAllShotSources();
    shotSources=shots[0]->GetAllShotSources();
    std::cout<<shotSources.size();
    CPPUNIT_ASSERT_EQUAL(shotSources.size(), (size_t) 0);
    
    auto source3 = sp->AddVideoSource();
    source3->SetClipName( "source 3" );
    shots[0]->AddShotSource(source3);
    shotSources=shots[0]->GetAllShotSources();
    
    spISource vsrc=NULL;
    try {
        shots[0]->AddShotSource(vsrc);
        CPPUNIT_ASSERT(false);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    shots[0]->RemoveAllShotSources();
    shotSources=shots[0]->GetAllShotSources();
    
    CPPUNIT_ASSERT_EQUAL(shotSources.size(), (size_t) 0);
    
	printf("DONE AddingShotSourcesToShotsTests::ShotSourcesContent \n");
}


void AddingShotSourcesToShotsTests::SerializeShotSources() {
	std::cout<< "********** AddingShotSourcesToShotsTests::SerializeShotSources **********"<<"\n";
	auto sp = CreateDefaultUMC();
	using namespace TestUtils;
	std::string result = ReadTextFileIntoString( Join( GetMaterialDir(), "AddingShotSources.xml" ) );
    CPPUNIT_ASSERT_EQUAL( sp->SerializeToBuffer(), result );

	printf("DONE AddingShotSourcesToShotsTests::SerializeShotSources \n");
}

void AddingShotSourcesToShotsTests::ParseShotSources() {
	std::cout<< "********** AddingShotSourcesToShotsTests::ParseShotSources **********"<<"\n";
	using namespace TestUtils;
	using namespace UMC;
	auto sp = IUMC::CreateUMCFromBuffer( ReadTextFileIntoString( Join( GetMaterialDir(), "AddingShotSources.xml" ) ) );
	auto outputs = sp->GetAllOutputs();
	auto tracks = outputs[0]->GetAllTracks();
	auto shots = tracks[0]->GetAllShots();
	auto shotSources = shots[0]->GetAllShotSources();

	auto source = shotSources[0]->GetSource();

	CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
	CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );

	auto vsource = dynamic_pointer_cast< const IVideoSource >( source );
	
	CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
	CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );

	shotSources = shots[1]->GetAllShotSources();
	source = shotSources[0]->GetSource();

	CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
	CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );

	vsource = dynamic_pointer_cast< const IVideoSource >( source );

	CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
	CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );

	source = shotSources[1]->GetSource();

	CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 2" ) );
	CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );

	vsource = dynamic_pointer_cast< const IVideoSource >( source );

	CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
	CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
    
    try {
        shots[0]->AddShotSource("");
        CPPUNIT_ASSERT(false);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    spIUMC sp2 = IUMC::CreateEmptyUMC();
    auto output2 = sp2->AddOutput();
    auto videoTrack2 = output2->AddVideoTrack();
    auto clipShot2 = videoTrack2->AddClipShot();
    
    try {
        auto shotSource1 = clipShot2->AddShotSource( ReadTextFileIntoString( Join( GetMaterialDir(), "ShotSourcesBuffer.xml" )));
        CPPUNIT_ASSERT(false);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    spIUMC sp3 = IUMC::CreateEmptyUMC();
    auto source3=sp3->AddSource(ReadTextFileIntoString( Join( GetMaterialDir(), "AddingVideoSource.xml" ) ) );
    auto output3 = sp3->AddOutput();
    auto videoTrack3 = output3->AddVideoTrack();
    auto clipShot3 = videoTrack3->AddClipShot();
    
    auto shotSource1 = clipShot3->AddShotSource( ReadTextFileIntoString( Join( GetMaterialDir(), "ShotSourcesBuffer.xml" )));
    auto bshotSources=clipShot3->GetAllShotSources();
    CPPUNIT_ASSERT_EQUAL( bshotSources[0]->GetShotInCount(), ( EditUnitInCount ) 10 );
    auto shSource=bshotSources[0]->GetSource();
    CPPUNIT_ASSERT_EQUAL( shSource->GetClipName(), std::string( "clipNamev1" ) );
    CPPUNIT_ASSERT_EQUAL( shSource->GetType(), ISource::kSourceTypeVideo );
    
	printf("DONE AddingShotSourcesToShotsTests::ParseShotSources \n");
    
}

void AddingShotSourcesToShotsTests::RemoveShotSources() {
    
    std::cout<< "********** AddingShotSourcesToShotsTests::RemoveShotSources **********"<<"\n";
    using namespace UMC;
    
    auto sp = CreateDefaultUMC();
    
    auto outputs = sp->GetAllOutputs();
    auto tracks = outputs[0]->GetAllTracks();
    auto shots = tracks[0]->GetAllShots();
    auto shotSources = shots[0]->GetAllShotSources();
    auto source = shotSources[0]->GetSource();
    
    shots[0]->RemoveShotSource("notAvailable");
    shots[1]->RemoveShotSource("notAvailable");
    CPPUNIT_ASSERT_EQUAL( shots[0]->ShotSourceCount(), ( size_t ) 1 );
    CPPUNIT_ASSERT_EQUAL( shots[1]->ShotSourceCount(), ( size_t ) 2 );
    
    
    shots[0]->RemoveAllShotSources();
    shots[1]->RemoveAllShotSources();
    
    try {
        shots[1]->RemoveAllShotSources();
        CPPUNIT_ASSERT(true);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(false);
    }
    
	printf("DONE AddingShotSourcesToShotsTests::RemoveShotSources \n");
}

void AddingShotSourcesToShotsTests::setUp() {
	UMC_Initialize();
}

void AddingShotSourcesToShotsTests::tearDown() {
	UMC_Terminate();
}


