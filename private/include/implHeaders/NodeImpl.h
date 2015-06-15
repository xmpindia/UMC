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
#include "interfaces/INodeI.h"
#include "interfaces/INode.h"
#include "utils/UMCAndXMPMapping.h"
#include <map>

namespace INT_UMC {

	class NodeImpl
		: public INodeI
	{
	public:
		NodeImpl();
		NodeImpl( const spIXMPStructureNode & xmpStructureNode );

		NodeImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, INode::eNodeTypes nodeType,
			const NamespacePropertyNamePair & namespacePropertyNamePair );

		NodeImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, INode::eNodeTypes nodeType,
			const spIXMPStructureNode & xmpStructureNode );

		void Init( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, INode::eNodeTypes nodeType );

		virtual const std::string & GetUniqueID() const;

		virtual wpcINode GetParentNode() const;
		virtual wpINode GetParentNode();

		virtual size_t GetReferenceCount() const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual void RemoveFromDOM();
		virtual void AddToDOM( const spINode & parent );

		virtual void SyncUMCToXMP() const;
		virtual void SyncXMPToUMC();

		virtual spIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker();
		virtual spcIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() const;

		virtual spIUniqueIDGenerator GetUniqueIDGenerator();
		virtual spcIUniqueIDGenerator GetUniqueIDGenerator() const;

		virtual ~NodeImpl();

	protected:
		virtual void CleanUpOnRemovalFromDOM() = 0;
		virtual void SetUpOnAdditionToDOM() = 0;;
		virtual void SyncInternalStuffToXMP() const = 0;
		virtual void SyncXMPToInternalStuff() = 0;
		virtual bool ValidateXMPNode() const = 0;

		void CreateExtensionNodeIfRequired();

		std::string GetCombinedString( const std::string & nameSpace, const std::string & name ) const;
		bool GetSplitStrings( const std::string & combinedString, std::string & nameSpace, std::string & name ) const;

		virtual void SetIndex( size_t index );
		virtual size_t GetIndex() const;

		NS_XMPCORE::spIXMPStructureNode						mXMPStructureNode;
		NS_XMPCORE::spIXMPStructureNode						mExtensionNode;
		std::string											mUniqueID;
		std::map< std::string, spICustomData >				mCustomDataMap;

		weak_ptr< INode >									mwpParentNode;
		spIUniqueIDAndReferenceTracker						mspUniqueIDAndReferenceTracker;
		spIUniqueIDGenerator								mspUniqueIDGenerator;
		size_t												mIndex;
	};
}

#endif  // NodeImpl_h__
