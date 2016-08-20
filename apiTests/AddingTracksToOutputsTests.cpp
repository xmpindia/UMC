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

class AddingTracksToOutputsTests : public CppUnit::TestCase {
    
    CPPUNIT_TEST_SUITE( AddingTracksToOutputsTests );
    CPPUNIT_TEST( CountOfTracks );
    CPPUNIT_TEST( TracksContent );
    CPPUNIT_TEST( SerializeTracks );
    CPPUNIT_TEST( ParseTracks );
    CPPUNIT_TEST( RemoveTracks );
    CPPUNIT_TEST_SUITE_END();
    
    
protected:
    void CountOfTracks();
    void TracksContent();
    void SerializeTracks();
    void ParseTracks();
    void RemoveTracks();
    
public:
    virtual void setUp();
    virtual void tearDown();
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingTracksToOutputsTests );

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
    //std::cout<<videoTrack1->Serialize();
    //std::cout<<audioTrack1->Serialize();
    
    return sp;
}

void AddingTracksToOutputsTests::CountOfTracks() {
    std::cout<< "********** AddingTracksToOuputsTests::CountOfTracks **********"<<"\n";
    using namespace UMC;
    
    auto sp = CreateDefaultUMC();
    auto outputs = sp->GetAllOutputs();
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 7 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 3 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 4 );
    
    auto videoTrack = outputs[0]->AddVideoTrack();
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 8 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 4 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 4 );
    
    auto audioTrack = outputs[0]->AddAudioTrack();
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 9 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 4 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 5 );
    
    outputs[0]->RemoveTrack( videoTrack->GetUniqueID() );
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 8 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 3 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 5 );
    
    outputs[0]->RemoveTrack( "notAvailable" );
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 8 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 3 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 5 );
    
    videoTrack = outputs[0]->AddVideoTrack();
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 9 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 4 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 5 );
    
    outputs[0]->RemoveAudioTrack( videoTrack->GetUniqueID() );
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 9 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 4 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 5 );
    
    outputs[0]->RemoveAudioTrack( audioTrack->GetUniqueID() );
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 8 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 4 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 4 );
    
    audioTrack = outputs[0]->AddAudioTrack();
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 9 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 4 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 5 );
    
    outputs[0]->RemoveVideoTrack( videoTrack->GetUniqueID() );
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 8 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 3 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 5 );
    
    outputs[0]->RemoveAllVideoTracks();
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 5 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 0 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 5 );
    
    outputs[0]->RemoveAllAudioTracks();
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 0 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 0 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 0 );
    
    outputs[0]->AddAudioTrack();
    outputs[0]->AddAudioTrack();
    outputs[0]->AddVideoTrack();
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 3 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 1 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 2 );
    
    outputs[0]->RemoveAllTracks();
    
    CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 0 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 0 );
    CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 0 );
    
}


