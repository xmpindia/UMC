#ifndef UMCFwdDeclarations_h__
#define UMCFwdDeclarations_h__ 1

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

#include "UMCDefines.h"
#include "baseTypes/SmartPointers.h"

namespace UMC {

	extern const std::string kEmptyString;

	// IUniqueIDGenerator
	class IUniqueIDGenerator;
	typedef IUniqueIDGenerator *					pIUniqueIDGenerator;
	typedef const IUniqueIDGenerator *				pcIUniqueIDGenerator;
	typedef shared_ptr< IUniqueIDGenerator >		spIUniqueIDGenerator;
	typedef shared_ptr< const IUniqueIDGenerator >	spcIUniqueIDGenerator;

	// IUMCNode
	class IUMCNode;
	typedef IUMCNode *									pIUMCNode;
	typedef const IUMCNode *							pcIUMCNode;
	typedef shared_ptr< IUMCNode >						spIUMCNode;
	typedef shared_ptr< const IUMCNode >				spcIUMCNode;
	typedef weak_ptr< IUMCNode >						wpIUMCNode;
	typedef weak_ptr< const IUMCNode >					wpcIUMCNode;


	// ISource
	class ISource;
	typedef ISource *								pISource;
	typedef const ISource *							pcISource;
	typedef shared_ptr< ISource >					spISource;
	typedef shared_ptr< const ISource >				spcISource;

	// IVideoVideoSource
	class IVideoSource;
	typedef IVideoSource *							pIVideoSource;
	typedef const IVideoSource *					pcIVideoSource;
	typedef shared_ptr< IVideoSource >				spIVideoSource;
	typedef shared_ptr< const IVideoSource >		spcIVideoSource;

	// IAudioSource
	class IAudioSource;
	typedef IAudioSource *							pIAudioSource;
	typedef const IAudioSource *					pcIAudioSource;
	typedef shared_ptr< IAudioSource >				spIAudioSource;
	typedef shared_ptr< const IAudioSource >		spcIAudioSource;

	// IVideoFrameSource
	class IVideoFrameSource;
	typedef IVideoFrameSource *						pIVideoFrameSource;
	typedef const IVideoFrameSource *				pcIVideoFrameSource;
	typedef shared_ptr< IVideoFrameSource >			spIVideoFrameSource;
	typedef shared_ptr< const IVideoFrameSource >	spcIVideoFrameSource;

	// IImageSource
	class IImageSource;
	typedef IImageSource *							pIImageSource;
	typedef const IImageSource *					pcIImageSource;
	typedef shared_ptr< IImageSource >				spIImageSource;
	typedef shared_ptr< const IImageSource >		spcIImageSource;

	// IUMC
	class IUMC;
	typedef IUMC *									pIUMC;
	typedef const IUMC *							pcIUMC;
	typedef shared_ptr< IUMC >						spIUMC;
	typedef shared_ptr< const IUMC >				spcIUMC;

	// IOutput
	class IOutput;
	typedef IOutput *								pIOutput;
	typedef const IOutput *							pcIOutput;
	typedef shared_ptr< IOutput >					spIOutput;
	typedef shared_ptr< const IOutput >				spcIOutput;

	// ITrack
	class ITrack;
	typedef ITrack *								pITrack;
	typedef const ITrack *							pcITrack;
	typedef shared_ptr< ITrack >					spITrack;
	typedef shared_ptr< const ITrack >				spcITrack;

	// IVideoTrack
	class IVideoTrack;
	typedef IVideoTrack *							pIVideoTrack;
	typedef const IVideoTrack *						pcIVideoTrack;
	typedef shared_ptr< IVideoTrack >				spIVideoTrack;
	typedef shared_ptr< const IVideoTrack >			spcIVideoTrack;

	// IAudioTrack
	class IAudioTrack;
	typedef IAudioTrack *							pIAudioTrack;
	typedef const IAudioTrack *						pcIAudioTrack;
	typedef shared_ptr< IAudioTrack >				spIAudioTrack;
	typedef shared_ptr< const IAudioTrack >			spcIAudioTrack;

	// IShot
	class IShot;
	typedef IShot *									pIShot;
	typedef const IShot *							pcIShot;
	typedef shared_ptr< IShot >						spIShot;
	typedef shared_ptr< const IShot >				spcIShot;

	// IClipShot
	class IClipShot;
	typedef IClipShot *								pIClipShot;
	typedef const IClipShot *						pcIClipShot;
	typedef shared_ptr< IClipShot >					spIClipShot;
	typedef shared_ptr< const IClipShot >			spcIClipShot;

	// ITransitionShot
	class ITransitionShot;
	typedef ITransitionShot *						pITransitionShot;
	typedef const ITransitionShot *					pcITransitionShot;
	typedef shared_ptr< ITransitionShot >			spITransitionShot;
	typedef shared_ptr< const ITransitionShot >		spcITransitionShot;

	// IFrame
	class IFrame;
	typedef IFrame *								pIFrame;
	typedef const IFrame *							pcIFrame;
	typedef shared_ptr< IFrame >					spIFrame;
	typedef shared_ptr< const IFrame >				spcIFrame;

	// IShotSource
	class IShotSource;	
	typedef IShotSource *							pIShotSource;
	typedef const IShotSource *						pcIShotSource;
	typedef shared_ptr< IShotSource >				spIShotSource;
	typedef shared_ptr< const IShotSource >			spcIShotSource;


	// ICustomData
	class ICustomData;
	typedef ICustomData *							pICustomData;
	typedef const ICustomData *						pcICustomData;
	typedef shared_ptr< ICustomData >				spICustomData;
	typedef shared_ptr< const ICustomData >			spcICustomData;

	// ICustomDataHandler
	class ICustomDataHandler;
	typedef ICustomDataHandler *					pICustomDataHandler;
	typedef const ICustomDataHandler *				pcICustomDataHandler;
	typedef shared_ptr< ICustomDataHandler >		spICustomDataHandler;
	typedef shared_ptr< const ICustomDataHandler >	spcICustomDataHandler;

};

#endif  // UMCFwdDeclarations_h__
