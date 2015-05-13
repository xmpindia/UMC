#ifndef CustomDataHandlerImpl_h__
#define CustomDataHandlerImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ICustomDataHandler.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"

#include <stack>

namespace INT_UMC {

	using namespace UMC;
	using namespace NS_XMPCORE;

	class CustomDataHandlerImpl
		: public ICustomDataHandler
	{
	public:
		CustomDataHandlerImpl( const spcICustomData & customData, const std::string & customDataNameSpace,
			const std::string & customDataName, const spIXMPStructureNode & baseNode );

		virtual bool BeginCustomData();
		virtual spICustomData EndCustomData();

		virtual bool BeginStructure( const std::string & structureName );
		virtual bool EndStructure( const std::string & structureName );

		virtual bool BeginArray( const std::string & arrayName );
		virtual bool EndArray( const std::string & arrayName );

		virtual bool AddKeyValuePair( const std::string & key, const std::string & value );
		virtual bool Serialize( const spICustomData & data, const spICustomDataHandler & customDataCreator ) const;

	protected:
		struct Parent {
			Parent( const spIXMPStructureNode & structureNode );
			Parent( const spIXMPArrayNode & arrayNode );
			spIXMPStructureNode mStructNode;
			spIXMPArrayNode mArrayNode;
			bool mIsArray;
		};

		std::stack< Parent >	mParents;
		const std::string &		mNameSpace;
		spIXMPStructureNode		mBaseNode;
	};
}

#endif  // CustomDataHandlerImpl_h__
