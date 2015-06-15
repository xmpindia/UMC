#ifndef ITrack_h__
#define ITrack_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include "interfaces/INode.h"

namespace UMC {

	class ITrack
		: public INode
	{
	public:
		typedef std::vector< spIShot > ShotList;
		typedef std::vector< spcIShot > cShotList;
		typedef std::vector< spIClipShot > ClipShotList;
		typedef std::vector< spcIClipShot > cClipShotList;
		typedef std::vector< spITransitionShot > TransitionShotList;
		typedef std::vector< spcITransitionShot > cTransitionShotList;

		typedef enum {
			kTrackTypeVideo		= 0,
			kTrackTypeAudio		= 1,

			kTrackTypeAll		= Max_UMC_Uns32 - 1,
			kTrackTypeMaxValue	= Max_UMC_Uns32
		} eTrackTypes;

		virtual eTrackTypes GetType() const = 0;

		virtual spIClipShot AddClipShot() = 0;
		virtual spITransitionShot AddTransitionShot() = 0;

		virtual spIShot AddShot( const std::string & buffer ) = 0;
		virtual spIClipShot AddClipShot( const std::string & buffer ) = 0;
		virtual spITransitionShot AddTransitionShot( const std::string & buffer ) = 0;

		virtual void SetName( const std::string & name ) = 0;
		virtual std::string GetName() const = 0;

		virtual size_t ShotCount() const = 0;
		virtual ShotList GetAllShots() = 0;
		virtual cShotList GetAllShots() const = 0;
		virtual spIShot GetShot( const std::string & uniqueID ) = 0;
		virtual spcIShot GetShot( const std::string & uniqueID ) const = 0;

		virtual size_t ClipShotCount() const = 0;
		virtual ClipShotList GetAllClipShots() = 0;
		virtual cClipShotList GetAllClipShots() const = 0;
		virtual spIClipShot GetClipShot( const std::string & uniqueID ) = 0;
		virtual spcIClipShot GetClipShot( const std::string & uniqueID ) const = 0;

		virtual size_t TransitionShotCount() const = 0;
		virtual TransitionShotList GetAllTransitionShots() = 0;
		virtual cTransitionShotList GetAllTransitionShots() const = 0;
		virtual spITransitionShot GetTransitionShot( const std::string & uniqueID ) = 0;
		virtual spcITransitionShot GetTransitionShot( const std::string & uniqueID ) const = 0;

		virtual size_t RemoveAllShots() = 0;
		virtual size_t RemoveAllClipShots() = 0;
		virtual size_t RemoveAllTransitionShots() = 0;

		virtual size_t RemoveShot( const std::string & uniqueID ) = 0;
		virtual size_t RemoveClipShot( const std::string & uniqueID ) = 0;
		virtual size_t RemoveTransitionShot( const std::string & uniqueID ) = 0;

		virtual ~ITrack() = 0;

	private:

	};

	inline ITrack::~ITrack() {}

};

#endif  // ITrack_h__
