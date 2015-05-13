// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/UMCImpl.h"

#include "interfaces/IUniqueIDGenerator.h"

#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/IVideoFrameSource.h"
#include "interfaces/IOutput.h"

#include "interfaces/ICustomDataHandlerRegistry.h"

#include "utils/Utils.h"

#include "utils/UMCToRDFConversion.h"

#include "XMPCore/Interfaces/IXMPDOMImplementationRegistry.h"
#include "XMPCore/Interfaces/IXMPCoreObjectFactory.h"
#include "XMPCore/Interfaces/IXMPDOMSerializer.h"

namespace INT_UMC {

	spIOutput UMCImpl::AddOutput() {
		spIOutput output = CreateOutput( mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker(),
			mNode->GetInternalNode()->GetUniqueIDGenerator() );
		AddElementToMap< OutputMap, spIOutput >( mOutputMap, output, shared_from_this() );
		return output;
	}

	std::string UMCImpl::SerializeToBuffer() const {
		using namespace NS_XMPCORE;
		spcIUMC umc = shared_from_this();
		auto sp = UMCToRDFConversion::Convert( umc );
		auto serializer = IXMPDOMImplementationRegistry::GetDOMImplementationRegistry()->CreateSerializer( "rdf" );
		auto spString = serializer->Serialize( sp );
		return std::string( spString->c_str() );
	}

	INode::eNodeTypes UMCImpl::GetNodeType() const {
		return kNodeTypeUMC;
	}

	const std::string & UMCImpl::GetUniqueID() const {
		return kEmptyString;
	}

	spcINode UMCImpl::GetParentNode() const {
		return spcINode();
	}

	spINode UMCImpl::GetParentNode() {
		return spINode();
	}

	spcINode UMCImpl::GetDecendantNode( const std::string & id ) const {
		return const_cast< UMCImpl * >( this )->GetDecendantNode( id );
	}

