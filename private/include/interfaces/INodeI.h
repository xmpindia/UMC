#ifndef INodeI_h__
#define INodeI_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations_I.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"

namespace INT_UMC {

	using namespace NS_XMPCORE;

	class INodeI {
	public:
		virtual void SetExtensionNode( const spIXMPStructureNode & structureNode ) = 0;
		virtual spIXMPStructureNode GetExtensionNode( bool create = false ) const = 0;
		virtual spIXMPStructureNode GetMergedExtensionNode() const = 0;
		virtual void RemoveFromDOM() = 0;
		virtual void AddToDOM( const spINode & parent ) = 0;

		virtual spIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() = 0;
		virtual spcIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() const = 0;

		virtual spIUniqueIDGenerator GetUniqueIDGenerator() = 0;
		virtual spcIUniqueIDGenerator GetUniqueIDGenerator() const = 0;
	};
}

#endif  // INodeI_h__
