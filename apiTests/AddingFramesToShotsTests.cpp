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
    CPPUNIT_TEST( CheckNodeHierarchy );
    CPPUNIT_TEST_SUITE_END();
    
    
protected:
    void CountOfFrames();
    void FramesContent();
    void SerializeFrames();
    void ParseFrames();
    void RemoveFrames();
    void CheckNodeHierarchy();
    
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

using namespace UMC;

static UMC::spIUMC CreateDefaultUMC() {
    
    
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
    
    //std::cout<<frame1->Serialize();
    
    return sp;
}

void AddingFramesToShotsTests::CountOfFrames() {
    std::cout<< "********** AddingFramesToShotsTests::CountOfFrames **********"<<"\n";
    
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
        CPPUNIT_ASSERT(false);
    } catch (std::logic_error) {
        CPPUNIT_ASSERT(true);
    }
    
    spIUMC sp2 = IUMC::CreateEmptyUMC();
    auto output1 = sp2->AddOutput();
    auto videoTrack1 = output1->AddVideoTrack();
    
    auto clipShot1 = videoTrack1->AddClipShot();
    
    
    auto frame1 = clipShot1->AddFrame( ReadTextFileIntoString( Join( GetMaterialDir(), "FrameBuffer.xml" ) ) );
    auto frames1=clipShot1->GetAllFrames();
    CPPUNIT_ASSERT_EQUAL( frames1[0]->GetShotInCount(), ( EditUnitInCount ) 12 );
    
    //auto fsource1=frames1[0]->GetSource();
    //CPPUNIT_ASSERT_EQUAL( fsource1->GetClipName(), std::string( "source 1" ) );
    //CPPUNIT_ASSERT_EQUAL( fsource1->GetType(), ISource::kSourceTypeVideo );
    
    
    
}

void AddingFramesToShotsTests::RemoveFrames() {
    std::cout<< "********** AddingFramesToShotsTests::RemoveFrames **********"<<"\n";
    
    auto sp = CreateDefaultUMC();
    auto sources = sp->GetAllSources();
    auto outputs = sp->GetAllOutputs();
    auto tracks = outputs[0]->GetAllTracks();
    auto shots = tracks[0]->GetAllShots();
    auto frames = shots[0]->GetAllFrames();
    
    shots[0]->RemoveFrame( "notAvailable" );
    
    CPPUNIT_ASSERT_EQUAL( shots[0]->FrameCount(), ( size_t ) 3 );
    
    
    
}

