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

class AddingTracksToOuputsTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( AddingTracksToOuputsTests );
	CPPUNIT_TEST( CountOfTracks );
	CPPUNIT_TEST( TracksContent );
	CPPUNIT_TEST( SerializeTracks );
	CPPUNIT_TEST( ParseTracks );
	CPPUNIT_TEST_SUITE_END();


protected:
	void CountOfTracks();
	void TracksContent();
	void SerializeTracks();
	void ParseTracks();

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

	outputs[0]->RemoveAudioTrack( videoTrack->GetUniqueID() );

	CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 8 );
	CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 4 );
	CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 4 );

	outputs[0]->RemoveVideoTrack( videoTrack->GetUniqueID() );

	CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 7 );
	CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 3 );
	CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 4 );

	outputs[0]->RemoveAllVideoTracks();

	CPPUNIT_ASSERT_EQUAL( outputs[0]->TrackCount(), (size_t) 4 );
	CPPUNIT_ASSERT_EQUAL( outputs[0]->VideoTrackCount(), (size_t) 0 );
	CPPUNIT_ASSERT_EQUAL( outputs[0]->AudioTrackCount(), (size_t) 4 );

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


void AddingTracksToOuputsTests::TracksContent() {
	std::cout<< "********** AddingTracksToOuputsTests::TracksContent **********"<<"\n";
	using namespace UMC;

	auto sp = CreateDefaultUMC();
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

	for( int i = 2; i < outputs[0]->VideoTrackCount(); i++ )
	{
		CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetType(), ITrack::kTrackTypeAudio );
		CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetName(), std::string( "" ) );
		CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetAudioEditRate(), EditRate( 1 ) );
	}
}

void AddingTracksToOuputsTests::SerializeTracks() {
	std::cout<< "********** AddingTracksToOuputsTests::SerializeTracks **********"<<"\n";
	auto sp = CreateDefaultUMC();

	using namespace TestUtils;
	std::string result = ReadTextFileIntoString( Join( GetMaterialDir(), "AddingTracks.xml" ) );
	CPPUNIT_ASSERT_EQUAL( sp->SerializeToBuffer(), result );
}

void AddingTracksToOuputsTests::ParseTracks() {
	std::cout<< "********** AddingTracksToOuputsTests::ParseTracks **********"<<"\n";
	using namespace TestUtils;
	using namespace UMC;
	auto sp = IUMC::CreateUMCFromBuffer( ReadTextFileIntoString( Join( GetMaterialDir(), "AddingTracks.xml" ) ) );

	auto outputs = sp->GetAllOutputs();
	/*auto videoTracks = outputs[0]->GetAllVideoTracks();

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

	for( int i = 2; i < outputs[0]->VideoTrackCount(); i++ )
	{
		CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetType(), ITrack::kTrackTypeAudio );
		CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetName(), std::string( "" ) );
		CPPUNIT_ASSERT_EQUAL( audioTracks[i]->GetAudioEditRate(), EditRate( 1 ) );
	}*/
}


void AddingTracksToOuputsTests::setUp() {
	UMC_Initialize();
}

void AddingTracksToOuputsTests::tearDown() {
	UMC_Terminate();
}


