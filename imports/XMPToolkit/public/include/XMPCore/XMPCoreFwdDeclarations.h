#ifndef XMPCoreFwdDeclarations_h__
#define XMPCoreFwdDeclarations_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  ADC	Amandeep Chawla
//  ANS Ankita Sharma
//
// mm-dd-yy who Description of changes, most recent first.
//
// 08-07-14 ANS 5.6-c023 Fixing compile time issues in XMPCore headers on Mac 32 bit.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-09-14 ADC 5.5-c026 Re-factoring of XMPCommon Framework
//
// =================================================================================================
#endif	// AdobePrivate

#include "XMPCore/XMPCoreDefines.h"
#include "XMPCommon/XMPCommonFwdDeclarations.h"

#ifdef XMPCORE_CLIENT_HEADER
	#define QUOTEME(FILE_NAME) #FILE_NAME
	#include QUOTEME(XMPCORE_CLIENT_HEADER)
#endif

namespace NS_XMPCORE {
	using NS_XMPCOMMON::shared_ptr;
    using NS_XMPCOMMON::UInt32;

	// IXMPPathSegment
	class IXMPPathSegment_v1;

	typedef IXMPPathSegment_v1							IXMPPathSegment_base;
	typedef IXMPPathSegment_v1 *						pIXMPPathSegment_base;
	typedef const IXMPPathSegment_v1 *					pcIXMPPathSegment_base;

	typedef IXMPPathSegment_v1							IXMPPathSegment_latest;

	#ifndef CLIENT_IXMPPATHSEGMENT_VERSION
		typedef IXMPPathSegment_latest					IXMPPathSegment;
	#else
		class CLIENT_IXMPPATHSEGMENT_VERSION;
		typedef CLIENT_IXMPPATHSEGMENT_VERSION			IXMPPathSegment;
	#endif
	typedef IXMPPathSegment *							pIXMPPathSegment;
	typedef const IXMPPathSegment *						pcIXMPPathSegment;
	typedef shared_ptr< IXMPPathSegment >				spIXMPPathSegment;
	typedef shared_ptr< const IXMPPathSegment >			spcIXMPPathSegment;

	// IXMPPath
	class IXMPPath_v1;

	typedef IXMPPath_v1									IXMPPath_base;
	typedef IXMPPath_v1 *								pIXMPPath_base;
	typedef const IXMPPath_v1 *							pcIXMPPath_base;

	typedef IXMPPath_v1									IXMPPath_latest;

	#ifndef CLIENT_IXMPPATH_VERSION
		typedef IXMPPath_latest							IXMPPath;
	#else
		class CLIENT_IXMPPATH_VERSION;
		typedef CLIENT_IXMPPATH_VERSION					IXMPPath;
	#endif
	typedef IXMPPath *									pIXMPPath;
	typedef const IXMPPath *							pcIXMPPath;
	typedef shared_ptr< IXMPPath >						spIXMPPath;
	typedef shared_ptr< const IXMPPath >				spcIXMPPath;

	// IXMPNameSpacePrefixMap
	class IXMPNameSpacePrefixMap_v1;

	typedef IXMPNameSpacePrefixMap_v1					IXMPNameSpacePrefixMap_base;
	typedef IXMPNameSpacePrefixMap_v1 *					pIXMPNameSpacePrefixMap_base;
	typedef const IXMPNameSpacePrefixMap_v1 *			pcIXMPNameSpacePrefixMap_base;

	typedef IXMPNameSpacePrefixMap_v1					IXMPNameSpacePrefixMap_latest;

	#ifndef CLIENT_IXMPNAMESPACEPREFIXMAP_VERSION
		typedef IXMPNameSpacePrefixMap_latest			IXMPNameSpacePrefixMap;
	#else
		class CLIENT_IXMPNAMESPACEPREFIXMAP_VERSION;
		typedef CLIENT_IXMPNAMESPACEPREFIXMAP_VERSION	IXMPNameSpacePrefixMap;
	#endif
	typedef IXMPNameSpacePrefixMap *					pIXMPNameSpacePrefixMap;
	typedef const IXMPNameSpacePrefixMap *				pcIXMPNameSpacePrefixMap;
	typedef shared_ptr< IXMPNameSpacePrefixMap >		spIXMPNameSpacePrefixMap;
	typedef shared_ptr< const IXMPNameSpacePrefixMap >	spcIXMPNameSpacePrefixMap;

