#ifndef NodeImpl_h__
#define NodeImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations_I.h"
#include "interfaces/INode.h"
#include "interfaces/INodeI.h"

#include <map>

namespace INT_UMC {
	class NodeImpl
		: public INode
		, public INodeI
		, public enable_shared_from_this< NodeImpl >
	{
	public:
		NodeImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, eNodeTypes nodeType );

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

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );

		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const spICustomData & customData );

		virtual void RemoveFromDOM();

		virtual void AddToDOM( const spINode & parent );

		virtual INT_UMC::pINodeI GetInternalNode();

		virtual INT_UMC::pcINodeI GetInternalNode() const;

		virtual void SetExtensionNode( const spIXMPStructureNode & structureNode );

		virtual spIXMPStructureNode GetExtensionNode( bool create = false ) const;
		virtual spIXMPStructureNode GetMergedExtensionNode() const;

	protected:
		std::string GetCombinedString( const std::string & nameSpace, const std::string & name ) const;

		virtual spIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker();

		virtual spcIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() const;

		virtual spIUniqueIDGenerator GetUniqueIDGenerator();

		virtual spcIUniqueIDGenerator GetUniqueIDGenerator() const;


		const std::string									mUniqueID;
		mutable NS_XMPCORE::spIXMPStructureNode				mExtensionNode;
		std::map< std::string, spICustomData >				mCustomDataMap;

		weak_ptr< INode >									mwpParentNode;
		spIUniqueIDAndReferenceTracker						mspUniqueIDAndReferenceTracker;
		spIUniqueIDGenerator								mspUniqueIDGenerator;
	};
}

#endif  // NodeImpl_h__
