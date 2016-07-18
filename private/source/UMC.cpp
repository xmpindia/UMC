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

#include "UMCDefines_I.h"
#include "interfaces/ICustomDataHandlerRegistry.h"
#include "utils/Utils.h"
#include "XMPCommon/XMPCommonDefines.h"
#include <string>
#include "XMP_Const.h"
#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"
#include "XMP.hpp"

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

