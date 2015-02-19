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

#include <string>
#include <vector>

namespace UMC {

	class IShot : public enable_shared_from_this< IShot > {

	public:
		typedef enum {
			kClipShotType		= 0,
			kTransitionShotType		= 1
		} eShotTypes;

		typedef std::vector< spIFrame > FrameList;
		typedef std::vector< spcIFrame > cFrameList;

		virtual const std::string & GetUniqueID() const = 0;
		virtual std::string GetUniqueID() = 0;

		virtual void SetType( eShotTypes type ) = 0;
		virtual eShotTypes GetType() const = 0;

		virtual void SetIn( const UMC_Int64 & editUnit ) = 0;
		virtual UMC_Int64 GetIn() const = 0;

		virtual void SetDuration( const UMC_Uns64 & duration ) = 0;
		virtual UMC_Uns64 GetDuration() const = 0;

		virtual spIFrame AddFrame( const char * uniqueID, size_t length = npos ) = 0;

		virtual size_t FrameCount() const = 0;
		virtual FrameList GetFrames() = 0;
		virtual cFrameList GetFrames() const = 0;

		virtual spcITrack GetParent() const = 0;
		virtual spITrack GetParent() = 0;

		virtual ~IShot() = 0;

	private:

	};

	inline IShot::~IShot() {}

};

#endif  // IShot_h__