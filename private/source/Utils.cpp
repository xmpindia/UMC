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


#include "utils/Utils.h"
#include "interfaces/IUMCNode.h"
#include "XMPCore/Interfaces/IDOMImplementationRegistry.h"
#include "XMPCore/Interfaces/ICoreObjectFactory.h"
#include "XMPCore/Interfaces/IArrayNode.h"
#include "XMPCore/Interfaces/IStructureNode.h"

namespace INT_UMC {

	using AdobeXMPCommon::npos;
	bool SafeToRemoveElement( const spcIUMCNode & node ) {
		if ( node->GetReferenceCount() == 0  ) {
			auto list = node->GetAllChildren();
			auto it = list.begin();
			auto itEnd = list.end();
			for ( ; it != itEnd; it++ ) {
				if( !SafeToRemoveElement( *it ) )
					return false;
			}
			return true;
		}
		return false;
	}

	AdobeXMPCore::spIDOMSerializer GetSerializer( bool reset /*= false */ ) {
		static spIDOMSerializer serializer;
		if ( reset ) {
			serializer.reset();
			return serializer;
		}

		if ( serializer )
			return serializer;
		else {
			serializer = IDOMImplementationRegistry::GetDOMImplementationRegistry()->GetSerializer( "rdf" );
			return serializer;
		}
	}

	AdobeXMPCore::spIDOMParser GetParser( bool reset /*= false */ ) {
		static spIDOMParser parser;
		if ( reset ) {
			parser.reset();
			return parser;
		}

		if ( parser )
			return parser;
		else {
			parser = IDOMImplementationRegistry::GetDOMImplementationRegistry()->GetParser( "rdf" );
			return parser;
		}
	}

	void CreateEquivalentXMPNodes( const spIStructureNode & parent, spIArrayNode & arrayNode,
		const NamespacePropertyNamePair & arrayPair )
	{
		if ( !arrayNode ) {
			arrayNode = IArrayNode::CreateUnorderedArrayNode( arrayPair.first, npos, arrayPair.second, npos );
			parent->AppendNode( arrayNode );
		}
	}

	void CreateEquivalentXMPNodes( const spIStructureNode & parent, spIArrayNode & arrayNode,
		const NamespacePropertyNamePair & arrayPair, spIStructureNode & containerNode, const NamespacePropertyNamePair & containerPair )
	{
		if ( !arrayNode ) {
			arrayNode = IArrayNode::CreateUnorderedArrayNode( arrayPair.first, npos, arrayPair.second, npos );
			if ( containerPair.first ) {
				if ( !containerNode ) {
					containerNode = IStructureNode::CreateStructureNode( containerPair.first, npos, containerPair.second, npos );
					parent->AppendNode( containerNode );
				}
				containerNode->AppendNode( arrayNode );
			} else {
				parent->AppendNode( arrayNode );
			}
		}
	}

	AdobeXMPCore::spIArrayNode TryToGetArrayNode( const spIStructureNode & parentNode, const NamespacePropertyNamePair & pair ) {
		try {
			return parentNode->GetArrayNode( pair.first, npos, pair.second, npos );
		} catch ( ... ) {
			return spIArrayNode();
		}
	}

	AdobeXMPCore::spIStructureNode TryToGetStructNode( const spIStructureNode & parentNode, const NamespacePropertyNamePair & pair ) {
		try {
			return parentNode->GetStructureNode( pair.first, npos, pair.second, npos );
		} catch ( ... ) {
			return spIStructureNode();
		}
	}

	AdobeXMPCore::spISimpleNode TryToGetSimpleNode( const spIStructureNode & parentNode, const NamespacePropertyNamePair & pair ) {
		try {
			return parentNode->GetSimpleNode( pair.first, npos, pair.second, npos );
		} catch ( ... ) {
			return spISimpleNode();
		}
	}

}

namespace UMC {
	const std::string kEmptyString("");
}
