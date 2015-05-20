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
#include "UMCDefines_I.h"
#include "interfaces/IFrame.h"
#include "interfaces/ISource.h"
#include "interfaces/INodeI.h"

#include <string>
#include <map>

namespace INT_UMC {
	using namespace UMC;

	class ShotImpl
		: public IShot
		, public INodeI
		, public enable_shared_from_this< ShotImpl >
	{
	public:
		ShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		virtual const std::string & GetUniqueID() const;

		virtual eShotTypes GetType() const ;

		virtual void SetInCount( const EditUnitInCount & inCount );
		virtual EditUnitInCount GetInCount() const;

		virtual void SetDuration( const EditUnitDuration & duration );
		virtual EditUnitDuration GetDuration() const;

		virtual spIFrame AddFrame();

		virtual size_t FrameCount() const;
		virtual FrameList GetFrames();
		virtual cFrameList GetFrames() const;
		virtual spIFrame GetFrame( const char * uniqueID, size_t length );

		virtual spIShotSource AddShotSource();

		virtual size_t ShotSourceCount() const;
		virtual ShotSourceList GetShotSources();
		virtual cShotSourceList GetShotSources() const;

		virtual spIShotSource GetShotSource( const std::string & uniqueID );
		virtual spcIShotSource GetShotSource( const std::string & uniqueID ) const;

		virtual eNodeTypes GetNodeType() const;

		virtual wpcINode GetParentNode() const;
		virtual wpINode GetParentNode();

		virtual spcINode GetDecendantNode( const std::string & id ) const;
		virtual spINode GetDecendantNode( const std::string & id );

		virtual spcINode GetChildNode( const std::string & id ) const;
		virtual spINode GetChildNode( const std::string & id );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual size_t GetReferenceCount() const;

		virtual void AddToDOM( const spINode & parent );
		virtual void RemoveFromDOM();

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual pINodeI GetInternalNode();
		virtual pcINodeI GetInternalNode() const;

		virtual void SetExtensionNode( const spIXMPStructureNode & structureNode );
		virtual spIXMPStructureNode GetExtensionNode(bool create = false) const;
		virtual spIXMPStructureNode GetMergedExtensionNode() const;

		virtual spIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker();

		virtual spcIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() const;

		virtual spIUniqueIDGenerator GetUniqueIDGenerator();

		virtual spcIUniqueIDGenerator GetUniqueIDGenerator() const;

	protected:
		typedef std::map< const std::string, spIFrame > FrameMap;
		typedef std::map< const std::string, spIShotSource > ShotSourceMap;

		spINode					mNode;
		eShotTypes				mShotType;
		EditUnitInCount			mInCount;
		EditUnitDuration		mDuration;
		weak_ptr< ITrack >		mwpTrack;
		FrameMap				mFrameMap;
		ShotSourceMap			mShotSourceMap;
	};
}

#endif  // ShotImpl_h__
