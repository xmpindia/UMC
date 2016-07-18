#ifndef AudioSourceImpl_h__
#define AudioSourceImpl_h__ 1
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

#include "interfaces/IAudioSource.h"
#include "implHeaders/SourceImpl.h"

namespace INT_UMC {
	class AudioSourceImpl
		: public IAudioSource
		, public SourceImpl
		, public enable_shared_from_this < AudioSourceImpl >
	{
	public:
		AudioSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		AudioSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node );

		virtual void SetAudioEditRate( const EditRate & editRate );
		virtual EditRate GetAudioEditRate() const;

		virtual void SetInCount( const EditUnitInCount & inCount );
		virtual EditUnitInCount GetInCount() const;

		virtual void SetDuration( const EditUnitDuration & duration );
		virtual EditUnitDuration GetDuration() const;

		virtual void SetTimeCode( const TimeCode & timeCode );
		virtual TimeCode GetTimeCode() const;

		virtual eSourceTypes GetType() const;

		virtual void SetClipName( const std::string & clipName );
		virtual std::string GetClipName() const;

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

		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff();

		virtual spIStructureNode GetXMPNode() const;

		virtual bool ValidateXMPNode() const;

		virtual pIUMCNode GetNode();

		virtual pcIUMCNode GetNode() const;

		virtual bool ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID );
		virtual spIUMCNode GetExternalNode();
		virtual bool SetUniqueID( const std::string & uniqueID );

	protected:
		EditUnitInCount				mInCount;
		EditUnitDuration			mDuration;
		EditRate					mAudioEditRate;
		TimeCode					mTimeCode;

	};
}

#endif  // AudioSourceImpl_h__
