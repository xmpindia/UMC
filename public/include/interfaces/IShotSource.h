#ifndef IShotSource_h__
#define IShotSource_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include "interfaces/IUMCNode.h"

namespace UMC {
	class IShotSource
		: public IUMCNode
	{

	public:

		//!
		//! Get the source from which the shot source has been created
		//! \return a shared pointer to a non const ISource object
		//!
		virtual spISource GetSource() = 0;

		//!
		//! Get the source from which the shot source has been created
		//! \return a shared pointer to a const ISource object
		//!
		virtual spcISource GetSource() const = 0;

		//!
		//! Set the in count for the source from which the shot source has been created
		//! \param[in] a value of type EditUnitCount indicating the in count for the source from which the shot source has been created
		//!
		virtual void SetSourceInCount( const EditUnitInCount & sourceInCount ) = 0;

		//!
		//! Get the in count for the source from which the shot source has been created
		//! \return  a value of type EditUnitCount indicating the in count for the source from which the shot source has been created
		//!
		virtual EditUnitInCount GetSourceInCount() const = 0;

		//!
		//! Set the duration for the source from which the shot source has been created
		//! \param[in] a value of type EditUnitDuration indicating the duration for the source from which the shot source has been created
		//!
		virtual void SetSourceDuration( const EditUnitDuration & sourceDuration ) = 0;

		//!
		//! Get the duration for the source from which the shot source has been created
		//! \return  a value of type EditUnitDuration indicating the duration for the source from which the shot source has been created
		//!
		virtual EditUnitDuration GetSourceDuration() const = 0;

		//!
		//! Set the in count of the shot from which the shot source has been created
		//! \param[in] a value of type EditUnitCount indicating the in count of the shot from which the shot source has been created
		//!
		virtual void SetShotInCount( const EditUnitInCount & shotInCount ) = 0;

		//!
		//! Get the in count of the shot from which the shot source has been created
		//! \return  a value of type EditUnitCount indicating the in count of the shot from which the shot source has been created
		//!
		virtual EditUnitInCount GetShotInCount() const = 0;

		virtual ~IShotSource() = 0;

	private:

	};

	inline IShotSource::~IShotSource() { }
}

#endif  // IShotSource_h__
