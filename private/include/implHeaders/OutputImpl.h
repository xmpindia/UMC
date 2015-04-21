#ifndef OutputImpl_h__
#define OutputImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IOutput.h"
#include "interfaces/ITrack.h"
#include "UMCFwdDeclarations_I.h"

#include <map>

namespace INT_UMC {
	using namespace UMC;

	class OutputImpl
		: public IOutput
		, public enable_shared_from_this< OutputImpl >
	{
	public:
		OutputImpl( const std::string & uniqueID, const spUniqueIDSet & uniqueIDSet,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spIUMC & parent );

		virtual const std::string & GetUniqueID() const;

		virtual spIVideoTrack AddVideoTrack();
		virtual spIAudioTrack AddAudioTrack();

		virtual void SetName( const std::string & name );
		virtual std::string GetName() const;

		virtual void SetTitle( const std::string & title );
		virtual std::string GetTitle() const;

		virtual void SetCanvasAspectRatio( const AspectRatio & canvasAspectRatio );
		virtual AspectRatio GetCanvasAspectRatio() const;

		virtual void SetImageAspectRatio( const AspectRatio & imageAspectRatio );
		virtual AspectRatio GetImageAspectRatio() const;

		virtual void SetVideoEditRate( const EditRate & videoEditRate );
		virtual EditRate GetVideoEditRate() const;

		virtual void SetAudioEditRate( const EditRate & audioEditRate );
		virtual EditRate GetAudioEditRate() const;

		virtual size_t	TrackCount() const;
		virtual TrackList GetAllTracks();
		virtual cTrackList GetAllTracks() const;
		virtual spITrack GetTrack( const std::string & uniqueID );
		virtual spcITrack GetTrack( const std::string & uniqueID ) const;

		virtual size_t VideoTrackCount() const;
		virtual VideoTrackList GetAllVideoTracks();
		virtual cVideoTrackList GetAllVideoTracks() const;
		virtual spIVideoTrack GetVideoTrack( const std::string & uniqueID );
		virtual spcIVideoTrack GetVideoTrack( const std::string & uniqueID ) const;

		virtual size_t AudioTrackCount() const;
		virtual AudioTrackList GetAllAudioTracks();
		virtual cAudioTrackList GetAllAudioTracks() const;
		virtual spIAudioTrack GetAudioTrack( const std::string & uniqueID );
		virtual spcIAudioTrack GetAudioTrack( const std::string & uniqueID ) const;

		virtual size_t RemoveAllTracks();
		virtual size_t RemoveAllVideoTracks();
		virtual size_t RemoveAllAudioTracks();
		virtual size_t RemoveTrack( const std::string & uniqueID );
		virtual size_t RemoveVideoTrack( const std::string & uniqueID );
		virtual size_t RemoveAudioTrack( const std::string & uniqueID );

		virtual eNodeTypes GetNodeType() const;

		virtual spcINode GetParentNode() const;
		virtual spINode GetParentNode();

		virtual spcINode GetDecendantNode( const std::string & id ) const;
		virtual spINode GetDecendantNode( const std::string & id );

		virtual spcINode GetChildNode( const std::string & id ) const;
		virtual spINode GetChildNode( const std::string & id );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

	protected:
		typedef std::map< const std::string, spIVideoTrack > VideoTrackMap;
		typedef std::map< const std::string, spIAudioTrack > AudioTrackMap;

	protected:
		const std::string		mUniqueID;
		std::string				mName;
		std::string				mTitle;
		AspectRatio 			mCanvasAspectRatio;
		AspectRatio 			mImageAspectRatio;
		EditRate				mVideoEditRate;
		EditRate				mAudioEditRate;
		VideoTrackMap			mVideoTrackMap;
		AudioTrackMap			mAudioTrackMap;

		weak_ptr< IUMC >		mwpUMC;
		spUniqueIDSet			mspUniqueIDSet;
		spIUniqueIDGenerator	mspUniqueIDGenerator;
	};
}

#endif  // OutputImpl_h__
