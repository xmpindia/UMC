#ifndef IImageSource_h__
#define IImageSource_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ISource.h"

namespace UMC {

	class IImageSource
		: public ISource
	{
	public:
		virtual ~IImageSource() = 0;
	};

	inline IImageSource::~IImageSource() {}
}

#endif  // IImageSource_h__
