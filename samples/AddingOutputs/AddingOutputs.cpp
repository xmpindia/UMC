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

#include "SampleUtils.h"


int main() {

	using namespace UMC;
	using namespace SampleUtils;

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