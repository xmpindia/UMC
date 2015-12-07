// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "utils/UMCAndXMPMapping.h"
#include "utils/Utils.h"
#include <sstream>

#include "XMPCore/Interfaces/IDOMImplementationRegistry.h"
#include "XMPCore/Interfaces/IDOMParser.h"
#include "XMPCore/Interfaces/IMetadata.h"
#include "XMPCore/Interfaces/IStructureNode.h"
#include "XMPCore/Interfaces/IArrayNode.h"
#include "XMPCommon/Interfaces/IUTF8String.h"

namespace INT_UMC {

	using AdobeXMPCommon::npos;
	const NamespacePropertyNamePair kSourcesPair( kXMP_NS_UMC, "sources" );
	const NamespacePropertyNamePair kVideoSourcesPair( kXMP_NS_UMC, "videoSources" );
	const NamespacePropertyNamePair kAudioSourcesPair( kXMP_NS_UMC, "audioSources" );
	const NamespacePropertyNamePair kImageSourcesPair( kXMP_NS_UMC, "imageSources" );
	const NamespacePropertyNamePair kVideoFrameSourcesPair( kXMP_NS_UMC, "videoFrameSources" );
	const NamespacePropertyNamePair kOutputsPair( kXMP_NS_UMC, "outputs" );
	const NamespacePropertyNamePair kTracksPair( kXMP_NS_UMC, "tracks" );
	const NamespacePropertyNamePair kVideoTracksPair( kXMP_NS_UMC, "videoTracks" );
	const NamespacePropertyNamePair kAudioTracksPair( kXMP_NS_UMC, "audioTracks" );
	const NamespacePropertyNamePair kUniqueIDPair( kXMP_NS_XMP_MM, "DocumentID" );
	const NamespacePropertyNamePair kNamePair( kXMP_NS_DM, "description" );
	const NamespacePropertyNamePair kTitlePair( kXMP_NS_DM, "title" );
	const NamespacePropertyNamePair kImageAspectRatioPair( kXMP_NS_UMC, "imageAspectRatio" );
	const NamespacePropertyNamePair kCanvasAspectRatioPair( kXMP_NS_UMC, "canvasAspectRatio" );
	const NamespacePropertyNamePair kVideoEditRatePair( kXMP_NS_UMC, "videoEditRate" );
	const NamespacePropertyNamePair kAudioEditRatePair( kXMP_NS_UMC, "audioEditRate" );
	const NamespacePropertyNamePair kStartTimeCodePair( kXMP_NS_DM, "startTimeCode" );
	const NamespacePropertyNamePair kTimeValuePair( kXMP_NS_DM, "timeValue" );
	const NamespacePropertyNamePair kTimeFormatPair( kXMP_NS_DM, "timeFormat" );
	const NamespacePropertyNamePair kExtensionPair( kXMP_NS_XMP, "extension" );
	const NamespacePropertyNamePair kInCountPair( kXMP_NS_UMC, "inCount" );
	const NamespacePropertyNamePair kDurationPair( kXMP_NS_UMC, "duration" );
	const NamespacePropertyNamePair kSourceIDPair( kXMP_NS_UMC, "sourceID" );
	const NamespacePropertyNamePair kShotsPair( kXMP_NS_UMC, "shots" );
	const NamespacePropertyNamePair kClipShotsPair( kXMP_NS_UMC, "clipShots" );
	const NamespacePropertyNamePair kTransitionShotsPair( kXMP_NS_UMC, "transitionShots" );
	const NamespacePropertyNamePair kFramesPair( kXMP_NS_UMC, "frames" );
	const NamespacePropertyNamePair kShotSourcesPair( kXMP_NS_UMC, "shotSources" );
	const NamespacePropertyNamePair kRecordPair( kXMP_NS_UMC, "record" );
	const NamespacePropertyNamePair kSourcePair( kXMP_NS_UMC, "source" );

	std::string to_string( const Signed64RationalType & rational ) {
		std::stringstream buf;
		if ( rational.Numerator() > 0 ) {
			buf<< rational.Numerator();
			if ( rational.Denominator() != 1 ) {
				buf << "/" << rational.Denominator();
			}
		}
		return buf.str();
	}

	std::string to_string( const Unsigned64RationalType & rational ) {
		std::stringstream buf;
		if ( rational.Numerator() > 0 ) {
			buf << rational.Numerator();
			if ( rational.Denominator() != 1 ) {
				buf << "/" << rational.Denominator();
			}
		}
		return buf.str();
	}

