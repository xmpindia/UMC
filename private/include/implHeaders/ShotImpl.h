#ifndef ShotImpl_h__
#define ShotImpl_h__ 1

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
#include "interfaces/IShot.h"
#include "implHeaders/NodeImpl.h"

#include <map>

namespace INT_UMC {
	using namespace UMC;

	class ShotImpl
		: public NodeImpl
	{
	public:
		ShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		ShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node );

		virtual void SetInCount( const EditUnitInCount & inCount );
		virtual EditUnitInCount GetInCount() const;

		virtual void SetDuration( const EditUnitDuration & duration );
		virtual EditUnitDuration GetDuration() const;

		virtual spIFrame AddFrame( const spISource & source, const spIUMCNode & spSelf );
		virtual spIFrame AddFrame( const std::string & buffer, const spIUMCNode & spSelf );

		virtual spIShotSource AddShotSource( const spISource & source, const spIUMCNode & spSelf );
		virtual spIShotSource AddShotSource( const std::string & buffer, const spIUMCNode & spSelf );

		virtual size_t FrameCount() const;
		virtual IShot::FrameList GetAllFrames();
		virtual IShot::cFrameList GetAllFrames() const;
		virtual spIFrame GetFrame( const std::string & uniqueID );
		virtual spcIFrame GetFrame( const std::string & uniqueID ) const;

		virtual size_t ShotSourceCount() const;
		virtual IShot::ShotSourceList GetAllShotSources();
		virtual IShot::cShotSourceList GetAllShotSources() const;
		virtual spIShotSource GetShotSource( const std::string & uniqueID );
		virtual spcIShotSource GetShotSource( const std::string & uniqueID ) const;

		virtual size_t RemoveAllShotSources();
		virtual size_t RemoveAllFrames();

		virtual size_t RemoveShotSource( const std::string & uniqueID );
		virtual size_t RemoveFrame( const std::string & uniqueID );

		spcIUMCNode GetDecendantNode( const std::string & uniqueID ) const;
		spIUMCNode GetDecendantNode( const std::string & uniqueID );

		spcIUMCNode GetChildNode( const std::string & uniqueID ) const;
		spIUMCNode GetChildNode( const std::string & uniqueID );

		IUMCNode::NodeList GetAllChildren();
		IUMCNode::cNodeList GetAllChildren() const;

		IUMCNode::NodeList GetAllDecendants();
		IUMCNode::cNodeList GetAllDecendants() const;

		void CleanUpOnRemovalFromDOM();
		void SetUpOnAdditionToDOM();

		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff( const spIUMCNode & spSelf );

		virtual bool ValidateXMPNode() const;

	protected:
		typedef std::map< const std::string, spIFrame > FrameMap;
		typedef std::map< const std::string, spIShotSource > ShotSourceMap;

		spIArrayNode			mFrames;
		spIArrayNode			mShotSources;

		spIShotSource AddShotSource( const spIStructureNode & node, const spIUMCNode & spSelf );
		spIFrame AddFrame( const spIStructureNode & node, const spIUMCNode & spSelf );

		EditUnitInCount			mInCount;
		EditUnitDuration		mDuration;
		FrameMap				mFrameMap;
		ShotSourceMap			mShotSourceMap;
	};
}

#endif  // ShotImpl_h__
