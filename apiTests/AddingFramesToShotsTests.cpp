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

class AddingFramesToShotsTests : public CppUnit::TestCase {
    
    CPPUNIT_TEST_SUITE( AddingFramesToShotsTests );
    CPPUNIT_TEST( CountOfFrames );
    CPPUNIT_TEST( FramesContent );
    CPPUNIT_TEST( SerializeFrames );
    CPPUNIT_TEST( ParseFrames );
    CPPUNIT_TEST( RemoveFrames );
    CPPUNIT_TEST_SUITE_END();
    
    
protected:
    void CountOfFrames();
    void FramesContent();
    void SerializeFrames();
    void ParseFrames();
    void RemoveFrames();
    
public:
    virtual void setUp();
    virtual void tearDown();
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingFramesToShotsTests );

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
    auto videoTrack1 = output1->AddVideoTrack();
    
    auto clipShot1 = videoTrack1->AddClipShot();
    clipShot1->SetInCount( 10 );
    clipShot1->SetDuration( 15 );
    
    auto frame1 = clipShot1->AddFrame( source1 );
    frame1->SetShotInCount( 12 );
    
    auto frame2 = clipShot1->AddFrame( source1 );
    frame2->SetShotInCount( 13 );
    
    auto frame3 = clipShot1->AddFrame( source1 );
    frame3->SetShotInCount( 14 );
    
    return sp;
}

void AddingFramesToShotsTests::CountOfFrames() {
    std::cout<< "********** AddingFramesToShotsTests::CountOfFrames **********"<<"\n";
    using namespace UMC;
    
    auto sp = CreateDefaultUMC();
    auto sources = sp->GetAllSources();
    auto outputs = sp->GetAllOutputs();
    auto tracks = outputs[0]->GetAllTracks();
    auto shots = tracks[0]->GetAllShots();
    auto frames = shots[0]->GetAllFrames();
    
    CPPUNIT_ASSERT_EQUAL( shots[0]->FrameCount(), ( size_t ) 3 );
    
    auto frame1 = shots[0]->AddFrame( sources[0] );
    frame1->SetShotInCount( 15 );
    
    CPPUNIT_ASSERT_EQUAL( shots[0]->FrameCount(), ( size_t ) 4 );
    
    shots[0]->RemoveFrame( frame1->GetUniqueID() );
    
    CPPUNIT_ASSERT_EQUAL( shots[0]->FrameCount(), ( size_t ) 3 );
    
    shots[0]->RemoveAllFrames();
    
    CPPUNIT_ASSERT_EQUAL( shots[0]->FrameCount(), ( size_t ) 0 );
}


void AddingFramesToShotsTests::FramesContent() {
    std::cout<< "********** AddingFramesToShotsTests::FramesContent **********"<<"\n";
    using namespace UMC;
    
    auto sp = CreateDefaultUMC();
    
    auto outputs = sp->GetAllOutputs();
    auto tracks = outputs[0]->GetAllTracks();
    auto shots = tracks[0]->GetAllShots();
    auto frames = shots[0]->GetAllFrames();
    auto source = frames[0]->GetSource();
    
    CPPUNIT_ASSERT_EQUAL( frames[0]->GetShotInCount(), ( EditUnitInCount ) 12 );
    CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
    CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );
    
    frames[0]->SetUniqueID("fr1");
    auto frame1=shots[0]->GetFrame("fr1");
    CPPUNIT_ASSERT_EQUAL( frame1->GetShotInCount(), ( EditUnitInCount ) 12 );
    
    auto fsource1=frame1->GetSource();
    CPPUNIT_ASSERT_EQUAL( fsource1->GetClipName(), std::string( "source 1" ) );
    CPPUNIT_ASSERT_EQUAL( fsource1->GetType(), ISource::kSourceTypeVideo );
    
    auto vsource = dynamic_pointer_cast< const IVideoSource >( source );
    
    CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
    CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
    
    source = frames[1]->GetSource();
    
    CPPUNIT_ASSERT_EQUAL( frames[1]->GetShotInCount(), ( EditUnitInCount ) 13 );
    
    CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
    CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );
    
    vsource = dynamic_pointer_cast< const IVideoSource >( source );
    
    CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
    CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
    
    source = frames[2]->GetSource();
    
    CPPUNIT_ASSERT_EQUAL( frames[2]->GetShotInCount(), ( EditUnitInCount ) 14 );
    
    CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
    CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );
    
    vsource = dynamic_pointer_cast< const IVideoSource >( source );
    
    CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
    CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
    
    auto frame2=shots[0]->GetFrame("notAvailable");
    if(frame2.get()==NULL)
        CPPUNIT_ASSERT(true);
    else
        CPPUNIT_ASSERT(false);
    
    try {
        frame2=shots[0]->GetFrame(NULL);
        CPPUNIT_ASSERT(true);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    spISource source1=NULL;
    
    try {
        shots[0]->AddFrame(source1);
    } catch (std::string) {
        CPPUNIT_ASSERT(true);
    }
    
    
    
    
    
    
}

