#ifndef NodeImpl_h__
#define NodeImpl_h__ 1

/*
*  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
*  This file is licensed to you under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License. You may obtain a copy
*  of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software distributed under
*  the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
*  OF ANY KIND, either express or implied. See the License for the specific language
*  governing permissions and limitations under the License.
*
*/
#include "UMCFwdDeclarations_I.h"
#include "interfaces/IUMCNodeI.h"
#include "interfaces/IUMCNode.h"
#include "utils/UMCAndXMPMapping.h"
#include <map>

namespace INT_UMC {

	class NodeImpl
		: public IUMCNodeI
	{
	public:
		NodeImpl();
		NodeImpl( const spIStructureNode & xmpStructureNode );

		NodeImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, IUMCNode::eNodeTypes nodeType,
			const NamespacePropertyNamePair & namespacePropertyNamePair );

		NodeImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, IUMCNode::eNodeTypes nodeType,
			const spIStructureNode & xmpStructureNode );

		void Init( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, IUMCNode::eNodeTypes nodeType );

		virtual const std::string & GetUniqueID() const;
		virtual std::string GetParsedID() const;
		virtual bool SetUniqueID( const std::string & newUniqueID );
		virtual void ChangeUniqueID( const std::string & newUniqueID );

		virtual wpcIUMCNode GetParentNode() const;
		virtual wpIUMCNode GetParentNode();

		virtual size_t GetReferenceCount() const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual void RemoveFromDOM();
		virtual void AddToDOM( const spIUMCNode & parent );

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

		AdobeXMPCore::spIStructureNode						mXMPStructureNode;
		AdobeXMPCore::spIStructureNode						mExtensionNode;
		std::string											mUniqueID;
		std::map< std::string, spICustomData >				mCustomDataMap;

		weak_ptr< IUMCNode >									mwpParentNode;
		spIUniqueIDAndReferenceTracker						mspUniqueIDAndReferenceTracker;
		spIUniqueIDGenerator								mspUniqueIDGenerator;
		size_t												mIndex;
	};
}

#endif  // NodeImpl_h__
