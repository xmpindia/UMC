// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "utils/UMCToRDFConversion.h"

#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IVideoFrameSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/IFrame.h"
#include "interfaces/IShot.h"
#include "interfaces/ITrack.h"
#include "interfaces/IVideoTrack.h"
#include "interfaces/IAudioTrack.h"
#include "interfaces/ITrack.h"
#include "interfaces/IOutput.h"
#include "interfaces/IUMC.h"
#include "interfaces/INodeI.h"
#include "interfaces/IShotSource.h"

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

		spIXMPNode Convert( const Unsigned64RationalType & rational, const std::string & label ) {
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

		spIXMPStructureNode Convert ( const spcIVideoSource & videoSource ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "source" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "type", "video" ) );

			std::stringstream buf;
			if ( videoSource->GetInCount() != 0 ) {
				buf << videoSource->GetInCount();
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "inCount", buf.str().c_str() ) );
			}

			if ( videoSource->GetDuration() != npos ) {
				buf.str( "" );
				buf << videoSource->GetDuration();
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "duration", buf.str().c_str() ) );
			}

			auto node = Convert( videoSource->GetVideoEditRate(), "videoEditRate" );
			if ( node ) sp->AppendNode( node );
			
			node = Convert( videoSource->GetAudioEditRate(), "audioEditRate" );
			if ( node ) sp->AppendNode( node );

			node = Convert( videoSource->GetTimeCode() );
			if ( node ) sp->AppendNode( node );
			return sp;
		}

		spIXMPStructureNode Convert( const spcIAudioSource & audioSource ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "source" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "type", "audio" ) );

			std::stringstream buf;
			if ( audioSource->GetInCount() != 0 ) {
				buf << audioSource->GetInCount();
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "inCount", buf.str().c_str() ) );
			}

			if ( audioSource->GetDuration() != npos ) {
				buf.str( "" );
				buf << audioSource->GetDuration();
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "duration", buf.str().c_str() ) );
			}

			auto node = Convert( audioSource->GetAudioEditRate(), "audioEditRate" );
			if ( node ) sp->AppendNode( node );

			node = Convert( audioSource->GetTimeCode() );
			if ( node ) sp->AppendNode( node );
			return sp;
		}

		spIXMPStructureNode Convert( const spcIImageSource & imageSource ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "source" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "type", "image" ) );
			return sp;
		}

		spIXMPStructureNode Convert( const spcIVideoFrameSource & videoFrameSource ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "source" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "type", "videoFrame" ) );

			std::stringstream buf;
			if ( videoFrameSource->GetInCount() != 0 ) {
				buf << videoFrameSource->GetInCount();
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "inCount", buf.str().c_str() ) );
			}

			buf.str( "" );
			buf << videoFrameSource->GetVideoSource()->GetUniqueID();
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "sourceID", buf.str().c_str() ) );
			return sp;
		}

		spIXMPNode Convert( const spcISource & source ) {
			spIXMPStructureNode sp;
			switch ( source->GetType() ) {
			case ISource::kSourceTypeVideo:
				sp = Convert( dynamic_pointer_cast< const IVideoSource >( source ) );
				break;

			case ISource::kSourceTypeAudio:
				sp = Convert( dynamic_pointer_cast< const IAudioSource >( source ) );
				break;

			case ISource::kSourceTypeVideoFrame:
				sp = Convert( dynamic_pointer_cast< const IVideoFrameSource >( source ) );
				break;

			case ISource::kSourceTypeImage:
				sp = Convert( dynamic_pointer_cast< const IImageSource >( source ) );
				break;
			}
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				source->GetUniqueID().c_str() ) );
			std::string temp;
			temp = source->GetClipName();
			if ( temp.size() > 0 )
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "title", temp.c_str() ) );

			return sp;
		}

		spIXMPNode Convert( const spcIFrame & frame ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "frame" );

			EditUnitInCount inCount( frame->GetShotInCount() );
			auto source = frame->GetSource();

			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				source->GetUniqueID().c_str() ) );

			if ( inCount != kEditUnitInCountFromBeginning ) {
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "inCount",
					ConvertToString( inCount ).c_str() ) );
			}

			return sp;
		}

		spIXMPNode Convert( const spcIShotSource & shotSource ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "shotSource" );

			EditUnitInCount inCount( shotSource->GetShotInCount() );
			auto source = shotSource->GetSource();

			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				source->GetUniqueID().c_str() ) );

			if ( inCount != kEditUnitInCountFromBeginning ) {
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "inCount",
					ConvertToString( inCount ).c_str() ) );
			}

			return sp;
		}

		spIXMPNode Convert( const spcIShot & shot ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "shot" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				shot->GetUniqueID().c_str() ) );

			const char * type( NULL );
			switch ( shot->GetType() ) {
				case IShot::kShotTypeClip:
					type = "clip";
					break;

				case IShot::kShotTypeTransition:
					type = "transition";
					break;
			}
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "shotType", type ) );

			EditUnitInCount inCount( shot->GetInCount() );
			EditUnitDuration duration( shot->GetDuration() );

			if ( inCount != kEditUnitInCountFromBeginning || duration != kEditUnitDurationTillEnd ) {
				auto recordSp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "record" );
				if ( inCount != kEditUnitInCountFromBeginning ) {
					recordSp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "inCount",
						ConvertToString( inCount ).c_str() ) );
				}
				if ( duration != kEditUnitDurationTillEnd ) {
					recordSp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_UMC, "duration",
						ConvertToString( duration ).c_str() ) );
				}
				sp->AppendNode( recordSp );
			}

			if ( shot->ShotSourceCount() > 0 ) {
				auto shotSourceArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "shotSourceList" );
				auto shotSources = shot->GetShotSources();

				for ( size_t i = 0, count = shotSources.size(); i < count; i++ ) {
					shotSourceArray->AppendNode( Convert( shotSources[ i ] ) );
				}

				sp->AppendNode( shotSourceArray );
			}

			if ( shot->FrameCount() > 0 ) {
				auto framesArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "frameList" );
				IShot::cFrameList frames = shot->GetFrames();
				for ( size_t i = 0, count = frames.size(); i < count; i++ ) {
					framesArray->AppendNode( Convert( frames[ i ] ) );
				}
				sp->AppendNode( framesArray );
			}
			return sp;
		}

		spIXMPNode Convert( const spcIVideoTrack & track ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "track" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				track->GetUniqueID().c_str() ) );
			std::string temp;
			temp = track->GetName();
			if ( temp.size() > 0 )
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "description", temp.c_str() ) );

			auto node = Convert( track->GetVideoEditRate(), "videoEditRate" );
			if ( node ) sp->AppendNode( node );

			node = Convert( track->GetAudioEditRate(), "audioEditRate" );
			if ( node ) sp->AppendNode( node );

			if ( track->ShotCount() > 0 ) {
				auto shotsArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "shotList" );
				ITrack::cShotList shots = track->GetAllShots();
				for ( size_t i = 0, count = shots.size(); i < count; i++ ) {
					shotsArray->AppendNode( Convert( shots[ i ] ) );
				}
				sp->AppendNode( shotsArray );
			}

			return sp;
		}

		spIXMPNode Convert( const spcIAudioTrack & track ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "track" );
			sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_XMP_MM, "DocumentID",
				track->GetUniqueID().c_str() ) );
			std::string temp;
			temp = track->GetName();
			if ( temp.size() > 0 )
				sp->AppendNode( IXMPSimpleNode::CreateSimpleNode( kXMP_NS_DM, "description", temp.c_str() ) );

			auto node = Convert( track->GetAudioEditRate(), "audioEditRate" );
			if ( node ) sp->AppendNode( node );

			if ( track->ShotCount() > 0 ) {
				auto shotsArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "shotList" );
				ITrack::cShotList shots = track->GetAllShots();
				for ( size_t i = 0, count = shots.size(); i < count; i++ ) {
					shotsArray->AppendNode( Convert( shots[ i ] ) );
				}
				sp->AppendNode( shotsArray );
			}

			return sp;
		}

		spIXMPNode Convert( const spcIOutput & output ) {
			auto sp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "output" );
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

			node = Convert( output->GetVideoEditRate(), "editRate" );
			if ( node ) videoSp->AppendNode( node );

			if ( output->VideoTrackCount() > 0 ) {
				auto tracksArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "trackList" );
				IOutput::cVideoTrackList tracks = output->GetAllVideoTracks();
				for ( size_t i = 0, count = tracks.size(); i < count; i++ ) {
					tracksArray->AppendNode( Convert( tracks[ i ] ) );
				}
				videoSp->AppendNode( tracksArray );
			}
			sp->AppendNode( videoSp );

			auto audioSp = IXMPStructureNode::CreateStructureNode( kXMP_NS_UMC, "audio" );

			node = Convert( output->GetAudioEditRate(), "editRate" );
			if ( node ) audioSp->AppendNode( node );

			if ( output->AudioTrackCount() > 0 ) {
				auto tracksArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "trackList" );
				IOutput::cAudioTrackList tracks = output->GetAllAudioTracks();
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
				auto outputArray = IXMPArrayNode::CreateUnorderedArrayNode( kXMP_NS_UMC, "outputList" );
				IUMC::cOutputList outputs = umc->GetAllOutputs();
				for ( size_t i = 0, count = outputs.size(); i < count; i++ ) {
					outputArray->AppendNode( Convert( outputs[ i ] ) );
				}
				sp->AppendNode( outputArray );
			}

			auto mergedNode = umc->GetInternalNode()->GetMergedExtensionNode();
			if ( mergedNode ) 
				sp->AppendNode( mergedNode );
			return sp;
		}

		template < typename T>
		std::string TConvertToString( const T & value ) {
			std::stringstream buf;
			buf << value;
			return buf.str();
		}

		std::string ConvertToString( const EditUnitInCount & inCount ) {
			return TConvertToString( inCount );
		}

		std::string ConvertToString( const EditUnitDuration & duration ) {
			return TConvertToString( duration );
		}

	}


}
