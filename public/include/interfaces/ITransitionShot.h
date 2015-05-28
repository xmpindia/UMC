#ifndef ITransitionShot_h__
#define ITransitionShot_h__ 1

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

	class ITransitionShot
		: public IShot
	{
	public:
		virtual ~ITransitionShot() = 0;
	};

	inline ITransitionShot::~ITransitionShot() {}
}
#endif  // ITransitionShot_h__
