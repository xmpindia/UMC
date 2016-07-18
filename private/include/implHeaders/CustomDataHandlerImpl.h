#ifndef CustomDataHandlerImpl_h__
#define CustomDataHandlerImpl_h__ 1
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

#include "interfaces/ICustomDataHandler.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"

#include <stack>

namespace INT_UMC {

	using namespace UMC;
	using namespace AdobeXMPCore;

	class CustomDataHandlerImpl
		: public ICustomDataHandler
	{
	public:
		CustomDataHandlerImpl( const spcICustomData & customData, const std::string & customDataNameSpace,
			const std::string & customDataName, const spIStructureNode & baseNode );

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
			Parent( const spIStructureNode & structureNode );
			Parent( const spIArrayNode & arrayNode );
			spIStructureNode mStructNode;
			spIArrayNode mArrayNode;
			bool mIsArray;
		};

		std::stack< Parent >	mParents;
		const std::string &		mNameSpace;
		spIStructureNode		mBaseNode;
	};
}

#endif  // CustomDataHandlerImpl_h__
