#ifndef AudioSourceImpl_h__
#define AudioSourceImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IAudioSource.h"
#include "implHeaders/SourceImpl.h"

namespace INT_UMC {
	class AudioSourceImpl
		: public IAudioSource
		, public enable_shared_from_this < AudioSourceImpl >
	{
	public:
		AudioSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		virtual void SetAudioEditRate( const EditRate & editRate );
		virtual EditRate GetAudioEditRate() const;

		virtual void SetInCount( const EditUnitInCount & inCount );
		virtual EditUnitInCount GetInCount() const;

		virtual void SetDuration( const EditUnitDuration & duration );
		virtual EditUnitDuration GetDuration() const;

		virtual void SetTimeCode( const TimeCode & timeCode );
		virtual TimeCode GetTimeCode() const;

		virtual eSourceTypes GetType() const;

		virtual void SetClipName( const std::string & clipName );
		virtual std::string GetClipName() const;

		virtual eNodeTypes GetNodeType() const;

		virtual const std::string & GetUniqueID() const;

		virtual spcINode GetParentNode() const;
		virtual spINode GetParentNode();

		virtual spcINode GetDecendantNode( const std::string & uniqueID ) const;
		virtual spINode GetDecendantNode( const std::string & uniqueID );

		virtual spcINode GetChildNode( const std::string & uniqueID ) const;
		virtual spINode GetChildNode( const std::string & uniqueID );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual size_t GetReferenceCount() const;

		virtual void RemoveFromDOM();

		virtual void AddToDOM( const spINode & parent );

	protected:
		SourceImpl					mSourceImpl;
		EditUnitInCount				mInCount;
		EditUnitDuration			mDuration;
		EditRate					mAudioEditRate;
		TimeCode					mTimeCode;

	};
}

#endif  // AudioSourceImpl_h__
