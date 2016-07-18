#ifndef SampleUtils_h__
#define SampleUtils_h__ 1

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
#include "interfaces/IVideoFrameSource.h"



namespace SampleUtils 
{
	static const std::string defaultIndent = "\t\t\t\t\t";
	static int maxFieldWidth = 30;
	static int maxLineFieldWidth = 100;

	/*Displaying the EditRate in a human readable format*/
	void displayEditRate(UMC::EditRate  editRate);

	/*Displaying the AspectRatio in a human readable format*/
	void displayAspectRatio(UMC::AspectRatio & aspectRatio);

	/*Displaying the TimeCode in a human readable format*/
	void displayTimeCode(UMC::TimeCode timeCode);

	/*Displaying the contents of a video source in a human readable format*/

	void displayVideoSource(const  UMC::spIVideoSource & videoSource, std::string beginIndent = defaultIndent);

	/*Displaying the contents of a audio source in a human readable format*/

	void displayAudioSource(const  UMC::spIAudioSource & audioSource, std::string beginIndent = defaultIndent);

	/*Displaying the contents of an image source in a human readable format*/

	void displayImageSource(const  UMC::spIImageSource & imageSource, std::string beginIndent = defaultIndent);

	/*Displaying the contents of a video frame in a human readable format*/
	void displayVideoFrameSource(const UMC::spIVideoFrameSource & videoFrameSource, std::string beginIndent = defaultIndent);

	/*Displaying the contents of a output in a human readable format*/
	void displayOutput(const  UMC::spIOutput & output, std::string beginIndent = defaultIndent);


	/*Displaying the contents of an audio track in a human readable format*/
	void displayAudioTrack(const  UMC::spIAudioTrack & audioTrack, std::string beginIndent = defaultIndent);


	/*Displaying the contents of a video track in a human readable format*/
	void displayVideoTrack(const  UMC::spIVideoTrack & videoTrack, std::string beginIndent = defaultIndent);

	/*Displaying the contents of a shot in a human readable format*/
	void displayShot(const  UMC::spIShot & shot, std::string beginIndent = defaultIndent);

	/*Displaying the contents of a frame in a human readable format*/
	void displayFrame(const  UMC::spIFrame & frame, std::string beginIndent = defaultIndent);

	/*Displaying the contents of a shot source in a human readable format*/
	void displayShotSource(const  UMC::spIShotSource & shotSource, std::string beginIndent = defaultIndent);
};

#endif