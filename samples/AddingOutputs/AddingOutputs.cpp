// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2016 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include <iostream>
#include <fstream>
#include <iomanip>

#include "interfaces/IUMC.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/IOutput.h"
#include "interfaces/IAudioTrack.h"
#include "interfaces/IVideoTrack.h"
#include "interfaces/IClipShot.h"
#include "interfaces/ITransitionShot.h"
#include "interfaces/IFrame.h"
#include "interfaces/IShotSource.h"


std::string defaultIndent = "\t\t\t\t\t";
int maxFieldWidth = 30;
int maxLineFieldWidth = 100;

void displayEditRate(UMC::EditRate  editRate) {

	std::cout << editRate;

}

void displayAspectRatio(UMC::AspectRatio & aspectRatio) {

	std::cout << aspectRatio;
}

void displayTimeCode(UMC::TimeCode timeCode) {

	std::cout << timeCode;
}


/*Displaying the contents of a video source in a human readable format*/

void displayVideoSource(const  UMC::spIVideoSource & videoSource, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;


	//cout << beginIndent<<"Printing contents of the video source" << endl;
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Video ClipName:" << beginIndent;
	cout << videoSource->GetClipName();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Video Unique ID:" << beginIndent;
	cout << videoSource->GetUniqueID();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Video Incount:" << beginIndent;
	cout << videoSource->GetInCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Video Duration:" << beginIndent;
	cout << videoSource->GetDuration();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Video TimeCode:" << beginIndent;
	displayTimeCode(videoSource->GetTimeCode());
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Video Edit Rate:" << beginIndent;
	displayEditRate(videoSource->GetVideoEditRate());
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Video Audio Edit Rate:" << beginIndent;
	displayEditRate(videoSource->GetAudioEditRate());
	cout << endl;
	cout << endl;
}

/*Displaying the contents of a audio source in a human readable format*/

void displayAudioSource(const  UMC::spIAudioSource & audioSource, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;


	//cout << beginIndent << "Printing contents of the audio source" << endl;
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Audio ClipName:" << beginIndent;
	cout << audioSource->GetClipName();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Audio Unique ID:" << beginIndent;
	cout << audioSource->GetUniqueID();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Audio Incount:" << beginIndent;
	cout << audioSource->GetInCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Audio Duration:" << beginIndent;
	cout << audioSource->GetDuration();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Audio TimeCode:" << beginIndent;
	displayTimeCode(audioSource->GetTimeCode());
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Audio Audio Edit Rate:" << beginIndent;
	displayEditRate(audioSource->GetAudioEditRate());
	cout << endl;
	cout << endl;
}

/*Displaying the contents of an image source in a human readable format*/

void displayImageSource(const  UMC::spIImageSource & imageSource, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;

	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Image ClipName:" << beginIndent;
	cout << imageSource->GetClipName();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Image Unique ID:" << beginIndent;
	cout << imageSource->GetUniqueID();
	cout << endl;
	cout << endl;
}


/*Displaying the contents of a output in a human readable format*/
void displayOutput(const  UMC::spIOutput & output, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;

	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Output Name:" << beginIndent;
	cout << output->GetName();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Output Title:" << beginIndent;
	cout << output->GetTitle();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Output Canvas Aspect Ratio:" << beginIndent;
	displayAspectRatio(output->GetCanvasAspectRatio());
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Output Image Aspect Ratio:" << beginIndent;
	displayAspectRatio(output->GetImageAspectRatio());
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Number of audio tracks:" << beginIndent;
	cout << output->AudioTrackCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Number of video tracks:" << beginIndent;
	cout << output->VideoTrackCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Audio edit rate:" << beginIndent;
	displayEditRate(output->GetAudioEditRate());
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Video edit rate:" << beginIndent;
	displayEditRate(output->GetVideoEditRate());
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Unique ID:" << beginIndent;
	cout << output->GetUniqueID();
	cout << endl;
	cout << endl;
}


/*Displaying the contents of an audio track in a human readable format*/
void displayAudioTrack(const  UMC::spIAudioTrack & audioTrack, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;
	
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Output Name:" << beginIndent;
	cout << audioTrack->GetName();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Audio edit rate:" << beginIndent;
	displayEditRate(audioTrack->GetAudioEditRate());
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Number of Clip Shots:" << beginIndent;
	cout << audioTrack->ClipShotCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Number of Transition Shots:" << beginIndent;
	cout << audioTrack->TransitionShotCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Unique ID:" << beginIndent;
	cout << audioTrack->GetUniqueID();
	cout << endl;
	cout << endl;
}


