#ifndef IShot_h__
#define IShot_h__ 1

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

#include <string>
#include <vector>

namespace UMC {

	class IShot
		: public INode
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

		virtual eShotTypes GetType() const = 0;

		virtual void SetInCount( const EditUnitInCount & inCount ) = 0;
		virtual EditUnitInCount GetInCount() const = 0;

		virtual void SetDuration( const EditUnitDuration & duration ) = 0;
		virtual EditUnitDuration GetDuration() const = 0;

		virtual spIFrame AddFrame( const spISource & source ) = 0;
		virtual spIFrame AddFrame( const std::string & buffer ) = 0;
		virtual spIShotSource AddShotSource( const spISource & source ) = 0;
		virtual spIShotSource AddShotSource( const std::string & buffer ) = 0;

		virtual size_t FrameCount() const = 0;
		virtual FrameList GetAllFrames() = 0;
		virtual cFrameList GetAllFrames() const = 0;
		virtual spIFrame GetFrame( const std::string & uniqueID ) = 0;
		virtual spcIFrame GetFrame( const std::string & uniqueID ) const = 0;

		virtual size_t ShotSourceCount() const = 0;
		virtual ShotSourceList GetAllShotSources() = 0;
		virtual cShotSourceList GetAllShotSources() const = 0;
		virtual spIShotSource GetShotSource( const std::string & uniqueID ) = 0;
		virtual spcIShotSource GetShotSource( const std::string & uniqueID ) const = 0;

		virtual size_t RemoveAllShotSources() = 0;
		virtual size_t RemoveAllFrames() = 0;
		virtual size_t RemoveFrame( const std::string & uniqueID ) = 0;
		virtual size_t RemoveShotSource( const std::string & uniqueID ) = 0;

		virtual ~IShot() = 0;

	private:

	};

	inline IShot::~IShot() {}

};

#endif  // IShot_h__
