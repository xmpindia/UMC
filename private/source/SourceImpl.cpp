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
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, IUMCNode::kNodeTypeSource, pair ) { }

	SourceImpl::SourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, ISource::eSourceTypes,
		const spIStructureNode & xmpStructureNode ) 
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, IUMCNode::kNodeTypeSource, xmpStructureNode ) { }

}
