#ifndef AudioTrackImpl_h__
#define AudioTrackImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IAudioTrack.h"
#include "implHeaders/TrackImpl.h"
#include "UMCFwdDeclarations_I.h"

namespace INT_UMC {
	class AudioTrackImpl
		: public IAudioTrack
		, public TrackImpl
		, public enable_shared_from_this < AudioTrackImpl >
	{
	public:
		AudioTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		AudioTrackImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node );

		virtual ~AudioTrackImpl() {}

		virtual void SetAudioEditRate( const EditRate & editRate );
		virtual EditRate GetAudioEditRate() const;

		virtual eTrackTypes GetType() const;

		virtual spIShot AddShot( const std::string & buffer );

		virtual spIClipShot AddClipShot();
		virtual spIClipShot AddClipShot( const std::string & buffer );

		virtual spITransitionShot AddTransitionShot();
		virtual spITransitionShot AddTransitionShot( const std::string & buffer );

		virtual void SetName( const std::string & uniqueID );
		virtual std::string GetName() const;

		virtual size_t ShotCount() const;
		virtual ShotList GetAllShots();
		virtual cShotList GetAllShots() const;
		virtual spIShot GetShot( const std::string & uniqueID );
		virtual spcIShot GetShot( const std::string & uniqueID ) const;

		virtual size_t ClipShotCount() const;
		virtual ClipShotList GetAllClipShots();
		virtual cClipShotList GetAllClipShots() const;
		virtual spIClipShot GetClipShot( const std::string & uniqueID );
		virtual spcIClipShot GetClipShot( const std::string & uniqueID ) const;

		virtual size_t TransitionShotCount() const;
		virtual TransitionShotList GetAllTransitionShots();
		virtual cTransitionShotList GetAllTransitionShots() const;
		virtual spITransitionShot GetTransitionShot( const std::string & uniqueID );
		virtual spcITransitionShot GetTransitionShot( const std::string & uniqueID ) const;

		virtual size_t RemoveAllShots();
		virtual size_t RemoveAllClipShots();
		virtual size_t RemoveAllTransitionShots();

		virtual size_t RemoveShot( const std::string & uniqueID );
		virtual size_t RemoveClipShot( const std::string & uniqueID );
		virtual size_t RemoveTransitionShot( const std::string & uniqueID );

		virtual eNodeTypes GetNodeType() const;

		virtual const std::string & GetUniqueID() const;
		virtual std::string GetParsedID() const;

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual wpcINode GetParentNode() const;
		virtual wpINode GetParentNode();

		virtual spcINode GetDecendantNode( const std::string & uniqueID ) const;
		virtual spINode GetDecendantNode( const std::string & uniqueID );

		virtual spcINode GetChildNode( const std::string & uniqueID ) const;
		virtual spINode GetChildNode( const std::string & uniqueID );

		virtual size_t GetReferenceCount() const;

		virtual std::string Serialize() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual INT_UMC::pINodeI GetInternalNode();
		virtual INT_UMC::pcINodeI GetInternalNode() const;

		virtual void CleanUpOnRemovalFromDOM();
		virtual void SetUpOnAdditionToDOM();

		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff();

		virtual spIXMPStructureNode GetXMPNode() const;

	protected:
		virtual bool ValidateXMPNode() const;

		virtual pINode GetNode();

		virtual pcINode GetNode() const;

		EditRate				mAudioEditRate;
	};
}

#endif  // AudioTrackImpl_h__
