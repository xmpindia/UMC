#ifndef IUMCNodeI_h__
#define IUMCNodeI_h__ 1
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

#include "UMCFwdDeclarations_I.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"

namespace INT_UMC {

	using namespace AdobeXMPCore;

	class IUMCNodeI {
	public:
		virtual const std::string & GetUniqueID() const = 0;
		virtual std::string GetParsedID() const = 0;

		virtual pIUMCNode GetNode() = 0;
		virtual pcIUMCNode GetNode() const = 0;

		virtual wpcIUMCNode GetParentNode() const = 0;
		virtual wpIUMCNode GetParentNode() = 0;

		virtual size_t GetReferenceCount() const = 0;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) = 0;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) = 0;
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const = 0;

		virtual void RemoveFromDOM() = 0;
		virtual void AddToDOM( const spIUMCNode & parent ) = 0;

		std::string SerializeXMP() const ;

		virtual spIStructureNode GetXMPNode() const = 0;
		virtual void SyncUMCToXMP() const = 0;
		virtual void SyncXMPToUMC() = 0;
		virtual void SetIndex( size_t index ) = 0;
		virtual size_t GetIndex() const = 0;
		virtual bool ChangeChildUniqueID( const spIUMCNode & childNode, const std::string & newUniqueID ) = 0;
		virtual void ChangeUniqueID( const std::string & newUniqueID ) = 0;

		virtual spIUMCNode GetExternalNode() = 0;
		spcIUMCNode GetExternalNode() const {
			return const_cast< pIUMCNodeI >( this )->GetExternalNode();
		}

		
		virtual spIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() = 0;
		virtual spcIUniqueIDAndReferenceTracker GetUniqueIDAndReferenceTracker() const = 0;

		virtual spIUniqueIDGenerator GetUniqueIDGenerator() = 0;
		virtual spcIUniqueIDGenerator GetUniqueIDGenerator() const = 0;

		virtual ~IUMCNodeI() = 0;
	};

}

#endif  // IUMCNodeI_h__