	void AddOrUpdateDataToXMPDOM( const std::string & stringValue,
		const NamespacePropertyNamePair & namespacePropertyNamePair,
		const spIStructureNode & parentNode )
	{
		auto existingNode = parentNode->GetNode( namespacePropertyNamePair.first, npos, namespacePropertyNamePair.second, npos );
		bool nodeAlreadyExists = existingNode ? true : false;

		if ( !stringValue.empty() ) {
			if ( nodeAlreadyExists && existingNode->GetNodeType() == INode::kNTSimple ) {
				auto simpleExistingNode = parentNode->GetSimpleNode( namespacePropertyNamePair.first, npos, namespacePropertyNamePair.second, npos );
				simpleExistingNode->SetValue( stringValue.c_str(), npos );
			} else {
				auto newNode = ISimpleNode::CreateSimpleNode( namespacePropertyNamePair.first, npos,
					namespacePropertyNamePair.second, npos, stringValue.c_str() );
				if ( nodeAlreadyExists ) parentNode->ReplaceNode( newNode );
				else parentNode->AppendNode( newNode );
			}
		} else if ( nodeAlreadyExists ) {
			parentNode->RemoveNode( namespacePropertyNamePair.first, npos, namespacePropertyNamePair.second, npos );
		}
	}

	void AddOrUpdateDataToXMPDOM( const TimeCode & timeCode, const spIStructureNode & parentNode )
	{
		if ( timeCode.StandardFrameRate() != TimeCode::kNonStandardFrameRate ) {
			auto sp = IStructureNode::CreateStructureNode( kStartTimeCodePair.first, npos, kStartTimeCodePair.second, npos );

			AddOrUpdateDataToXMPDOM( timeCode.SMPTETimecode(), kTimeValuePair, sp );

			const char * timeFormat = NULL;
			switch ( timeCode.StandardFrameRate() ) {
			case TimeCode::k24Fps:
				timeFormat = "24Timecode";
				break;

			case TimeCode::k25Fps:
				timeFormat = "25Timecode";
				break;

			case TimeCode::k29_97Fps:
				timeFormat = timeCode.IsDropFrame() ? "2997DropTimecode" : "2997NonDropTimecode";
				break;

			case TimeCode::k30Fps:
				timeFormat = "30Timecode";
				break;

			case TimeCode::k50Fps:
				timeFormat = "50Timecode";
				break;

			case TimeCode::k59_94Fps:
				timeFormat = timeCode.IsDropFrame() ? "5994DropTimecode" : "5994NonDropTimecode";
				break;

			case TimeCode::k60Fps:
				timeFormat = "60Timecode";
				break;

			case TimeCode::k23_976Fps:
				timeFormat = "23976Timecode";
				break;

			default:
				timeFormat = "";
				break;

			}
			AddOrUpdateDataToXMPDOM( std::string( timeFormat ), kTimeFormatPair, sp );
			if ( parentNode->GetNode( kStartTimeCodePair.first, npos, kStartTimeCodePair.second, npos ) ) {
				parentNode->ReplaceNode( sp );
			} else {
				parentNode->AppendNode( sp );
			}
		}
		
	}

	bool IgnoreEditUnitInCount( const EditUnitInCount & value ) {
		if ( value == kEditUnitInCountFromBeginning ) return true;
		return false;
	}

	bool IgnoreEditUnitDuration( const EditUnitDuration & value ) {
		if ( value == kEditUnitDurationTillEnd ) return true;
		return false;
	}

	UMC::UMC_Int64 stoi64( const std::string & strValue ) {
		return std::stoll( strValue );
	}

	UMC::UMC_Uns64 stou64( const std::string & strValue ) {
		return std::stoull( strValue );
	}

	//TODO: Handle error conditions later on
	UMC::Unsigned64RationalType stou64rt( const std::string & strValue ) {
		Unsigned64RationalType rt( 0 );
		rt.Numerator( strtoul( strValue.c_str(), NULL, 10 ) );
		size_t pos = strValue.find_first_of( "/" );
		if ( pos != std::string::npos ) {
			rt.Denominator( strtoul( strValue.c_str() + pos + 1, NULL, 10 ) );
		}
		return rt;
	}

	UMC::Signed64RationalType stos64rt( const std::string & strValue ) {
		Signed64RationalType rt( 0 );
		rt.Numerator( strtol( strValue.c_str(), NULL, 10 ) );
		size_t pos = strValue.find_first_of( "/" );
		if ( pos != std::string::npos ) {
			rt.Denominator( strtol( strValue.c_str() + pos + 1, NULL, 10 ) );
		}
		return rt;
	}

	bool UpdateDataFromXMPDOM( std::string & dataValue, const NamespacePropertyNamePair & pair,
		const spIStructureNode & parentNode, const std::string & resetValue )
	{
		spISimpleNode node = TryToGetSimpleNode( parentNode, pair );
		if ( node ) {
			auto value = node->GetValue();
			if ( value->size() ) {
				dataValue.assign( value->c_str() );
				return true;
			}
		}
		dataValue.assign( resetValue );
		return false;
	}

