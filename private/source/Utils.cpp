// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "utils/Utils.h"
#include "interfaces/INode.h"
#include "XMPCore/Interfaces/IXMPDOMImplementationRegistry.h"
#include "XMPCore/Interfaces/IXMPCoreObjectFactory.h"

namespace INT_UMC {

	bool SafeToRemoveElement( const spcINode & node ) {
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

	NS_XMPCORE::spIXMPDOMSerializer GetSerializer( bool reset /*= false */ ) {
		static spIXMPDOMSerializer serializer;
		if ( reset ) {
			serializer.reset();
			return serializer;
		}

		if ( serializer )
			return serializer;
		else {
			serializer = IXMPDOMImplementationRegistry::GetDOMImplementationRegistry()->CreateSerializer( "rdf" );
			return serializer;
		}
	}

	NS_XMPCORE::spIXMPDOMParser GetParser( bool reset /*= false */ ) {
		static spIXMPDOMParser parser;
		if ( reset ) {
			parser.reset();
			return parser;
		}

		if ( parser )
			return parser;
		else {
			parser = IXMPDOMImplementationRegistry::GetDOMImplementationRegistry()->CreateParser( "rdf" );
			return parser;
		}
	}

	void CreateEquivalentXMPNodes( const spIXMPStructureNode & parent, spIXMPArrayNode & arrayNode,
		const NamespacePropertyNamePair & arrayPair )
	{
		if ( !arrayNode ) {
			arrayNode = IXMPArrayNode::CreateUnorderedArrayNode( arrayPair.first, arrayPair.second );
			parent->AppendNode( arrayNode );
		}
	}

	void CreateEquivalentXMPNodes( const spIXMPStructureNode & parent, spIXMPArrayNode & arrayNode,
		const NamespacePropertyNamePair & arrayPair, spIXMPStructureNode & containerNode, const NamespacePropertyNamePair & containerPair )
	{
		if ( !arrayNode ) {
			arrayNode = IXMPArrayNode::CreateUnorderedArrayNode( arrayPair.first, arrayPair.second );
			if ( containerPair.first ) {
				if ( !containerNode ) {
					containerNode = IXMPStructureNode::CreateStructureNode( containerPair.first, containerPair.second );
					parent->AppendNode( containerNode );
				}
				containerNode->AppendNode( arrayNode );
			} else {
				parent->AppendNode( arrayNode );
			}
		}
	}

	NS_XMPCORE::spIXMPArrayNode TryToGetArrayNode( const spIXMPStructureNode & parentNode, const NamespacePropertyNamePair & pair ) {
		try {
			return parentNode->GetArrayNode( pair.first, pair.second );
		} catch ( ... ) {
			return spIXMPArrayNode();
		}
	}

	NS_XMPCORE::spIXMPStructureNode TryToGetStructNode( const spIXMPStructureNode & parentNode, const NamespacePropertyNamePair & pair ) {
		try {
			return parentNode->GetStructureNode( pair.first, pair.second );
		} catch ( ... ) {
			return spIXMPStructureNode();
		}
	}

	NS_XMPCORE::spIXMPSimpleNode TryToGetSimpleNode( const spIXMPStructureNode & parentNode, const NamespacePropertyNamePair & pair ) {
		try {
			return parentNode->GetSimpleNode( pair.first, pair.second );
		} catch ( ... ) {
			return spIXMPSimpleNode();
		}
	}

}

namespace UMC {
	const std::string kEmptyString("");
}