	spINode UMCImpl::GetDecendantNode( const std::string & id ) {
		spINode node = GetChildNode( id );
		if ( node ) return node;
		node = GetDecendantFromMap< VideoSourceMap >( mVideoSourceMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap< AudioSourceMap >( mAudioSourceMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap< VideoFrameSourceMap >( mVideoFrameSourceMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap< ImageSourceMap >( mImageSourceMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap< OutputMap >( mOutputMap, id );
		return node;
	}

	spcINode UMCImpl::GetChildNode( const std::string & id ) const {
		return const_cast< UMCImpl * >( this )->GetChildNode( id );
	}

	spINode UMCImpl::GetChildNode( const std::string & id ) {
		spINode node = mVideoSourceMap.find( id )->second;
		if ( node ) return node;
		node = mAudioSourceMap.find( id )->second;
		if ( node ) return node;
		node = mVideoFrameSourceMap.find( id )->second;
		if ( node ) return node;
		node = mImageSourceMap.find( id )->second;
		if ( node ) return node;
		node = mOutputMap.find( id )->second;
		return node;
	}

	size_t UMCImpl::OutputCount() const {
		return mOutputMap.size();
	}

	IUMC::OutputList UMCImpl::GetAllOutputs() {
		return CreateListFromMap< spIOutput, OutputMap >( mOutputMap );
	}

	IUMC::cOutputList UMCImpl::GetAllOutputs() const {
		return CreateListFromMap< spcIOutput, OutputMap >( mOutputMap );
	}

	spIOutput UMCImpl::GetOutput( const std::string & uniqueID ) {
		return GetElementFromMap< spIOutput, OutputMap > ( mOutputMap, uniqueID );
	}

	spcIOutput UMCImpl::GetOutput( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIOutput, OutputMap > ( mOutputMap, uniqueID );
	}

	size_t UMCImpl::RemoveAllOutputs() {
		bool safeToClear = SafeToClearMap( mOutputMap );
		if ( safeToClear )
			return ClearMap( mOutputMap );
		else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
	}

	size_t UMCImpl::RemoveOutput( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap< OutputMap >( mOutputMap, uniqueID );
	}

	spIVideoSource UMCImpl::AddVideoSource() {
		spIVideoSource source = CreateVideoSource( mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker(),
			mNode->GetInternalNode()->GetUniqueIDGenerator() );
		AddElementToMap< VideoSourceMap, spIVideoSource >( mVideoSourceMap, source,shared_from_this() );
		return source;
	}

	spIAudioSource UMCImpl::AddAudioSource() {
		spIAudioSource source = CreateAudioSource( mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker(),
			mNode->GetInternalNode()->GetUniqueIDGenerator() );
		AddElementToMap< AudioSourceMap, spIAudioSource >( mAudioSourceMap, source, shared_from_this() );
		return source;
	}

	spIVideoFrameSource UMCImpl::AddVideoFrameSource( const spIVideoSource & videoSource ) {
		spIVideoFrameSource source = CreateVideoFrameSource( videoSource, mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker(),
			mNode->GetInternalNode()->GetUniqueIDGenerator() );
		AddElementToMap< VideoFrameSourceMap, spIVideoFrameSource >( mVideoFrameSourceMap, source, shared_from_this() );
		return source;
	}

	spIImageSource UMCImpl::AddImageSource() {
		spIImageSource source = CreateImageSource( mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker(),
			mNode->GetInternalNode()->GetUniqueIDGenerator() );
		AddElementToMap< ImageSourceMap, spIImageSource >( mImageSourceMap, source, shared_from_this() );
		return source;
	}

	size_t UMCImpl::SourceCount() const {
		return mVideoSourceMap.size() + mAudioSourceMap.size() + mVideoFrameSourceMap.size() + mImageSourceMap.size();
	}

	size_t UMCImpl::VideoSourceCount() const {
		return mVideoSourceMap.size();
	}

	size_t UMCImpl::AudioSourceCount() const {
		return mAudioSourceMap.size();
	}

	size_t UMCImpl::VideoFrameSourceCount() const {
		return mVideoFrameSourceMap.size();
	}

	size_t UMCImpl::ImageSourceCount() const {
		return mImageSourceMap.size();
	}

	IUMC::SourceList UMCImpl::GetAllSources() {
		SourceList list;
		AppendToListFromMap< spISource, VideoSourceMap >( list, mVideoSourceMap );
		AppendToListFromMap< spISource, AudioSourceMap >( list, mAudioSourceMap );
		AppendToListFromMap< spISource, VideoFrameSourceMap >( list, mVideoFrameSourceMap );
		AppendToListFromMap< spISource, ImageSourceMap >( list, mImageSourceMap );
		return list;
	}

	IUMC::cSourceList UMCImpl::GetAllSources() const {
		cSourceList list;
		AppendToListFromMap< spcISource, VideoSourceMap >( list, mVideoSourceMap );
		AppendToListFromMap< spcISource, AudioSourceMap >( list, mAudioSourceMap );
		AppendToListFromMap< spcISource, VideoFrameSourceMap >( list, mVideoFrameSourceMap );
		AppendToListFromMap< spcISource, ImageSourceMap >( list, mImageSourceMap );
		return list;
	}

	IUMC::VideoSourceList UMCImpl::GetAllVideoSources() {
		return CreateListFromMap< spIVideoSource, VideoSourceMap >( mVideoSourceMap );
	}

	IUMC::cVideoSourceList UMCImpl::GetAllVideoSources() const {
		return CreateListFromMap< spcIVideoSource, VideoSourceMap >( mVideoSourceMap );
	}

	IUMC::AudioSourceList UMCImpl::GetAllAudioSources() {
		return CreateListFromMap< spIAudioSource, AudioSourceMap >( mAudioSourceMap );
	}

	IUMC::cAudioSourceList UMCImpl::GetAllAudioSources() const {
		return CreateListFromMap< spcIAudioSource, AudioSourceMap >( mAudioSourceMap );
	}

	IUMC::VideoFrameSourceList UMCImpl::GetAllVideoFrameSources() {
		return CreateListFromMap< spIVideoFrameSource, VideoFrameSourceMap >( mVideoFrameSourceMap );
	}

	IUMC::cVideoFrameSourceList UMCImpl::GetAllVideoFrameSources() const {
		return CreateListFromMap< spcIVideoFrameSource, VideoFrameSourceMap >( mVideoFrameSourceMap );
	}

	IUMC::ImageSourceList UMCImpl::GetAllImageSources() {
		return CreateListFromMap< spIImageSource, ImageSourceMap >( mImageSourceMap );
	}

	IUMC::cImageSourceList UMCImpl::GetAllImageSources() const {
		return CreateListFromMap< spcIImageSource, ImageSourceMap >( mImageSourceMap );
	}

	spISource UMCImpl::GetSource( const std::string & uniqueID ) {
		spISource node = GetElementFromMap< spISource, VideoSourceMap >( mVideoSourceMap, uniqueID );
		if ( node ) return node;
		node = GetElementFromMap< spISource, AudioSourceMap >( mAudioSourceMap, uniqueID );
		if ( node ) return node;
		node = GetElementFromMap< spISource, VideoFrameSourceMap >( mVideoFrameSourceMap, uniqueID );
		if ( node ) return node;
		node = GetElementFromMap< spISource, ImageSourceMap >( mImageSourceMap, uniqueID );
		return node;
	}

	spcISource UMCImpl::GetSource( const std::string & uniqueID ) const {
		return const_cast< UMCImpl *>( this )->GetSource( uniqueID );
	}

	spIVideoSource UMCImpl::GetVideoSource( const std::string & uniqueID ) {
		return GetElementFromMap< spIVideoSource, VideoSourceMap >( mVideoSourceMap, uniqueID );
	}

	spcIVideoSource UMCImpl::GetVideoSource( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIVideoSource, VideoSourceMap >( mVideoSourceMap, uniqueID );
	}

	spIAudioSource UMCImpl::GetAudioSource( const std::string & uniqueID ) {
		return GetElementFromMap< spIAudioSource, AudioSourceMap >( mAudioSourceMap, uniqueID );
	}

	spcIAudioSource UMCImpl::GetAudioSource( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIAudioSource, AudioSourceMap >( mAudioSourceMap, uniqueID );
	}

	spIVideoFrameSource UMCImpl::GetVideoFrameSource( const std::string & uniqueID ) {
		return GetElementFromMap< spIVideoFrameSource, VideoFrameSourceMap >( mVideoFrameSourceMap, uniqueID );
	}

	spcIVideoFrameSource UMCImpl::GetVideoFrameSource( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIVideoFrameSource, VideoFrameSourceMap >( mVideoFrameSourceMap, uniqueID );
	}

	spIImageSource UMCImpl::GetImageSource( const std::string & uniqueID ) {
		return GetElementFromMap< spIImageSource, ImageSourceMap >( mImageSourceMap, uniqueID );
	}

	spcIImageSource UMCImpl::GetImageSource( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIImageSource, ImageSourceMap >( mImageSourceMap, uniqueID );
	}

	size_t UMCImpl::RemoveAllSources() {
		bool safeToClear = SafeToClearMap( mVideoFrameSourceMap );
		if ( safeToClear ) {
			safeToClear = SafeToClearMap( mAudioSourceMap );
		} else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
		if ( safeToClear ) {
			safeToClear = SafeToClearMap( mImageSourceMap ); 
		} else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}

		if ( safeToClear ) {
			// Get the list of all 
			if ( mVideoFrameSourceMap.size() > 0 ) {
				std::map< std::string, size_t > videoSourceReferences;
				auto it = mVideoFrameSourceMap.begin(); auto itEnd = mVideoFrameSourceMap.end();
				for ( ; it != itEnd; it++ ) {
					const std::string & uid = it->second->GetVideoSource()->GetUniqueID();
					auto rtVal = videoSourceReferences.insert( std::make_pair( uid, ( size_t ) 0 ) );
					rtVal.first->second++;
				}
				auto it2 = mVideoSourceMap.begin();
				auto it2End = mVideoSourceMap.end();
				for( ; it2 != it2End; it2++ ) {
					size_t actualReferenceCount = it2->second->GetReferenceCount();
					size_t expectedReferenceCount(0 );
					try {
						expectedReferenceCount = videoSourceReferences.at( it2->second->GetUniqueID() );
					} catch( std::out_of_range & ) {
						// do nothing
					}
					if ( actualReferenceCount != expectedReferenceCount ) {
						THROW_NODE_IS_REFERENCED( "remove" );
						return 0;
					}
				}
			} else {
				safeToClear = SafeToClearMap( mVideoSourceMap );
				if ( !safeToClear ) {
					THROW_NODE_IS_REFERENCED( "remove" );
					return 0;
				}
			}
		} else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}

		size_t expectedCount = SourceCount();

		size_t count( 0 );
		count += ClearMap( mVideoFrameSourceMap );
		count += ClearMap( mVideoSourceMap );
		count += ClearMap( mAudioSourceMap );
		count += ClearMap( mImageSourceMap );
		assert( expectedCount == count );
		return count;
	}

	size_t UMCImpl::RemoveAllVideoSources() {
		bool safeToClear = SafeToClearMap( mVideoSourceMap );
		if ( safeToClear )
			return ClearMap( mVideoSourceMap );
		else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
	}

	size_t UMCImpl::RemoveAllAudioSources() {
		bool safeToClear = SafeToClearMap( mAudioSourceMap );
		if ( safeToClear )
			return ClearMap( mAudioSourceMap );
		else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
	}

	size_t UMCImpl::RemoveAllVideoFramesSources() {
		bool safeToClear = SafeToClearMap( mVideoFrameSourceMap );
		if ( safeToClear )
			return ClearMap( mVideoFrameSourceMap );
		else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
	}

	size_t UMCImpl::RemoveAllImageSources() {
		bool safeToClear = SafeToClearMap( mImageSourceMap );
		if ( safeToClear )
			return ClearMap( mImageSourceMap );
		else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
	}

	size_t UMCImpl::RemoveSource( const std::string & uniqueID ) {
		size_t count = TryAndRemoveElementFromMap( mVideoSourceMap, uniqueID );
		if ( count != 0 ) return count;
		count = TryAndRemoveElementFromMap( mAudioSourceMap, uniqueID );
		if ( count != 0 ) return count;
		count = TryAndRemoveElementFromMap( mVideoFrameSourceMap, uniqueID );
		if ( count != 0 ) return count;
		count = TryAndRemoveElementFromMap( mImageSourceMap, uniqueID );
		return count;
	}

	size_t UMCImpl::RemoveVideoSource( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mVideoSourceMap, uniqueID );
	}

	size_t UMCImpl::RemoveAudioSource( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mAudioSourceMap, uniqueID );
	}

