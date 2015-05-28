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
#include "interfaces/INodeI.h"
#include "UMCDefines_I.h"

namespace INT_UMC {
	using namespace UMC;

	class ShotSourceImpl
		: public IShotSource
		, public INodeI
		, public enable_shared_from_this< ShotSourceImpl >
	{
	public:
		ShotSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source );

		virtual spISource GetSource();
		virtual spcISource GetSource() const;
		
		virtual void SetSourceInCount( const EditUnitInCount & sourceInCount );
		virtual EditUnitInCount GetSourceInCount() const;

		virtual void SetSourceDuration( const EditUnitDuration & sourceDuration );
		virtual EditUnitDuration GetSourceDuration() const;

		virtual void SetShotInCount( const EditUnitInCount & shotInCount );
		virtual EditUnitInCount GetShotInCount() const;

		// INODEI

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

		virtual void AddToDOM( const spINode & parent );
		virtual void RemoveFromDOM();

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual INT_UMC::pINodeI GetInternalNode();
		virtual INT_UMC::pcINodeI GetInternalNode() const;

		virtual void SetExtensionNode( const spIXMPStructureNode & structureNode );
		virtual spIXMPStructureNode GetExtensionNode(bool create = false) const;
		virtual spIXMPStructureNode GetMergedExtensionNode() const;

		virtual spIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker();

		virtual spcIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() const;

		virtual spIUniqueIDGenerator GetUniqueIDGenerator();

		virtual spcIUniqueIDGenerator GetUniqueIDGenerator() const;

	private:
		spINode					mNode;
		weak_ptr< ISource >     mwpSource;
		EditUnitInCount			mSourceInCount;
		EditUnitDuration		mSourceDuration;
		EditUnitInCount			mShotInCount;
	};
}
#endif  // ShotSourceImpl_h__
