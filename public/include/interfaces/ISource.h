#ifndef ISource_h__
#define ISource_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"

#include "baseTypes/TimeCode.h"
#include "INode.h"

#include <string>

namespace UMC {

	class ISource
		: public INode
	{

	public:
		typedef enum {
			kSourceTypeVideo		= 0,
			kSourceTypeAudio		= 1,
			kSourceTypeVideoFrame	= 2,
			kSourceTypeImage		= 3,

			kSourceTypeAll			= Max_UMC_Uns32 - 1,
			kSourceTypeMaxValue		= Max_UMC_Uns32
		} eSourceTypes;

		virtual void SetClipName( const std::string & clipName ) = 0;
		virtual std::string GetClipName() const = 0;

		virtual eSourceTypes GetType() const = 0;

		virtual ~ISource() = 0;

	};

	inline ISource::~ISource() {}

};

#endif  // ISource_h__
