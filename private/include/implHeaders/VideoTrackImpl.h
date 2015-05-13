#ifndef VideoTrackImpl_h__
#define VideoTrackImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IVideoTrack.h"
#include "implHeaders/TrackImpl.h"

namespace INT_UMC {

	class VideoTrackImpl
		: public IVideoTrack
		, enable_shared_from_this< VideoTrackImpl >
	{
	public:
		VideoTrackImpl( const std::string & uniqueID, const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spIOutput & parent );

		virtual void SetVideoEditRate( const EditRate & editRate );
		virtual EditRate GetVideoEditRate() const;

		virtual void SetAudioEditRate( const EditRate & editRate );
		virtual EditRate GetAudioEditRate() const;

		virtual eTrackTypes GetType() const;

		virtual spIShot AddClipShot();
		virtual spIShot AddTransitionShot();

		virtual void SetName( const std::string & uniqueID );
		virtual std::string GetName() const;

		virtual size_t ShotCount() const;
		virtual ShotList GetAllShots();
		virtual cShotList GetAllShots() const;
		virtual spIShot GetShot( const std::string & uniqueID );
		virtual spcIShot GetShot( const std::string & uniqueID ) const;

		virtual size_t ClipShotCount() const;
		virtual ShotList GetAllClipShots();
		virtual cShotList GetAllClipShots() const;
		virtual spIShot GetClipShot( const std::string & uniqueID );
		virtual spcIShot GetClipShot( const std::string & uniqueID ) const;

		virtual size_t TransitionShotCount() const;
		virtual ShotList GetAllTransitionShots();
		virtual cShotList GetAllTransitionShots() const;
		virtual spIShot GetTransitionShot( const std::string & uniqueID );
		virtual spcIShot GetTransitionShot( const std::string & uniqueID ) const;

		virtual size_t RemoveAllShots();
		virtual size_t RemoveAllClipShots();
		virtual size_t RemoveAllTransitionShots();
		virtual size_t RemoveShot( const std::string & uniqueID );

		virtual size_t RemoveClipShot( const std::string & uniqueID );
		virtual size_t RemoveTransitionShot( const std::string & uniqueID );

		virtual eNodeTypes GetNodeType() const;

		virtual const std::string & GetUniqueID() const;

		virtual wpcINode GetParentNode() const;
		virtual wpINode GetParentNode();

		virtual spcINode GetDecendantNode( const std::string & uniqueID ) const;
		virtual spINode GetDecendantNode( const std::string & uniqueID );

		virtual spcINode GetChildNode( const std::string & uniqueID ) const;
		virtual spINode GetChildNode( const std::string & uniqueID );

		virtual ~VideoTrackImpl() {}

	protected:
		TrackImpl				mTrackImpl;
		EditRate				mVideoEditRate;
		EditRate				mAudioEditRate;
	};
}

#endif  // VideoTrackImpl_h__
