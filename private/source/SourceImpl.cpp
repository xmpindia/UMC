// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/SourceImpl.h"
#include "utils/UMCAndXMPMapping.h"

namespace INT_UMC {

	void SourceImpl::SetClipName( const std::string & clipName ) {
		mClipName = clipName;
	}

	std::string SourceImpl::GetClipName() const  {
		return mClipName;
	}

	void SourceImpl::SyncInternalStuffToXMP() const {
		AddOrUpdateDataToXMPDOM( mClipName, kTitlePair, mXMPStructureNode );
	}

	void SourceImpl::SyncXMPToInternalStuff() {
		UpdateDataFromXMPDOM( mClipName, kTitlePair, mXMPStructureNode, kEmptyString );
	}

	bool SourceImpl::ValidateXMPNode() const {
		return true;
	}

	SourceImpl::SourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, ISource::eSourceTypes sourceType,
		const NamespacePropertyNamePair & pair )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeSource, pair ) { }

	SourceImpl::SourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, ISource::eSourceTypes,
		const spIXMPStructureNode & xmpStructureNode ) 
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeSource, xmpStructureNode ) { }

}
