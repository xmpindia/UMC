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
		virtual const std::string & GetUniqueID() const = 0;
		virtual std::string GetParsedID() const = 0;

		virtual pINode GetNode() = 0;
		virtual pcINode GetNode() const = 0;

		virtual wpcINode GetParentNode() const = 0;
		virtual wpINode GetParentNode() = 0;

		virtual size_t GetReferenceCount() const = 0;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) = 0;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) = 0;
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const = 0;

		virtual void RemoveFromDOM() = 0;
		virtual void AddToDOM( const spINode & parent ) = 0;

		std::string SerializeXMP() const ;

		virtual spIXMPStructureNode GetXMPNode() const = 0;
		virtual void SyncUMCToXMP() const = 0;
		virtual void SyncXMPToUMC() = 0;
		virtual void SetIndex( size_t index ) = 0;
		virtual size_t GetIndex() const = 0;

		
		virtual spIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() = 0;
		virtual spcIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() const = 0;

		virtual spIUniqueIDGenerator GetUniqueIDGenerator() = 0;
		virtual spcIUniqueIDGenerator GetUniqueIDGenerator() const = 0;

		virtual ~INodeI() = 0;
	};

}

#endif  // INodeI_h__
