#ifndef IFrame_h__
#define IFrame_h__ 1

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

	class IFrame : public enable_shared_from_this< IFrame > {

	public:
		virtual const std::string & GetUniqueID() const = 0;
		virtual std::string GetUniqueID() = 0;

		virtual spcIShot GetParent() const = 0;
		virtual spIShot GetParent() = 0;

		virtual ~IFrame() = 0;

	private:

	};

	inline IFrame::~IFrame() {}

};

#endif  // IFrame_h__
