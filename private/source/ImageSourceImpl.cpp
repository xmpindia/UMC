// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/ImageSourceImpl.h"

namespace INT_UMC {

	ImageSourceImpl::ImageSourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mSource( CreateSource( uniqueIDAndReferenceTracker, uniqueIDGenerator ) ) { }

	ISource::eSourceTypes ImageSourceImpl::GetType() const {
		return ISource::kSourceTypeImage;
	}

	void ImageSourceImpl::SetClipName( const std::string & clipName ) {
		mSource->SetClipName( clipName );
	}

	std::string ImageSourceImpl::GetClipName() const {
		return mSource->GetClipName();
	}

	INode::eNodeTypes ImageSourceImpl::GetNodeType() const {
		return mSource->GetNodeType();
	}

	const std::string & ImageSourceImpl::GetUniqueID() const {
		return mSource->GetUniqueID();
	}

	wpcINode ImageSourceImpl::GetParentNode() const {
		return mSource->GetParentNode();
	}

	wpINode ImageSourceImpl::GetParentNode() {
		return mSource->GetParentNode();
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
		return mSource->GetAllChildren();
	}

	INode::cNodeList ImageSourceImpl::GetAllChildren() const {
		return const_pointer_cast< const ISource >( mSource )->GetAllChildren();
	}

	INode::NodeList ImageSourceImpl::GetAllDecendants() {
		return mSource->GetAllDecendants();
	}

	INode::cNodeList ImageSourceImpl::GetAllDecendants() const {
		return const_pointer_cast< const ISource >( mSource )->GetAllDecendants();
	}

	size_t ImageSourceImpl::GetReferenceCount() const {
		return mSource->GetReferenceCount();
	}

	spICustomData ImageSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mSource->GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData ImageSourceImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mSource->GetCustomData( customDataNameSpace, customDataName );
	}

	bool ImageSourceImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mSource->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pINodeI ImageSourceImpl::GetInternalNode() {
		return mSource->GetInternalNode();
	}

	pcINodeI ImageSourceImpl::GetInternalNode() const {
		return mSource->GetInternalNode();
	}

	spIImageSource CreateImageSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< ImageSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}
