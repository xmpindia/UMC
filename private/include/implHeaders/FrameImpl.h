#ifndef FrameImpl_h__
#define FrameImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IFrame.h"
#include "UMCDefines_I.h"
#include <map>
#include "interfaces/ISource.h"

#include <string>

namespace INT_UMC {
	using namespace UMC;
	class FrameImpl : public IFrame {
	public:
		FrameImpl( const char * uniqueID, size_t length, const spIShot & parent );

		virtual const std::string & GetUniqueID() const;
		virtual std::string GetUniqueID();

		virtual void SetEditOffset( const UMC_Int64 & editOffset );
		virtual UMC_Int64 GetEditOffset() const;

		virtual spcIShot GetParent() const;
		virtual spIShot GetParent();

	protected:
		UMC_Int64				mEditOffset;
		std::string				mUniqueID;
		weak_ptr< IShot >		mwpShot;
	};
}

#endif  // FrameImpl_h__
