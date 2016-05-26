
#include <string>
#define ENABLE_XMP_CPP_INTERFACE 1
#include "XMPCommon/XMPCommonDefines.h"
#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"

#include "XMPCore/Interfaces/IMetadata.h"
#include "XMPCore/Interfaces/IArrayNode.h"
#include "XMPCore/Interfaces/ISimpleNode.h"

#include "XMPCore/Interfaces/IDOMImplementationRegistry.h"
#include "XMPCore/Interfaces/IDOMSerializer.h"
#include "XMPCommon/Interfaces/IUTF8String.h"
#include "XMPCore/Interfaces/ICoreObjectFactory.h"

#include <iostream>
#include <fstream>
#include "interfaces/IUMC.h"
#include "interfaces/ISource.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/IVideoFrameSource.h"

using namespace AdobeXMPCore;
using namespace AdobeXMPCommon;



void displayEditRate(UMC::EditRate  editRate) {

	std::cout << editRate;

}

void displayTimeCode(UMC::TimeCode timeCode) {

	std::cout << timeCode;
}


/*Displaying the contents of a video source in a human readable format*/

void displayVideoSource(const  UMC::spIVideoSource & videoSource, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;


	cout << beginIndent<<"Printing contents of the video source" << endl;

	cout << beginIndent<<" Video ClipName:"<<beginIndent;
	cout << videoSource->GetClipName();
	cout << endl;

	cout << beginIndent << " Video Incount:" << beginIndent;
	cout << videoSource->GetInCount();
	cout << endl;

	cout << beginIndent << " Video Duration:" << beginIndent;
	cout << videoSource->GetDuration();
	cout << endl;

	cout << beginIndent<<" Video TimeCode:"<<beginIndent;
	displayTimeCode(videoSource->GetTimeCode());
	cout << endl;

	cout << beginIndent<<" Video Edit Rate:"<<beginIndent;
	displayEditRate(videoSource->GetVideoEditRate());
	cout << endl;

	cout << beginIndent<<" Video Audio Edit Rate:"<<beginIndent;
	displayEditRate(videoSource->GetAudioEditRate());
	cout << endl;

}

void displayAudioSource(const  UMC::spIAudioSource & audioSource, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;


	cout << beginIndent << "Printing contents of the audio source" << endl;

	cout << beginIndent << " Audio ClipName:" << beginIndent;
	cout << audioSource->GetClipName();
	cout << endl;

	cout << beginIndent << " Audio Incount:" << beginIndent;
	cout << audioSource->GetInCount();
	cout << endl;

	cout << beginIndent << " Audio Duration:" << beginIndent;
	cout << audioSource->GetDuration();
	cout << endl;

	cout << beginIndent << " Audio TimeCode:" << beginIndent;
	displayTimeCode(audioSource->GetTimeCode());
	cout << endl;

	cout << beginIndent << " Audio Audio Edit Rate:" << beginIndent;
	displayEditRate(audioSource->GetAudioEditRate());
	cout << endl;

}


void displayImageSource(const  UMC::spIImageSource & imageSource, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;


	cout << beginIndent << "Printing contents of the image source" << endl;

	cout << beginIndent << " image ClipName:" << beginIndent;
	cout << imageSource->GetClipName();
	cout << endl;
}


void displayVideoFrameSources(const UMC::spIVideoFrameSource videoFrameSource, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;

	cout << beginIndent << "Printing contents of the video frame source" << endl;

	cout << beginIndent << " Video ClipName:" << beginIndent;
	cout << videoFrameSource->GetClipName();
	cout << endl;

	cout << beginIndent << " Video Incount:" << beginIndent;
	cout << videoFrameSource->GetInCount();
	cout << endl;

	cout << beginIndent << " Video TimeCode:" << beginIndent;
	displayTimeCode(videoFrameSource->GetTimeCode());
	cout << endl;
}

int main() {

	using namespace UMC;

	/*
	Initializing the UMC SDK is necessary before using any of the UMC APIs
	*/
	UMC_Initialize();

	auto umcObject = IUMC::CreateEmptyUMC();

	auto videoSource = umcObject->AddVideoSource();
	videoSource->SetClipName("clipNamev1");
	videoSource->SetInCount(5);
	videoSource->SetDuration(50);
	videoSource->SetVideoEditRate(EditRate(24000, 1001));
	videoSource->SetAudioEditRate(48000);
	videoSource->SetTimeCode(TimeCode(TimeCode::k23_976Fps, "02:04:12:21"));

	displayVideoSource(videoSource);

	auto emptyVideoSource = umcObject->AddVideoSource();

	displayVideoSource(emptyVideoSource);

	umcObject->AddVideoSource();
	umcObject->AddVideoSource();
	umcObject->AddVideoSource();

	// add 5 audio source( 2 filled, 1 blank )
	auto audioSource = umcObject->AddAudioSource();
	audioSource->SetClipName("clipNamea1");
	audioSource->SetInCount(10);
	audioSource->SetAudioEditRate(EditRate(48000));
	audioSource->SetTimeCode(TimeCode(TimeCode::k25Fps, 1, 2, 3, 4));

	audioSource = umcObject->AddAudioSource();
	audioSource->SetClipName("clipNamea2");
	audioSource->SetDuration(200);
	audioSource->SetAudioEditRate(EditRate(44100));
	audioSource->SetTimeCode(TimeCode(TimeCode::k29_97Fps, 1, 2, 3, 4, true));

	displayAudioSource(audioSource);
	umcObject->AddAudioSource();
	umcObject->AddAudioSource();
	umcObject->AddAudioSource();

	// add 5 images ( 1 filled, 2 blank )
	auto imageSource = umcObject->AddImageSource();
	imageSource->SetClipName("clipNamei1");

	umcObject->AddImageSource();
	umcObject->AddImageSource();
	umcObject->AddImageSource();
	umcObject->AddImageSource();

	// add 5 video frame sources
	auto videoFrameSource = umcObject->AddVideoFrameSource(videoSource);
	videoFrameSource->SetClipName("clipNamevf1");
	videoFrameSource->SetInCount(5);
	umcObject->AddVideoFrameSource(videoSource);
	umcObject->AddVideoFrameSource(videoSource);
	umcObject->AddVideoFrameSource(videoSource);
	umcObject->AddVideoFrameSource(videoSource);

	std::ofstream umcBuffer("umcBuffer.xmp");
	umcBuffer << umcObject->SerializeToBuffer();
	umcBuffer.close();

	/*
	There must be a matching terminate call for each UMC_Initialize() call
	*/
	UMC_Terminate();
}