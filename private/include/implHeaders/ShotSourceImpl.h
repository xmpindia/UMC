#ifndef ShotSourceImpl_h__
#define ShotSourceImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IShotSource.h"
#include "implHeaders/NodeImpl.h"

namespace INT_UMC {
	using namespace UMC;

	class ShotSourceImpl
		: public IShotSource
		, public NodeImpl
		, public enable_shared_from_this< ShotSourceImpl >
	{
	public:
		ShotSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source );

		ShotSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source,
			const spIXMPStructureNode & node );

		virtual spISource GetSource();
		virtual spcISource GetSource() const;
		
		virtual void SetSourceInCount( const EditUnitInCount & sourceInCount );
		virtual EditUnitInCount GetSourceInCount() const;

		virtual void SetSourceDuration( const EditUnitDuration & sourceDuration );
		virtual EditUnitDuration GetSourceDuration() const;

		virtual void SetShotInCount( const EditUnitInCount & shotInCount );
		virtual EditUnitInCount GetShotInCount() const;

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

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual INT_UMC::pINodeI GetInternalNode();
		virtual INT_UMC::pcINodeI GetInternalNode() const;

		virtual std::string Serialize() const;

		virtual void CleanUpOnRemovalFromDOM();
		virtual void SetUpOnAdditionToDOM();
		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff();
		virtual bool ValidateXMPNode() const;

		virtual pINode GetNode();
		virtual pcINode GetNode() const;

		virtual spIXMPStructureNode GetXMPNode() const;

	private:
		spISource				mSource;
		EditUnitInCount			mSourceInCount;
		EditUnitDuration		mSourceDuration;
		EditUnitInCount			mShotInCount;
	};
}
#endif  // ShotSourceImpl_h__
