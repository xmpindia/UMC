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

#include "implHeaders/ShotImpl.h"
#include "interfaces/IShotSource.h"
#include "interfaces/IFrame.h"
#include "interfaces/IUMC.h"

#include "utils/Utils.h"
#include "utils/UMCAndXMPMapping.h"

namespace INT_UMC {

	using AdobeXMPCommon::npos;
	void ShotImpl::SetInCount( const EditUnitInCount & inCount ) {
		mInCount = inCount;
	}

	EditUnitInCount ShotImpl::GetInCount() const {
		return mInCount;
	}

	void ShotImpl::SetDuration( const EditUnitDuration & duration ) {
		mDuration = duration;
	}

	EditUnitDuration ShotImpl::GetDuration() const {
		return mDuration;
	}

	spIFrame ShotImpl::AddFrame( const spISource & source, const spIUMCNode & spSelf ) {
        if(!source){
            THROW_INPUT_CANT_BE_NULL;
        }
		spIFrame frame = CreateFrame( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, source );
		CreateEquivalentXMPNodes( mXMPStructureNode, mFrames, kFramesPair );
		AddElementToMap( mFrameMap, frame, spSelf, mFrames );
		return frame;
	}

	UMC::spIFrame ShotImpl::AddFrame( const std::string & buffer, const spIUMCNode & spSelf ) {
        if(buffer.empty())
            THROW_BUFFER_CANT_BE_EMPTY;
        
		spIStructureNode xmpNode = ParseRDF( buffer );
		return AddFrame( xmpNode, spSelf );
	}

	UMC::spIFrame ShotImpl::AddFrame( const spIStructureNode & node, const spIUMCNode & spSelf ) {
		auto actualNode = TryToGetActualNode( node, kFramesPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIFrame frame = CreateFrame( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, spISource(), node );
		CreateEquivalentXMPNodes( mXMPStructureNode, mFrames, kFramesPair );
		AddElementToMap( mFrameMap, frame, spSelf, mFrames );
		frame->GetInternalNode()->SyncXMPToUMC();
		return frame;
	}

	size_t ShotImpl::FrameCount() const {
		return mFrameMap.size();
	}

	IShot::FrameList ShotImpl::GetAllFrames() {
		return CreateListFromMap< spIFrame >( mFrameMap );
	}

	IShot::cFrameList ShotImpl::GetAllFrames() const {
		return CreateListFromMap< spcIFrame >( mFrameMap );
	}

	spIShotSource ShotImpl::AddShotSource( const spISource & source, const spIUMCNode & spSelf ) {
        if(!source){
            THROW_INPUT_CANT_BE_NULL;
        }
		spIShotSource shotSource = CreateShotSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, source );
		CreateEquivalentXMPNodes( mXMPStructureNode, mShotSources, kShotSourcesPair );
		AddElementToMap( mShotSourceMap, shotSource, spSelf, mShotSources );
		return shotSource;
	}

	UMC::spIShotSource ShotImpl::AddShotSource( const std::string & buffer, const spIUMCNode & spSelf ) {
        if(buffer.empty())
            THROW_BUFFER_CANT_BE_EMPTY;
		spIStructureNode xmpNode = ParseRDF( buffer );
		return AddShotSource( xmpNode, spSelf );
	}

	UMC::spIShotSource ShotImpl::AddShotSource( const spIStructureNode & node, const spIUMCNode & spSelf ) {
		auto actualNode = TryToGetActualNode( node, kShotSourcesPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIShotSource shotSource = CreateShotSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, spISource(), node );
		CreateEquivalentXMPNodes( mXMPStructureNode, mShotSources, kShotSourcesPair );
		AddElementToMap( mShotSourceMap, shotSource, spSelf, mShotSources );
		shotSource->GetInternalNode()->SyncXMPToUMC();
		return shotSource;
	}

	UMC::spIFrame ShotImpl::GetFrame( const std::string & uniqueID ) {
		return GetElementFromMap< spIFrame >( mFrameMap, uniqueID );
	}

	UMC::spcIFrame ShotImpl::GetFrame( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIFrame >( mFrameMap, uniqueID );
	}

	size_t ShotImpl::ShotSourceCount() const {
		return mShotSourceMap.size();
	}

	IShot::ShotSourceList ShotImpl::GetAllShotSources() {
		return CreateListFromMap< spIShotSource >( mShotSourceMap );
	}

	IShot::cShotSourceList ShotImpl::GetAllShotSources() const {
		return CreateListFromMap< spcIShotSource >( mShotSourceMap );
	}

	spIShotSource ShotImpl::GetShotSource( const std::string & uniqueID ) {
		return GetElementFromMap< spIShotSource >( mShotSourceMap, uniqueID );
	}

	spcIShotSource ShotImpl::GetShotSource( const std::string & uniqueID ) const {
		return const_cast< ShotImpl *>( this )->GetShotSource( uniqueID );
	}

