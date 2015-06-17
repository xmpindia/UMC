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

class AddingOutputsToUMCTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( AddingOutputsToUMCTests );
	CPPUNIT_TEST( CountOfOutputs );
	CPPUNIT_TEST( OutputsContent );
	CPPUNIT_TEST( SerializeOutputs );
	CPPUNIT_TEST( ParseOutputs );
	CPPUNIT_TEST_SUITE_END();


protected:
	void CountOfOutputs();
	void OutputsContent();
	void SerializeOutputs();
	void ParseOutputs();

public:
	virtual void setUp();
	virtual void tearDown();

	};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingOutputsToUMCTests );

#include "interfaces/IUMC.h"
#include "interfaces/IOutput.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/ITrack.h"
#include "interfaces/IShot.h"
#include "interfaces/IShotSource.h"

static UMC::spIUMC CreateDefaultUMC() {
	using namespace UMC;
	spIUMC sp = IUMC::CreateEmptyUMC();

	// add 2 video source ( 1 filled, 1 empty )
	auto sourcev1 = sp->AddVideoSource();
	sourcev1->SetClipName( "clipNamev1" );
	sourcev1->SetInCount( 5 );
	sourcev1->SetDuration( 50 );
	sourcev1->SetVideoEditRate( EditRate( 24000, 1001 ) );
	sourcev1->SetAudioEditRate( 48000 );
	sourcev1->SetTimeCode( TimeCode( TimeCode::k23_976Fps, "02:04:12:21" ) );

	sp->AddVideoSource();

	// add 3 audio source( 2 filled, 1 blank )
	auto sourcea1 = sp->AddAudioSource();
	sourcea1->SetClipName( "clipNamea1" );
	sourcea1->SetInCount( 10 );
	sourcea1->SetAudioEditRate( EditRate( 48000 ) );
	sourcea1->SetTimeCode( TimeCode( TimeCode::k25Fps, 1, 2, 3, 4 ) );

	auto sourcea2 = sp->AddAudioSource();
	sourcea2->SetClipName( "clipNamea2" );
	sourcea2->SetDuration( 200 );
	sourcea2->SetAudioEditRate( EditRate( 44100 ) );
	sourcea2->SetTimeCode( TimeCode( TimeCode::k29_97Fps, 1, 2, 3, 4, true ) );

	sp->AddAudioSource();

	// add 3 images ( 1 filled, 2 blank )
	auto sourcea3 = sp->AddImageSource();
	sourcea3->SetClipName( "clipNamei1" );

	sp->AddImageSource();
	sp->AddImageSource();

	// add 2 outputs
	auto output1 = sp->AddOutput();
	output1->SetAudioEditRate( EditRate( 48000 ) );
	output1->SetVideoEditRate( EditRate( 24 ) );
	output1->SetName( "Output One" );
	output1->SetTitle( "Video for Output One" );
	output1->SetImageAspectRatio( AspectRatio( 1080, 720 ) );
	output1->SetCanvasAspectRatio( AspectRatio( 640, 480 ) );

	sp->AddOutput();
	return sp;
}

void AddingOutputsToUMCTests::CountOfOutputs() {
	auto sp = CreateDefaultUMC();

	CPPUNIT_ASSERT_EQUAL( sp ? true : false, true );
	CPPUNIT_ASSERT_EQUAL( sp->OutputCount(), ( size_t ) 2 );

	// remove non existent output
	sp->RemoveOutput( "notAvailable" );
	CPPUNIT_ASSERT_EQUAL( sp->OutputCount(), ( size_t ) 2 );

	// remove existing output
	sp->RemoveOutput( "9" );
	CPPUNIT_ASSERT_EQUAL( sp->OutputCount(), ( size_t ) 1 );

	// remove all outputs
	sp->RemoveAllOutputs();
	CPPUNIT_ASSERT_EQUAL( sp->OutputCount(), ( size_t ) 0 );
}

void AddingOutputsToUMCTests::OutputsContent() {
	std::cout<< "********** AddingOutputsToUMCTests::OuputsContent **********"<<"\n";
	using namespace UMC;
	spIUMC sp = IUMC::CreateEmptyUMC();

	auto output1 = sp->AddOutput();
	output1->SetAudioEditRate( EditRate( 48000 ) );
	output1->SetVideoEditRate( EditRate( 24 ) );
	output1->SetName( "Output One" );
	output1->SetTitle( "Video for Output One" );
	output1->SetImageAspectRatio( AspectRatio( 1080, 720 ) );
	output1->SetCanvasAspectRatio( AspectRatio( 640, 480 ) );

	auto output2 = sp->AddOutput();
	output2->SetAudioEditRate( EditRate( 240000 ) );
	output2->SetVideoEditRate( EditRate( 50 ) );
	output2->SetName( "O Two" );
	output2->SetTitle( "Output Two Title" );
	output2->SetImageAspectRatio( AspectRatio( 1920, 1080 ) );
	output2->SetCanvasAspectRatio( AspectRatio( 1000, 500 ) );

	IUMC::OutputList outputs = sp->GetAllOutputs();
	CPPUNIT_ASSERT_EQUAL( outputs.size(), (size_t) 2 );

	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetName(), std::string( "Output One" ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetTitle(), std::string( "Video for Output One" ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetVideoEditRate(), EditRate( 24 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetImageAspectRatio(), AspectRatio( 1080, 720 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetCanvasAspectRatio(), AspectRatio( 640, 480 ) );

	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetName(), std::string( "O Two" ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetTitle(), std::string( "Output Two Title" ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetAudioEditRate(), EditRate( 240000 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetVideoEditRate(), EditRate( 50 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetImageAspectRatio(), AspectRatio( 1920, 1080 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetCanvasAspectRatio(), AspectRatio( 1000, 500 ) );
}

void AddingOutputsToUMCTests::SerializeOutputs() {
	std::cout<< "********** AddingOutputsToUMCTests::SerializeOutputs **********"<<"\n";
	auto sp = CreateDefaultUMC();

	using namespace TestUtils;
	std::string result = ReadTextFileIntoString( Join( GetMaterialDir(), "AddingOutputs.xml" ) );
	CPPUNIT_ASSERT_EQUAL( sp->SerializeToBuffer(), result );
}

void AddingOutputsToUMCTests::ParseOutputs() {
	std::cout<< "********** AddingOutputsToUMCTests::ParseOutputs **********"<<"\n";
	using namespace TestUtils;
	using namespace UMC;
	auto sp = IUMC::CreateUMCFromBuffer( ReadTextFileIntoString( Join( GetMaterialDir(), "AddingOutputs.xml" ) ) );

	IUMC::OutputList outputs = sp->GetAllOutputs();
	CPPUNIT_ASSERT_EQUAL( outputs.size(), (size_t) 2 );

	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetName(), std::string( "Output One" ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetTitle(), std::string( "Video for Output One" ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetVideoEditRate(), EditRate( 24 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetImageAspectRatio(), AspectRatio( 1080, 720 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 1 ]->GetCanvasAspectRatio(), AspectRatio( 640, 480 ) );

	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetName(), std::string( "" ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetTitle(), std::string( "" ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetAudioEditRate(), EditRate( 1 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetVideoEditRate(), EditRate( 1 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetImageAspectRatio(), AspectRatio( 1 ) );
	CPPUNIT_ASSERT_EQUAL( outputs[ 0 ]->GetCanvasAspectRatio(), AspectRatio( 1 ) );
}

void AddingOutputsToUMCTests::setUp() {
	UMC_Initialize();
}

void AddingOutputsToUMCTests::tearDown() {
	UMC_Terminate();
}


