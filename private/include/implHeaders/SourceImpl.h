#ifndef SourceImpl_h__
#define SourceImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

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
