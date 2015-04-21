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
#include "UMCFwdDeclarations_I.h"

namespace INT_UMC {
	using namespace UMC;

	class SourceImpl
		: public ISource
	{
	public:
		SourceImpl( const std::string & uniqueID, const spUniqueIDSet & uniqueIDSet,
			const spIUniqueIDGenerator & uniqueIDGenerator, const spIUMC & parent );

		virtual const std::string & GetUniqueID() const;

		virtual void SetClipName( const std::string & clipName );
		virtual std::string GetClipName() const;

		virtual spcINode GetParentNode() const;
		virtual spINode GetParentNode();

		virtual spcINode GetDecendantNode( const std::string & id ) const;
		virtual spINode GetDecendantNode( const std::string & id );

		virtual spcINode GetChildNode( const std::string & id ) const;
		virtual spINode GetChildNode( const std::string & id );

		virtual eNodeTypes GetNodeType() const { return kNodeTypeSource; }

		virtual eSourceTypes GetType() const { return ISource::kSourceTypeAll; }

		virtual NodeList GetAllChildren();

		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();

		virtual cNodeList GetAllDecendants() const;

	protected:
		const std::string		mUniqueID;
		std::string				mClipName;

		weak_ptr< IUMC >		mwpUMC;
		spUniqueIDSet			mspUniqueIDSet;
		spIUniqueIDGenerator	mspUniqueIDGenerator;
	};
}

#endif  // SourceImpl_h__
