// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/ImageSourceImpl.h"
#include "XMPCore/Interfaces/IXMPStructureNode.h"
#include "utils/UMCAndXMPMapping.h"

namespace INT_UMC {

	ImageSourceImpl::ImageSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: SourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, kSourceTypeImage, kImageSourcesPair ) { }

	ImageSourceImpl::ImageSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
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

	INode::eNodeTypes ImageSourceImpl::GetNodeType() const {
		return SourceImpl::GetNodeType();
	}

	const std::string & ImageSourceImpl::GetUniqueID() const {
		return SourceImpl::GetUniqueID();
	}

	wpcINode ImageSourceImpl::GetParentNode() const {
		return SourceImpl::GetParentNode();
	}

	wpINode ImageSourceImpl::GetParentNode() {
		return SourceImpl::GetParentNode();
	}

	spcINode ImageSourceImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return spcINode();
	}

	spINode ImageSourceImpl::GetDecendantNode( const std::string & uniqueID ) {
		return spINode();
	}

	spcINode ImageSourceImpl::GetChildNode( const std::string & uniqueID ) const {
		return spINode();
	}

	spINode ImageSourceImpl::GetChildNode( const std::string & uniqueID ) {
		return spINode();
	}

	INode::NodeList ImageSourceImpl::GetAllChildren() {
		return NodeList();
	}

	INode::cNodeList ImageSourceImpl::GetAllChildren() const {
		return cNodeList();
	}

	INode::NodeList ImageSourceImpl::GetAllDecendants() {
		return NodeList();
	}

	INode::cNodeList ImageSourceImpl::GetAllDecendants() const {
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

	pINodeI ImageSourceImpl::GetInternalNode() {
		return this;
	}

	pcINodeI ImageSourceImpl::GetInternalNode() const {
		return this;
	}

	NS_XMPCORE::spIXMPStructureNode ImageSourceImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	bool ImageSourceImpl::ValidateXMPNode() const {
		if ( SourceImpl::ValidateXMPNode() )
			return true;
		return false;
	}

	UMC::pINode ImageSourceImpl::GetNode() {
		return this;
	}

	UMC::pcINode ImageSourceImpl::GetNode() const {
		return this;
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
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< ImageSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		} else {
			return std::make_shared< ImageSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}

}
