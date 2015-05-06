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

#include <set>
#include <string>

namespace INT_UMC {
	using namespace UMC;

	// IUniqueIDAndReferenceTracker
	class IUniqueIDAndReferenceTracker;
	typedef IUniqueIDAndReferenceTracker *						pIUniqueIDAndReferenceTracker;
	typedef const IUniqueIDAndReferenceTracker *				pcIUniqueIDAndReferenceTracker;
	typedef shared_ptr< IUniqueIDAndReferenceTracker >			spIUniqueIDAndReferenceTracker;
	typedef shared_ptr< const IUniqueIDAndReferenceTracker >	spcIUniqueIDAndReferenceTracker;

	spIUniqueIDAndReferenceTracker CreateUniqueIDAndReferenceTracker();
	spIUniqueIDGenerator CreateUniqueIDGenerator( const spcIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker );

	spIVideoSource CreateVideoSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator );
	spIAudioSource CreateAudioSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator );
	spIImageSource CreateImageSource( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator );
	spIVideoFrameSource CreateVideoFrameSource( const spIVideoSource & videoSource,
		const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator );

	spIOutput CreateOutput( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator );

	spIVideoTrack CreateVideoTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator );
	spIAudioTrack CreateAudioTrack( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator );

}
#endif  // UMCFwdDeclarations_I_h__
