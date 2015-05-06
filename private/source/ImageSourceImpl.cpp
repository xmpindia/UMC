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
		: mSourceImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator ) {}

	ISource::eSourceTypes ImageSourceImpl::GetType() const {
		return ISource::kSourceTypeImage;
	}

	void ImageSourceImpl::SetClipName( const std::string & clipName ) {
		mSourceImpl.SetClipName( clipName );
	}

	std::string ImageSourceImpl::GetClipName() const {
		return mSourceImpl.GetClipName();
	}

	INode::eNodeTypes ImageSourceImpl::GetNodeType() const {
		return mSourceImpl.GetNodeType();
	}

	const std::string & ImageSourceImpl::GetUniqueID() const {
		return mSourceImpl.GetUniqueID();
	}

	spcINode ImageSourceImpl::GetParentNode() const {
		return mSourceImpl.GetParentNode();
	}

	spINode ImageSourceImpl::GetParentNode() {
		return mSourceImpl.GetParentNode();
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
		return mSourceImpl.GetAllChildren();
	}

	INode::cNodeList ImageSourceImpl::GetAllChildren() const {
		return mSourceImpl.GetAllChildren();
	}

	INode::NodeList ImageSourceImpl::GetAllDecendants() {
		return mSourceImpl.GetAllDecendants();
	}

	INode::cNodeList ImageSourceImpl::GetAllDecendants() const {
		return mSourceImpl.GetAllDecendants();
	}

	size_t ImageSourceImpl::GetReferenceCount() const {
		return mSourceImpl.GetReferenceCount();
	}

	void ImageSourceImpl::RemoveFromDOM() {
		return mSourceImpl.RemoveFromDOM();
	}

	void ImageSourceImpl::AddToDOM( const spINode & parent ) {
		return mSourceImpl.AddToDOM( parent );
	}

	spIImageSource CreateImageSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< ImageSourceImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}
