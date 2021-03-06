#ifndef ITrack_h__
#define ITrack_h__ 1

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

namespace UMC {

	//!
	//! \brief This interface acts as a base interface for tracks added to outputs in UMC
	//! \details Provides functions to add,remove and access shots to tracks. It also provides functions to get and set various properties.
	//!

	class ITrack
		: public IUMCNode
	{
	public:
		typedef std::vector< spIShot > ShotList;
		typedef std::vector< spcIShot > cShotList;
		typedef std::vector< spIClipShot > ClipShotList;
		typedef std::vector< spcIClipShot > cClipShotList;
		typedef std::vector< spITransitionShot > TransitionShotList;
		typedef std::vector< spcITransitionShot > cTransitionShotList;


		//!
		//! \brief Indicates various types of tracks available in UMC.
		//!
		typedef enum {
			kTrackTypeVideo		= 0,
			kTrackTypeAudio		= 1,

			kTrackTypeAll		= Max_UMC_Uns32 - 1,
			kTrackTypeMaxValue	= Max_UMC_Uns32
		} eTrackTypes;


		//!
		//! \brief Gets the track type of the track.
		//! \return an object of type eTrackTypes indicating the track type of the track
		//!
		virtual eTrackTypes GetType() const = 0;

		//!
		//! \brief Creates a new clip shot and adds it to the track
		//! \return a shared pointer to a non-const object of type IClipShot indicating the clip shot that was newly created
		//!
		virtual spIClipShot AddClipShot() = 0;

		//!
		//! \brief Creates a new transition shot and adds it to the track
		//! \return a shared pointer to a non-const object of type ITransitionShot indicating the clip shot that was newly created
		//!
		virtual spITransitionShot AddTransitionShot() = 0;

		//!
		//! \brief Creates a new shot from the provided buffer and adds it to the track
		//! \param[in] buffer A value of type std::string indicating the serialized form of a shot/
		//! \return a shared pointer to a non-const object of type IShot indicating the shot that was newly created. An error will be thrown if parsing of the buffer fails.
        //! \attention Error is thrown in case buffer is empty
		//!
		virtual spIShot AddShot( const std::string & buffer ) = 0;

		//!
		//! \brief Creates a new clip shot from the provided buffer and adds it to the track
		//! \param[in] buffer A value of type std::string indicating the serialized form of a clip shot
		//! \return a shared pointer to a non-const object of type IClipShot indicating the shot that was newly created.An error will be thrown if parsing of the buffer fails.
        //! \attention Error is thrown in case buffer is empty
		//!
		virtual spIClipShot AddClipShot( const std::string & buffer ) = 0;

		//!
		//! \brief Creates a new transition shot from the provided buffer and adds it to the track
		//! \param[in] buffer A value of type std::string indicating the serialized form of a transition shot
		//! \return a shared pointer to a non-const object of type ITransitionShot indicating the shot that was newly created.An error will be thrown if parsing of the buffer fails.
        //! \attention Error is thrown in case buffer is empty
		//!
		virtual spITransitionShot AddTransitionShot( const std::string & buffer ) = 0;

		//!
		//! \brief Sets the name of the track
		//! \param[in] name a value of type std::string indicating the name of the track
		//!
		virtual void SetName( const std::string & name ) = 0;

		//!
		//! \brief Gets the name of the track
		//! \return a value of type std::string indicating the name of the track
		//!
		virtual std::string GetName() const = 0;

		//!
		//! \brief Returns the number of shots present in the track
		//! \return a value of type size_t indicating the number of shots present in the track
		//!
		virtual size_t ShotCount() const = 0;

		//!
		//! \brief Gets all the shots present in the track
		//! \return object of type ShotList indicating the list of all shots present in the track
		//!
		virtual ShotList GetAllShots() = 0;

		//!
		//! \brief Gets all the shots present in the track
		//! \return a const object of type ShotList indicating the list of all shots present in the track
		//!
		virtual cShotList GetAllShots() const = 0;

		//!
		//! \brief Gets a shot with a particular unique id
		//! \param[in] uniqueID A value of type std::string indicating the unique id of the shot
		//! \return a shared pointer to a non-const object of type IShot. An empty shared pointer is returned if no shot is found with the provided id
		//!
		virtual spIShot GetShot( const std::string & uniqueID ) = 0;

		//!
		//! \brief Gets a shot with a particular unique id
		//! \param[in] uniqueID A value of type std::string indicating the unique id of the shot
		//! \return a shared pointer to a const object of type IShot. An empty shared pointer is returned if no shot is found with the provided id
		//!
		virtual spcIShot GetShot( const std::string & uniqueID ) const = 0;

		//!
		//! \brief Returns the number of clip shots present in the track
		//! \return a value of type size_t indicating the number of clip shots present in the track
		//!
		virtual size_t ClipShotCount() const = 0;

		//!
		//! \brief Gets all the clip shots present in the track
		//! \return object of type ClipShotList indicating the list of all clip shots present in the track
		//!
		virtual ClipShotList GetAllClipShots() = 0;

		//!
		//! \brief Gets all the clip shots present in the track
		//! \return const object of type ClipShotList indicating the list of all clip shots present in the track
		//!
		virtual cClipShotList GetAllClipShots() const = 0;

		//!
		//! \brief Gets a clip shot with a particular unique id
		//! \param[in] uniqueID a value of type std::string indicating the unique id of the clip shot
		//! \return a shared pointer to a non-const object of type IClipShot. An empty shared pointer is returned if no clip shot is found with the provided id
		//! 
		virtual spIClipShot GetClipShot( const std::string & uniqueID ) = 0;

		//!
		//! \brief Gets a clip shot with a particular unique id
		//! \param[in] uniqueID a value of type std::string indicating the unique id of the clip shot
		//! \return a shared pointer to a const object of type IClipShot. An empty shared pointer is returned if no clip shot is found with the provided id
		//!
		virtual spcIClipShot GetClipShot( const std::string & uniqueID ) const = 0;

		//!
		//! \brief Returns the number of transition shots present in the track
		//! \return a value of type size_t indicating the number of transition shots present in the track
		//!
		virtual size_t TransitionShotCount() const = 0;

		//!
		//! \brief Gets all the transition shots present in the track
		//! \return object of type TransitionShotList indicating the list of all transition shots present in the track
		//!
		virtual TransitionShotList GetAllTransitionShots() = 0;

		//!
		//! \brief Gets all the transition shots present in the track
		//! \return const object of type TransitionShotList indicating the list of all transition shots present in the track
		//!
		virtual cTransitionShotList GetAllTransitionShots() const = 0;

		//!
		//! \brief Gets a transition shot with a particular unique id
		//! \param[in] uniqueID a value of type std::string indicating the unique id of the transition shot
		//! \return a shared pointer to a non-const object of type ITransitionShot. An empty shared pointer is returned if no transition shot is found with the provided id
		//!
		virtual spITransitionShot GetTransitionShot( const std::string & uniqueID ) = 0;

		//!
		//! \brief Gets a clip shot with a particular unique id
		//! \param[in] uniqueID a value of type std::string indicating the unique id of the transition shot
		//! \return a shared pointer to a const object of type ITransitionShot. An empty shared pointer is returned if no transition shot is found with the provided id
		//!
		virtual spcITransitionShot GetTransitionShot( const std::string & uniqueID ) const = 0;

		//!
		//! \brief Removes all shots present in the track
		//! \return a value of type size_t indicating the number of shots present in the track before removal.
		//!
		virtual size_t RemoveAllShots() = 0;

		//!
		//! \brief Removes all clip shots present in the track
		//! \return a value of type size_t indicating the number of clip shots present in the track before removal.
		//!
		virtual size_t RemoveAllClipShots() = 0;

		//!
		//! \brief Removes all transition shots present in the track
		//! \return a value of type size_t indicating the number of clip shots present in the track before removal.
		//!
		virtual size_t RemoveAllTransitionShots() = 0;

		//!
		//! \brief Removes a shot with a particular unique id
		//! \param[in] uniqueID a value of type std::string indicating the unique id of the shot to be removed
		//! \return a value of type size_t indicating whether the removal of the shot was successful. 1 is returned if the removal was successful, else 0 is returned
		//!
		virtual size_t RemoveShot( const std::string & uniqueID ) = 0;

		//!
		//! \brief Removes a clip shot with a particular unique id
		//! \param[in] uniqueID a value of type std::string indicating the unique id of the clip shot to be removed
		//! \return a value of type size_t indicating whether the removal of the clip shot was successful. 1 is returned if the removal was successful, else 0 is returned
		//!
		virtual size_t RemoveClipShot( const std::string & uniqueID ) = 0;

		//!
		//! \brief Removes a transition shot with a particular unique id
		//! \param[in] uniqueID a value of type std::string indicating the unique id of the transition shot to be removed
		//! \return a value of type size_t indicating whether the removal of the transition shot was successful. 1 is returned if the removal was successful, else 0 is returned
		//!
		virtual size_t RemoveTransitionShot( const std::string & uniqueID ) = 0;

		virtual ~ITrack() = 0;

	private:

	};

	inline ITrack::~ITrack() {}

};

#endif  // ITrack_h__
