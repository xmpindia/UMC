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


#include "implHeaders/ImageSourceImpl.h"
#include "XMPCore/Interfaces/IStructureNode.h"
#include "utils/UMCAndXMPMapping.h"

namespace INT_UMC {

	ImageSourceImpl::ImageSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, kSourceTypeImage, kImageSourcesPair ) { }

	ImageSourceImpl::ImageSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, kSourceTypeImage, node ) { }

	ISource::eSourceTypes ImageSourceImpl::GetType() const {
		return ISource::kSourceTypeImage;
	}

	void ImageSourceImpl::SetClipName( const std::string & clipName ) {
		SourceImpl::SetClipName( clipName );
	}

	std::string ImageSourceImpl::GetClipName() const {
		return SourceImpl::GetClipName();
	}

	IUMCNode::eNodeTypes ImageSourceImpl::GetNodeType() const {
		return SourceImpl::GetNodeType();
	}

	const std::string & ImageSourceImpl::GetUniqueID() const {
		return SourceImpl::GetUniqueID();
	}

	std::string ImageSourceImpl::GetParsedID() const {
		return SourceImpl::GetParsedID();
	}

	wpcIUMCNode ImageSourceImpl::GetParentNode() const {
		return SourceImpl::GetParentNode();
	}

	wpIUMCNode ImageSourceImpl::GetParentNode() {
		return SourceImpl::GetParentNode();
	}

	spcIUMCNode ImageSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcIUMCNode();
	}

	spIUMCNode ImageSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	spcIUMCNode ImageSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spIUMCNode();
	}

	spIUMCNode ImageSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spIUMCNode();
	}

	IUMCNode::NodeList ImageSourceImpl::GetAllChildren() {
		return NodeList();
	}

	IUMCNode::cNodeList ImageSourceImpl::GetAllChildren() const {
		return cNodeList();
	}

	IUMCNode::NodeList ImageSourceImpl::GetAllDecendants() {
		return NodeList();
	}

	IUMCNode::cNodeList ImageSourceImpl::GetAllDecendants() const {
		return cNodeList();
	}

	size_t ImageSourceImpl::GetReferenceCount() const {
		return SourceImpl::GetReferenceCount();
	}

	spICustomData ImageSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return SourceImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData ImageSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return SourceImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	bool ImageSourceImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return SourceImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pIUMCNodeI ImageSourceImpl::GetInternalNode() {
		return this;
	}

	pcIUMCNodeI ImageSourceImpl::GetInternalNode() const {
		return this;
	}

	AdobeXMPCore::spIStructureNode ImageSourceImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool ImageSourceImpl::ValidateXMPNode() const {
		if ( SourceImpl::ValidateXMPNode() )
			return true;
		return false;
	}

	UMC::pIUMCNode ImageSourceImpl::GetNode() {
		return this;
	}

	UMC::pcIUMCNode ImageSourceImpl::GetNode() const {
		return this;
	}

	bool ImageSourceImpl::SetUniqueID( const std::string & uniqueID ) {
		return NodeImpl::SetUniqueID( uniqueID );
	}

	bool ImageSourceImpl::ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) {
		return false;
	}

	UMC::spIUMCNode ImageSourceImpl::GetExternalNode() {
		return shared_from_this();
	}

	void ImageSourceImpl::SyncXMPToInternalStuff() {
		SourceImpl::SyncXMPToInternalStuff();
	}

	void ImageSourceImpl::SyncInternalStuffToXMP() const {
		SourceImpl::SyncInternalStuffToXMP();
	}

	void ImageSourceImpl::SetUpOnAdditionToDOM() { }

	void ImageSourceImpl::CleanUpOnRemovalFromDOM() { }

	std::string ImageSourceImpl::Serialize() const {
		return SerializeXMP();
	}

	spIImageSource CreateImageSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< ImageSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		} else {
			return std::make_shared< ImageSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}

}