/*Displaying the contents of a video track in a human readable format*/
void displayVideoTrack(const  UMC::spIVideoTrack & videoTrack, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;

	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Output Name:" << beginIndent;
	cout << videoTrack->GetName();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Audio edit rate:" << beginIndent;
	displayEditRate(videoTrack->GetVideoEditRate());
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Number of Clip Shots:" << beginIndent;
	cout << videoTrack->ClipShotCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Number of Transition Shots:" << beginIndent;
	cout << videoTrack->TransitionShotCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Unique ID:" << beginIndent;
	cout << videoTrack->GetUniqueID();
	cout << endl;
	cout << endl;
}

/*Displaying the contents of a shot in a human readable format*/
void displayShot(const  UMC::spIShot & shot, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;

	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Incount:" << beginIndent;
	cout << shot->GetInCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Shot Type:" << beginIndent;
	cout << (shot->GetType() == 0) ? "Clip Shot" : "Transition Shot";
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Duration:" << beginIndent;
	cout << shot->GetDuration();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Number of frames:" << beginIndent;
	cout << shot->FrameCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Number of shot sources:" << beginIndent;
	cout << shot->ShotSourceCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Unique ID:" << beginIndent;
	cout << shot->GetUniqueID();
	cout << endl;
	cout << endl;
}

/*Displaying the contents of a frame in a human readable format*/
void displayFrame(const  UMC::spIFrame & frame, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;

	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Source Incount:" << beginIndent;
	cout << frame->GetSourceInCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Shot Incount:" << beginIndent;
	cout << frame->GetShotInCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Source Unique Id:" << beginIndent;
	cout << frame->GetSource()->GetUniqueID();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Unique ID:" << beginIndent;
	cout << frame->GetUniqueID();
	cout << endl;
	cout << endl;
}

/*Displaying the contents of a shot source in a human readable format*/
void displayShotSource(const  UMC::spIShotSource & shotSource, std::string beginIndent = "\t\t\t\t\t") {

	using namespace std;
	using namespace UMC;

	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Source Incount:" << beginIndent;
	cout << shotSource->GetSourceInCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Shot Incount:" << beginIndent;
	cout << shotSource->GetShotInCount();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Source Duration:" << beginIndent;
	cout << shotSource->GetSourceDuration();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Source Unique Id:" << beginIndent;
	cout << shotSource->GetSource()->GetUniqueID();
	cout << endl;

	cout << beginIndent << setw(maxFieldWidth) << " Unique ID:" << beginIndent;
	cout << shotSource->GetUniqueID();
	cout << endl;
	cout << endl;
}