void AddingFramesToShotsTests::SerializeFrames() {
    std::cout<< "********** AddingFramesToShotsTests::SerializeFrames **********"<<"\n";
    auto sp = CreateDefaultUMC();
    
    using namespace TestUtils;
    std::string result = ReadTextFileIntoString( Join( GetMaterialDir(), "AddingFrames.xml" ) );
    CPPUNIT_ASSERT_EQUAL( sp->SerializeToBuffer(), result );
}

void AddingFramesToShotsTests::ParseFrames() {
    std::cout<< "********** AddingFramesToShotsTests::ParseFrames **********"<<"\n";
    using namespace TestUtils;
    using namespace UMC;
    auto sp = IUMC::CreateUMCFromBuffer( ReadTextFileIntoString( Join( GetMaterialDir(), "AddingFrames.xml" ) ) );
    
    auto outputs = sp->GetAllOutputs();
    auto tracks = outputs[0]->GetAllTracks();
    auto shots = tracks[0]->GetAllShots();
    auto frames = shots[0]->GetAllFrames();
    
    auto source = frames[0]->GetSource();
    
    CPPUNIT_ASSERT_EQUAL( frames[0]->GetShotInCount(), ( EditUnitInCount ) 12 );
    
    CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
    CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );
    
    auto vsource = dynamic_pointer_cast< const IVideoSource >( source );
    
    CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
    CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
    
    source = frames[1]->GetSource();
    
    CPPUNIT_ASSERT_EQUAL( frames[1]->GetShotInCount(), ( EditUnitInCount ) 13 );
    
    CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
    CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );
    
    vsource = dynamic_pointer_cast< const IVideoSource >( source );
    
    CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
    CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
    
    source = frames[2]->GetSource();
    
    CPPUNIT_ASSERT_EQUAL( frames[2]->GetShotInCount(), ( EditUnitInCount ) 14 );
    
    CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
    CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );
    
    vsource = dynamic_pointer_cast< const IVideoSource >( source );
    
    CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
    CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
    CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
    CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
    
    try {
        shots[0]->AddFrame("");
        CPPUNIT_ASSERT(true);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    
    spIUMC sp2 = IUMC::CreateEmptyUMC();
    auto output1 = sp2->AddOutput();
    auto videoTrack1 = output1->AddVideoTrack();
    
    auto clipShot1 = videoTrack1->AddClipShot();
    clipShot1->SetInCount( 10 );
    clipShot1->SetDuration( 15 );
    
    auto frame1 = clipShot1->AddFrame( ReadTextFileIntoString( Join( GetMaterialDir(), "FrameBuffer.xml" ) ) );
    auto frames1=clipShot1->GetAllFrames();
    CPPUNIT_ASSERT_EQUAL( frames1[0]->GetShotInCount(), ( EditUnitInCount ) 12 );
    
    auto fsource1=frames1[0]->GetSource();
    CPPUNIT_ASSERT_EQUAL( fsource1->GetClipName(), std::string( "source 1" ) );
    CPPUNIT_ASSERT_EQUAL( fsource1->GetType(), ISource::kSourceTypeVideo );
    
    
    
}

void AddingFramesToShotsTests::RemoveFrames() {
    std::cout<< "********** AddingFramesToShotsTests::RemoveFrames **********"<<"\n";
    using namespace UMC;
    
    auto sp = CreateDefaultUMC();
    auto sources = sp->GetAllSources();
    auto outputs = sp->GetAllOutputs();
    auto tracks = outputs[0]->GetAllTracks();
    auto shots = tracks[0]->GetAllShots();
    auto frames = shots[0]->GetAllFrames();
    
    shots[0]->RemoveFrame( "notAvailable" );
    
    CPPUNIT_ASSERT_EQUAL( shots[0]->FrameCount(), ( size_t ) 3 );
    
    //error scenarios with NULL
    
    try {
        shots[0]->RemoveFrame(NULL);
        CPPUNIT_ASSERT(false);
    } catch (std::logic_error) {
        
        CPPUNIT_ASSERT(true);
    }
    
    shots[0]->RemoveAllFrames();
    
    try {
        shots[0]->RemoveAllFrames();
        CPPUNIT_ASSERT(true);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(false);
    }
    
    
}

void AddingFramesToShotsTests::setUp() {
    UMC_Initialize();
}

void AddingFramesToShotsTests::tearDown() {
    UMC_Terminate();
}