	size_t ShotImpl::RemoveAllShotSources() {
		if ( SafeToClearMap( mShotSourceMap ) ) {
			return ClearMap( mShotSourceMap, mShotSources );
		}
		return 0;
	}

	size_t ShotImpl::RemoveAllFrames() {
		if ( SafeToClearMap( mFrameMap ) ) {
			return ClearMap( mFrameMap, mFrames );
		}
		return 0;
	}

	size_t ShotImpl::RemoveShotSource( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mShotSourceMap, uniqueID, mShotSources );
	}

	size_t ShotImpl::RemoveFrame( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mFrameMap, uniqueID, mFrames );
	}

	spcIUMCNode ShotImpl::GetDecendantNode( const std::string & id ) const {
		return const_cast< ShotImpl * >( this )->GetDecendantNode( id );
	}

	spIUMCNode ShotImpl::GetDecendantNode( const std::string & id ) {
		auto node = GetChildNode( id );
		if ( node ) return node;
		node = GetDecendantFromMap( mShotSourceMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap( mFrameMap, id );
		return node;
	}

	spcIUMCNode ShotImpl::GetChildNode( const std::string & id ) const {
		return const_cast< ShotImpl * >( this )->GetChildNode( id );
	}

	spIUMCNode ShotImpl::GetChildNode( const std::string & id ) {
		spIUMCNode node = GetShotSource( id );
		if ( node ) return node;
		node = GetFrame( id );
		return node;
	}

	IUMCNode::NodeList ShotImpl::GetAllChildren() {
		IUMCNode::NodeList list;
		AppendToListFromMap< spIUMCNode >( list, mShotSourceMap );
		AppendToListFromMap< spIUMCNode >( list, mFrameMap );
		return list;
	}

	IUMCNode::cNodeList ShotImpl::GetAllChildren() const {
		IUMCNode::cNodeList list;
		AppendToListFromMap< spcIUMCNode >( list, mShotSourceMap );
		AppendToListFromMap< spcIUMCNode >( list, mFrameMap );
		return list;
	}

	IUMCNode::NodeList ShotImpl::GetAllDecendants() {
		IUMCNode::NodeList list;
		AppendDecendantsFromMapToList< spIUMCNode >( list, mShotSourceMap );
		AppendDecendantsFromMapToList< spIUMCNode >( list, mFrameMap );
		return list;
	}

	IUMCNode::cNodeList ShotImpl::GetAllDecendants() const {
		IUMCNode::cNodeList list;
		AppendDecendantsFromMapToList< spcIUMCNode >( list, mShotSourceMap );
		AppendDecendantsFromMapToList< spcIUMCNode >( list, mFrameMap );
		return list;
	}

	void ShotImpl::CleanUpOnRemovalFromDOM() {
		ClearMap( mShotSourceMap, mShotSources );
		ClearMap( mFrameMap, mFrames );
	}

	void ShotImpl::SetUpOnAdditionToDOM() { }

	void ShotImpl::SyncInternalStuffToXMP() const {
		if ( mInCount != kEditUnitInCountFromBeginning || mDuration != kEditUnitDurationTillEnd ) {
			spIStructureNode record = TryToGetStructNode( mXMPStructureNode, kRecordPair );
			if ( !record ) {
				record = IStructureNode::CreateStructureNode( kRecordPair.first, npos, kRecordPair.second, npos );
				mXMPStructureNode->AppendNode( record );
			}
			AddOrUpdateDataToXMPDOM( mInCount, kInCountPair, record, IgnoreEditUnitInCount );
			AddOrUpdateDataToXMPDOM( mDuration, kDurationPair, record, IgnoreEditUnitDuration );
		}

		CallSyncUMCToXMPOnMapElements( mShotSourceMap );
		CallSyncUMCToXMPOnMapElements( mFrameMap );
	}

	void ShotImpl::SyncXMPToInternalStuff( const spIUMCNode & spSelf ) {
		mShotSources = TryToGetArrayNode( mXMPStructureNode, kShotSourcesPair );
		mFrames = TryToGetArrayNode( mXMPStructureNode, kFramesPair );

		auto record = TryToGetStructNode( mXMPStructureNode, kRecordPair );
		if ( record ) {
			UpdateDataFromXMPDOM( mInCount, kInCountPair, record, stoi64 );
			UpdateDataFromXMPDOM( mDuration, kDurationPair, record, stou64 );
		}

		PopulateMapFromXMPArrayNode< spIShotSource, ShotImpl >( this, &ShotImpl::AddShotSource, mShotSources, spSelf );
		PopulateMapFromXMPArrayNode< spIFrame, ShotImpl >( this, &ShotImpl::AddFrame, mFrames, spSelf );
	}

	bool ShotImpl::ValidateXMPNode() const {
		return true;
	}

	ShotImpl::ShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, IUMCNode::kNodeTypeShot, node )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd ) { }

	ShotImpl::ShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, IUMCNode::kNodeTypeShot, kShotsPair )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd ) { }

}

