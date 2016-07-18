#ifndef ISource_h__
#define ISource_h__ 1

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
