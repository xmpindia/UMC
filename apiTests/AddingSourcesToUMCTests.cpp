#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"

class AddingSourcesToUMCTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( AddingSourcesToUMCTests );
		CPPUNIT_TEST( CountOfSources );
		CPPUNIT_TEST( SerializeSources );
	CPPUNIT_TEST_SUITE_END();


protected:
	void CountOfSources();
	void SerializeSources();

public:
	virtual void setUp();
	virtual void tearDown();

};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingSourcesToUMCTests );

#include "interfaces/IUMC.h"
#include "interfaces/ISource.h"

static UMC::spIUMC CreateDefaultUMC() {
	using namespace UMC;
	spIUMC sp = IUMC::CreateEmptyUMC();

	// add 2 video source ( 1 filled, 1 empty )
	auto source = sp->AddVideoSource( "video1" );
	source->SetClipName( "clipNamev1" );
	source->SetInCount( 5 );
	source->SetDuration( 50 );
	source->SetEditRate( EditRate( 24000, 1001 ) );
	source->SetTimeCode( TimeCode( TimeCode::k23_976Fps, "02:04:12:21" ) );

	source = sp->AddVideoSource( "video2" );

	// add 3 audio source( 2 filled, 1 blank )
	source = sp->AddAudioSource( "audio1" );
	source->SetClipName( "clipNamea1" );
	source->SetInCount( 10 );
	source->SetEditRate( EditRate( 48000 ) );
	source->SetTimeCode( TimeCode( TimeCode::k25Fps, 1, 2, 3, 4 ) );

	source = sp->AddAudioSource( "audio2" );
	source->SetClipName( "clipNamea2" );
	source->SetDuration( 200 );
	source->SetEditRate( EditRate( 44100 ) );
	source->SetTimeCode( TimeCode( TimeCode::k29_97Fps, 1, 2, 3, 4, true ) );

	source = sp->AddAudioSource( "audio3" );

	// add 3 images ( 1 filled, 2 blank )
	source = sp->AddFrameSource( "image1" );
	source->SetClipName( "clipNamei1" );

	sp->AddFrameSource( "image2" );
	sp->AddFrameSource( "image3" );

	return sp;
}

void AddingSourcesToUMCTests::CountOfSources() {
	auto sp = CreateDefaultUMC();

	CPPUNIT_ASSERT_EQUAL( sp ? true : false, true );
	CPPUNIT_ASSERT_EQUAL( sp->SourceCount(),( size_t ) 8 );
	CPPUNIT_ASSERT_EQUAL( sp->VideoSourceCount(), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( sp->AudioSourceCount(), ( size_t ) 3 );
	CPPUNIT_ASSERT_EQUAL( sp->FrameSourceCount(), ( size_t ) 3 );

	// remove image source
	sp->RemoveSource( "image2" );
	CPPUNIT_ASSERT_EQUAL( sp->SourceCount(), ( size_t ) 7 );
	CPPUNIT_ASSERT_EQUAL( sp->VideoSourceCount(), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( sp->AudioSourceCount(), ( size_t ) 3 );
	CPPUNIT_ASSERT_EQUAL( sp->FrameSourceCount(), ( size_t ) 2 );

	// remove Audio source
	sp->RemoveSource( "audio1" );
	CPPUNIT_ASSERT_EQUAL( sp->SourceCount(), ( size_t ) 6 );
	CPPUNIT_ASSERT_EQUAL( sp->VideoSourceCount(), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( sp->AudioSourceCount(), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( sp->FrameSourceCount(), ( size_t ) 2 );

	// remove Video source
	sp->RemoveSource( "video1" );
	CPPUNIT_ASSERT_EQUAL( sp->SourceCount(), ( size_t ) 5 );
	CPPUNIT_ASSERT_EQUAL( sp->VideoSourceCount(), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( sp->AudioSourceCount(), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( sp->FrameSourceCount(), ( size_t ) 2 );

	// remove non existent source
	sp->RemoveSource( "notAvailable" );
	CPPUNIT_ASSERT_EQUAL( sp->SourceCount(), ( size_t ) 5 );
	CPPUNIT_ASSERT_EQUAL( sp->VideoSourceCount(), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( sp->AudioSourceCount(), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( sp->FrameSourceCount(), ( size_t ) 2 );

	// remove all sources
	sp->RemoveAllSources();
	CPPUNIT_ASSERT_EQUAL( sp->SourceCount(), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->VideoSourceCount(), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->AudioSourceCount(), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->FrameSourceCount(), ( size_t ) 0 );
}

void AddingSourcesToUMCTests::SerializeSources() {
	auto sp = CreateDefaultUMC();
	std::string rdf = sp->SerializeToBuffer();
	std::cout<<rdf<<"\n";
	
}

void AddingSourcesToUMCTests::setUp() {
	UMC_Initialize();
}

void AddingSourcesToUMCTests::tearDown() {
	UMC_Terminate();
}


