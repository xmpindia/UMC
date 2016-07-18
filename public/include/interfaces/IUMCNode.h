#ifndef IUMCNode_h__
#define IUMCNode_h__ 1

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

#include "UMCFwdDeclarations.h"

#include <string>
#include <vector>

namespace INT_UMC {
	class IUMCNodeI;
	typedef IUMCNodeI *		pIUMCNodeI;
	typedef const IUMCNodeI *	pcIUMCNodeI;
};

namespace UMC {
	class IUMCNode {
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

		typedef std::vector< spIUMCNode >		NodeList;
		typedef std::vector< spcIUMCNode >		cNodeList;

		//!
		//! Get the node type of the node.
		//! \return an object of type eNodeType indicating the type of the node.
		//!
		virtual eNodeTypes GetNodeType() const = 0;


		//!
		//! Get the unique id of the node
		//! \return a value of type std::string indicating the unique id of the node.
		//!
		virtual const std::string & GetUniqueID() const = 0;


		//!
		//! Set the unique id of the node
		//! \param[in] a value of type std::string indicating the unique id of the node.
		//! \return a value of type bool indicating whether the unique id was successfully set. False is returned if the id is not unique, has length zero.
		//!
		virtual bool SetUniqueID( const std::string & uniqueID ) = 0;


		//!
		//! Get the parsed id of the node
		//! \return a value of type std::string indicating the parsed id of the node.
		//!
		virtual std::string GetParsedID() const = 0;

		//!
		//! Get the parent node of the current node
		//! \return a weak pointer to non-const object of type requiredNodeType indicating the parent node of the current node
		//!
		template< typename requiredNodeType >
		weak_ptr< requiredNodeType > GetParent();


		//!
		//! Get the parent node of the current node
		//! \return a weak pointer to const object of type requiredNodeType indicating the parent node of the current node
		//!
		template< typename requiredNodeType >
		weak_ptr< const requiredNodeType > GetParent() const;


		//!
		//! Get the child node of the current node with a particular unique id
		//! \param[in] a value of type std::string indicating the unique id of the node.
		//! \return a weak pointer to const object of type requiredNodeType indicating the child node of the current node. If no child node with the provided unique id is found, an empty shared pointer is returned.
		//!
		template< typename requiredNodeType >
		shared_ptr< requiredNodeType > GetChild( const std::string & uniqueID );


		//!
		//! Get the child node of the current node with a particular unique id
		//! \param[in] a value of type std::string indicating the unique id of the node.
		//! \return a weak pointer to const object of type requiredNodeType indicating the child node of the current node. If no child node with the provided unique id is found, an empty shared pointer is returned.
		//!
		template< typename requiredNodeType >
		shared_ptr< const requiredNodeType > GetChild( const std::string & uniqueID ) const;


		//!
		//! Get the descendant node of the current node with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the descendant node to be found
		//! \return a shared pointer to non-const object of type requiredNodeType indicating the descendant node with the unique id. An empty shared pointer will be returned if no descendant node is found with the provided unique id. 
		//!
		template< typename requiredNodeType >
		shared_ptr< requiredNodeType > GetDecendant( const std::string & uniqueID );


		//!
		//! Get the descendant node of the current node with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the descendant node to be found
		//! \return a shared pointer to const object of type requiredNodeType indicating the descendant node with the unique id. An empty shared pointer will be returned if no descendant node is found with the provided unique id. 
		//!
		template< typename requiredNodeType >
		shared_ptr< const requiredNodeType > GetDecendant( const std::string & uniqueID ) const;

		//!
		//! Get the parent node of the current node
		//! \return a weak pointer to const object of type IUMCNode indicating the parent node of the current node
		//!
		virtual wpcIUMCNode GetParentNode() const = 0;

		//!
		//! Get the parent node of the current node
		//! \return a weak pointer to non-const object of type IUMCNode indicating the parent node of the current node
		//!
		virtual wpIUMCNode GetParentNode() = 0;


		//!
		//! Get the descendant node of the current node with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the descendant node to be found
		//! \return a shared pointer to const object of type IUMCNode indicating the descendant node with the unique id. An empty shared pointer will be returned if no descendant node is found with the provided unique id. 
		//!
		virtual spcIUMCNode GetDecendantNode( const std::string & uniqueID ) const = 0;

		//!
		//! Get the descendant node of the current node with a particular unique id
		//! param[in] a value of type std::string indicating the unique id of the descendant node to be found
		//! \return a shared pointer to non-const object of type IUMCNode indicating the descendant node with the unique id. An empty shared pointer will be returned if no descendant node is found with the provided unique id. 
		//!
		virtual spIUMCNode GetDecendantNode( const std::string & uniqueID ) = 0;


		//!
		//! Get the child node of the current node with a particular unique id
		//! \param[in] a value of type std::string indicating the unique id of the node.
		//! \return a weak pointer to const object of type IUMCNode indicating the child node of the current node. If no child node with the provided unique id is found, an empty shared pointer is returned.
		//!
		virtual spcIUMCNode GetChildNode( const std::string & uniqueID ) const = 0;

		//!
		//! Get the child node of the current node with a particular unique id
		//! \param[in] a value of type std::string indicating the unique id of the node.
		//! \return a weak pointer to non-const object of type IUMCNode indicating the child node of the current node. If no child node with the provided unique id is found, an empty shared pointer is returned.
		//!
		virtual spIUMCNode GetChildNode( const std::string & uniqueID ) = 0;

