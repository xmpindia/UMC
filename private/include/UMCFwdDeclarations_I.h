#ifndef UMCFwdDeclarations_I_h__
#define UMCFwdDeclarations_I_h__ 1

/*
*  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
*  This file is licensed to you under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License. You may obtain a copy
*  of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software distributed under
*  the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
*  OF ANY KIND, either express or implied. See the License for the specific language
*  governing permissions and limitations under the License.
*
*/

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
