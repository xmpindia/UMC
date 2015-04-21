#ifndef VideoFrameSourceImpl_h__
#define VideoFrameSourceImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IVideoFrameSource.h"
#include "implHeaders/SourceImpl.h"

namespace INT_UMC {
	class VideoFrameSourceImpl
		: public IVideoFrameSource
		, public enable_shared_from_this < VideoFrameSourceImpl >
	{
	public:
		VideoFrameSourceImpl( const std::string & uniqueID, const spIVideoSource & videoSource,
			const spUniqueIDSet & uniqueIDSet, const spIUniqueIDGenerator & uniqueIDGenerator, const spIUMC & parent );

		virtual void SetInCount( const EditUnitInCount & inCount );
		virtual EditUnitInCount GetInCount() const;

		virtual TimeCode GetTimeCode() const;

		virtual spIVideoSource GetVideoSource();
		virtual spcIVideoSource GetVideoSource() const;

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

	protected:
		SourceImpl					mSourceImpl;
		spIVideoSource				mVideoSource;
		EditUnitInCount				mInCount;
	};
}

#endif  // VideoFrameSourceImpl_h__