	// IXMPNode
	class IXMPNode_v1;

	typedef IXMPNode_v1									IXMPNode_base;
	typedef IXMPNode_v1 *								pIXMPNode_base;
	typedef const IXMPNode_v1 *							pcIXMPNode_base;

	typedef IXMPNode_v1									IXMPNode_latest;

	#ifndef CLIENT_IXMPNODE_VERSION
		typedef IXMPNode_latest							IXMPNode;
	#else
		class CLIENT_IXMPNODE_VERSION;
		typedef CLIENT_IXMPNODE_VERSION					IXMPNode;
	#endif
	typedef IXMPNode	*								pIXMPNode;
	typedef const IXMPNode	*							pcIXMPNode;
	typedef shared_ptr< IXMPNode >						spIXMPNode;
	typedef shared_ptr< const IXMPNode >				spcIXMPNode;

	// IXMPCompositeNode
	class IXMPCompositeNode_v1;

	typedef IXMPCompositeNode_v1						IXMPCompositeNode_base;
	typedef IXMPCompositeNode_v1 *						pIXMPCompositeNode_base;
	typedef const IXMPCompositeNode_v1 *				pcIXMPCompositeNode_base;

	typedef IXMPCompositeNode_v1						IXMPCompositeNode_latest;

	#ifndef CLIENT_IXMPCOMPOSITENODE_VERSION
		typedef IXMPCompositeNode_latest				IXMPCompositeNode;
	#else
		class CLIENT_IXMPCOMPOSITENODE_VERSION;
		typedef CLIENT_IXMPCOMPOSITENODE_VERSION		IXMPCompositeNode;
	#endif
	typedef IXMPCompositeNode *							pIXMPCompositeNode;
	typedef const IXMPCompositeNode *					pcIXMPCompositeNode;
	typedef shared_ptr< IXMPCompositeNode >				spIXMPCompositeNode;
	typedef shared_ptr< const IXMPCompositeNode >		spcIXMPCompositeNode;

	// IXMPArrayNode
	class IXMPArrayNode_v1;

	typedef IXMPArrayNode_v1							IXMPArrayNode_base;
	typedef IXMPArrayNode_v1 *							pIXMPArrayNode_base;
	typedef const IXMPArrayNode_v1 *					pcIXMPArrayNode_base;

	typedef IXMPArrayNode_v1							IXMPArrayNode_latest;

	#ifndef CLIENT_IXMPARRAYNODE_VERSION
		typedef IXMPArrayNode_latest					IXMPArrayNode;
	#else
		class CLIENT_IXMPARRAYNODE_VERSION;
		typedef CLIENT_IXMPARRAYNODE_VERSION			IXMPArrayNode;
	#endif
	typedef IXMPArrayNode *								pIXMPArrayNode;
	typedef const IXMPArrayNode *						pcIXMPArrayNode;
	typedef shared_ptr< IXMPArrayNode >					spIXMPArrayNode;
	typedef shared_ptr< const IXMPArrayNode >			spcIXMPArrayNode;

	// IXMPStructureNode
	class IXMPStructureNode_v1;

	typedef IXMPStructureNode_v1						IXMPStructureNode_base;
	typedef IXMPStructureNode_v1 *						pIXMPStructureNode_base;
	typedef const IXMPStructureNode_v1 *				pcIXMPStructureNode_base;

	typedef IXMPStructureNode_v1						IXMPStructureNode_latest;

