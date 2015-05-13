#ifndef UMCFwdDeclarations_h__
#define UMCFwdDeclarations_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


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

	// INode
	class INode;
	typedef INode *									pINode;
	typedef const INode *							pcINode;
	typedef shared_ptr< INode >						spINode;
	typedef shared_ptr< const INode >				spcINode;
	typedef weak_ptr< INode >						wpINode;
	typedef weak_ptr< const INode >					wpcINode;


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

	// ITrack
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
