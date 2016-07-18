#ifndef ShotSourceImpl_h__
#define ShotSourceImpl_h__ 1

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
			const spIStructureNode & node );

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

		virtual wpcIUMCNode GetParentNode() const;
		virtual wpIUMCNode GetParentNode();

		virtual spcIUMCNode GetDecendantNode( const std::string & uniqueID ) const;
		virtual spIUMCNode GetDecendantNode( const std::string & uniqueID );

		virtual spcIUMCNode GetChildNode( const std::string & uniqueID ) const;
		virtual spIUMCNode GetChildNode( const std::string & uniqueID );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual size_t GetReferenceCount() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual INT_UMC::pIUMCNodeI GetInternalNode();
		virtual INT_UMC::pcIUMCNodeI GetInternalNode() const;

		virtual std::string Serialize() const;

		virtual void CleanUpOnRemovalFromDOM();
		virtual void SetUpOnAdditionToDOM();
		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff();
		virtual bool ValidateXMPNode() const;

		virtual pIUMCNode GetNode();
		virtual pcIUMCNode GetNode() const;

		virtual spIStructureNode GetXMPNode() const;

		virtual bool SetUniqueID( const std::string & uniqueID );
		virtual bool ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID );
		virtual spIUMCNode GetExternalNode();

	private:
		spISource				mSource;
		EditUnitInCount			mSourceInCount;
		EditUnitDuration		mSourceDuration;
		EditUnitInCount			mShotInCount;
	};
}
#endif  // ShotSourceImpl_h__
