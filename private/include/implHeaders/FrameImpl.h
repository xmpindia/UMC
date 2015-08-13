#ifndef FrameImpl_h__
#define FrameImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IFrame.h"
#include "implHeaders/NodeImpl.h"

namespace INT_UMC {
	using namespace UMC;
	
	class FrameImpl
		: public IFrame
		, public NodeImpl
		, public enable_shared_from_this< FrameImpl >
	{
	public:
		FrameImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source );

		FrameImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source,
			const spIXMPStructureNode & node );

		const std::string & GetUniqueID() const;
		virtual std::string GetParsedID() const;

		virtual spISource GetSource();
		virtual spcISource GetSource() const;

		virtual void SetSourceInCount( const EditUnitInCount & sourceInCount );
		virtual EditUnitInCount GetSourceInCount() const;

		virtual void SetShotInCount( const EditUnitInCount & shotInCount );
		virtual EditUnitInCount GetShotInCount() const;

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

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual pINodeI GetInternalNode();
		virtual pcINodeI GetInternalNode() const;

		virtual std::string Serialize() const;

		virtual void CleanUpOnRemovalFromDOM();
		virtual void SetUpOnAdditionToDOM();
		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff();
		virtual bool ValidateXMPNode() const;

		virtual pINode GetNode();
		virtual pcINode GetNode() const;

		virtual spIXMPStructureNode GetXMPNode() const;

		virtual bool SetUniqueID( const std::string & uniqueID );
		virtual bool ChangeChildUniqueID( const spINode & childNode, const std::string & newUniqueID );
		virtual spINode GetExternalNode();

	protected:
		spISource				mSource;
		EditUnitInCount			mSourceInCount;
		EditUnitInCount			mShotInCount;
	};
}

#endif  // FrameImpl_h__