	#ifndef CLIENT_IXMPSTRUCTURENODE_VERSION
		typedef IXMPStructureNode_latest				IXMPStructureNode;
	#else
		class CLIENT_IXMPSTRUCTURENODE_VERSION;
		typedef CLIENT_IXMPSTRUCTURENODE_VERSION		IXMPStructureNode;
	#endif
	typedef IXMPStructureNode *							pIXMPStructureNode;
	typedef const IXMPStructureNode *					pcIXMPStructureNode;
	typedef shared_ptr< IXMPStructureNode >				spIXMPStructureNode;
	typedef shared_ptr< const IXMPStructureNode >		spcIXMPStructureNode;

	// IXMPCoreObjectFactory
	class IXMPCoreObjectFactory_v1;

	typedef IXMPCoreObjectFactory_v1					IXMPCoreObjectFactory_base;
	typedef IXMPCoreObjectFactory_v1 *					pIXMPCoreObjectFactory_base;
	typedef const IXMPCoreObjectFactory_v1 *			pcIXMPCoreObjectFactory_base;

	typedef IXMPCoreObjectFactory_v1					IXMPCoreObjectFactory_latest;

	#ifndef CLIENT_IXMPCOREOBJECTFACTORY_VERSION
		typedef IXMPCoreObjectFactory_latest			IXMPCoreObjectFactory;
	#else
		class CLIENT_IXMPCOREOBJECTFACTORY_VERSION;
		typedef CLIENT_IXMPCOREOBJECTFACTORY_VERSION	IXMPCoreObjectFactory;
	#endif
	typedef IXMPCoreObjectFactory *						pIXMPCoreObjectFactory;
	typedef const IXMPCoreObjectFactory *				pcIXMPCoreObjectFactory;
	typedef shared_ptr< IXMPCoreObjectFactory >			spIXMPCoreObjectFactory;
	typedef shared_ptr< const IXMPCoreObjectFactory >	spcIXMPCoreObjectFactory;

	// IXMPSimpleNode
	class IXMPSimpleNode_v1;

	typedef IXMPSimpleNode_v1							IXMPSimpleNode_base;
	typedef IXMPSimpleNode_v1 *							pIXMPSimpleNode_base;
	typedef const IXMPSimpleNode_v1 *					pcIXMPSimpleNode_base;

	typedef IXMPSimpleNode_v1							IXMPSimpleNode_latest;

	#ifndef CLIENT_IXMPSIMPLENODE_VERSION
		typedef IXMPSimpleNode_latest					IXMPSimpleNode;
	#else
		class CLIENT_IXMPSIMPLENODE_VERSION;
		typedef CLIENT_IXMPSIMPLENODE_VERSION			IXMPSimpleNode;
	#endif
	typedef IXMPSimpleNode *							pIXMPSimpleNode;
	typedef const IXMPSimpleNode *						pcIXMPSimpleNode;
	typedef shared_ptr< IXMPSimpleNode >				spIXMPSimpleNode;
	typedef shared_ptr< const IXMPSimpleNode >			spcIXMPSimpleNode;

	// IXMPArrayNode
	class IXMPArrayNode_v1;

	typedef IXMPArrayNode_v1							IXMPArrayNode_base;
	typedef IXMPArrayNode_v1 *							pIXMPArrayNode_base;
	typedef const IXMPArrayNode_v1 *					pcIXMPArrayNode_base;

	typedef IXMPArrayNode_v1							IXMPArrayNode_latest;

	#ifndef CLIENT_IXMPARRAYNODE_VERSION
		typedef IXMPArrayNode_latest					IXMPArrayNode;
	#else
		class CLIENT_IXMPARRAYNODE_VERSION;
		typedef CLIENT_IXMPARRAYNODE_VERSION			IXMPArrayNode;
	#endif
	typedef IXMPArrayNode *								pIXMPArrayNode;
	typedef const IXMPArrayNode *						pcIXMPArrayNode;
	typedef shared_ptr< IXMPArrayNode >					spIXMPArrayNode;
	typedef shared_ptr< const IXMPArrayNode >			spcIXMPArrayNode;

	// IXMPStructureNode
	class IXMPStructureNode_v1;

	typedef IXMPStructureNode_v1						IXMPStructureNode_base;
	typedef IXMPStructureNode_v1 *						pIXMPStructureNode_base;
	typedef const IXMPStructureNode_v1 *				pcIXMPStructureNode_base;

