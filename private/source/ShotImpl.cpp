// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/ShotImpl.h"
#include "interfaces/IShotSource.h"
#include "interfaces/IFrame.h"
#include "interfaces/IUMC.h"

#include "utils/Utils.h"
#include "utils/UMCAndXMPMapping.h"

namespace INT_UMC {

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

	spIFrame ShotImpl::AddFrame( const spISource & source, const spINode & spSelf ) {
		spIFrame frame = CreateFrame( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, source );
		CreateEquivalentXMPNodes( mXMPStructureNode, mFrames, kFramesPair );
		AddElementToMap( mFrameMap, frame, spSelf, mFrames );
		return frame;
	}

	UMC::spIFrame ShotImpl::AddFrame( const std::string & buffer, const spINode & spSelf ) {
		spIXMPStructureNode xmpNode = ParseRDF( buffer );
		return AddFrame( xmpNode, spSelf );
	}

	UMC::spIFrame ShotImpl::AddFrame( const spIXMPStructureNode & node, const spINode & spSelf ) {
		auto actualNode = TryToGetActualNode( node, kFramesPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIFrame frame = CreateFrame( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, spISource(), node );
		CreateEquivalentXMPNodes( mXMPStructureNode, mFrames, kFramesPair );
		AddElementToMap( mFrameMap, frame, spSelf, mFrames );
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

	spIShotSource ShotImpl::AddShotSource( const spISource & source, const spINode & spSelf ) {
		spIShotSource shotSource = CreateShotSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, source );
		CreateEquivalentXMPNodes( mXMPStructureNode, mShotSources, kShotSourcesPair );
		AddElementToMap( mShotSourceMap, shotSource, spSelf, mShotSources );
		return shotSource;
	}

	UMC::spIShotSource ShotImpl::AddShotSource( const std::string & buffer, const spINode & spSelf ) {
		spIXMPStructureNode xmpNode = ParseRDF( buffer );
		return AddShotSource( xmpNode, spSelf );
	}

	UMC::spIShotSource ShotImpl::AddShotSource( const spIXMPStructureNode & node, const spINode & spSelf ) {
		auto actualNode = TryToGetActualNode( node, kShotSourcesPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIShotSource shotSource = CreateShotSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, spISource(), node );
		CreateEquivalentXMPNodes( mXMPStructureNode, mShotSources, kShotSourcesPair );
		AddElementToMap( mShotSourceMap, shotSource, spSelf, mShotSources );
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

	spcINode ShotImpl::GetDecendantNode( const std::string & id ) const {
		return const_cast< ShotImpl * >( this )->GetDecendantNode( id );
	}

	spINode ShotImpl::GetDecendantNode( const std::string & id ) {
		auto node = GetChildNode( id );
		if ( node ) return node;
		node = GetDecendantFromMap( mShotSourceMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap( mFrameMap, id );
		return node;
	}

	spcINode ShotImpl::GetChildNode( const std::string & id ) const {
		return const_cast< ShotImpl * >( this )->GetChildNode( id );
	}

	spINode ShotImpl::GetChildNode( const std::string & id ) {
		spINode node = GetShotSource( id );
		if ( node ) return node;
		node = GetFrame( id );
		return node;
	}

	INode::NodeList ShotImpl::GetAllChildren() {
		INode::NodeList list;
		AppendToListFromMap< spINode >( list, mShotSourceMap );
		AppendToListFromMap< spINode >( list, mFrameMap );
		return list;
	}

	INode::cNodeList ShotImpl::GetAllChildren() const {
		INode::cNodeList list;
		AppendToListFromMap< spcINode >( list, mShotSourceMap );
		AppendToListFromMap< spcINode >( list, mFrameMap );
		return list;
	}

	INode::NodeList ShotImpl::GetAllDecendants() {
		INode::NodeList list;
		AppendDecendantsFromMapToList< spINode >( list, mShotSourceMap );
		AppendDecendantsFromMapToList< spINode >( list, mFrameMap );
		return list;
	}

	INode::cNodeList ShotImpl::GetAllDecendants() const {
		INode::cNodeList list;
		AppendDecendantsFromMapToList< spcINode >( list, mShotSourceMap );
		AppendDecendantsFromMapToList< spcINode >( list, mFrameMap );
		return list;
	}

	void ShotImpl::CleanUpOnRemovalFromDOM() {
		ClearMap( mShotSourceMap, mShotSources );
		ClearMap( mFrameMap, mFrames );
	}

	void ShotImpl::SetUpOnAdditionToDOM() { }

	void ShotImpl::SyncInternalStuffToXMP() const {
		if ( mInCount != kEditUnitInCountFromBeginning || mDuration != kEditUnitDurationTillEnd ) {
			spIXMPStructureNode record = TryToGetStructNode( mXMPStructureNode, kRecordPair );
			if ( !record ) {
				record = IXMPStructureNode::CreateStructureNode( kRecordPair.first, kRecordPair.second );
				mXMPStructureNode->AppendNode( record );
			}
			AddOrUpdateDataToXMPDOM( mInCount, kInCountPair, record, IgnoreEditUnitInCount );
			AddOrUpdateDataToXMPDOM( mDuration, kDurationPair, record, IgnoreEditUnitDuration );
		}

		CallSyncUMCToXMPOnMapElements( mShotSourceMap );
		CallSyncUMCToXMPOnMapElements( mFrameMap );
	}

	void ShotImpl::SyncXMPToInternalStuff( const spINode & spSelf ) {
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
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeShot, node )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd ) { }

	ShotImpl::ShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeShot, kShotsPair )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd ) { }

}

