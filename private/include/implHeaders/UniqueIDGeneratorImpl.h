#ifndef UniqueIDGeneratorImpl_h__
#define UniqueIDGeneratorImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations_I.h"
#include "interfaces/IUniqueIDGenerator.h"

namespace INT_UMC {
	class UniqueIDGeneratorImpl
		: public IUniqueIDGenerator
	{
	public:
		UniqueIDGeneratorImpl( const spcIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker );
		virtual std::string GenerateUniqueID( INode::eNodeTypes nodeType );

	protected:
		spcIUniqueIDAndReferenceTracker				mUniqueIDAndReferenceTracker;
		size_t										mCurrentID;
	};
}
#endif  // UniqueIDGeneratorImpl_h__
