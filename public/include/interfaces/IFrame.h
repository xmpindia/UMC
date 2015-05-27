#ifndef IFrame_h__
#define IFrame_h__ 1

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

namespace UMC {

	class IFrame 
		: public INode
	{

	public:
		virtual spISource GetSource() = 0;
		virtual spcISource GetSource() const = 0;

		virtual void SetSourceInCount( const EditUnitInCount & sourceInCount ) = 0;
		virtual EditUnitInCount GetSourceInCount() const = 0;

		virtual void SetShotInCount( const EditUnitInCount & shotInCount ) = 0;
		virtual EditUnitInCount GetShotInCount() const = 0;

		virtual ~IFrame() = 0;

	private:

	};

	inline IFrame::~IFrame() {}

};

#endif  // IFrame_h__
