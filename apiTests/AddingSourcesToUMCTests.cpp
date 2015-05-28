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
#include <stdexcept>

class AddingSourcesToUMCTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( AddingSourcesToUMCTests );
		CPPUNIT_TEST( CountOfSources );
		CPPUNIT_TEST( SourcesContent );
		CPPUNIT_TEST( SerializeSources );
	CPPUNIT_TEST_SUITE_END();


protected:
	void CountOfSources();
	void SourcesContent();
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

void AddingSourcesToUMCTests::SourcesContent() {
	std::cout<< "********** AddingSourcesToUMCTests::SourcesContent 1 **********"<<"\n";
	using namespace UMC;

	auto sp = CreateDefaultUMC();
	auto videoSources = sp->GetAllVideoSources();
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetClipName(), std::string( "clipNamev1" ) );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetType(), ISource::kSourceTypeVideo );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetVideoEditRate(), EditRate( 24000, 1001 ) );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetInCount(), ( EditUnitInCount ) 5 );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetDuration(), ( EditUnitDuration ) 50 );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetTimeCode(), TimeCode( TimeCode::k23_976Fps, "02:04:12:21" ) );

	for( int i= 1; i<sp->VideoSourceCount(); i++)
	{
		CPPUNIT_ASSERT_EQUAL( videoSources[i]->GetClipName(), std::string( "" ) );
		CPPUNIT_ASSERT_EQUAL( videoSources[i]->GetType(), ISource::kSourceTypeVideo );
		CPPUNIT_ASSERT_EQUAL( videoSources[i]->GetVideoEditRate(), EditRate( 1 ) );
		CPPUNIT_ASSERT_EQUAL( videoSources[i]->GetAudioEditRate(), EditRate( 48000 ) );
		CPPUNIT_ASSERT_EQUAL( videoSources[i]->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
		CPPUNIT_ASSERT_EQUAL( videoSources[i]->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
		CPPUNIT_ASSERT_EQUAL( videoSources[i]->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
	}

	auto audioSources = sp->GetAllAudioSources();
	CPPUNIT_ASSERT_EQUAL( audioSources[1]->GetClipName(), std::string( "clipNamea1" ) );
	CPPUNIT_ASSERT_EQUAL( audioSources[1]->GetType(), ISource::kSourceTypeAudio );
	CPPUNIT_ASSERT_EQUAL( audioSources[1]->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( audioSources[1]->GetInCount(), ( EditUnitInCount ) 10 );
	CPPUNIT_ASSERT_EQUAL( audioSources[1]->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
	CPPUNIT_ASSERT_EQUAL( audioSources[1]->GetTimeCode(), TimeCode( TimeCode::k25Fps, 1, 2, 3, 4 ) );

	CPPUNIT_ASSERT_EQUAL( audioSources[2]->GetClipName(), std::string( "clipNamea2" ) );
	CPPUNIT_ASSERT_EQUAL( audioSources[2]->GetType(), ISource::kSourceTypeAudio );
	CPPUNIT_ASSERT_EQUAL( audioSources[2]->GetAudioEditRate(), EditRate( 44100 ) );
	CPPUNIT_ASSERT_EQUAL( audioSources[2]->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( audioSources[2]->GetDuration(), ( EditUnitDuration ) 200 );
	CPPUNIT_ASSERT_EQUAL( audioSources[2]->GetTimeCode(), TimeCode( TimeCode::k29_97Fps, 1, 2, 3, 4, true ) );

	for( int i= 0; i<sp->VideoSourceCount(); i++)
	{
		if( i == 1 || i == 2 )
			continue;
		CPPUNIT_ASSERT_EQUAL( audioSources[i]->GetClipName(), std::string( "" ) );
		CPPUNIT_ASSERT_EQUAL( audioSources[i]->GetType(), ISource::kSourceTypeAudio );
		CPPUNIT_ASSERT_EQUAL( audioSources[i]->GetAudioEditRate(), EditRate( 48000 ) );
		CPPUNIT_ASSERT_EQUAL( audioSources[i]->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
		CPPUNIT_ASSERT_EQUAL( audioSources[i]->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
		CPPUNIT_ASSERT_EQUAL( audioSources[i]->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );
	}

	auto videoFrameSources = sp->GetAllVideoFrameSources();
	CPPUNIT_ASSERT_EQUAL( videoFrameSources[0]->GetClipName(), std::string( "clipNamevf1" ) );
	CPPUNIT_ASSERT_EQUAL( videoFrameSources[0]->GetType(), ISource::kSourceTypeVideoFrame );
	CPPUNIT_ASSERT_EQUAL( videoFrameSources[0]->GetInCount(), ( EditUnitInCount ) 5 );
	CPPUNIT_ASSERT_EQUAL( videoFrameSources[0]->GetTimeCode(), TimeCode( TimeCode::k23_976Fps, "02:04:12:21" ) );

	for( int i= 1; i<sp->VideoFrameSourceCount(); i++)
	{
		CPPUNIT_ASSERT_EQUAL( videoFrameSources[i]->GetClipName(), std::string( "" ) );
		CPPUNIT_ASSERT_EQUAL( videoFrameSources[i]->GetType(), ISource::kSourceTypeVideoFrame );
		CPPUNIT_ASSERT_EQUAL( videoFrameSources[i]->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
		CPPUNIT_ASSERT_EQUAL( videoFrameSources[i]->GetTimeCode(), TimeCode( TimeCode::k23_976Fps, "02:04:12:21" ) );
	}

	auto imageSources = sp->GetAllImageSources();
	CPPUNIT_ASSERT_EQUAL( imageSources[0]->GetClipName(), std::string( "clipNamei1" ) );
	CPPUNIT_ASSERT_EQUAL( imageSources[0]->GetType(), ISource::kSourceTypeImage );

	for( int i= 1; i<sp->ImageSourceCount(); i++)
	{
		CPPUNIT_ASSERT_EQUAL( imageSources[i]->GetClipName(), std::string( "" ) );
		CPPUNIT_ASSERT_EQUAL( imageSources[i]->GetType(), ISource::kSourceTypeImage );
	}

	std::cout<< "********** AddingSourcesToUMCTests::SourcesContent 2 **********"<<"\n";

	sp = IUMC::CreateEmptyUMC();

	auto videoSource = sp->AddVideoSource();
	videoSource->SetClipName( "videoClip" );
	videoSource->SetVideoEditRate( EditRate( 24, 1001 ) );
	videoSource->SetAudioEditRate( EditRate( 48000 ) );
	videoSource->SetInCount( 3 );
	videoSource->SetDuration( 11 );
	videoSource->SetTimeCode( TimeCode( TimeCode::k23_976Fps, "03:02:10:00" ) );

	auto audioSource = sp->AddAudioSource();
	audioSource->SetClipName( "audioClip" );
	audioSource->SetAudioEditRate( EditRate( 44000 ) );
	audioSource->SetInCount( 5 );
	audioSource->SetDuration( 9 );
	audioSource->SetTimeCode( TimeCode( TimeCode::k25Fps, "04:03:13:20" ) );

	auto videoFrameSource = sp->AddVideoFrameSource( videoSource );
	videoFrameSource->SetClipName( "videoFrameClip" );
	videoFrameSource->SetInCount( 8 );

	auto imageSource = sp->AddImageSource();
	imageSource->SetClipName( "imageClip" );

	videoSources = sp->GetAllVideoSources();
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetClipName(), std::string( "videoClip" ) );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetType(), ISource::kSourceTypeVideo );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetVideoEditRate(), EditRate( 24, 1001 ) );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetInCount(), ( EditUnitInCount ) 3 );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetDuration(), ( EditUnitDuration ) 11 );
	CPPUNIT_ASSERT_EQUAL( videoSources[0]->GetTimeCode(), TimeCode( TimeCode::k23_976Fps, "03:02:10:00" ) );

	audioSources = sp->GetAllAudioSources();
	CPPUNIT_ASSERT_EQUAL( audioSources[0]->GetClipName(), std::string( "audioClip" ) );
	CPPUNIT_ASSERT_EQUAL( audioSources[0]->GetType(), ISource::kSourceTypeAudio );
	CPPUNIT_ASSERT_EQUAL( audioSources[0]->GetAudioEditRate(), EditRate( 44000 ) );
	CPPUNIT_ASSERT_EQUAL( audioSources[0]->GetInCount(), ( EditUnitInCount ) 5 );
	CPPUNIT_ASSERT_EQUAL( audioSources[0]->GetDuration(), ( EditUnitDuration ) 9 );
	CPPUNIT_ASSERT_EQUAL( audioSources[0]->GetTimeCode(), TimeCode( TimeCode::k25Fps, "04:03:13:20" ) );

	videoFrameSources = sp->GetAllVideoFrameSources();
	CPPUNIT_ASSERT_EQUAL( videoFrameSources[0]->GetClipName(), std::string( "videoFrameClip" ) );
	CPPUNIT_ASSERT_EQUAL( videoFrameSources[0]->GetType(), ISource::kSourceTypeVideoFrame );
	CPPUNIT_ASSERT_EQUAL( videoFrameSources[0]->GetInCount(), ( EditUnitInCount ) 8 );
	CPPUNIT_ASSERT_EQUAL( videoFrameSources[0]->GetTimeCode(), TimeCode( TimeCode::k23_976Fps, "03:02:10:00" ) );

	imageSources = sp->GetAllImageSources();
	CPPUNIT_ASSERT_EQUAL( imageSources[0]->GetClipName(), std::string( "imageClip" ) );
	CPPUNIT_ASSERT_EQUAL( imageSources[0]->GetType(), ISource::kSourceTypeImage );
}

void AddingSourcesToUMCTests::SerializeSources() {
	auto sp = CreateDefaultUMC();
	std::string rdf = sp->SerializeToBuffer();
	//std::cout<<rdf<<"\n";
	
}

void AddingSourcesToUMCTests::setUp() {
	UMC_Initialize();
}

void AddingSourcesToUMCTests::tearDown() {
	UMC_Terminate();
}


