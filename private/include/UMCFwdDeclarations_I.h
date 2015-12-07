#ifndef UMCFwdDeclarations_I_h__
#define UMCFwdDeclarations_I_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include "UMCDefines_I.h"
#include "interfaces/IUMCNode.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"


#include <set>
#include <string>

namespace INT_UMC {
	using namespace UMC;
	using AdobeXMPCore::spIStructureNode;

	// IUMCNodeI
	class IUMCNodeI;
	typedef IUMCNodeI *											pIUMCNodeI;
	typedef const IUMCNodeI *										pcIUMCNodeI;
	typedef shared_ptr< IUMCNodeI >								spIUMCNodeI;
	typedef shared_ptr< const IUMCNodeI >							spcIUMCNodeI;
	
	// IUniqueIDAndReferenceTracker
	class IUniqueIDAndReferenceTracker;
	typedef IUniqueIDAndReferenceTracker *						pIUniqueIDAndReferenceTracker;
	typedef const IUniqueIDAndReferenceTracker *				pcIUniqueIDAndReferenceTracker;
	typedef shared_ptr< IUniqueIDAndReferenceTracker >			spIUniqueIDAndReferenceTracker;
	typedef shared_ptr< const IUniqueIDAndReferenceTracker >	spcIUniqueIDAndReferenceTracker;

	// ICustomDataHandlerRegistry
	class ICustomDataHandlerRegistry;
	typedef ICustomDataHandlerRegistry *						pICustomDataHandlerRegistry;
	typedef const ICustomDataHandlerRegistry *					pcICustomDataHandlerRegistry;
	typedef shared_ptr< ICustomDataHandlerRegistry >			spICustomDataHandlerRegistry;
	typedef shared_ptr< const ICustomDataHandlerRegistry >		spcICustomDataHandlerRegistry;

	spICustomDataHandler CreateSerializerHandler( const spcICustomData & customData, const std::string & customDataNameSpace,
		const std::string & customDataName, const AdobeXMPCore::spIStructureNode & baseNode );

	spIUniqueIDAndReferenceTracker CreateUniqueIDAndReferenceTracker();
	spIUniqueIDGenerator CreateUniqueIDGenerator( const spcIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker );

	spISource CreateSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node = spIStructureNode() );
	spIVideoSource CreateVideoSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node = spIStructureNode() );
	spIAudioSource CreateAudioSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node = spIStructureNode() );
	spIImageSource CreateImageSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node = spIStructureNode() );
	spIVideoFrameSource CreateVideoFrameSource(const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIVideoSource & videoSource,
		const spIStructureNode & node = spIStructureNode() );

	spIOutput CreateOutput( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node = spIStructureNode() );

	spIVideoTrack CreateVideoTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node = spIStructureNode() );
	spIAudioTrack CreateAudioTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node = spIStructureNode() );

	spIClipShot CreateClipShot( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node = spIStructureNode() );
	spITransitionShot CreateTransitionShot( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIStructureNode & node = spIStructureNode() );

	spIFrame CreateFrame( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source, const spIStructureNode & node = spIStructureNode() );

	spIShotSource CreateShotSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source, const spIStructureNode & node = spIStructureNode() );

}
#endif  // UMCFwdDeclarations_I_h__
