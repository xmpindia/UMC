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
#include "interfaces/ISource.h"
#include "interfaces/INodeI.h"

namespace INT_UMC {
	class VideoFrameSourceImpl
		: public IVideoFrameSource
		, public INodeI
		, public enable_shared_from_this < VideoFrameSourceImpl >
	{
	public:
		VideoFrameSourceImpl( const spIVideoSource & videoSource,
			const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker, const spIUniqueIDGenerator & uniqueIDGenerator );

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

		virtual wpcINode GetParentNode() const;
		virtual wpINode GetParentNode();

		virtual spcINode GetDecendantNode( const std::string & uniqueID ) const;
		virtual spINode GetDecendantNode( const std::string & uniqueID );

		virtual spcINode GetChildNode( const std::string & uniqueID ) const;
		virtual spINode GetChildNode( const std::string & uniqueID );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual size_t GetReferenceCount() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual pINodeI GetInternalNode();
		virtual pcINodeI GetInternalNode() const;

		virtual void SetExtensionNode( const spIXMPStructureNode & structureNode );

		virtual spIXMPStructureNode GetExtensionNode(bool create = false) const;
		virtual spIXMPStructureNode GetMergedExtensionNode() const;

		virtual void RemoveFromDOM();
		virtual void AddToDOM( const spINode & parent );

		virtual spIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker();

		virtual spcIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() const;

		virtual spIUniqueIDGenerator GetUniqueIDGenerator();

		virtual spcIUniqueIDGenerator GetUniqueIDGenerator() const;

	protected:
		spISource					mSource;
		spIVideoSource				mVideoSource;
		EditUnitInCount				mInCount;
	};
}

#endif  // VideoFrameSourceImpl_h__
