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
#include "IUMCNode.h"

#include <string>

namespace UMC {

	class ISource
		: public IUMCNode
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

		//!
		//! Set the clip name of the source
		//! \param[in] std::string object containing the clip name of the source
		//!
		virtual void SetClipName( const std::string & clipName ) = 0;

		//!
		//! Get the clip name of the source
		//! \return a value of type std::string containing the clip name of the souce
		//!
		virtual std::string GetClipName() const = 0;

		//!
		//! Get the type of the source
		//! \return a value of eSourceType containing the type of the source
		//!
		virtual eSourceTypes GetType() const = 0;

		virtual ~ISource() = 0;

	};

	inline ISource::~ISource() {}

};

#endif  // ISource_h__
