#ifndef INode_h__
#define INode_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"

#include <string>
#include <vector>

namespace UMC {
	class INode {
	public:
		typedef enum {
			kNodeTypeSource				= 0,

			kNodeTypeOutput				= 10,

			kNodeTypeTrack				= 20,

			kNodeTypeShot				= 30,

			kNodeTypeShotSource			= 40,

			kNodeTypeFrame				= 50,

			kNodeTypeUMC				= 60
		} eNodeTypes;

		typedef std::vector< spINode >		NodeList;
		typedef std::vector< spcINode >		cNodeList;

		virtual eNodeTypes GetNodeType() const = 0;
		virtual const std::string & GetUniqueID() const = 0;

		template< typename requiredNodeType >
		shared_ptr< requiredNodeType > GetParent();

		template< typename requiredNodeType >
		shared_ptr< const requiredNodeType > GetParent() const;

		template< typename requiredNodeType >
		shared_ptr< requiredNodeType > GetChild( const std::string & uniqueID );

		template< typename requiredNodeType >
		shared_ptr< const requiredNodeType > GetChild( const std::string & uniqueID ) const;

		template< typename requiredNodeType >
		shared_ptr< requiredNodeType > GetDecendant( const std::string & uniqueID );

		template< typename requiredNodeType >
		shared_ptr< const requiredNodeType > GetDecendant( const std::string & uniqueID ) const;

		virtual spcINode GetParentNode() const = 0;
		virtual spINode GetParentNode() = 0;

		virtual spcINode GetDecendantNode( const std::string & uniqueID ) const = 0;
		virtual spINode GetDecendantNode( const std::string & uniqueID ) = 0;

		virtual spcINode GetChildNode( const std::string & uniqueID ) const = 0;
		virtual spINode GetChildNode( const std::string & uniqueID ) = 0;

		virtual NodeList GetAllChildren() = 0;
		virtual cNodeList GetAllChildren() const = 0;

		virtual NodeList GetAllDecendants() = 0;
		virtual cNodeList GetAllDecendants() const = 0;
	};

	template< typename requiredNodeType >
	shared_ptr< requiredNodeType > ConvertNode( const spINode & node ) {
		auto t = dynamic_pointer_cast< requiredNodeType >( node );
		if ( t ) {
			return t;
		} else {
			throw std::bad_cast();
		}
	}

	template< typename requiredNodeType >
	shared_ptr< const requiredNodeType > UMC::INode::GetDecendant( const std::string & uniqueID ) const {
		return const_cast< INode * >( this )->GetDecendant( uniqueID );
	}

	template< typename requiredNodeType >
	shared_ptr< requiredNodeType > UMC::INode::GetDecendant( const std::string & uniqueID ) {
		auto node = GetDecendantNode( uniqueID );
		if ( node ) {
			return ConvertNode< requiredNodeType >( node );
		} else {
			return shared_ptr< requiredNodeType >();
		}
	}

	template< typename requiredNodeType >
	shared_ptr< const requiredNodeType > UMC::INode::GetChild( const std::string & uniqueID ) const {
		return const_cast< INode * >( this )->GetChild( uniqueID );
	}

	template< typename requiredNodeType >
	shared_ptr< requiredNodeType > UMC::INode::GetChild( const std::string & uniqueID ) {
		auto node = GetChildNode( uniqueID );
		if ( node ) {
			return ConvertNode< requiredNodeType >( node );
		} else {
			return shared_ptr< requiredNodeType >();
		}
	}

	template< typename requiredNodeType >
	shared_ptr< const requiredNodeType > UMC::INode::GetParent() const {
		return const_cast< INode * >( this )->GetParent();
	}

	template< typename requiredNodeType >
	shared_ptr< requiredNodeType > UMC::INode::GetParent() {
		auto node = GetParentNode();
		if ( node ) {
			return ConvertNode< requiredNodeType >( node );
		} else {
			return shared_ptr< requiredNodeType >();
		}
	}
}

#endif  // INode_h__