	typedef IXMPStructureNode_v1						IXMPStructureNode_latest;

	#ifndef CLIENT_IXMPSTRUCTURENODE_VERSION
		typedef IXMPStructureNode_latest				IXMPStructureNode;
	#else
		class CLIENT_IXMPSTRUCTURENODE_VERSION;
		typedef CLIENT_IXMPSTRUCTURENODE_VERSION		IXMPStructureNode;
	#endif
	typedef IXMPStructureNode *							pIXMPStructureNode;
	typedef const IXMPStructureNode *					pcIXMPStructureNode;
	typedef shared_ptr< IXMPStructureNode >				spIXMPStructureNode;
	typedef shared_ptr< const IXMPStructureNode >		spcIXMPStructureNode;

	// IXMPQualifiers
	class IXMPQualifiers_v1;

	typedef IXMPQualifiers_v1							IXMPQualifiers_base;
	typedef IXMPQualifiers_v1 *							pIXMPQualifiers_base;
	typedef const IXMPQualifiers_v1 *					pcIXMPQualifiers_base;

	typedef IXMPQualifiers_v1							IXMPQualifiers_latest;

	#ifndef CLIENT_IXMPQUALIFIERS_VERSION
		typedef IXMPQualifiers_latest					IXMPQualifiers;
	#else
		class CLIENT_IXMPQUALIFIERS_VERSION;
		typedef CLIENT_IXMPQUALIFIERS_VERSION			IXMPQualifiers;
	#endif
	typedef IXMPQualifiers *							pIXMPQualifiers;
	typedef const IXMPQualifiers *						pcIXMPQualifiers;
	typedef shared_ptr< IXMPQualifiers >				spIXMPQualifiers;
	typedef shared_ptr< const IXMPQualifiers >			spcIXMPQualifiers;

	// IXMPNodeIterator
	class IXMPNodeIterator_v1;

	typedef IXMPNodeIterator_v1							IXMPNodeIterator_base;
	typedef IXMPNodeIterator_v1 *						pIXMPNodeIterator_base;

	typedef IXMPNodeIterator_v1							IXMPNodeIterator_latest;

#ifndef CLIENT_IXMPNODEITERATOR_VERSION
	typedef IXMPNodeIterator_latest						IXMPNodeIterator;
#else
	class CLIENT_IXMPNODEITERATOR_VERSION;
	typedef CLIENT_IXMPNODEITERATOR_VERSION				IXMPNodeIterator;
#endif
	typedef IXMPNodeIterator	*						pIXMPNodeIterator;
	typedef shared_ptr< IXMPNodeIterator >				spIXMPNodeIterator;


	// IXMPConstNodeIterator
	class IXMPConstNodeIterator_v1;

	typedef IXMPConstNodeIterator_v1					IXMPConstNodeIterator_base;
	typedef IXMPConstNodeIterator_v1 *					pIXMPConstNodeIterator_base;

	typedef IXMPConstNodeIterator_v1					IXMPConstNodeIterator_latest;

#ifndef CLIENT_IXMPCONSTNODEITERATOR_VERSION
	typedef IXMPConstNodeIterator_latest				IXMPConstNodeIterator;
#else
	class CLIENT_IXMPCONSTNODEITERATOR_VERSION;
	typedef CLIENT_IXMPCONSTNODEITERATOR_VERSION		IXMPConstNodeIterator;
#endif
	typedef IXMPConstNodeIterator	*					pIXMPConstNodeIterator;
	typedef shared_ptr< IXMPConstNodeIterator >			spIXMPConstNodeIterator;

	// IXMPMetadata
	class IXMPMetadata_v1;

	typedef IXMPMetadata_v1								IXMPMetadata_base;
	typedef IXMPMetadata_v1 *							pIXMPMetadata_base;
	typedef const IXMPMetadata_v1 *						pcIXMPMetadata_base;

