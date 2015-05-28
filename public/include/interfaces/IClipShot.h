#ifndef IClipShot_h__
#define IClipShot_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IShot.h"

namespace UMC {

	class IClipShot
		: public IShot
	{
	public:
		virtual ~IClipShot() = 0;
	};

	inline IClipShot::~IClipShot() {}
}
#endif  // IClipShot_h__
