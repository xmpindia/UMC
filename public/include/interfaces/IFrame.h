#ifndef IFrame_h__
#define IFrame_h__ 1

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
#include "interfaces/IUMCNode.h"

#include <string>

namespace UMC {
	//!
	//! \brief This interface is for frames added to shots in UMC
	//! \details Provides functions to get and set various properties of frames
	//!

	class IFrame 
		: public IUMCNode
	{

	public:

		//!
		//! \brief Get the source from which the frame has been created
		//! \return a shared pointer to a non const ISource object
		//!
		virtual spISource GetSource() = 0;

		//!
		//! \brief Get the source from which the frame has been created
		//! \return a shared pointer to a const ISource object
		//!
		virtual spcISource GetSource() const = 0;

		//!
		//! \brief Set the in count for the source from which the frame has been created
		//! \param[in] sourceInCount a value of type EditUnitCount indicating the in count for the source from which the frame has been created
		//!
		virtual void SetSourceInCount( const EditUnitInCount & sourceInCount ) = 0;

		//!
		//! \brief Get the in count for the source from which the frame has been created
		//! \return  a value of type EditUnitCount indicating the in count for the source from which the frame has been created
		//!
		virtual EditUnitInCount GetSourceInCount() const = 0;
		
		//!
		//! \brief Set the in count of the shot from which the frame has been created
		//! \param[in] shotInCount a value of type EditUnitCount indicating the in count of the shot from which the frame has been created
		//!
		virtual void SetShotInCount( const EditUnitInCount & shotInCount ) = 0;

		//!
		//! \brief Get the in count of the shot from which the frame has been created
		//! \return  a value of type EditUnitCount indicating the in count of the shot from which the frame has been created
		//!
		virtual EditUnitInCount GetShotInCount() const = 0;

		virtual ~IFrame() = 0;

	private:

	};

	inline IFrame::~IFrame() {}

};

#endif  // IFrame_h__
