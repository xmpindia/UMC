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
#include "interfaces/INode.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"


#include <set>
#include <string>

namespace INT_UMC {
	using namespace UMC;
	using NS_XMPCORE::spIXMPStructureNode;

	// INodeI
	class INodeI;
	typedef INodeI *											pINodeI;
	typedef const INodeI *										pcINodeI;
	typedef shared_ptr< INodeI >								spINodeI;
	typedef shared_ptr< const INodeI >							spcINodeI;
	
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
		const std::string & customDataName, const NS_XMPCORE::spIXMPStructureNode & baseNode );

	spIUniqueIDAndReferenceTracker CreateUniqueIDAndReferenceTracker();
	spIUniqueIDGenerator CreateUniqueIDGenerator( const spcIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker );

	spISource CreateSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node = spIXMPStructureNode() );
	spIVideoSource CreateVideoSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node = spIXMPStructureNode() );
	spIAudioSource CreateAudioSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node = spIXMPStructureNode() );
	spIImageSource CreateImageSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node = spIXMPStructureNode() );
	spIVideoFrameSource CreateVideoFrameSource(const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIVideoSource & videoSource,
		const spIXMPStructureNode & node = spIXMPStructureNode() );

	spIOutput CreateOutput( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node = spIXMPStructureNode() );

	spIVideoTrack CreateVideoTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node = spIXMPStructureNode() );
	spIAudioTrack CreateAudioTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node = spIXMPStructureNode() );

	spIClipShot CreateClipShot( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node = spIXMPStructureNode() );
	spITransitionShot CreateTransitionShot( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node = spIXMPStructureNode() );

	spIFrame CreateFrame( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source, const spIXMPStructureNode & node = spIXMPStructureNode() );

	spIShotSource CreateShotSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spISource & source, const spIXMPStructureNode & node = spIXMPStructureNode() );

}
#endif  // UMCFwdDeclarations_I_h__