int main() {

	using namespace UMC;
	
	/*
	Initializing the UMC SDK is necessary before using any of the UMC APIs
	*/
	UMC_Initialize();

	
	spIUMC umcObject = IUMC::CreateEmptyUMC();

	std::cout << "Adding first video source to the UMC object" << std::endl;

	auto videoSourceOne = umcObject->AddVideoSource();
	videoSourceOne->SetClipName("VideoSourceOne");
	videoSourceOne->SetInCount(1);
	videoSourceOne->SetDuration(500);
	videoSourceOne->SetVideoEditRate(EditRate(24000, 1001));
	videoSourceOne->SetAudioEditRate(24000);
	videoSourceOne->SetTimeCode(TimeCode(TimeCode::k23_976Fps, "02:04:12:34"));

	/* Display the contents of the video source*/
	displayVideoSource(videoSourceOne);

	std::cout << "Adding second video source to the UMC object" << std::endl;

	auto videoSourceTwo = umcObject->AddVideoSource();
	videoSourceTwo->SetClipName("VideoSourceTwo");
	videoSourceTwo->SetInCount(1);
	videoSourceTwo->SetDuration(200);
	videoSourceTwo->SetVideoEditRate(EditRate(24000, 1001));
	videoSourceTwo->SetAudioEditRate(24000);
	videoSourceTwo->SetTimeCode(TimeCode(TimeCode::k24Fps, "01:00:00:00"));

	/* Display the contents of the video source*/
	displayVideoSource(videoSourceTwo);

	std::cout << "Adding the first audio source to the UMC object" << std::endl;

	/*Adding an audio source to the UMC object*/
	auto audioSource = umcObject->AddAudioSource();
	audioSource->SetClipName("AudioSourceOne");
	audioSource->SetDuration(200);
	audioSource->SetAudioEditRate(EditRate(44100));
	audioSource->SetTimeCode(TimeCode(TimeCode::k29_97Fps, 1, 2, 3, 4, true));

	/* Display the contents of the audio source*/
	displayAudioSource(audioSource);
	
	std::cout << "Adding the first output to the UMC object" << std::endl;

	auto outputOne = umcObject->AddOutput();
	outputOne->SetAudioEditRate(EditRate(44100));
	outputOne->SetVideoEditRate(EditRate(24));
	outputOne->SetName("OutputOne");
	outputOne->SetTitle("Video for Output One");
	outputOne->SetImageAspectRatio(AspectRatio(1080, 720));
	outputOne->SetCanvasAspectRatio(AspectRatio(640, 480));

	std::cout << "Adding the first video track to the first output" << std::endl;

	/*Adding the first video track to the UMC output*/
	auto videoTrackOne = outputOne->AddVideoTrack();
	videoTrackOne->SetName("VideoTrackOne");
	videoTrackOne->SetVideoEditRate(EditRate(24000, 1001));
	videoTrackOne->SetAudioEditRate(48000);
	
	std::cout << "Adding the first audio track to the first output" << std::endl;

	/*Adding the first audio track to the UMC output*/
	auto audioTrackOne = outputOne->AddAudioTrack();
	audioTrackOne->SetName("AudioTrackOne");
	audioTrackOne->SetAudioEditRate(44100);

	std::cout << "Adding the first video track to the first output" << std::endl;

	/*Adding the second video track to the UMC output*/
	auto audioTrackTwo = outputOne->AddAudioTrack();
	audioTrackTwo->SetName("AudioTrackTwo");
	audioTrackOne->SetAudioEditRate(48000);

	std::cout << "Adding the first clip shot to the first video track" << std::endl;

	/*Adding the first clip shot to the first video track*/
	auto clipShotOne = videoTrackOne->AddClipShot();
	clipShotOne->SetInCount(10);
	clipShotOne->SetDuration(15);

	std::cout << "Adding the first transition shot to the first video track" << std::endl;

	/*Adding the first transition track to the UMC output*/
	auto transitionShotOne = videoTrackOne->AddTransitionShot();
	transitionShotOne->SetInCount(8);
	transitionShotOne->SetDuration(3);

	std::cout << "Adding the first frame to the first video track" << std::endl;

	/*Adding the first frame to the clip shot*/

	auto frameOne = clipShotOne->AddFrame(videoSourceOne);
	frameOne->SetShotInCount(12);

	std::cout << "Adding the second frame to the first video track" << std::endl;

	/*Adding the second frame to the clip shot*/

	auto frameTwo = clipShotOne->AddFrame(videoSourceOne);
	frameTwo->SetShotInCount(13);

	std::cout << "Adding the third frame to the first video track" << std::endl;

	/*Adding the third frame to the clip shot*/
	auto frameThree = clipShotOne->AddFrame(videoSourceOne);
	frameThree->SetShotInCount(14);

	std::cout << "Adding the first shot source to the clip shot using the first video source" << std::endl;
	
	/*Adding the first shot source to the clip shot*/
	auto shotSourceOne = clipShotOne->AddShotSource(videoSourceOne);
	shotSourceOne->SetSourceInCount(1);
	shotSourceOne->SetSourceDuration(10);
	shotSourceOne->SetShotInCount(1);

	std::cout << "Adding the first shot source to the clip shot using the second video source" << std::endl;

	/*Adding the second shot source to the clip shot*/
	auto shotSourceTwo = transitionShotOne->AddShotSource(videoSourceTwo);
	shotSourceTwo->SetSourceInCount(100);
	shotSourceTwo->SetSourceDuration(100);
	shotSourceTwo->SetShotInCount(100);

	std::cout << " Displaying the first output" << std::endl;

	displayOutput(outputOne);

	std::cout << " Displaying the first video track" << std::endl;

	displayVideoTrack(videoTrackOne);

	std::cout << " Displaying the first audio track" << std::endl;

	displayAudioTrack(audioTrackOne);

	std::cout << " Displaying the second audio track" << std::endl;

	displayAudioTrack(audioTrackTwo);

	std::cout << " Displaying the first clip shot" << std::endl;
	
	displayShot(clipShotOne);

	std::cout << " Displaying the first output" << std::endl;

	displayShot(transitionShotOne);

	std::cout << " Displaying the first frame" << std::endl;

	displayFrame(frameOne);

	std::cout << " Displaying the second frame" << std::endl;

	displayFrame(frameTwo);

	std::cout << " Displaying the third frame" << std::endl;

	displayFrame(frameThree);

	std::cout << " Displaying the first shot source" << std::endl;

	displayShotSource(shotSourceOne);

	std::cout << " Displaying the second shot source" << std::endl;

	displayShotSource(shotSourceTwo);


	/*Creating a file stream for dumping rdf serialization of the UMC object*/
	std::ofstream fileWriter("rdfRepresentationOfUMC.xmp");

	/*Dumping the RDF serialization of the umcObj on to the file stream*/
	fileWriter << umcObject->SerializeToBuffer();

	/*Closing the file stream*/
	fileWriter.close();

	/*
	There must be a matching UMC_Terminate() call for each UMC_Initialize() call
	*/
	UMC_Terminate();
}