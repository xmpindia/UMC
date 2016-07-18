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
#include "implHeaders/TransitionShotImpl.h"
#include "interfaces/IShotSource.h"
#include "interfaces/IFrame.h"
#include "utils/Utils.h"

namespace INT_UMC {

	TransitionShotImpl::TransitionShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: ShotImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator ) { }

	TransitionShotImpl::TransitionShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
		: ShotImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, node ) { }

	IShot::eShotTypes TransitionShotImpl::GetType() const {
		return IShot::kShotTypeTransition;
	}

	IUMCNode::eNodeTypes TransitionShotImpl::GetNodeType() const {
		return IUMCNode::kNodeTypeShot;
	}

	const std::string & TransitionShotImpl::GetUniqueID() const {
		return ShotImpl::GetUniqueID();
	}

	std::string TransitionShotImpl::GetParsedID() const {
		return ShotImpl::GetParsedID();
	}

	UMC::wpcIUMCNode TransitionShotImpl::GetParentNode() const {
		return ShotImpl::GetParentNode();
	}

	UMC::wpIUMCNode TransitionShotImpl::GetParentNode() {
		return ShotImpl::GetParentNode();
	}

	UMC::spcIUMCNode TransitionShotImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return ShotImpl::GetDecendantNode( uniqueID );
	}

	UMC::spIUMCNode TransitionShotImpl::GetDecendantNode( const std::string & uniqueID ) {
		return ShotImpl::GetDecendantNode( uniqueID );
	}

	UMC::spcIUMCNode TransitionShotImpl::GetChildNode( const std::string & uniqueID ) const {
		return ShotImpl::GetChildNode( uniqueID );
	}

	UMC::spIUMCNode TransitionShotImpl::GetChildNode( const std::string & uniqueID ) {
		return ShotImpl::GetChildNode( uniqueID );
	}

	IUMCNode::NodeList TransitionShotImpl::GetAllChildren() {
		return ShotImpl::GetAllChildren();
	}

	IUMCNode::cNodeList TransitionShotImpl::GetAllChildren() const {
		return ShotImpl::GetAllChildren();
	}

	IUMCNode::NodeList TransitionShotImpl::GetAllDecendants() {
		return ShotImpl::GetAllDecendants();
	}

	IUMCNode::cNodeList TransitionShotImpl::GetAllDecendants() const {
		return ShotImpl::GetAllDecendants();
	}

	size_t TransitionShotImpl::GetReferenceCount() const {
		return ShotImpl::GetReferenceCount();
	}

	std::string TransitionShotImpl::Serialize() const {
		return ShotImpl::SerializeXMP();
	}

	UMC::spICustomData TransitionShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return ShotImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	UMC::spcICustomData TransitionShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return ShotImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	bool TransitionShotImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return ShotImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	INT_UMC::pIUMCNodeI TransitionShotImpl::GetInternalNode() {
		return this;
	}

	INT_UMC::pcIUMCNodeI TransitionShotImpl::GetInternalNode() const {
		return this;
	}

	void TransitionShotImpl::CleanUpOnRemovalFromDOM() {
		ShotImpl::CleanUpOnRemovalFromDOM();
	}

	void TransitionShotImpl::SetUpOnAdditionToDOM() {
		ShotImpl::SetUpOnAdditionToDOM();
	}

	void TransitionShotImpl::SyncXMPToInternalStuff() {
		ShotImpl::SyncXMPToInternalStuff( shared_from_this() );
	}

	void TransitionShotImpl::SyncInternalStuffToXMP() const {
		ShotImpl::SyncInternalStuffToXMP();
	}

	UMC::pIUMCNode TransitionShotImpl::GetNode() {
		return this;
	}

	UMC::pcIUMCNode TransitionShotImpl::GetNode() const {
		return this;
	}

	INT_UMC::spIStructureNode TransitionShotImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	TransitionShotImpl::~TransitionShotImpl() { }

	bool TransitionShotImpl::SetUniqueID( const std::string & uniqueID ) {
		return NodeImpl::SetUniqueID( uniqueID );
	}

	bool TransitionShotImpl::ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) {
		switch ( childNode->GetNodeType() ) {
		case IUMCNode::kNodeTypeFrame:
		{
			spIFrame frameChild = ConvertNode< IFrame >( childNode );
			ChangeUniqueIDOfChildNode< IFrame >( mFrameMap, frameChild, newUniqueID, mFrames, shared_from_this() );
			return true;
		}
		break;

		case IUMCNode::kNodeTypeShotSource:
		{
			spIShotSource shotSourceChild = ConvertNode< IShotSource >( childNode );
			ChangeUniqueIDOfChildNode< IShotSource >( mShotSourceMap, shotSourceChild, newUniqueID, mFrames, shared_from_this() );
			return true;
		}
		break;

		default:
			return false;
		}
		return false;
	}

	UMC::spIUMCNode TransitionShotImpl::GetExternalNode() {
		return shared_from_this();
	}

	size_t TransitionShotImpl::RemoveShotSource( const std::string & uniqueID ) {
		return ShotImpl::RemoveShotSource( uniqueID );
	}

	size_t TransitionShotImpl::RemoveFrame( const std::string & uniqueID ) {
		return ShotImpl::RemoveFrame( uniqueID );
	}

	size_t TransitionShotImpl::RemoveAllFrames() {
		return ShotImpl::RemoveAllFrames();
	}

	size_t TransitionShotImpl::RemoveAllShotSources() {
		return ShotImpl::RemoveAllShotSources();
	}

	UMC::spcIShotSource TransitionShotImpl::GetShotSource( const std::string & uniqueID ) const {
		return ShotImpl::GetShotSource( uniqueID );
	}

	UMC::spIShotSource TransitionShotImpl::GetShotSource( const std::string & uniqueID ) {
		return ShotImpl::GetShotSource( uniqueID );
	}

	IShot::cShotSourceList TransitionShotImpl::GetAllShotSources() const {
		return ShotImpl::GetAllShotSources();
	}

	IShot::ShotSourceList TransitionShotImpl::GetAllShotSources() {
		return ShotImpl::GetAllShotSources();
	}

	size_t TransitionShotImpl::ShotSourceCount() const {
		return ShotImpl::ShotSourceCount();
	}

	UMC::spcIFrame TransitionShotImpl::GetFrame( const std::string & uniqueID ) const {
		return ShotImpl::GetFrame( uniqueID );
	}

	UMC::spIFrame TransitionShotImpl::GetFrame( const std::string & uniqueID ) {
		return ShotImpl::GetFrame( uniqueID );
	}

	IShot::cFrameList TransitionShotImpl::GetAllFrames() const {
		return ShotImpl::GetAllFrames();
	}

	IShot::FrameList TransitionShotImpl::GetAllFrames() {
		return ShotImpl::GetAllFrames();
	}

	size_t TransitionShotImpl::FrameCount() const {
		return ShotImpl::FrameCount();
	}

	UMC::spIShotSource TransitionShotImpl::AddShotSource( const std::string & buffer ) {
		return ShotImpl::AddShotSource( buffer, shared_from_this() );
	}

	UMC::spIShotSource TransitionShotImpl::AddShotSource( const spISource & source ) {
		return ShotImpl::AddShotSource( source, shared_from_this() );
	}

	UMC::spIFrame TransitionShotImpl::AddFrame( const std::string & buffer ) {
		return ShotImpl::AddFrame( buffer, shared_from_this() );
	}

	UMC::spIFrame TransitionShotImpl::AddFrame( const spISource & source ) {
		return ShotImpl::AddFrame( source, shared_from_this() );
	}

	UMC::EditUnitDuration TransitionShotImpl::GetDuration() const {
		return ShotImpl::GetDuration();
	}

	void TransitionShotImpl::SetDuration( const EditUnitDuration & duration ) {
		return ShotImpl::SetDuration( duration );
	}

	UMC::EditUnitInCount TransitionShotImpl::GetInCount() const {
		return ShotImpl::GetInCount();
	}

	void TransitionShotImpl::SetInCount( const EditUnitInCount & inCount ) {
		return ShotImpl::SetInCount( inCount );
	}

	spITransitionShot CreateTransitionShot( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< TransitionShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		} else {
			return std::make_shared< TransitionShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}

}