void AddingFramesToShotsTests::CheckNodeHierarchy() {
    
    spIUMC sp = IUMC::CreateEmptyUMC();
    auto output1 = sp->AddOutput();
    output1->SetName("output 1");
    
    auto source1 = sp->AddVideoSource();
    source1->SetClipName( "source 1" );
    
    auto source2 = sp->AddAudioSource();
    source2->SetClipName( "source 2" );
    
    auto videoTrack1 = output1->AddVideoTrack();
    videoTrack1->SetName("vtrack 1");
    auto audioTrack1 = output1->AddAudioTrack();
    audioTrack1->SetName("atrack 1");
    
    auto clipShot1 = videoTrack1->AddClipShot();
    clipShot1->SetInCount( 10 );
    clipShot1->SetDuration( 15 );
    
    auto transitionShot1 = audioTrack1->AddTransitionShot();
    transitionShot1->SetInCount( 20 );
    transitionShot1->SetDuration( 25 );
    
    auto cframe1 = clipShot1->AddFrame( source1 );
    cframe1->SetShotInCount( 12 );
    
    auto shotSource1 = clipShot1->AddShotSource( source2 );
    shotSource1->SetShotInCount(10);
    shotSource1->SetSourceInCount(2);
    shotSource1->SetSourceDuration(4);
    
    auto tframe1 = transitionShot1->AddFrame( source2 );
    tframe1->SetShotInCount( 12 );
    
    auto tframe2 = transitionShot1->AddFrame( source2 );
    tframe2->SetShotInCount( 13 );
    
    auto uAllChildren=sp->GetAllChildren();
    CPPUNIT_ASSERT_EQUAL(uAllChildren.size(), (size_t)3 );
    
    spIOutput uoutput=dynamic_pointer_cast<IOutput>(uAllChildren[2]);
    CPPUNIT_ASSERT_EQUAL(uoutput->GetName(),std::string("output 1"));
    
    auto uAllDecendants=sp->GetAllDecendants();
    CPPUNIT_ASSERT_EQUAL(uAllDecendants.size(), (size_t) 11 );
    
    auto oAllChildren=uoutput->GetAllChildren();
    CPPUNIT_ASSERT_EQUAL(oAllChildren.size(), (size_t)2 );
    
    auto oAllDecendants=uoutput->GetAllDecendants();
    CPPUNIT_ASSERT_EQUAL(oAllDecendants.size(), (size_t) 8 );
    
    auto oChild1=uoutput->GetChildNode(videoTrack1->GetUniqueID());
    CPPUNIT_ASSERT_EQUAL(oChild1->GetNodeType(), IUMCNode::kNodeTypeTrack );
    auto oVideoTrack1=dynamic_pointer_cast<IVideoTrack>(oChild1);
    CPPUNIT_ASSERT_EQUAL(oVideoTrack1->GetName(), std::string("vtrack 1") );
    
    auto oAudioTrack1=output1->GetChild<IAudioTrack>(audioTrack1->GetUniqueID());
    CPPUNIT_ASSERT_EQUAL(oAudioTrack1->GetName(), std::string("atrack 1") );
    
    auto vtAllChildren=oVideoTrack1->GetAllChildren();
    CPPUNIT_ASSERT_EQUAL(vtAllChildren.size(), (size_t) 1);
    CPPUNIT_ASSERT_EQUAL(vtAllChildren[0]->GetNodeType(), IUMCNode::kNodeTypeShot );
    
    auto cShot1=oVideoTrack1->GetChild<IClipShot>(clipShot1->GetUniqueID());
    CPPUNIT_ASSERT_EQUAL(cShot1->GetInCount(), (EditUnitInCount) 10 );
    CPPUNIT_ASSERT_EQUAL(cShot1->GetDuration(), (EditUnitDuration) 15 );
    
    auto atAllChildren=oAudioTrack1->GetAllChildren();
    CPPUNIT_ASSERT_EQUAL(atAllChildren.size(), (size_t) 1);
    CPPUNIT_ASSERT_EQUAL(atAllChildren[0]->GetNodeType(), IUMCNode::kNodeTypeShot );
    
    auto tShot1=oAudioTrack1->GetChild<ITransitionShot>(transitionShot1->GetUniqueID());
    CPPUNIT_ASSERT_EQUAL(tShot1->GetInCount(), (EditUnitInCount) 20 );
    CPPUNIT_ASSERT_EQUAL(tShot1->GetDuration(), (EditUnitDuration) 25 );
    CPPUNIT_ASSERT_EQUAL((tShot1->GetAllChildren()).size(), (size_t) 2 );
    
    auto scFrame1=cShot1->GetChild<IFrame>(cframe1->GetUniqueID());
    CPPUNIT_ASSERT_EQUAL(scFrame1->GetShotInCount(), (EditUnitInCount) 12 );
    
    auto vSource=dynamic_pointer_cast< const IVideoSource >(scFrame1->GetSource());
    CPPUNIT_ASSERT_EQUAL(vSource->GetClipName(), std::string("source 1"));
    
    auto stFrame1=tShot1->GetChild<IFrame>(tframe1->GetUniqueID());
    CPPUNIT_ASSERT_EQUAL(stFrame1->GetShotInCount(), (EditUnitInCount) 12 );
    CPPUNIT_ASSERT_EQUAL(stFrame1->GetAllChildren().size(), (size_t) 0 );
    
    auto aSource=dynamic_pointer_cast< const IAudioSource >(stFrame1->GetSource());
    CPPUNIT_ASSERT_EQUAL(aSource->GetClipName(), std::string("source 2"));
    
    
    shotSource1=output1->GetDecendant<IShotSource>(shotSource1->GetUniqueID());
    CPPUNIT_ASSERT_EQUAL(shotSource1->GetSourceInCount(), (EditUnitInCount) 2 );
    aSource=dynamic_pointer_cast<const IAudioSource >(shotSource1->GetSource());
    CPPUNIT_ASSERT_EQUAL(aSource->GetClipName(), std::string("source 2"));
    
    auto decendant1=videoTrack1->GetDecendantNode(cframe1->GetUniqueID());
    scFrame1=dynamic_pointer_cast<IFrame>(decendant1);
    CPPUNIT_ASSERT_EQUAL(scFrame1->GetShotInCount(), (EditUnitInCount) 12 );
    
    auto framesParent=(decendant1->GetParent<IClipShot>()).lock();
    CPPUNIT_ASSERT_EQUAL(framesParent->GetNodeType(), IUMC::kNodeTypeShot);
    CPPUNIT_ASSERT_EQUAL(framesParent->GetInCount(), (EditUnitInCount) 10 );
    
    auto shotsParent=dynamic_pointer_cast<IVideoTrack>((framesParent->GetParentNode()).lock());
    CPPUNIT_ASSERT_EQUAL(shotsParent->GetName(), std::string("vtrack 1"));
    
    auto tracksParent=(shotsParent->GetParent<IOutput>()).lock();
    CPPUNIT_ASSERT_EQUAL(tracksParent->GetName(), std::string("output 1"));
    
    auto outputsParent= (tracksParent->GetParent<IUMC>()).lock();
    CPPUNIT_ASSERT_EQUAL(outputsParent->GetNodeType(), IUMC::kNodeTypeUMC);
   
    
    
}

void AddingFramesToShotsTests::setUp() {
    UMC_Initialize();
}

void AddingFramesToShotsTests::tearDown() {
    UMC_Terminate();
}