	typedef IXMPMetadata_v1								IXMPMetadata_latest;

#ifndef CLIENT_IXMPMETADATA_VERSION
	typedef IXMPMetadata_latest							IXMPMetadata;
#else
	class CLIENT_IXMPMETADATA_VERSION;
	typedef CLIENT_IXMPMETADATA_VERSION					IXMPMetadata;
#endif
	typedef IXMPMetadata *								pIXMPMetadata;
	typedef const IXMPMetadata *						pcIXMPMetadata;
	typedef shared_ptr< IXMPMetadata >					spIXMPMetadata;
	typedef shared_ptr< const IXMPMetadata >			spcIXMPMetadata;

	// IXMPDOMConfiguration
	class IXMPDOMConfiguration_v1;

	typedef IXMPDOMConfiguration_v1						IXMPDOMConfiguration_base;
	typedef IXMPDOMConfiguration_v1 *					pIXMPDOMConfiguration_base;
	typedef const IXMPDOMConfiguration_v1 *				pcIXMPDOMConfiguration_base;

	typedef IXMPDOMConfiguration_v1						IXMPDOMConfiguration_latest;

	#ifndef CLIENT_IXMPDOMCONFIGURATION_VERSION
		typedef IXMPDOMConfiguration_latest				IXMPDOMConfiguration;
	#else
		class CLIENT_IXMPDOMCONFIGURATION_VERSION;
		typedef CLIENT_IXMPDOMCONFIGURATION_VERSION		IXMPDOMConfiguration;
	#endif
	typedef IXMPDOMConfiguration *						pIXMPDOMConfiguration;
	typedef const IXMPDOMConfiguration *				pcIXMPDOMConfiguration;
	typedef shared_ptr< IXMPDOMConfiguration >			spIXMPDOMConfiguration;
	typedef shared_ptr< const IXMPDOMConfiguration >	spcIXMPDOMConfiguration;


	// IXMPDOMParser
	class IXMPDOMParser_v1;

	typedef IXMPDOMParser_v1							IXMPDOMParser_base;
	typedef IXMPDOMParser_v1 *							pIXMPDOMParser_base;
	typedef const IXMPDOMParser_v1 *					pcIXMPDOMParser_base;

	typedef IXMPDOMParser_v1							IXMPDOMParser_latest;

	#ifndef CLIENT_IXMPDOMPARSER_VERSION
		typedef IXMPDOMParser_latest					IXMPDOMParser;
	#else
		class CLIENT_IXMPDOMPARSER_VERSION;
		typedef CLIENT_IXMPDOMPARSER_VERSION			IXMPDOMParser;
	#endif
	typedef IXMPDOMParser *								pIXMPDOMParser;
	typedef const IXMPDOMParser *						pcIXMPDOMParser;
	typedef shared_ptr< IXMPDOMParser >					spIXMPDOMParser;
	typedef shared_ptr< const IXMPDOMParser >			spcIXMPDOMParser;

	// IXMPDOMSerializer
	class IXMPDOMSerializer_v1;

	typedef IXMPDOMSerializer_v1						IXMPDOMSerializer_base;
	typedef IXMPDOMSerializer_v1 *						pIXMPDOMSerializer_base;
	typedef const IXMPDOMSerializer_v1 *				pcIXMPDOMSerializer_base;

	typedef IXMPDOMSerializer_v1						IXMPDOMSerializer_latest;

	#ifndef CLIENT_IXMPDOMSERIALIZER_VERSION
		typedef IXMPDOMSerializer_latest				IXMPDOMSerializer;
	#else
		class CLIENT_IXMPDOMSERIALIZER_VERSION;
		typedef CLIENT_IXMPDOMSERIALIZER_VERSION		IXMPDOMSerializer;
	#endif
	typedef IXMPDOMSerializer *							pIXMPDOMSerializer;
	typedef const IXMPDOMSerializer *					pcIXMPDOMSerializer;
	typedef shared_ptr< IXMPDOMSerializer >				spIXMPDOMSerializer;
	typedef shared_ptr< const IXMPDOMSerializer >		spcIXMPDOMSerializer;

	// IXMPDOMImplementationRegistry
	class IXMPDOMImplementationRegistry_v1;

