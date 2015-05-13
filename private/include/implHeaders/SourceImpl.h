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
#include "interfaces/INodeI.h"

namespace INT_UMC {
	using namespace UMC;

	class SourceImpl
		: public ISource
	{
	public:
		SourceImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

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

		virtual size_t GetReferenceCount() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );

		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const spICustomData & customData );

		virtual INT_UMC::pINodeI GetInternalNode();

		virtual INT_UMC::pcINodeI GetInternalNode() const;

	protected:
		spINode								mNode;
		std::string							mClipName;

		friend class VideoFrameSourceImpl;
	};
}

#endif  // SourceImpl_h__
