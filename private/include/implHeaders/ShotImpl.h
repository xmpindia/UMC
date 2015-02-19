#ifndef ShotImpl_h__
#define ShotImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IShot.h"
#include "UMCDefines_I.h"
#include "interfaces/IFrame.h"
#include "interfaces/ISource.h"

#include <string>
#include <map>

namespace INT_UMC {
	using namespace UMC;
	class ShotImpl : public IShot {
	public:
		ShotImpl( const char * uniqueID, size_t length, eShotTypes type, const spITrack & parent );

		virtual const std::string & GetUniqueID() const;
		virtual std::string GetUniqueID();

		virtual void SetType( eShotTypes type );
		virtual eShotTypes GetType() const ;

		virtual void SetIn( const UMC_Int64 & editUnit );
		virtual UMC_Int64 GetIn() const;

		virtual void SetDuration( const UMC_Uns64 & duration );
		virtual UMC_Uns64 GetDuration() const;

		virtual spIFrame AddFrame( const char * uniqueID, size_t length = npos );

		virtual size_t FrameCount() const;
		virtual FrameList GetFrames();
		virtual cFrameList GetFrames() const;

		virtual spcITrack GetParent() const;
		virtual spITrack GetParent();

	protected:
		std::string				mUniqueID;
		eShotTypes				mShotType;
		UMC_Int64				mIn;
		UMC_Uns64				mDuration;
		weak_ptr< ITrack >		mwpTrack;

		typedef std::map< const std::string, spIFrame > FrameMap;
		FrameMap				mFrameMap;

	};
}

#endif  // ShotImpl_h__
