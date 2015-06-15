// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCDefines_I.h"
#include "interfaces/ICustomDataHandlerRegistry.h"
#include "utils/Utils.h"

#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"


extern "C" void UMC_Initialize() {
	SXMPMeta::Initialize();
	std::string registeredPrefix;
	SXMPMeta::RegisterNamespace( INT_UMC::kXMP_NS_UMC, "umc", &registeredPrefix );
}

extern "C" void UMC_Terminate() {
	INT_UMC::GetSerializer( true );
	INT_UMC::GetParser( true );
	INT_UMC::ICustomDataHandlerRegistry::DestroyInstance();
	SXMPMeta::Terminate();
}

