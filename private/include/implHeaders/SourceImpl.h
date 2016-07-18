#ifndef SourceImpl_h__
#define SourceImpl_h__ 1

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

#include "interfaces/ISource.h"
#include "implHeaders/NodeImpl.h"

namespace INT_UMC {
	using namespace UMC;

	class SourceImpl
		: public NodeImpl
	{
	public:
		SourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, ISource::eSourceTypes sourceType,
			const NamespacePropertyNamePair & pair );

		SourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator, ISource::eSourceTypes sourceType,
			const spIStructureNode & xmpStructureNode );

		virtual void SetClipName( const std::string & clipName );
		virtual std::string GetClipName() const;

		virtual IUMCNode::eNodeTypes GetNodeType() const { return IUMCNode::kNodeTypeSource; }

		virtual void SyncInternalStuffToXMP() const = 0;
		virtual void SyncXMPToInternalStuff() = 0;

		virtual bool ValidateXMPNode() const = 0;

	protected:
		std::string							mClipName;

	};
}

#endif  // SourceImpl_h__
