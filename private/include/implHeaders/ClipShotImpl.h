#ifndef ClipShotImpl_h__
#define ClipShotImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IClipShot.h"
#include "implHeaders/ShotImpl.h"

namespace INT_UMC {
	class ClipShotImpl
		: public IClipShot
		, public ShotImpl
		, public enable_shared_from_this< ClipShotImpl >
	{
	public:
		ClipShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		ClipShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node );

		virtual eShotTypes GetType() const;

		virtual eNodeTypes GetNodeType() const;

		virtual const std::string & GetUniqueID() const;
		virtual std::string GetParsedID() const;

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

		virtual std::string Serialize() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );

		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual INT_UMC::pINodeI GetInternalNode();

		virtual INT_UMC::pcINodeI GetInternalNode() const;

		virtual void CleanUpOnRemovalFromDOM();

		virtual void SetUpOnAdditionToDOM();

		virtual void SyncXMPToInternalStuff();

		virtual void SyncInternalStuffToXMP() const;

		virtual pINode GetNode();

		virtual pcINode GetNode() const;

		virtual spIXMPStructureNode GetXMPNode() const;

		virtual void SetInCount( const EditUnitInCount & inCount );

		virtual EditUnitInCount GetInCount() const;

		virtual void SetDuration( const EditUnitDuration & duration );

		virtual EditUnitDuration GetDuration() const;

		virtual spIFrame AddFrame( const spISource & source );

		virtual spIFrame AddFrame( const std::string & buffer );

		virtual spIShotSource AddShotSource( const spISource & source );

		virtual spIShotSource AddShotSource( const std::string & buffer );

		virtual size_t FrameCount() const;

		virtual FrameList GetAllFrames();

		virtual cFrameList GetAllFrames() const;

		virtual spIFrame GetFrame( const std::string & uniqueID );

		virtual spcIFrame GetFrame( const std::string & uniqueID ) const;

		virtual size_t ShotSourceCount() const;

		virtual ShotSourceList GetAllShotSources();

		virtual cShotSourceList GetAllShotSources() const;

		virtual spIShotSource GetShotSource( const std::string & uniqueID );

		virtual spcIShotSource GetShotSource( const std::string & uniqueID ) const;

		virtual size_t RemoveAllShotSources();

		virtual size_t RemoveAllFrames();

		virtual size_t RemoveFrame( const std::string & uniqueID );

		virtual size_t RemoveShotSource( const std::string & uniqueID );

		~ClipShotImpl();

		virtual bool SetUniqueID( const std::string & uniqueID );

		virtual bool ChangeChildUniqueID( const spINode & childNode, const std::string & newUniqueID );

		virtual spINode GetExternalNode();

	};
}

#endif  // ClipShotImpl_h__
