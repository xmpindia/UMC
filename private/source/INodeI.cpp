// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "interfaces/INodeI.h"
#include "utils/Utils.h"

#include "XMPCore/Interfaces/IDOMSerializer.h"
#include "XMPCommon/Interfaces/IUTF8String.h"

namespace INT_UMC {

	std::string IUMCNodeI::SerializeXMP() const {
		auto serializer = GetSerializer();
		SyncUMCToXMP();
		auto sp = GetXMPNode();
		auto spString = serializer->Serialize( sp );
		return std::string( spString->c_str(), spString->size() );
	}

	IUMCNodeI::~IUMCNodeI() {

	}

}
