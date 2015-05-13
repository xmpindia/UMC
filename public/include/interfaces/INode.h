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

namespace INT_UMC {
	class INodeI;
	typedef INodeI *		pINodeI;
	typedef const INodeI *	pcINodeI;
	//using namespace UMC;
	//template< typename mapType, typename mapElementType >
	//void AddElementToMap( mapType & map, const mapElementType & element, const spINode & parent );
	//template< typename mapType >
	//size_t ClearMap( mapType & map );
	//template< typename mapType >
	//void RemoveElementFromMap( mapType & map, typename mapType::iterator it );
};

namespace UMC {
	class INode {
	public:
		typedef enum {
			kNodeTypeNone				= 0,

			kNodeTypeSource				= 1,

			kNodeTypeOutput				= 2,

			kNodeTypeTrack				= 4,

			kNodeTypeShot				= 8,

			kNodeTypeShotSource			= 16,

			kNodeTypeFrame				= 32,

			kNodeTypeUMC				= 64,

			kNodeTypeAll				= 0xFFFFFFFF,
		} eNodeTypes;

		typedef std::vector< spINode >		NodeList;
		typedef std::vector< spcINode >		cNodeList;

		virtual eNodeTypes GetNodeType() const = 0;
		virtual const std::string & GetUniqueID() const = 0;

		template< typename requiredNodeType >
		weak_ptr< requiredNodeType > GetParent();

		template< typename requiredNodeType >
		weak_ptr< const requiredNodeType > GetParent() const;

		template< typename requiredNodeType >
		shared_ptr< requiredNodeType > GetChild( const std::string & uniqueID );

		template< typename requiredNodeType >
		shared_ptr< const requiredNodeType > GetChild( const std::string & uniqueID ) const;

		template< typename requiredNodeType >
		shared_ptr< requiredNodeType > GetDecendant( const std::string & uniqueID );

		template< typename requiredNodeType >
		shared_ptr< const requiredNodeType > GetDecendant( const std::string & uniqueID ) const;

		virtual wpcINode GetParentNode() const = 0;
		virtual wpINode GetParentNode() = 0;

		virtual spcINode GetDecendantNode( const std::string & uniqueID ) const = 0;
		virtual spINode GetDecendantNode( const std::string & uniqueID ) = 0;

		virtual spcINode GetChildNode( const std::string & uniqueID ) const = 0;
		virtual spINode GetChildNode( const std::string & uniqueID ) = 0;

		virtual NodeList GetAllChildren() = 0;
		virtual cNodeList GetAllChildren() const = 0;

		virtual NodeList GetAllDecendants() = 0;
		virtual cNodeList GetAllDecendants() const = 0;

		virtual size_t GetReferenceCount() const = 0;

		// plugin-able extension node handling
		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) = 0;
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const = 0;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) = 0;

		virtual INT_UMC::pINodeI GetInternalNode() = 0;
		virtual INT_UMC::pcINodeI GetInternalNode() const = 0;

	protected:

		//template< typename mapType, typename mapElementType >
		//friend void INT_UMC::AddElementToMap( mapType & map, const mapElementType & element, const spINode & parent );
		//template< typename mapType >
		//friend size_t INT_UMC::ClearMap( mapType & map );
		//template< typename mapType >
		//friend void INT_UMC::RemoveElementFromMap( mapType & map, typename mapType::iterator it );
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
		return const_cast< INode * >( this )->GetDecendant< requiredNodeType >( uniqueID );
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
		return const_cast< INode * >( this )->GetChild< requiredNodeType >( uniqueID );
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
	weak_ptr< const requiredNodeType > UMC::INode::GetParent() const {
		return const_cast< INode * >( this )->GetParent< requiredNodeType >();
	}

	template< typename requiredNodeType >
	weak_ptr< requiredNodeType > UMC::INode::GetParent() {
		auto node = GetParentNode();
		if ( node ) {
			auto spNode = node.lock();
			if ( spNode )
				return ConvertNode< requiredNodeType >( spNode );
		}
		return weak_ptr< requiredNodeType >();
	}
}

#endif  // INode_h__
