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
#include "interfaces/IFrame.h"
#include "interfaces/IShot.h"
#include "interfaces/ITrack.h"
#include "interfaces/IOutput.h"
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

		spIXMPNode Convert( const Unsigned64RationalType & rational, const std::string label ) {
			std::stringstream buf;
			if ( rational.Numerator() > 0 ) {
				if ( rational.Denominator() != 1 ) {
					buf << rational.Numerator() << "/" << rational.Denominator();
				} else if ( rational.Numerator() != 1 ) {
					buf << rational.Numerator();
				}
			}
			if ( buf.str().size() > 0 )
				return IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, label.c_str(), buf.str().c_str() );
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

			auto node = Convert( source->GetEditRate(), "edit_rate" );
			if ( node ) sp->AppendNode( node );
			node = Convert( source->GetTimeCode() );
			if ( node ) sp->AppendNode( node );
			return sp;
		}

		spIXMPNode Convert( const spcIFrame & frame ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_DM, "frame" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				frame->GetUniqueID().c_str() ) );

			return sp;
		}

		spIXMPNode Convert( const spcIShot & shot ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_DM, "shot" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				shot->GetUniqueID().c_str() ) );

			if ( shot->FrameCount() > 0 ) {
				auto framesArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "frames" );
				IShot::cFrameList frames = shot->GetFrames();
				for ( size_t i = 0, count = frames.size(); i < count; i++ ) {
					framesArray->AppendNode( Convert( frames[ i ] ) );
				}
				sp->AppendNode( framesArray );
			}

			return sp;
		}

		spIXMPNode Convert( const spcITrack & track ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_DM, "track" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				track->GetUniqueID().c_str() ) );
			std::string temp;
			temp = track->GetName();
			if ( temp.size() > 0 )
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "description", temp.c_str() ) );

			auto node = Convert( track->GetEditRate(), "editRate" );
			if ( node ) sp->AppendNode( node );

			if ( track->ShotCount() > 0 ) {
				auto shotsArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "shots" );
				ITrack::cShotList shots = track->GetShots();
				for ( size_t i = 0, count = shots.size(); i < count; i++ ) {
					shotsArray->AppendNode( Convert( shots[ i ] ) );
				}
				sp->AppendNode( shotsArray );
			}

			return sp;
		}

		spIXMPNode Convert( const spcIOutput & output ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_DM, "output" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				output->GetUniqueID().c_str() ) );
			std::string temp;
			temp = output->GetName();
			if ( temp.size() > 0 )
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "description", temp.c_str() ) );

			temp = output->GetTitle();
			if ( temp.size() > 0 )
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "title", temp.c_str() ) );

			auto node = Convert( output->GetCanvasAspectRatio(), "canvasAspectRatio" );
			if ( node ) sp->AppendNode( node );

			node = Convert( output->GetImageAspectRatio(), "imageAspectRatio" );
			if ( node ) sp->AppendNode( node );

			auto videoSp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "video" );

			node = Convert( output->GetVideoEditRate(), "videoFrameRate" );
			if ( node ) videoSp->AppendNode( node );

			if ( output->VideoTrackCount() > 0 ) {
				auto tracksArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "tracks" );
				IOutput::cTrackList tracks = output->GetVideoTracks();
				for ( size_t i = 0, count = tracks.size(); i < count; i++ ) {
					tracksArray->AppendNode( Convert( tracks[ i ] ) );
				}
				videoSp->AppendNode( tracksArray );
			}
			sp->AppendNode( videoSp );

			auto audioSp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "audio" );

			node = Convert( output->GetAudioEditRate(), "audioFrameRate" );
			if ( node ) audioSp->AppendNode( node );

			if ( output->AudioTrackCount() > 0 ) {
				auto tracksArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "tracks" );
				IOutput::cTrackList tracks = output->GetAudioTracks();
				for ( size_t i = 0, count = tracks.size(); i < count; i++ ) {
					tracksArray->AppendNode( Convert( tracks[ i ] ) );
				}
				audioSp->AppendNode( tracksArray );
			}
			sp->AppendNode( audioSp );
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

			if ( umc->OutputCount() > 0 ) {
				auto outputArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "compositions" );
				IUMC::cOutputList outputs = umc->GetOutputs();
				for ( size_t i = 0, count = outputs.size(); i < count; i++ ) {
					outputArray->AppendNode( Convert( outputs[ i ] ) );
				}
				sp->AppendNode( outputArray );
			}
			return sp;
		}

	}


}