	typedef IXMPDOMImplementationRegistry_v1					IXMPDOMImplementationRegistry_base;
	typedef IXMPDOMImplementationRegistry_v1 *					pIXMPDOMImplementationRegistry_base;
	typedef const IXMPDOMImplementationRegistry_v1 *			pcIXMPDOMImplementationRegistry_base;

	typedef IXMPDOMImplementationRegistry_v1					IXMPDOMImplementationRegistry_latest;

	#ifndef CLIENT_IXMPDOMIMPLEMENTATIONREGISTRY_VERSION
		typedef IXMPDOMImplementationRegistry_latest			IXMPDOMImplementationRegistry;
	#else
		class CLIENT_IXMPDOMIMPLEMENTATIONREGISTRY_VERSION;
		typedef CLIENT_IXMPDOMIMPLEMENTATIONREGISTRY_VERSION	IXMPDOMImplementationRegistry;
	#endif
typedef IXMPDOMImplementationRegistry *							pIXMPDOMImplementationRegistry;
typedef const IXMPDOMImplementationRegistry *					pcIXMPDOMImplementationRegistry;
typedef shared_ptr< IXMPDOMImplementationRegistry >				spIXMPDOMImplementationRegistry;
typedef shared_ptr< const IXMPDOMImplementationRegistry >		spcIXMPDOMImplementationRegistry;


	typedef enum {
		//! Indicates that IXMPNameSpacePrefixMap has an entry missing.
		kXMPDataModelCodeXMPNameSpacePrefixMapEntryMissing				= 0,
		//! Indicates that a different type of node is present than one user is expecting
		kXMPDataModelCodeDifferentNodeTypePresent						= 1,
		//! Indicates that node is already a child of another parent.
		kXMPDataModelNodeAlreadyAChild									= 2,
		//! Indicates a node with the same qualified name or index already exists.
		kXMPDataModelNodeAlreadyExists									= 3,
		//! Indicates no such node exists.
		kXMPDataModelNoSuchNodeExists									= 4,
		//! Indicates current array element type is not same as that of other child items
		kXMPDataModelArrayItemTypeDifferent								= 5,
		//! Indicates invalid path segment inside a path.
		kXMPDataModelInvalidPathSegment									= 6,

		//! Indicates Bad schema parameter
		kXMPDataModelCodeBadSchema										= 101,
		//! Indicates Bad XPath parameter
		kXMPDataModelCodeBadXPath										= 102,
		//! Indicates Bad options parameter
		kXMPDataModelCodeBadOptions										= 103,
		//! Indicates Bad iteration position
		kXMPDataModelCodeBadIterPosition								= 104,
		//! Indicates Unicode error
		kXMPDataModelCodeBadUnicode										= 105,
		//! Indicates XMP format error
		kXMPDataModelCodeValidationError								= 106,
		//! Indicates Empty iterator
		kXMPDataModelCodeEmptyIterator									= 107,

		//! Maximum value this enum can hold, should be treated as invalid value.
		kXMPDataModelCodeMaxValue										= NS_XMPCOMMON::kMaxEnumValue
	} eXMPDataModelErrorCode;

	typedef enum {
		//! Indicates XML parsing error.
		kXMPParserCodeBadXML											= 0,
		/// RDF format error
		kXMPParserCodeBadRDF											= 1,
		/// XMP format error
		kXMPParserCodeBadXMP											= 2,

		//! Maximum value this enum can hold, should be treated as invalid value.
		kXMPParserCodeMaxValue											= NS_XMPCOMMON::kMaxEnumValue
	} eXMPParserErrorCode;

	typedef enum {
		//! Indicates serialization failed to achieve size requirement.
		kXMPSerializerCodeSizeExceed									= 0,
		//! Indicates un registered namespace encountered during serialization.
		kXMPSerializerCodeUnRegisteredNameSpace							= 1,

		//! Maximum value this enum can hold, should be treated as invalid value.
		kXMPSerializerCodeMaxValue										= NS_XMPCOMMON::kMaxEnumValue

	} eXMPSerializerErrorCode;

}

#endif // XMPCoreFwdDeclarations_h__
