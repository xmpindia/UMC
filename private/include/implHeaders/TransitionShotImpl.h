#ifndef TransitionShotImpl_h__
#define TransitionShotImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ITransitionShot.h"
#include "implHeaders/ShotImpl.h"
#include "UMCFwdDeclarations_I.h"

namespace INT_UMC {
	class TransitionShotImpl
		: public ITransitionShot
		, public enable_shared_from_this< TransitionShotImpl >
	{
	public:
		TransitionShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
			const spIUniqueIDGenerator & uniqueIDGenerator );

		virtual ~TransitionShotImpl() {}

		virtual eShotTypes GetType() const ;

		virtual void SetInCount( const EditUnitInCount & inCount );
		virtual EditUnitInCount GetInCount() const;

		virtual void SetDuration( const EditUnitDuration & duration );
		virtual EditUnitDuration GetDuration() const;

		virtual spIFrame AddFrame();

		virtual size_t FrameCount() const;
		virtual FrameList GetFrames();
		virtual cFrameList GetFrames() const;

		virtual spIShotSource AddShotSource();

		virtual size_t ShotSourceCount() const;
		virtual ShotSourceList GetShotSources();
		virtual cShotSourceList GetShotSources() const;

		virtual spIShotSource GetShotSource( const std::string & uniqueID );
		virtual spcIShotSource GetShotSource( const std::string & uniqueID ) const;

		// INODEI

		virtual const std::string & GetUniqueID() const;

		virtual eNodeTypes GetNodeType() const;

		virtual wpcINode GetParentNode() const;
		virtual wpINode GetParentNode();

		virtual spcINode GetDecendantNode( const std::string & id ) const;
		virtual spINode GetDecendantNode( const std::string & id );

		virtual spcINode GetChildNode( const std::string & id ) const;
		virtual spINode GetChildNode( const std::string & id );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual size_t GetReferenceCount() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

		virtual pINodeI GetInternalNode();
		virtual pcINodeI GetInternalNode() const;

	protected:
		spIShot					mShot;
	};
}

#endif  // TransitionShotImpl_h__
