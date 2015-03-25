#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"

class AddingOutputsToUMCTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( AddingOutputsToUMCTests );
	CPPUNIT_TEST( CountOfOutputs );
	CPPUNIT_TEST( SerializeOutputs );
	CPPUNIT_TEST_SUITE_END();


protected:
	void CountOfOutputs();
	void SerializeOutputs();

public:
	virtual void setUp();
	virtual void tearDown();

	};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingOutputsToUMCTests );

#include "interfaces/IUMC.h"
#include "interfaces/IOutput.h"
#include "interfaces/ISource.h"
#include "interfaces/ITrack.h"
#include "interfaces/IShot.h"
#include "interfaces/IShotSource.h"

static UMC::spIUMC CreateDefaultUMC() {
	using namespace UMC;
	spIUMC sp = IUMC::CreateEmptyUMC();

	// add 2 video source ( 1 filled, 1 empty )
	auto sourcev1 = sp->AddVideoSource( "video1" );
	sourcev1->SetClipName( "clipNamev1" );
	sourcev1->SetInCount( 5 );
	sourcev1->SetDuration( 50 );
	sourcev1->SetEditRate( EditRate( 24000, 1001 ) );
	sourcev1->SetTimeCode( TimeCode( TimeCode::k23_976Fps, "02:04:12:21" ) );

	auto sourcea1 = sp->AddVideoSource( "video2" );

	// add 3 audio source( 2 filled, 1 blank )
	sourcea1 = sp->AddAudioSource( "audio1" );
	sourcea1->SetClipName( "clipNamea1" );
	sourcea1->SetInCount( 10 );
	sourcea1->SetEditRate( EditRate( 48000 ) );
	sourcea1->SetTimeCode( TimeCode( TimeCode::k25Fps, 1, 2, 3, 4 ) );

	auto sourcea2 = sp->AddAudioSource( "audio2" );
	sourcea2->SetClipName( "clipNamea2" );
	sourcea2->SetDuration( 200 );
	sourcea2->SetEditRate( EditRate( 44100 ) );
	sourcea2->SetTimeCode( TimeCode( TimeCode::k29_97Fps, 1, 2, 3, 4, true ) );

	auto sourcea3 = sp->AddAudioSource( "audio3" );

	// add 3 images ( 1 filled, 2 blank )
	sourcea3 = sp->AddFrameSource( "image1" );
	sourcea3->SetClipName( "clipNamei1" );

	sp->AddFrameSource( "image2" );
	sp->AddFrameSource( "image3" );

	// add 2 outputs
	auto output1 = sp->AddOutput( "output1" );
	output1->SetAudioEditRate( EditRate( 48000 ) );
	output1->SetVideoEditRate( EditRate( 24 ) );
	output1->SetName( "Output One" );
	output1->SetTitle( "Video for Output One" );
	output1->SetImageAspectRatio( AspectRatio( 1080, 720 ) );
	output1->SetCanvasAspectRatio( AspectRatio( 640, 480 ) );

	auto videoTrack = output1->AddVideoTrack( "videoTrack1" );
	auto shot1 = videoTrack->AddClipShot( "clipShot" );
	auto shotSource1 = shot1->AddShotSource( sourcev1, -5, 200, 10 );

	return sp;
}

void AddingOutputsToUMCTests::CountOfOutputs() {
	auto sp = CreateDefaultUMC();

	CPPUNIT_ASSERT_EQUAL( sp ? true : false, true );
	CPPUNIT_ASSERT_EQUAL( sp->OutputCount(), ( size_t ) 1 );

	// remove non existent output
	sp->RemoveOutput( "notAvailable" );
	CPPUNIT_ASSERT_EQUAL( sp->OutputCount(), ( size_t ) 1 );

	// remove existing output
	sp->RemoveOutput( "output1" );
	CPPUNIT_ASSERT_EQUAL( sp->OutputCount(), ( size_t ) 0 );

	// remove all outputs
	sp->RemoveAllOutputs();
	CPPUNIT_ASSERT_EQUAL( sp->OutputCount(), ( size_t ) 0 );
}

void AddingOutputsToUMCTests::SerializeOutputs() {
	std::cout<< "********** AddingOutputsToUMCTests::SerializeOutputs **********"<<"\n";
	auto sp = CreateDefaultUMC();
	std::string rdf = sp->SerializeToBuffer();
	std::cout << rdf << "\n";
}

void AddingOutputsToUMCTests::setUp() {
	UMC_Initialize();
}

void AddingOutputsToUMCTests::tearDown() {
	UMC_Terminate();
}


