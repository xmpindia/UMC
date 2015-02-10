// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "utils/UMCToRDFConversion.h"

#include "interfaces/ISource.h"
#include "interfaces/IUMC.h"

#include "XMPCore/Interfaces/IXMPMetadata.h"
#include "XMPCore/Interfaces/IXMPArrayNode.h"
#include "XMPCore/Interfaces/IXMPSimpleNode.h"
#include "XMPCore/Interfaces/IXMPCoreObjectFactory.h"

#include <sstream>

namespace INT_UMC {
	namespace UMCToRDFConversion {

		spIXMPNode Convert( const TimeCode & timeCode ) {
			if( timeCode.StandardFrameRate() != TimeCode::kNonStandardFrameRate ) {
				auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_DM, "startTimecode" );
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "timeValue",
					timeCode.SMPTETimecode().c_str() ) );
				const char * timeFormat = NULL;
				switch( timeCode.StandardFrameRate() ) {
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

				}
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "timeFormat", timeFormat ) );
				return sp;
			}
			return spIXMPNode();
		}

		spIXMPNode Convert( const FrameRate & frameRate ) {
			std::stringstream buf;
			if ( frameRate.Numerator() > 0 ) {
				if ( frameRate.Denominator() != 1 ) {
					buf << frameRate.Numerator() << "/" << frameRate.Denominator();
				} else if ( frameRate.Numerator() != 1 ) {
					buf << frameRate.Numerator();
				}
			}
			if ( buf.str().size() > 0 )
				return IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "editRate", buf.str().c_str() );
			else
				return spIXMPNode();
		}

		spIXMPNode Convert( const spcISource & source ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_DM, "source" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				source->GetUniqueID().c_str() ) );
			std::string temp;
			temp = source->GetClipName();
			if ( temp.size() > 0 )
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "title", temp.c_str() ) );

			const char * type( NULL );
			switch ( source->GetSourceType() ) {
				case ISource::kVideoSourceType:
					type = "video";
					break;

				case ISource::kAudioSourceType:
					type = "audio";
					break;

				case ISource::kStillImageSourceType:
					type = "stillImage";
					break;
			}
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "type", type ) );

			std::stringstream buf;

			if ( source->GetInCount() != 0 ) {
				buf << source->GetInCount();
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "startTime", buf.str().c_str() ) );
			}

			if ( source->GetDuration() != npos ) {
				buf.str("");
				buf << source->GetDuration();
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "duration", buf.str().c_str() ) );
			}

			auto node = Convert( source->GetEditRate() );
			if ( node ) sp->AppendNode( node );
			node = Convert( source->GetTimeCode() );
			if ( node ) sp->AppendNode( node );
			return sp;
		}

		spIXMPMetadata Convert( const spcIUMC & umc ) {
			auto sp = IXMPMetadata::CreateMetadata();
			if ( umc->SourceCount() > 0 ) {
				auto sourceArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "sourceList" );
				IUMC::cSourceList sources = umc->GetAllSources();
				for ( size_t i = 0, count = sources.size(); i < count; i++ ) {
					sourceArray->AppendNode( Convert( sources[ i ] ) );
				}
				sp->AppendNode( sourceArray );
			}
			return sp;
		}

	}


}