	size_t UMCImpl::RemoveVideoFrameSource( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mVideoFrameSourceMap, uniqueID );
	}

	size_t UMCImpl::RemoveImageSource( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mImageSourceMap, uniqueID );
	}

	INode::NodeList UMCImpl::GetAllChildren() {
		NodeList list;
		AppendToListFromMap< spINode, VideoSourceMap >( list, mVideoSourceMap );
		AppendToListFromMap< spINode, AudioSourceMap >( list, mAudioSourceMap );
		AppendToListFromMap< spINode, VideoFrameSourceMap >( list, mVideoFrameSourceMap );
		AppendToListFromMap< spINode, ImageSourceMap >( list, mImageSourceMap );
		AppendToListFromMap< spINode, OutputMap >( list, mOutputMap );
		return list;
	}

	INode::cNodeList UMCImpl::GetAllChildren() const {
		cNodeList list;
		AppendToListFromMap< spcINode, VideoSourceMap >( list, mVideoSourceMap );
		AppendToListFromMap< spcINode, AudioSourceMap >( list, mAudioSourceMap );
		AppendToListFromMap< spcINode, VideoFrameSourceMap >( list, mVideoFrameSourceMap );
		AppendToListFromMap< spcINode, ImageSourceMap >( list, mImageSourceMap );
		AppendToListFromMap< spcINode, OutputMap >( list, mOutputMap );
		return list;
	}

	INode::NodeList UMCImpl::GetAllDecendants() {
		NodeList list;
		AppendDecendantsFromMapToList< spINode >( list, mVideoSourceMap );
		AppendDecendantsFromMapToList< spINode >( list, mAudioSourceMap );
		AppendDecendantsFromMapToList< spINode >( list, mVideoFrameSourceMap );
		AppendDecendantsFromMapToList< spINode >( list, mImageSourceMap );
		AppendDecendantsFromMapToList< spINode >( list, mOutputMap );
		return list;
	}

	INode::cNodeList UMCImpl::GetAllDecendants() const {
		cNodeList list;
		AppendDecendantsFromMapToList< spcINode >( list, mVideoSourceMap );
		AppendDecendantsFromMapToList< spcINode >( list, mAudioSourceMap );
		AppendDecendantsFromMapToList< spcINode >( list, mVideoFrameSourceMap );
		AppendDecendantsFromMapToList< spcINode >( list, mImageSourceMap );
		AppendDecendantsFromMapToList< spcINode >( list, mOutputMap );
		return list;
	}

	size_t UMCImpl::GetReferenceCount() const { return 0; }

	spICustomData UMCImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData UMCImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}

	bool UMCImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mNode->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pINodeI UMCImpl::GetInternalNode() {
		return mNode->GetInternalNode();
	}

	pcINodeI UMCImpl::GetInternalNode() const {
		return mNode->GetInternalNode();
	}

	UMCImpl::UMCImpl()
	{
		auto first = CreateUniqueIDAndReferenceTracker();
		auto second = CreateUniqueIDGenerator( first );
		mNode = CreateNode( first, second, INode::kNodeTypeUMC );
	}

}

namespace UMC {
	spIUMC IUMC::CreateEmptyUMC() {
		INT_UMC::UMCImpl * ptr = new INT_UMC::UMCImpl();
		return shared_ptr< INT_UMC::UMCImpl >( ptr );
	}

	bool IUMC::RegisterCustomNodeHandler( const std::string & customNameSpace, const std::string & customName, const spICustomDataHandler & customDataHandler ) {
		return INT_UMC::ICustomDataHandlerRegistry::GetInstance()->RegisterHandler( customNameSpace, customName, customDataHandler );
	}

}
