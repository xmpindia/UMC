
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
#include "interfaces/IUMC.h"
#include "interfaces/ITrack.h"
#include "DoViDisplayHandler.h"

using namespace AdobeXMPCore;
using namespace AdobeXMPCommon;



int main() {

	UMC_Initialize();
	UMC::IUMC::RegisterCustomNodeHandler(DoVi::Display::GetNameSpace(), DoVi::Display::GetPropertyName(),

		std::make_shared< DoVi::DisplayHandler >());
	auto umc = UMC::IUMC::CreateEmptyUMC();
	std::shared_ptr< DoVi::Display > display = std::make_shared< DoVi::Display >();
	display->setID("id-1");
	display->setName("reference display - 1");
	display->setDiagonalSize(52.0);
	umc->SetCustomData(DoVi::Display::GetNameSpace(), DoVi::Display::GetPropertyName(), display);

	auto rdfRep = umc->SerializeToBuffer();

	auto um1 = UMC::IUMC::CreateUMCFromBuffer(rdfRep);
	std::shared_ptr< DoVi::Display >parsedDisplay = std::dynamic_pointer_cast< DoVi::Display >(
		um1->GetCustomData(DoVi::Display::GetNameSpace(), DoVi::Display::GetPropertyName()));
	UMC_Terminate();
}