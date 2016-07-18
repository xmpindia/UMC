#ifndef IShot_h__
#define IShot_h__ 1

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
#include <vector>

namespace UMC {

	class IShot
		: public IUMCNode
	{

	public:
		typedef enum {
			kShotTypeClip			= 0,
			kShotTypeTransition		= 1,

			kShotTypeAll			= Max_UMC_Uns32 - 1,
			kShotTypeMaxValue		= Max_UMC_Uns32

		} eShotTypes;


		typedef std::vector< spIFrame > FrameList;
		typedef std::vector< spcIFrame > cFrameList;

		typedef std::vector< spIShotSource > ShotSourceList;
		typedef std::vector< spcIShotSource > cShotSourceList;

		//!
		//! Gets the shot type.
		//! \return an object of type eShotType indicating the type of the shot.
		//!
		virtual eShotTypes GetType() const = 0;

		//!
		//! Sets the in count of the shot
		//! \param[in] a value of type EditUnitInCount indicating the in count of the shot.
		//!
		virtual void SetInCount( const EditUnitInCount & inCount ) = 0;

		//!
		//! Sets the in count of the shot
		//! \return a value of type EditUnitInCount indicating the in count of the shot.
		//!
		virtual EditUnitInCount GetInCount() const = 0;

		//!
		//! Sets the duration of the shot
		//! \param[in] a value of type EditUnitInDuration indicating the duration of the shot.
		//!
		virtual void SetDuration( const EditUnitDuration & duration ) = 0;

		//!
		//! Gets the duration of the shot
		//! \return a value of type EditUnitInDuration indicating the duration of the shot.
		//!
		virtual EditUnitDuration GetDuration() const = 0;

		//!
		//! Creates a new frame from a buffer and adds it to the shot
		//! \param[in] a value of type std::string indicating the buffer from which the frame is to be created
		//! \return a shared pointer to a non-object of type IFrame. A parsing error will be thrown in case the creation of the frame fails.
		//!
		virtual spIFrame AddFrame( const spISource & source ) = 0;

		//!
		//! Creates a new frame from a buffer and adds it to the shot
		//! \param[in] a value of type std::string indicating the buffer from which the frame is to be created
		//! \return a shared pointer to a non-object of type IFrame. A parsing error will be thrown in case the creation of the frame fails.
		//!
		virtual spIFrame AddFrame( const std::string & buffer ) = 0;
		virtual spIShotSource AddShotSource( const spISource & source ) = 0;

		//!
		//! Creates a new shot source from a buffer and adds it to the shot
		//! \param[in] a value of type std::string indicating the buffer from which the shot source is to be created
		//! \return a shared pointer to a non-object of type IShotSource. A parsing error will be thrown in case the creation of the shot source fails.
		//!
		virtual spIShotSource AddShotSource( const std::string & buffer ) = 0;

		//!
		//! Gets the number of frames present in the shot
		//! \return value of type size_t indicating the number of frames present in the shot
		//!
		virtual size_t FrameCount() const = 0;

		//!
		//! Gets all the frames present in the shot
		//! \return a object of type FrameList indicating all the frames present in the shot
		//!
		virtual FrameList GetAllFrames() = 0;

		//!
		//! Gets all the frames present in the shot
		//! \return a const object of type cFrameList indicating all the frames present in the shot
		//!
		virtual cFrameList GetAllFrames() const = 0;

		//!
		//! Gets a frame with a particular unique id from the shot
		//! \param[in] a value of type std::string indicating the unique id of the frame
		//! \return a shared pointer to a non-const object of type IFrame. An empty shared pointer is returned if no frame is found with the specified id.
		//!
		virtual spIFrame GetFrame( const std::string & uniqueID ) = 0;

		//!
		//! Gets a shot source with a particular unique id from the shot
		//! \param[in] a value of type std::string indicating the unique id of the frame
		//! \return a shared pointer to a non-const object of type IFrame. An empty shared pointer is returned if no frame is found with the specified id.
		//!
		virtual spcIFrame GetFrame( const std::string & uniqueID ) const = 0;

		//!
		//! Gets the number of frames present in the shot
		//! \return value of type size_t indicating the number of frames present in the shot
		//!
		virtual size_t ShotSourceCount() const = 0;

		//!
		//! Gets all the shot sources present in the shot
		//! \return a object of type ShotSourceList indicating all the shot sources present in the shot
		//!
		virtual ShotSourceList GetAllShotSources() = 0;

		//!
		//! Gets all the shot sources present in the shot
		//! \return a const object of type cShotSourceList indicating all the shot sources present in the shot
		//!
		virtual cShotSourceList GetAllShotSources() const = 0;

		//!
		//! Gets a shot source with a particular unique id from the shot
		//! \param[in] a value of type std::string indicating the unique id of the shot source
		//! \return a shared pointer to a non-const object of type IShotSource. An empty shared pointer is returned if no shot source is found with the specified id.
		//!
		virtual spIShotSource GetShotSource( const std::string & uniqueID ) = 0;

		//!
		//! Gets a shot source with a particular unique id from the shot
		//! \param[in] a value of type std::string indicating the unique id of the shot source
		//! \return a shared pointer to a const object of type IShotSource. An empty shared pointer is returned if no shot source is found with the specified id.
		//!
		virtual spcIShotSource GetShotSource( const std::string & uniqueID ) const = 0;

		//!
		//! Removes all the shot sources from the shot
		//! \return a value of type size_t indicating the count of the shot sources present in the track before removal.
		//!
		virtual size_t RemoveAllShotSources() = 0;

		//!
		//! Removes all the frames from the shot
		//! \return a value of type size_t indicating the count of the frames present in the track before removal.
		//! \return a value of type size_t indicating whether the removal of the shot source was successful
		//!
		virtual size_t RemoveAllFrames() = 0;

		//!
		//! Removes a frame with a particular unique id from the shot
		//! \param[in] a value of type std::string indicating the unique id of the frame to be removed
		//! \return a value of type size_t indicating whether the removal of the frame was successful. 1 is returned if the removal of the frame is successful.
		//!
		virtual size_t RemoveFrame( const std::string & uniqueID ) = 0;

		//!
		//! Removes a shot source with a particular unique id from the shot
		//! \param[in] a value of type std::string indicating the unique id of the shot source to be removed
		//! \return a value of type size_t indicating whether the removal of the shot source was successful. 1 is returned if the removal of the shot source is successful.
		//!
		virtual size_t RemoveShotSource( const std::string & uniqueID ) = 0;

		virtual ~IShot() = 0;

	private:

	};

	inline IShot::~IShot() {}

};

#endif  // IShot_h__
