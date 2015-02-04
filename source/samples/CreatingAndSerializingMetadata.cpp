
#include <string>

#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"

#include "XMPCore/Interfaces/IXMPMetadata.h"
#include "XMPCore/Interfaces/IXMPArrayNode.h"
#include "XMPCore/Interfaces/IXMPSimpleNode.h"

#include "XMPCore/Interfaces/IXMPDOMImplementationRegistry.h"
#include "XMPCore/Interfaces/IXMPDOMSerializer.h"

#include <iostream>

using namespace NS_XMPCORE;
using namespace NS_XMPCOMMON;
int main() {
	SXMPMeta::Initialize();
	std::string registeredPrefix;
	SXMPMeta::RegisterNamespace( "ns1", "n1", &registeredPrefix );
	SXMPMeta::RegisterNamespace( "ns2", "n2", &registeredPrefix );
	SXMPMeta::RegisterNamespace( "ns3", "n3", &registeredPrefix );

	auto metadata = IXMPMetadata::CreateMetadata();
	metadata->AppendNode( IXMPSimpleNode::CreateSimpleNode( "ns1", "simpleType", "simpleValue" ) );
	auto arrayNode = IXMPArrayNode::CreateOrderedArrayNode( "ns2", "arrayNode" );
	metadata->AppendNode( arrayNode );
	arrayNode->AppendNode( IXMPSimpleNode::CreateSimpleNode( "ns1", "simpleType2", "simpleValue2" ) );
	arrayNode->AppendNode( IXMPSimpleNode::CreateSimpleNode( "ns1", "simpleType3", "simpleValue3" ) );
	auto structureNode = IXMPStructureNode::CreateStructureNode( "ns3", "structureNode" );

	//Note: you can't add a same node at two different places, so use Clone method to create the exact replica.
	structureNode->AppendNode(arrayNode->Clone());
	metadata->AppendNode( structureNode );

	// Serialize the metadata as rdf
	auto serializer = IXMPDOMImplementationRegistry::GetDOMImplementationRegistry()->CreateSerializer( "rdf" );
	auto str = serializer->Serialize( metadata );
	std::cout<<str->c_str();

	SXMPMeta::Terminate();
}