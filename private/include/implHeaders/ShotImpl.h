#ifndef ShotImpl_h__
#define ShotImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IShot.h"
#include "implHeaders/NodeImpl.h"

#include <map>

namespace INT_UMC {
	using namespace UMC;

	class ShotImpl
		: public NodeImpl
	{
	public:
		ShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		ShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node );

		virtual void SetInCount( const EditUnitInCount & inCount );
		virtual EditUnitInCount GetInCount() const;

		virtual void SetDuration( const EditUnitDuration & duration );
		virtual EditUnitDuration GetDuration() const;

		virtual spIFrame AddFrame( const spISource & source, const spINode & spSelf );
		virtual spIFrame AddFrame( const std::string & buffer, const spINode & spSelf );

		virtual spIShotSource AddShotSource( const spISource & source, const spINode & spSelf );
		virtual spIShotSource AddShotSource( const std::string & buffer, const spINode & spSelf );

		virtual size_t FrameCount() const;
		virtual IShot::FrameList GetAllFrames();
		virtual IShot::cFrameList GetAllFrames() const;
		virtual spIFrame GetFrame( const std::string & uniqueID );
		virtual spcIFrame GetFrame( const std::string & uniqueID ) const;

		virtual size_t ShotSourceCount() const;
		virtual IShot::ShotSourceList GetAllShotSources();
		virtual IShot::cShotSourceList GetAllShotSources() const;
		virtual spIShotSource GetShotSource( const std::string & uniqueID );
		virtual spcIShotSource GetShotSource( const std::string & uniqueID ) const;

		virtual size_t RemoveAllShotSources();
		virtual size_t RemoveAllFrames();

		virtual size_t RemoveShotSource( const std::string & uniqueID );
		virtual size_t RemoveFrame( const std::string & uniqueID );

		spcINode GetDecendantNode( const std::string & uniqueID ) const;
		spINode GetDecendantNode( const std::string & uniqueID );

		spcINode GetChildNode( const std::string & uniqueID ) const;
		spINode GetChildNode( const std::string & uniqueID );

		INode::NodeList GetAllChildren();
		INode::cNodeList GetAllChildren() const;

		INode::NodeList GetAllDecendants();
		INode::cNodeList GetAllDecendants() const;

		void CleanUpOnRemovalFromDOM();
		void SetUpOnAdditionToDOM();

		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff( const spINode & spSelf );

		virtual bool ValidateXMPNode() const;

	protected:
		typedef std::map< const std::string, spIFrame > FrameMap;
		typedef std::map< const std::string, spIShotSource > ShotSourceMap;

		spIXMPArrayNode			mFrames;
		spIXMPArrayNode			mShotSources;

		spIShotSource AddShotSource( const spIXMPStructureNode & node, const spINode & spSelf );
		spIFrame AddFrame( const spIXMPStructureNode & node, const spINode & spSelf );

		EditUnitInCount			mInCount;
		EditUnitDuration		mDuration;
		FrameMap				mFrameMap;
		ShotSourceMap			mShotSourceMap;
	};
}

#endif  // ShotImpl_h__
