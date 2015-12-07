// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/ShotSourceImpl.h"
#include "interfaces/ISource.h"
#include "interfaces/IUniqueIDAndReferenceTracker.h"
#include "interfaces/IUMC.h"

#include "utils/Utils.h"

namespace INT_UMC {

	using AdobeXMPCommon::npos;
	ShotSourceImpl::ShotSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, IUMCNode::kNodeTypeShotSource, kShotSourcesPair )
		, mSource( source )
		, mSourceInCount( kEditUnitInCountFromBeginning )
		, mSourceDuration( kEditUnitDurationTillEnd )
		, mShotInCount( kEditUnitInCountFromBeginning ) { }

	ShotSourceImpl::ShotSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source, const spIStructureNode & node )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, IUMCNode::kNodeTypeShotSource, node )
		, mSource( source )
		, mSourceInCount( kEditUnitInCountFromBeginning )
		, mSourceDuration( kEditUnitDurationTillEnd )
		, mShotInCount( kEditUnitInCountFromBeginning ) { }

	spISource ShotSourceImpl::GetSource() {
		return mSource;
	}

	spcISource ShotSourceImpl::GetSource() const {
		return mSource;
	}

	void ShotSourceImpl::SetSourceInCount( const EditUnitInCount & sourceInCount ) {
		mSourceInCount = sourceInCount;
	}

	UMC::EditUnitInCount ShotSourceImpl::GetSourceInCount() const {
		return mSourceInCount;
	}

	void ShotSourceImpl::SetSourceDuration( const EditUnitDuration & sourceDuration ) {
		mSourceDuration = sourceDuration;
	}

	UMC::EditUnitDuration ShotSourceImpl::GetSourceDuration() const {
		return mSourceDuration;
	}

	void ShotSourceImpl::SetShotInCount( const EditUnitInCount & shotInCount ) {
		mShotInCount = shotInCount;
	}

	UMC::EditUnitInCount ShotSourceImpl::GetShotInCount() const {
		return mShotInCount;
	}

	IUMCNode::eNodeTypes ShotSourceImpl::GetNodeType() const {
		return IUMCNode::kNodeTypeShotSource;
	}

	const std::string & ShotSourceImpl::GetUniqueID() const {
		return NodeImpl::GetUniqueID();
	}

	std::string ShotSourceImpl::GetParsedID() const {
		return NodeImpl::GetParsedID();
	}

	wpcIUMCNode ShotSourceImpl::GetParentNode() const {
		return NodeImpl::GetParentNode();
	}

	wpIUMCNode ShotSourceImpl::GetParentNode() {
		return NodeImpl::GetParentNode();
	}

	spcIUMCNode ShotSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcIUMCNode();
	}

	spIUMCNode ShotSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	spcIUMCNode ShotSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spIUMCNode();
	}

	spIUMCNode ShotSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	IUMCNode::NodeList ShotSourceImpl::GetAllChildren() {
		return NodeList();
	}

	IUMCNode::cNodeList ShotSourceImpl::GetAllChildren() const {
		return cNodeList();
	}

	IUMCNode::NodeList ShotSourceImpl::GetAllDecendants() {
		return NodeList();
	}

	IUMCNode::cNodeList ShotSourceImpl::GetAllDecendants() const {
		return cNodeList();
	}

	size_t ShotSourceImpl::GetReferenceCount() const {
		return NodeImpl::GetReferenceCount();
	}

	pcIUMCNodeI ShotSourceImpl::GetInternalNode() const {
		return this;
	}

	pIUMCNodeI ShotSourceImpl::GetInternalNode() {
		return this;
	}

	bool ShotSourceImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return NodeImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	spcICustomData ShotSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return NodeImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spICustomData ShotSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return NodeImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	INT_UMC::spIStructureNode ShotSourceImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool ShotSourceImpl::SetUniqueID( const std::string & uniqueID ) {
		return NodeImpl::SetUniqueID( uniqueID );
	}

	bool ShotSourceImpl::ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) {
		return false;
	}

	UMC::spIUMCNode ShotSourceImpl::GetExternalNode() {
		return shared_from_this();
	}

	UMC::pcIUMCNode ShotSourceImpl::GetNode() const {
		return this;
	}

	UMC::pIUMCNode ShotSourceImpl::GetNode() {
		return this;
	}

	bool ShotSourceImpl::ValidateXMPNode() const {
		std::string userUniqueID;
		auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
		if ( !source ) return false;
		UpdateDataFromXMPDOM( userUniqueID, kUniqueIDPair, source, kEmptyString );
		if ( userUniqueID.empty() ) return false;
		std::string sourceID;
		mspUniqueIDAndReferenceTracker->GetUserUniqueID( userUniqueID, sourceID );
		if ( sourceID.empty() ) return false;
		return mspUniqueIDAndReferenceTracker->IsUniqueIDPresent( sourceID );
	}

	void ShotSourceImpl::SyncXMPToInternalStuff() {
		auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
		if ( source ) {
			UpdateDataFromXMPDOM( mSourceInCount, kInCountPair, source, stoi64 );
			UpdateDataFromXMPDOM( mSourceDuration, kDurationPair, source, stou64 );
		}
		UpdateDataFromXMPDOM( mShotInCount, kInCountPair, mXMPStructureNode, stoi64 );
	}

	void ShotSourceImpl::SyncInternalStuffToXMP() const {
		auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
		if ( !source ) {
			source = IStructureNode::CreateStructureNode( kSourcePair.first, npos, kSourcePair.second, npos );
			mXMPStructureNode->AppendNode( source );
		}
		AddOrUpdateDataToXMPDOM( mSourceInCount, kInCountPair, source, IgnoreEditUnitInCount );
		AddOrUpdateDataToXMPDOM( mSourceDuration, kDurationPair, source, IgnoreEditUnitDuration );
		AddOrUpdateDataToXMPDOM( mSource->GetUniqueID(), kUniqueIDPair, source );
		AddOrUpdateDataToXMPDOM( mShotInCount, kInCountPair, mXMPStructureNode, IgnoreEditUnitInCount );
	}

	void ShotSourceImpl::SetUpOnAdditionToDOM() {
		if ( !mSource ) {
			std::string userUniqueID;
			auto source = TryToGetStructNode( mXMPStructureNode, kSourcePair );
			UpdateDataFromXMPDOM( userUniqueID, kUniqueIDPair, source, kEmptyString );
			std::string sourceID;
			mspUniqueIDAndReferenceTracker->GetUserUniqueID( userUniqueID, sourceID );
			spIUMC umc = GetParentNode().lock()->GetParentNode().lock()->GetParentNode().lock()->GetParent< IUMC >().lock();
			mSource = umc->GetSource( sourceID );
		}
		mspUniqueIDAndReferenceTracker->AddReference( mSource->GetUniqueID() );
	}

	void ShotSourceImpl::CleanUpOnRemovalFromDOM() {
		mspUniqueIDAndReferenceTracker->RemoveReference( mSource->GetUniqueID() );
	}

	std::string ShotSourceImpl::Serialize() const {
		return NodeImpl::SerializeXMP();
	}

	spIShotSource CreateShotSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source, const spIStructureNode & node)
	{
		if ( node ) {
			return std::make_shared< ShotSourceImpl >( uniqueIDAndReferenceTracker,  uniqueIDGenerator, source, node );
		} else {
			return std::make_shared< ShotSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, source );
		}
	}

}
