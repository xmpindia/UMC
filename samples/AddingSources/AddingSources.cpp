/*
*  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
*  This file is licensed to you under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License. You may obtain a copy
*  of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software distributed under
*  the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
*  OF ANY KIND, either express or implied. See the License for the specific language
*  governing permissions and limitations under the License.
*
*/



/*
 This sample seeks to demonstrate adding various kinds of sources to the UMC. It more specifically elucidates creating
 various kinds of sources (video sources, image sources, audio sources and video frame sources), adding different kind
 of properties to the sources, adding the sources created to the UMC object, removing sources, and retrieving various
 source properties. For more details, programmer's guide and interface
 documentation should be referred.
 */


#include <string>
#include <iostream>
#include <fstream>
#include "interfaces/IUMC.h"
#include "interfaces/ISource.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/IVideoFrameSource.h"

#include "SampleUtils.h"

int main() {

	using namespace UMC;
	using namespace SampleUtils;

	/*
	Initializing the UMC SDK is necessary before using any of the UMC APIs
	*/
	UMC_Initialize();

	/*Creating an empty UMC object*/
	auto umcObject = IUMC::CreateEmptyUMC();

	std::cout << "Adding the first video source to the umc object" << std::endl;

	auto videoSource = umcObject->AddVideoSource();
	videoSource->SetClipName("Video Source");
	videoSource->SetInCount(1);
	videoSource->SetDuration(500);
	videoSource->SetVideoEditRate(EditRate(24000, 1001));
	videoSource->SetAudioEditRate(24000);
	videoSource->SetTimeCode(TimeCode(TimeCode::k23_976Fps, "02:04:12:34"));

	/* Display the contents of the video source*/
	displayVideoSource(videoSource);

	/*Adding an empty source*/

	std::cout << "Adding the second video source to the umc object" << std::endl;

	auto emptyVideoSource = umcObject->AddVideoSource();

	/*Printing the video source count, should be 2 now*/

	std::cout << "Number of video sources present is " << umcObject->GetAllVideoSources().size() << std::endl;

	/*Displaying the contents of the empty video source*/
	displayVideoSource(emptyVideoSource);
	
	/*Removing the empty video source by getting it's unique id*/
	umcObject->RemoveVideoSource(emptyVideoSource->GetUniqueID());

	/*Printing the video source count, should be 1 now*/


	std::cout << "Number of video sources present is " << umcObject->GetAllVideoSources().size() << std::endl;
	
	/*Adding an audio source to the UMC object*/
	auto audioSourceOne = umcObject->AddAudioSource();

	std::cout << "Adding the first audio source to the umc object" << std::endl;
	audioSourceOne->SetClipName("Audio Source 1");
	audioSourceOne->SetDuration(200);
	audioSourceOne->SetAudioEditRate(EditRate(44100));
	audioSourceOne->SetTimeCode(TimeCode(TimeCode::k29_97Fps, 1, 2, 3, 4, true));
	displayAudioSource(audioSourceOne);

	std::cout << "Number of audio sources present is " << umcObject->GetAllAudioSources().size() << std::endl;

	std::cout << "Adding the second audio source to the umc object" << std::endl;

	auto audioSourceTwo = umcObject->AddAudioSource();
	audioSourceTwo->SetClipName("Audio Source 2");
	audioSourceTwo->SetInCount(10);
	audioSourceTwo->SetAudioEditRate(EditRate(48000));
	audioSourceTwo->SetTimeCode(TimeCode(TimeCode::k25Fps, 1, 2, 3, 4));

	displayAudioSource(audioSourceTwo);

	std::cout << "Number of audio sources present is " << umcObject->GetAllAudioSources().size() << std::endl;
	
	std::cout << "Removing all audio sources" << std::endl;
	umcObject->RemoveAllAudioSources();

	std::cout << "Number of audio sources present is " << umcObject->GetAllAudioSources().size() << std::endl;

	auto imageSourceOne = umcObject->AddImageSource();
	imageSourceOne->SetClipName("Image Source 1");

	displayImageSource(imageSourceOne);
	
	auto imageSourceTwo = umcObject->AddImageSource();
	imageSourceTwo->SetClipName("Image Source 2");
	
	displayImageSource(imageSourceTwo);

	std::cout << "Number of images sources present is " << umcObject->GetAllImageSources().size() << std::endl;
	
	std::cout << "Adding the first video frame source to the umc object" << std::endl;

	auto videoFrameSourceOne = umcObject->AddVideoFrameSource(videoSource);
	videoFrameSourceOne->SetClipName("Video Frame Source 1");
	videoFrameSourceOne->SetInCount(5);
	
	displayVideoFrameSource(videoFrameSourceOne);
	std::cout << "Number of video frame sources present is"<< defaultIndent << umcObject->GetAllVideoFrameSources().size() << std::endl;

	std::cout << "Adding the second video frame source to the umc object" << std::endl;

	auto videoFrameSourceTwo = umcObject->AddVideoFrameSource(videoSource);
	videoFrameSourceTwo->SetClipName("Video Frame Source 2");
	videoFrameSourceTwo->SetInCount(10);
	
	displayVideoFrameSource(videoFrameSourceTwo);

	std::cout << "Number of video frame sources present is " << umcObject->GetAllVideoFrameSources().size() << std::endl;

	auto videoFrameSourceTwoId = videoFrameSourceTwo->GetUniqueID();

	std::cout << "Unique id of the videoFrameSourceTwo is\t" << videoFrameSourceTwo->GetUniqueID() << std::endl;

	std::cout << "Changing the unique id of videoFrameSourceTwo" << std::endl;

	videoFrameSourceTwo->SetUniqueID("100");

	std::cout << "Changed unique id of the videoFrameSourceTwo is" << defaultIndent << videoFrameSourceTwo->GetUniqueID() << std::endl;

	std::cout << "Total number of sources present in the umc object" << defaultIndent << umcObject->GetAllSources().size() << std::endl;
	

	/* Writing the xml serialization of the umcObject to a file called umcBuffer.xmp*/
	std::ofstream umcBuffer("umcBuffer.xmp");
	/*Serializing the umcObject and writing it to umcBuffer.xmp*/
	umcBuffer << umcObject->SerializeToBuffer();
	/*Closing the umcBuffer file*/
	umcBuffer.close();

	/*
	There must be a matching UMC_Terminate() call for each UMC_Initialize() call
	*/
	UMC_Terminate();
}