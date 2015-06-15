#include "TestUtils.h"

#include "interfaces/IUMC.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/IVideoFrameSource.h"
#include "interfaces/IOutput.h"

namespace TestUtils {
	using namespace UMC;

	struct SourceData {
		std::string				uniqueID;
		const char *			clipName;
		EditUnitInCount			inCount;
		EditUnitDuration		duration;
		EditRate				videoEditRate;
		EditRate				audioEditRate;
		TimeCode				timeCode;
		ISource::eSourceTypes sourceType;

		SourceData( const char * clipName, EditUnitInCount inCount, EditUnitDuration duration, UMC_Uns64 videoEditRateNumerator,
			UMC_Uns64 videoEditRateDenominator, UMC_Uns64 audioEditRateNumerator, UMC_Uns64 audioEditRateDenominator );
	};



	UMC::spIUMC CreateDefaultUMC() {
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
}
