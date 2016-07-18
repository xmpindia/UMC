#ifndef UMCAndXMPMapping_h__
#define UMCAndXMPMapping_h__ 1

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

#include "UMCDefines_I.h"
#include "UMCFwdDeclarations.h"
#include "baseTypes/RationalType.h"
#include "baseTypes/TimeCode.h"

#include "XMPCore/Interfaces/IStructureNode.h"
#include "XMPCore/Interfaces/ISimpleNode.h"
#include "XMPCore/Interfaces/ICoreObjectFactory.h"

namespace INT_UMC {
	using namespace UMC;
	using namespace AdobeXMPCore;

	// Pair for namespace and property name
	typedef std::pair< const char *, const char * >				NamespacePropertyNamePair;

	extern const NamespacePropertyNamePair kSourcesPair;
	extern const NamespacePropertyNamePair kVideoSourcesPair;
	extern const NamespacePropertyNamePair kAudioSourcesPair;
	extern const NamespacePropertyNamePair kImageSourcesPair;
	extern const NamespacePropertyNamePair kVideoFrameSourcesPair;
	extern const NamespacePropertyNamePair kOutputsPair;
	extern const NamespacePropertyNamePair kTracksPair;
	extern const NamespacePropertyNamePair kVideoTracksPair;
	extern const NamespacePropertyNamePair kAudioTracksPair;
	extern const NamespacePropertyNamePair kUniqueIDPair;
	extern const NamespacePropertyNamePair kNamePair;
	extern const NamespacePropertyNamePair kTitlePair;
	extern const NamespacePropertyNamePair kImageAspectRatioPair;
	extern const NamespacePropertyNamePair kCanvasAspectRatioPair;
	extern const NamespacePropertyNamePair kVideoEditRatePair;
	extern const NamespacePropertyNamePair kAudioEditRatePair;
	extern const NamespacePropertyNamePair kStartTimeCodePair;
	extern const NamespacePropertyNamePair kTimeValuePair;
	extern const NamespacePropertyNamePair kTimeFormatPair;
	extern const NamespacePropertyNamePair kExtensionPair;
	extern const NamespacePropertyNamePair kInCountPair;
	extern const NamespacePropertyNamePair kDurationPair;
	extern const NamespacePropertyNamePair kShotsPair;
	extern const NamespacePropertyNamePair kClipShotsPair;
	extern const NamespacePropertyNamePair kTransitionShotsPair;
	extern const NamespacePropertyNamePair kFramesPair;
	extern const NamespacePropertyNamePair kShotSourcesPair;
	extern const NamespacePropertyNamePair kRecordPair;
	extern const NamespacePropertyNamePair kSourcePair;

	using std::to_string;
	std::string to_string( const Unsigned64RationalType & rational );
	std::string to_string( const Signed64RationalType & rational );

	void AddOrUpdateDataToXMPDOM( const std::string & stringValue,
		const NamespacePropertyNamePair & namespacePropertyNamePair,
		const spIStructureNode & parentNode );
	
	template< typename dataType >
	void AddOrUpdateDataToXMPDOM( const dataType & dataValue,
		const NamespacePropertyNamePair & namespacePropertyNamePair,
		const spIStructureNode & parentNode,
		bool (*ignore)( const dataType & ) = NULL )
	{
		if ( ignore != NULL ) {
			if ( ignore( dataValue ) ) return;
		}
		std::string temp;
		temp = to_string( dataValue );
		AddOrUpdateDataToXMPDOM( temp, namespacePropertyNamePair, parentNode );
	}

	void AddOrUpdateDataToXMPDOM( const TimeCode & timeCodeValue, const spIStructureNode & parentNode );

	bool IgnoreEditUnitInCount( const EditUnitInCount & value );
	bool IgnoreEditUnitDuration( const EditUnitDuration & value );

	UMC_Int64 stoi64( const std::string & strValue );
	UMC_Uns64 stou64( const std::string & strValue );
	Unsigned64RationalType stou64rt( const std::string & strValue );
	Signed64RationalType stos64rt( const std::string & strValue );

	bool UpdateDataFromXMPDOM( std::string & dataValue, const NamespacePropertyNamePair & pair,
		const spIStructureNode & parentNode, const std::string & resetValue );

	template< typename dataType >
	bool UpdateDataFromXMPDOM( dataType & dataValue, const NamespacePropertyNamePair & pair,
		const spIStructureNode & parentNode, dataType( *ConvertFromString ) ( const std::string & ),
		const dataType * resetValue = NULL )
	{
		std::string strValue;
		bool retValue = UpdateDataFromXMPDOM( strValue, pair, parentNode, kEmptyString );
		if ( retValue && strValue.size() ) {
			try {
				dataValue = ConvertFromString( strValue );
			} catch ( ... ) {}
		}
		if ( resetValue )
			dataValue = *resetValue;
		return false;

	}

	bool UpdateDataFromXMPDOM( TimeCode & dataValue, const spIStructureNode & parentNode );

	spIStructureNode ParseRDF( const std::string & buffer );

	spIStructureNode TryToGetActualNode( const spIStructureNode & node, const NamespacePropertyNamePair & pair );

	size_t GetMatchingIndexForActualNode( const spIStructureNode & node, const NamespacePropertyNamePair ** array, size_t nElement );

}

#endif  // UMCAndXMPMapping_h__
