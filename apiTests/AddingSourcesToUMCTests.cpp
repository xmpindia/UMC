#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"
#include <stdexcept>

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
#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/IVideoFrameSource.h"

static UMC::spIUMC CreateDefaultUMC() {
	using namespace UMC;
	spIUMC sp = IUMC::CreateEmptyUMC();

	// add 5 video source ( 1 filled, 1 empty )
	auto videoSource = sp->AddVideoSource();
	videoSource->SetClipName( "clipNamev1" );
	videoSource->SetInCount( 5 );
	videoSource->SetDuration( 50 );
	videoSource->SetVideoEditRate( EditRate( 24000, 1001 ) );
	videoSource->SetAudioEditRate( 48000 );
	videoSource->SetTimeCode( TimeCode( TimeCode::k23_976Fps, "02:04:12:21" ) );

	sp->AddVideoSource();
	sp->AddVideoSource();
	sp->AddVideoSource();
	sp->AddVideoSource();

	// add 5 audio source( 2 filled, 1 blank )
	auto audioSource = sp->AddAudioSource();
	audioSource->SetClipName( "clipNamea1" );
	audioSource->SetInCount( 10 );
	audioSource->SetAudioEditRate( EditRate( 48000 ) );
	audioSource->SetTimeCode( TimeCode( TimeCode::k25Fps, 1, 2, 3, 4 ) );

	audioSource = sp->AddAudioSource();
	audioSource->SetClipName( "clipNamea2" );
	audioSource->SetDuration( 200 );
	audioSource->SetAudioEditRate( EditRate( 44100 ) );
	audioSource->SetTimeCode( TimeCode( TimeCode::k29_97Fps, 1, 2, 3, 4, true ) );

	sp->AddAudioSource();
	sp->AddAudioSource();
	sp->AddAudioSource();

	// add 5 images ( 1 filled, 2 blank )
	auto imageSource = sp->AddImageSource();
	imageSource->SetClipName( "clipNamei1" );

	sp->AddImageSource();
	sp->AddImageSource();
	sp->AddImageSource();
	sp->AddImageSource();

	// add 5 video frame sources
	auto videoFrameSource = sp->AddVideoFrameSource( videoSource );
	videoFrameSource->SetClipName( "clipNamevf1" );
	videoFrameSource->SetInCount( 5 );
	sp->AddVideoFrameSource( videoSource );
	sp->AddVideoFrameSource( videoSource );
	sp->AddVideoFrameSource( videoSource );
	sp->AddVideoFrameSource( videoSource );

	return sp;
}

bool CheckCount( const UMC::spcIUMC & umc, size_t videoSources, size_t audioSources, size_t imageSources, size_t videoFrameSources ) {
	bool everythingOk = false;
	if ( umc->SourceCount() == videoSources + audioSources + videoFrameSources + imageSources ) {
		if ( umc->VideoFrameSourceCount() == videoFrameSources &&
			umc->AudioSourceCount() == audioSources &&
			umc->VideoSourceCount() == videoSources &&
			umc->ImageSourceCount() == imageSources )
		{
			everythingOk = true;
		}
	}
	return everythingOk;
}

void AddingSourcesToUMCTests::CountOfSources() {
	auto sp = CreateDefaultUMC();
	size_t videoSourceCount( 5 ), audioSourceCount( 5 ), imageSourceCount( 5 ), videoFrameSourceCount( 5 );

	CPPUNIT_ASSERT_EQUAL( sp ? true : false, true );
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	// remove image source
	CPPUNIT_ASSERT_EQUAL( sp->RemoveSource( "11" ), ( size_t ) 1 );
	imageSourceCount--;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );


	CPPUNIT_ASSERT_EQUAL( sp->RemoveImageSource( "12" ), ( size_t ) 1 );
	imageSourceCount--;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	CPPUNIT_ASSERT_EQUAL( sp->RemoveImageSource( "5" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveImageSource( "10" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveImageSource( "20" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveImageSource( "0" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	// remove Audio source
	CPPUNIT_ASSERT_EQUAL( sp->RemoveSource( "6" ), ( size_t ) 1 );
	audioSourceCount--;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	CPPUNIT_ASSERT_EQUAL( sp->RemoveAudioSource( "7" ), ( size_t ) 1 );
	audioSourceCount--;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	CPPUNIT_ASSERT_EQUAL( sp->RemoveAudioSource( "5" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveAudioSource( "15" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveAudioSource( "20" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveAudioSource( "0" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	// remove Video source
	CPPUNIT_ASSERT_THROW_MESSAGE( "can't remove as node is referenced somewhere in the DOM", sp->RemoveSource( "1" ), std::logic_error );
	CPPUNIT_ASSERT_THROW_MESSAGE( "can't remove as node is referenced somewhere in the DOM", sp->RemoveVideoSource( "1" ), std::logic_error );

	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoSource( "3" ), ( size_t ) 1 );
	videoSourceCount--;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoSource( "2" ), ( size_t ) 1 );
	videoSourceCount--;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoSource( "10" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoSource( "15" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoSource( "20" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoSource( "0" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	// remove Video Frame Source source
	CPPUNIT_ASSERT_EQUAL( sp->RemoveSource( "16" ), ( size_t ) 1 );
	videoFrameSourceCount--;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoFrameSource( "17" ), ( size_t ) 1 );
	videoFrameSourceCount--;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoFrameSource( "5" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoFrameSource( "10" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoFrameSource( "15" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveVideoFrameSource( "0" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	// remove non existent source
	CPPUNIT_ASSERT_EQUAL( sp->RemoveSource( "0" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	// remove all sources
	sp->RemoveAllImageSources();
	imageSourceCount = 0;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	sp->RemoveAllAudioSources();
	audioSourceCount = 0;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	CPPUNIT_ASSERT_THROW_MESSAGE( "can't remove as node is referenced somewhere in the DOM", sp->RemoveAllVideoSources(), std::logic_error );
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	sp->RemoveAllVideoFramesSources();
	videoFrameSourceCount = 0;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	sp->RemoveAllVideoSources();
	videoSourceCount = 0;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );

	sp = CreateDefaultUMC();
	videoSourceCount = imageSourceCount = audioSourceCount = videoFrameSourceCount = 5;
	CPPUNIT_ASSERT_THROW_MESSAGE( "can't remove as node is referenced somewhere in the DOM", sp->RemoveAllVideoSources(), std::logic_error );
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );
	CPPUNIT_ASSERT_EQUAL( sp->RemoveAllSources(), videoSourceCount + imageSourceCount + audioSourceCount + videoFrameSourceCount );
	videoSourceCount = imageSourceCount = audioSourceCount = videoFrameSourceCount = 0;
	CPPUNIT_ASSERT_EQUAL( CheckCount( sp, videoSourceCount, audioSourceCount, imageSourceCount, videoFrameSourceCount ), true );
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


