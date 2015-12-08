
#include <string>
#define ENABLE_XMP_CPP_INTERFACE 1
#include "XMPCommon/XMPCommonDefines.h"
#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"

#include "XMPCore/Interfaces/IMetadata.h"
#include "XMPCore/Interfaces/IArrayNode.h"
#include "XMPCore/Interfaces/ISimpleNode.h"

#include "XMPCore/Interfaces/IDOMImplementationRegistry.h"
#include "XMPCore/Interfaces/IDOMSerializer.h"
#include "XMPCommon/Interfaces/IUTF8String.h"
#include "XMPCore/Interfaces/ICoreObjectFactory.h"

#include <iostream>

using namespace AdobeXMPCore;
using namespace AdobeXMPCommon;
int main() {
	using AdobeXMPCommon::npos;
	SXMPMeta::Initialize();
	std::string registeredPrefix;
	SXMPMeta::RegisterNamespace( "ns1", "n1", &registeredPrefix );
	SXMPMeta::RegisterNamespace( "ns2", "n2", &registeredPrefix );
	SXMPMeta::RegisterNamespace( "ns3", "n3", &registeredPrefix );

	auto metadata = IMetadata::CreateMetadata();
	metadata->AppendNode( ISimpleNode::CreateSimpleNode( "ns1", npos, "simpleType", npos, "simpleValue", npos ) );
	auto arrayNode = IArrayNode::CreateOrderedArrayNode( "ns2", npos, "arrayNode", npos );
	metadata->AppendNode( arrayNode );
	arrayNode->AppendNode( ISimpleNode::CreateSimpleNode( "ns1", npos, "simpleType2", npos,"simpleValue2", npos ) );
	arrayNode->AppendNode( ISimpleNode::CreateSimpleNode( "ns1", npos, "simpleType3", npos, "simpleValue3", npos ) );
	auto structureNode = IStructureNode::CreateStructureNode( "ns3", npos, "structureNode", npos );

	//Note: you can't add a same node at two different places, so use Clone method to create the exact replica.
	structureNode->AppendNode(arrayNode->Clone());
	metadata->AppendNode( structureNode );

	// Serialize the metadata as rdf
	auto serializer = IDOMImplementationRegistry::GetDOMImplementationRegistry()->GetSerializer( "rdf" );
	auto str = serializer->Serialize( metadata );
	std::cout<<str->c_str();

	SXMPMeta::Terminate();
}