	bool UpdateDataFromXMPDOM( TimeCode & dataValue, const spIStructureNode & parentNode ) {
		spIStructureNode timeCodeNode = TryToGetStructNode( parentNode, kStartTimeCodePair );
		if ( timeCodeNode ) {
			spISimpleNode timeValue = TryToGetSimpleNode( timeCodeNode, kTimeValuePair );
			if ( timeValue ) {
				dataValue.SMPTETimecode( timeValue->GetValue()->c_str() );
				spISimpleNode timeFormat = TryToGetSimpleNode( timeCodeNode, kTimeFormatPair );
				if ( timeFormat ) {
					const char * timeFormatValue = timeFormat->GetValue()->c_str();
					if ( strcmp( timeFormatValue, "24Timecode" ) == 0 ) {
						dataValue.NonDropFrame();
						dataValue.StandardFrameRate( TimeCode::k24Fps );
						return true;
					} else if ( strcmp( timeFormatValue, "25Timecode" ) == 0 ) {
						dataValue.NonDropFrame();
						dataValue.StandardFrameRate( TimeCode::k25Fps );
						return true;
					} else if ( strcmp( timeFormatValue, "2997DropTimecode" ) == 0 ) {
						dataValue.DropFrame();
						dataValue.StandardFrameRate( TimeCode::k29_97Fps );
						return true;
					} else if ( strcmp( timeFormatValue, "2997NonDropTimecode" ) == 0 ) {
						dataValue.NonDropFrame();
						dataValue.StandardFrameRate( TimeCode::k29_97Fps );
						return true;
					} else if ( strcmp( timeFormatValue, "30Timecode" ) == 0 ) {
						dataValue.NonDropFrame();
						dataValue.StandardFrameRate( TimeCode::k30Fps );
						return true;
					} else if ( strcmp( timeFormatValue, "50Timecode" ) == 0 ) {
						dataValue.NonDropFrame();
						dataValue.StandardFrameRate( TimeCode::k50Fps );
						return true;
					} else if ( strcmp( timeFormatValue, "5994DropTimecode" ) == 0 ) {
						dataValue.DropFrame();
						dataValue.StandardFrameRate( TimeCode::k59_94Fps );
						return true;
					} else if ( strcmp( timeFormatValue, "5994NonDropTimecode" ) == 0 ) {
						dataValue.NonDropFrame();
						dataValue.StandardFrameRate( TimeCode::k59_94Fps );
						return true;
					} else if ( strcmp( timeFormatValue, "60Timecode" ) == 0 ) {
						dataValue.NonDropFrame();
						dataValue.StandardFrameRate( TimeCode::k60Fps );
						return true;
					} else if ( strcmp( timeFormatValue, "23976Timecode" ) == 0 ) {
						dataValue.NonDropFrame();
						dataValue.StandardFrameRate( TimeCode::k23_976Fps );
						return true;
					}
				}
			}
		}
		return false;
	}

	AdobeXMPCore::spIStructureNode ParseRDF( const std::string & buffer ) {
		spIDOMParser parser = GetParser();
		auto node = parser->Parse( buffer.c_str(), buffer.length() );
		if ( !node ) THROW_PARSING_ERROR;
		return node->ConvertToStructureNode();
	}

	AdobeXMPCore::spIStructureNode TryToGetActualNode( const spIStructureNode & node, const NamespacePropertyNamePair & pair ) {
		auto retNode = TryToGetStructNode( node, pair );
		if ( retNode ) {
			node->RemoveNode( pair.first, npos, pair.second, npos );
			return retNode;
		} else {
			auto parentNode = node->GetParent();
			if ( ( strcmp( parentNode->GetName()->c_str(), pair.second ) == 0 ) &&
				 ( strcmp( parentNode->GetNameSpace()->c_str(), pair.first ) == 0 ) )
			{
				return node;
			} 
		}
		return spIStructureNode();
	}

	size_t GetMatchingIndexForActualNode( const spIStructureNode & node, const NamespacePropertyNamePair ** array,
		size_t nElement )
	{
		for ( size_t i = 0; i < nElement; ++i ) {
			auto retNode = TryToGetStructNode( node, *array[ i ] );
			if ( retNode ) {
				return i;
			}
		}
		return -1;
	}

	/*AdobeXMPCore::spIStructureNode TryToGetActualNode( const spIStructureNode & node, const NamespacePropertyNamePair ** array,
		size_t nElement, size_t & matchedIndex )
	{
		matchedIndex = -1;
		for ( size_t i = 0; i < nElement; ++i ) {
			auto retNode = TryToGetActualNode( node, *array[i] );
			if ( retNode ) {
				matchedIndex = i;
				return retNode;
			}
		}
		return spIStructureNode();
	}*/

}
