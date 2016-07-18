#ifndef ClipShotImpl_h__
#define ClipShotImpl_h__ 1

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
			const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node );

		virtual eShotTypes GetType() const;

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

		virtual std::string Serialize() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );

		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual INT_UMC::pIUMCNodeI GetInternalNode();

		virtual INT_UMC::pcIUMCNodeI GetInternalNode() const;

		virtual void CleanUpOnRemovalFromDOM();

		virtual void SetUpOnAdditionToDOM();

		virtual void SyncXMPToInternalStuff();

		virtual void SyncInternalStuffToXMP() const;

		virtual pIUMCNode GetNode();

		virtual pcIUMCNode GetNode() const;

		virtual spIStructureNode GetXMPNode() const;

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

		virtual bool ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID );

		virtual spIUMCNode GetExternalNode();

	};
}

#endif  // ClipShotImpl_h__