		//!
		//! Get the list of all the children of the node
		//! \return a std::vector of non-const objects of type IUMCNode indicating all the child nodes of the current node.
		//!
		virtual NodeList GetAllChildren() = 0;

		//!
		//! Get the list of all the children of the node
		//! \return a std::vector of const objects of type IUMCNode indicating all the child nodes of the current node.
		//!
		virtual cNodeList GetAllChildren() const = 0;


		//!
		//! Get the list of all the descendants of the node
		//! \return a std::vector of non-const objects of type IUMCNode indicating all the descendants of the current node.
		//!
		virtual NodeList GetAllDecendants() = 0;

		//!
		//! Get the list of all the descendants of the node
		//! \return a std::vector of const objects of type IUMCNode indicating all the descendants of the current node.
		//!
		virtual cNodeList GetAllDecendants() const = 0;


		//!
		//! Get the reference count of the node based on the unique id of the node
		//! \return a value of type size_t indicating the reference count of the node.
		//!
		virtual size_t GetReferenceCount() const = 0;


		//!
		//! Get the serialized XMP representation of the node
		//! \return a value of type std::string indicating the serialized XMP representation of the node.
		//!
		virtual std::string Serialize() const = 0;

		// plugin-able extension node handling

		//!
		//! Get the custom data associated with the node having a certain namespace and name
		//! \param[in] a value of type std::string indicating the namespace of the custom data
		//! \param[in] a value of type std::string indicating the name of the custom data
		//! \return a shared pointer to a non-const object of type ICustomData indicating the custom data. An empty shared pointer will be returned in case no custom data is found with the provided namespace and name.
		//!
		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) = 0;

		//!
		//! Get the custom data associated with the node having a certain namespace and name
		//! \param[in] a value of type std::string indicating the namespace of the custom data
		//! \param[in] a value of type std::string indicating the name of the custom data
		//! \return a shared pointer to a const object of type ICustomData indicating the custom data. An empty shared pointer will be returned in case no custom data is found with the provided namespace and name.
		//!
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const = 0;

		//!
		//! Add the custom data associated with the node having a certain namespace and name
		//! \param[in] a value of type std::string indicating the namespace of the custom data
		//! \param[in] a value of type std::string indicating the name of the custom data
		//! \param[in] a shared pointer to a const object of type ICustomData indicating the custom data
		//! \return a value of type bool indicating whether the custom data was successfully added to the node.
		//!
		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) = 0;


		//!
		//! Get the pointer to the internal node object
		//! \return a pointer to const object of type IUMCNode indicating the internal node.
		//!
		virtual INT_UMC::pIUMCNodeI GetInternalNode() = 0;

		//!
		//! Get the pointer to the internal node object
		//! \return a pointer to const object of type IUMCNode indicating the internal node.
		//!
		virtual INT_UMC::pcIUMCNodeI GetInternalNode() const = 0;

	protected:

		//template< typename mapType, typename mapElementType >
		//friend void INT_UMC::AddElementToMap( mapType & map, const mapElementType & element, const spIUMCNode & parent );
		//template< typename mapType >
		//friend size_t INT_UMC::ClearMap( mapType & map );
		//template< typename mapType >
		//friend void INT_UMC::RemoveElementFromMap( mapType & map, typename mapType::iterator it );
	};

	template< typename requiredNodeType >
	shared_ptr< requiredNodeType > ConvertNode( const spIUMCNode & node ) {
		auto t = dynamic_pointer_cast< requiredNodeType >( node );
		if ( t ) {
			return t;
		} else {
			throw std::bad_cast();
		}
	}

	template< typename requiredNodeType >
	shared_ptr< const requiredNodeType > UMC::IUMCNode::GetDecendant( const std::string & uniqueID ) const {
		return const_cast< IUMCNode * >( this )->GetDecendant< requiredNodeType >( uniqueID );
	}

	template< typename requiredNodeType >
	shared_ptr< requiredNodeType > UMC::IUMCNode::GetDecendant( const std::string & uniqueID ) {
		auto node = GetDecendantNode( uniqueID );
		if ( node ) {
			return ConvertNode< requiredNodeType >( node );
		} else {
			return shared_ptr< requiredNodeType >();
		}
	}

	template< typename requiredNodeType >
	shared_ptr< const requiredNodeType > UMC::IUMCNode::GetChild( const std::string & uniqueID ) const {
		return const_cast< IUMCNode * >( this )->GetChild< requiredNodeType >( uniqueID );
	}

	template< typename requiredNodeType >
	shared_ptr< requiredNodeType > UMC::IUMCNode::GetChild( const std::string & uniqueID ) {
		auto node = GetChildNode( uniqueID );
		if ( node ) {
			return ConvertNode< requiredNodeType >( node );
		} else {
			return shared_ptr< requiredNodeType >();
		}
	}

	template< typename requiredNodeType >
	weak_ptr< const requiredNodeType > UMC::IUMCNode::GetParent() const {
		return const_cast< IUMCNode * >( this )->GetParent< requiredNodeType >();
	}

	template< typename requiredNodeType >
	weak_ptr< requiredNodeType > UMC::IUMCNode::GetParent() {
		auto node = GetParentNode();
		if ( !node.expired() ) {
			auto spNode = node.lock();
			if ( spNode )
				return ConvertNode< requiredNodeType >( spNode );
		}
		return weak_ptr< requiredNodeType >();
	}
}

#endif  // IUMCNode_h__