void AddingTracksToOutputsTests::TracksContent() {
    std::cout<< "********** AddingTracksToOuputsTests::TracksContent **********"<<"\n";
    using namespace UMC;
    
    auto sp = CreateDefaultUMC();
    auto outputs = sp->GetAllOutputs();
    auto videoTracks = outputs[0]->GetAllVideoTracks();
    CPPUNIT_ASSERT_EQUAL(videoTracks.size(), (size_t)3 );
    
    
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetType(), ITrack::kTrackTypeVideo );
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetName(), std::string( "videoTrack1" ) );
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetVideoEditRate(), EditRate( 24000, 1001 ) );
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetAudioEditRate(), EditRate( 48000 ) );
    
    videoTracks[0]->SetUniqueID("vt1");
    auto vt1=outputs[0]->GetVideoTrack("vt1");
    
    CPPUNIT_ASSERT_EQUAL( vt1->GetType(), ITrack::kTrackTypeVideo );
    CPPUNIT_ASSERT_EQUAL( vt1->GetName(), std::string( "videoTrack1" ) );
    CPPUNIT_ASSERT_EQUAL( vt1->GetVideoEditRate(), EditRate( 24000, 1001 ) );
    CPPUNIT_ASSERT_EQUAL( vt1->GetAudioEditRate(), EditRate( 48000 ) );
    
    
    for( int i = 1; i < outputs[0]->VideoTrackCount(); i++ )
    {
        CPPUNIT_ASSERT_EQUAL( videoTracks[i]->GetType(), ITrack::kTrackTypeVideo );
        CPPUNIT_ASSERT_EQUAL( videoTracks[i]->GetName(), std::string( "" ) );
        CPPUNIT_ASSERT_EQUAL( videoTracks[i]->GetVideoEditRate(), EditRate( 1 ) );
        CPPUNIT_ASSERT_EQUAL( videoTracks[i]->GetAudioEditRate(), EditRate( 1 ) );
    }
    
    auto audioTracks = outputs[0]->GetAllAudioTracks();
    CPPUNIT_ASSERT_EQUAL(audioTracks.size(), (size_t)4 );
    
    CPPUNIT_ASSERT_EQUAL( audioTracks[0]->GetType(), ITrack::kTrackTypeAudio );
    CPPUNIT_ASSERT_EQUAL( audioTracks[0]->GetName(), std::string( "audioTrack1" ) );
    CPPUNIT_ASSERT_EQUAL( audioTracks[0]->GetAudioEditRate(), EditRate( 44000 ) );
    
    CPPUNIT_ASSERT_EQUAL( audioTracks[1]->GetType(), ITrack::kTrackTypeAudio );
    CPPUNIT_ASSERT_EQUAL( audioTracks[1]->GetName(), std::string( "audioTrack2" ) );
    CPPUNIT_ASSERT_EQUAL( audioTracks[1]->GetAudioEditRate(), EditRate( 1 ) );
    
    audioTracks[0]->SetUniqueID("at1");
    auto at1=outputs[0]->GetAudioTrack("at1");
    
    CPPUNIT_ASSERT_EQUAL( at1->GetType(), ITrack::kTrackTypeAudio );
    CPPUNIT_ASSERT_EQUAL( at1->GetName(), std::string( "audioTrack1" ) );
    CPPUNIT_ASSERT_EQUAL( at1->GetAudioEditRate(), EditRate( 44000 ) );
    
    for( int i = 2; i < outputs[0]->AudioTrackCount(); i++ )
    {
        CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetType(), ITrack::kTrackTypeAudio );
        CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetName(), std::string( "" ) );
        CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetAudioEditRate(), EditRate( 1 ) );
    }
    
    audioTracks[1]->SetUniqueID("at2");
    auto t1=outputs[0]->GetTrack("at2");
    
    CPPUNIT_ASSERT_EQUAL( t1->GetType(), ITrack::kTrackTypeAudio );
    CPPUNIT_ASSERT_EQUAL( t1->GetName(), std::string( "audioTrack2" ) );
    
    
    spIVideoTrack video1=outputs[0]->GetVideoTrack("notAvailable");
    if(video1.get()==NULL)
        CPPUNIT_ASSERT(true);
    else
        CPPUNIT_ASSERT(false);
    
    spIAudioTrack audio1=outputs[0]->GetAudioTrack("notAvailable");
    if(audio1.get()==NULL)
        CPPUNIT_ASSERT(true);
    else
        CPPUNIT_ASSERT(false);
    
    spITrack track1=outputs[0]->GetTrack("notAvailable");
    if (track1.get()==NULL)
        CPPUNIT_ASSERT(true);
    else
        CPPUNIT_ASSERT(false);
    
    outputs[0]->RemoveAllTracks();
    
    auto allVideoTracks = outputs[0]->GetAllVideoTracks();
    auto allAudioTracks = outputs[0]->GetAllAudioTracks();
    auto allTracks= outputs[0]->GetAllTracks();
    
    CPPUNIT_ASSERT_EQUAL(allAudioTracks.size(), (size_t)0 );
    CPPUNIT_ASSERT_EQUAL(allVideoTracks.size(), (size_t)0 );
    CPPUNIT_ASSERT_EQUAL(allTracks.size(), (size_t)0 );
    
    
    
    //error scenarios
    auto output2 = sp->AddOutput();
    auto videoTrack1 = output2->AddVideoTrack();
    
    try {
        videoTrack1->SetAudioEditRate( EditRate( 0 ) );
        CPPUNIT_ASSERT(false);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    try {
        videoTrack1->SetVideoEditRate( EditRate( 20,0 ) );
        CPPUNIT_ASSERT(false);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    auto audioTrack1 = output2->AddVideoTrack();

    
    try {
        audioTrack1->SetAudioEditRate( EditRate( 0 ) );
        CPPUNIT_ASSERT(false);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    try {
        audioTrack1->SetVideoEditRate( EditRate( 0,0 ) );
        CPPUNIT_ASSERT(false);
        
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    
    
}

void AddingTracksToOutputsTests::SerializeTracks() {
    std::cout<< "********** AddingTracksToOuputsTests::SerializeTracks **********"<<"\n";
    auto sp = CreateDefaultUMC();
    std::cout<<sp->SerializeToBuffer();
    using namespace TestUtils;
    std::string result = ReadTextFileIntoString( Join( GetMaterialDir(), "AddingTracks.xml" ) );
    
}

void AddingTracksToOutputsTests::ParseTracks() {
    std::cout<< "********** AddingTracksToOuputsTests::ParseTracks **********"<<"\n";
    
    using namespace TestUtils;
    using namespace UMC;
    auto sp = IUMC::CreateUMCFromBuffer( ReadTextFileIntoString( Join( GetMaterialDir(), "AddingTracks.xml" ) ) );
    
    auto outputs = sp->GetAllOutputs();
    auto videoTracks = outputs[0]->GetAllVideoTracks();
    
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetType(), ITrack::kTrackTypeVideo );
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetName(), std::string( "videoTrack1" ) );
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetVideoEditRate(), EditRate( 24000, 1001 ) );
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetAudioEditRate(), EditRate( 48000 ) );
    
    for( int i = 1; i < outputs[0]->VideoTrackCount(); i++ )
    {
        CPPUNIT_ASSERT_EQUAL( videoTracks[i]->GetType(), ITrack::kTrackTypeVideo );
        CPPUNIT_ASSERT_EQUAL( videoTracks[i]->GetName(), std::string( "" ) );
        CPPUNIT_ASSERT_EQUAL( videoTracks[i]->GetVideoEditRate(), EditRate( 1 ) );
        CPPUNIT_ASSERT_EQUAL( videoTracks[i]->GetAudioEditRate(), EditRate( 1 ) );
    }
    
    auto audioTracks = outputs[0]->GetAllAudioTracks();
    
    CPPUNIT_ASSERT_EQUAL( audioTracks[0]->GetType(), ITrack::kTrackTypeAudio );
    CPPUNIT_ASSERT_EQUAL( audioTracks[0]->GetName(), std::string( "audioTrack1" ) );
    CPPUNIT_ASSERT_EQUAL( audioTracks[0]->GetAudioEditRate(), EditRate( 44000 ) );
    
    CPPUNIT_ASSERT_EQUAL( audioTracks[1]->GetType(), ITrack::kTrackTypeAudio );
    CPPUNIT_ASSERT_EQUAL( audioTracks[1]->GetName(), std::string( "audioTrack2" ) );
    CPPUNIT_ASSERT_EQUAL( audioTracks[1]->GetAudioEditRate(), EditRate( 1 ) );
    
    for( int i = 2; i < outputs[0]->AudioTrackCount(); i++ )
    {
        CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetType(), ITrack::kTrackTypeAudio );
        CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetName(), std::string( "" ) );
        CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetAudioEditRate(), EditRate( 1 ) );
    }
    
    spIUMC sp2 = IUMC::CreateEmptyUMC();
    auto output1 = sp2->AddOutput();
    
    //checking for Empty string as input
    try {
        output1->AddTrack("");
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    try {
        output1->AddVideoTrack("");
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    
    try {
        output1->AddAudioTrack("");
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    output1->AddVideoTrack( ReadTextFileIntoString( Join( GetMaterialDir(), "VideoTrackBuffer.xml" ) ) );
    
    auto videoTracks1 = output1->GetAllVideoTracks();
    
    CPPUNIT_ASSERT_EQUAL( videoTracks1[0]->GetType(), ITrack::kTrackTypeVideo );
    CPPUNIT_ASSERT_EQUAL( videoTracks1[0]->GetVideoEditRate(), EditRate( 2400, 1001 ) );
    CPPUNIT_ASSERT_EQUAL( videoTracks1[0]->GetAudioEditRate(), EditRate( 4800 ) );
    
    output1->AddAudioTrack( ReadTextFileIntoString( Join( GetMaterialDir(), "AudioTrackBuffer.xml" ) ) );
    auto audioTracks1 = output1->GetAllAudioTracks();
    
    CPPUNIT_ASSERT_EQUAL( audioTracks1[0]->GetType(), ITrack::kTrackTypeAudio );
    CPPUNIT_ASSERT_EQUAL( audioTracks1[0]->GetAudioEditRate(), EditRate( 4400 ) );
    
    auto output2 = sp2->AddOutput();
    output2->AddTrack( ReadTextFileIntoString( Join( GetMaterialDir(), "TrackBuffer.xml" ) ) );
    
    videoTracks = output2->GetAllVideoTracks();
    
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetType(), ITrack::kTrackTypeVideo );
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetVideoEditRate(), EditRate( 24000, 1001 ) );
    CPPUNIT_ASSERT_EQUAL( videoTracks[0]->GetAudioEditRate(), EditRate( 48000 ) );
    
    
}

void AddingTracksToOutputsTests::RemoveTracks() {
    std::cout<< "********** AddingTracksToOuputsTests::RemoveTracks **********"<<"\n";
    using namespace UMC;
    spIUMC sp = IUMC::CreateEmptyUMC();
    auto outputs=sp->GetAllOutputs();
    
    auto output1 = sp->AddOutput();
    //output1->AddAudioTrack();
    try{
        output1->RemoveAllAudioTracks();
        CPPUNIT_ASSERT(true);
        
    }catch(std::logic_error){
        CPPUNIT_ASSERT(false);
        
    }
    
    try{
        output1->RemoveAllVideoTracks();
        CPPUNIT_ASSERT(true);
        
    }catch(std::logic_error){
        CPPUNIT_ASSERT(false);
        
    }
    
    try{
        output1->RemoveAllTracks();
        CPPUNIT_ASSERT(true);
        
    }catch(std::logic_error){
        CPPUNIT_ASSERT(false);
        
    }
    
    
    
}

void AddingTracksToOutputsTests::setUp() {
    UMC_Initialize();
}

void AddingTracksToOutputsTests::tearDown() {
    UMC_Terminate();
}


