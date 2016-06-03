// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2016 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "SampleUtils.h"

namespace SampleUtils {

	void displayEditRate(UMC::EditRate editRate) {

		std::cout << editRate;

	}

	void displayAspectRatio(UMC::AspectRatio aspectRatio) {

		std::cout << aspectRatio;
	}

	void displayTimeCode(UMC::TimeCode timeCode) {

		std::cout << timeCode;
	}


	/*Displaying the contents of a video source in a human readable format*/

	void displayVideoSource(const  UMC::spIVideoSource & videoSource, std::string beginIndent) {

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

	void displayAudioSource(const  UMC::spIAudioSource & audioSource, std::string beginIndent) {

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

	void displayImageSource(const  UMC::spIImageSource & imageSource, std::string beginIndent) {

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

	/*Displaying the contents of a video frame in a human readable format*/
	void displayVideoFrameSource(const UMC::spIVideoFrameSource & videoFrameSource, std::string beginIndent) {

		using namespace std;
		using namespace UMC;

		//cout << beginIndent << "Printing contents of the video frame source" << endl;
		cout << endl;
		cout << beginIndent << " Video Frame ClipName:" << beginIndent;
		cout << videoFrameSource->GetClipName();
		cout << endl;

		cout << beginIndent << " Video Frame Unique ID:" << beginIndent;
		cout << videoFrameSource->GetUniqueID();
		cout << endl;

		cout << beginIndent << " Video Frame Incount:" << beginIndent;
		cout << videoFrameSource->GetInCount();
		cout << endl;

		cout << beginIndent << " Video Frame TimeCode:" << beginIndent;
		displayTimeCode(videoFrameSource->GetTimeCode());
		cout << endl;
		cout << endl;
	}



	/*Displaying the contents of a output in a human readable format*/
	void displayOutput(const  UMC::spIOutput & output, std::string beginIndent) {

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
	void displayAudioTrack(const  UMC::spIAudioTrack & audioTrack, std::string beginIndent) {

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
	void displayVideoTrack(const  UMC::spIVideoTrack & videoTrack, std::string beginIndent) {

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
	void displayShot(const  UMC::spIShot & shot, std::string beginIndent) {

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
	void displayFrame(const  UMC::spIFrame & frame, std::string beginIndent) {

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
	void displayShotSource(const  UMC::spIShotSource & shotSource, std::string beginIndent) {

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
}