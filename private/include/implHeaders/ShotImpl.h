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

#include <string>
#include <map>

namespace INT_UMC {
	using namespace UMC;
	class ShotImpl : public IShot {
	public:
		ShotImpl( const char * uniqueID, size_t length, const spITrack & parent );

		virtual const std::string & GetUniqueID() const;
		virtual std::string GetUniqueID();

		virtual size_t FrameCount() const;
		virtual FrameList GetFrames();
		virtual cFrameList GetFrames() const;

		virtual spcITrack GetParent() const;
		virtual spITrack GetParent();

	protected:
		std::string				mUniqueID;
		weak_ptr< ITrack >		mwpTrack;

		typedef std::map< const std::string, spIFrame > FrameMap;
		FrameMap				mFrameMap;
	};
}

#endif  // ShotImpl_h__
