// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/UMCImpl.h"
#include "implHeaders/VideoSourceImpl.h"
#include "implHeaders/AudioSourceImpl.h"
#include "implHeaders/VideoFrameSourceImpl.h"
#include "implHeaders/ImageSourceImpl.h"
#include "implHeaders/SourceImpl.h"
#include "implHeaders/OutputImpl.h"

#include "implHeaders/UniqueIDGeneratorImpl.h"

#include "utils/UMCToRDFConversion.h"
#include "utils/Utils.h"

#include "XMPCore/Interfaces/IXMPDOMImplementationRegistry.h"
#include "XMPCore/Interfaces/IXMPCoreObjectFactory.h"
#include "XMPCore/Interfaces/IXMPDOMSerializer.h"

namespace INT_UMC {

	spIOutput UMCImpl::AddOutput() {
		const std::string & uniqueIDStr = mspUniqueIDGenerator->GenerateUniqueID( INode::kNodeTypeOutput );
		spIOutput output = std::make_shared
			<
				OutputImpl, const std::string &, const spUniqueIDSet &, spIUniqueIDGenerator &, const spIUMC &
			> ( uniqueIDStr, mspUniqueIDSet, mspUniqueIDGenerator, shared_from_this() );
		;
		AddElementToMap< spIOutput, OutputMap >( mOutputMap, uniqueIDStr, output, mspUniqueIDSet );
		return output;
	}

	std::string UMCImpl::SerializeToBuffer() const {
		using namespace NS_XMPCORE;
		auto sp = UMCToRDFConversion::Convert( shared_from_this() );
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
		node = GetDecendantFromMap< spINode, VideoSourceMap >( mVideoSourceMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap< spINode, AudioSourceMap >( mAudioSourceMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap< spINode, VideoFrameSourceMap >( mVideoFrameSourceMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap< spINode, ImageSourceMap >( mImageSourceMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap< spINode, OutputMap >( mOutputMap, id );
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
		return ClearMap< OutputMap >( mOutputMap, mspUniqueIDSet );
	}

	size_t UMCImpl::RemoveOutput( const std::string & uniqueID ) {
		return RemoveElementFromMap< OutputMap >( mOutputMap, uniqueID, mspUniqueIDSet );
	}

	spIVideoSource UMCImpl::AddVideoSource() {
		const std::string & uniqueIDStr = mspUniqueIDGenerator->GenerateUniqueID( INode::kNodeTypeSource );
		spIVideoSource source = std::make_shared
			<
				VideoSourceImpl, const std::string &, const spUniqueIDSet &, spIUniqueIDGenerator &, const spIUMC &
			> ( uniqueIDStr, mspUniqueIDSet, mspUniqueIDGenerator, shared_from_this() );
		;
		AddElementToMap< spIVideoSource, VideoSourceMap >( mVideoSourceMap, uniqueIDStr, source, mspUniqueIDSet );
		return source;
	}

	spIAudioSource UMCImpl::AddAudioSource() {
		const std::string & uniqueIDStr = mspUniqueIDGenerator->GenerateUniqueID( INode::kNodeTypeSource );
		spIAudioSource source = std::make_shared
			<
				AudioSourceImpl, const std::string &, const spUniqueIDSet &, spIUniqueIDGenerator &, const spIUMC &
			> ( uniqueIDStr, mspUniqueIDSet, mspUniqueIDGenerator, shared_from_this() );
		;
		AddElementToMap< spIAudioSource, AudioSourceMap >( mAudioSourceMap, uniqueIDStr, source, mspUniqueIDSet );
		return source;
	}

	spIVideoFrameSource UMCImpl::AddVideoFrameSource( const spIVideoSource & videoSource ) {
		const std::string & uniqueIDStr = mspUniqueIDGenerator->GenerateUniqueID( INode::kNodeTypeSource );
		spIVideoFrameSource source = std::make_shared
			<
				VideoFrameSourceImpl, const std::string &, const spIVideoSource &,
				const spUniqueIDSet &, spIUniqueIDGenerator &, const spIUMC &
			> ( uniqueIDStr, videoSource, mspUniqueIDSet, mspUniqueIDGenerator, shared_from_this() );
		;
		AddElementToMap< spIVideoFrameSource, VideoFrameSourceMap >( mVideoFrameSourceMap, uniqueIDStr, source, mspUniqueIDSet );
		return source;
	}

	spIImageSource UMCImpl::AddImageSource() {
		const std::string & uniqueIDStr = mspUniqueIDGenerator->GenerateUniqueID( INode::kNodeTypeSource );
		spIImageSource source = std::make_shared
			<
				ImageSourceImpl, const std::string &, const spUniqueIDSet &, spIUniqueIDGenerator &, const spIUMC &
			> ( uniqueIDStr, mspUniqueIDSet, mspUniqueIDGenerator, shared_from_this() );
		;
		AddElementToMap< spIImageSource, ImageSourceMap >( mImageSourceMap, uniqueIDStr, source, mspUniqueIDSet );
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
		size_t expectedCount = SourceCount();
		size_t count = ClearMap< VideoSourceMap >( mVideoSourceMap, mspUniqueIDSet );
		count += ClearMap< AudioSourceMap >( mAudioSourceMap, mspUniqueIDSet );
		count += ClearMap< VideoFrameSourceMap >( mVideoFrameSourceMap, mspUniqueIDSet );
		count += ClearMap< ImageSourceMap >( mImageSourceMap, mspUniqueIDSet );
		assert( expectedCount == count );
		return count;
	}

	size_t UMCImpl::RemoveAllVideoSources() {
		size_t expectedCount = VideoSourceCount();
		size_t count = ClearMap( mVideoSourceMap, mspUniqueIDSet );
		assert( expectedCount == count );
		return count;
	}

	size_t UMCImpl::RemoveAllAudioSources() {
		size_t expectedCount = AudioSourceCount();
		size_t count = ClearMap( mAudioSourceMap, mspUniqueIDSet );
		assert( expectedCount == count );
		return count;
	}

	size_t UMCImpl::RemoveAllVideoFramesSources() {
		size_t expectedCount = VideoFrameSourceCount();
		size_t count = ClearMap( mVideoFrameSourceMap, mspUniqueIDSet );
		assert( expectedCount == count );
		return count;
	}

	size_t UMCImpl::RemoveAllImageSources() {
		size_t expectedCount = ImageSourceCount();
		size_t count = ClearMap( mImageSourceMap, mspUniqueIDSet );
		assert( expectedCount == count );
		return count;
	}

	size_t UMCImpl::RemoveSource( const std::string & uniqueID ) {
		size_t count = RemoveElementFromMap( mVideoSourceMap, uniqueID, mspUniqueIDSet );
		if ( count != 0 ) return count;
		count = RemoveElementFromMap( mAudioSourceMap, uniqueID, mspUniqueIDSet );
		if ( count != 0 ) return count;
		count = RemoveElementFromMap( mVideoFrameSourceMap, uniqueID, mspUniqueIDSet );
		if ( count != 0 ) return count;
		count = RemoveElementFromMap( mImageSourceMap, uniqueID, mspUniqueIDSet );
		return count;
	}

	size_t UMCImpl::RemoveVideoSource( const std::string & uniqueID ) {
		return RemoveElementFromMap( mVideoSourceMap, uniqueID, mspUniqueIDSet );
	}

	size_t UMCImpl::RemoveAudioSource( const std::string & uniqueID ) {
		return RemoveElementFromMap( mAudioSourceMap, uniqueID, mspUniqueIDSet );
	}

	size_t UMCImpl::RemoveVideoFrameSource( const std::string & uniqueID ) {
		return RemoveElementFromMap( mVideoFrameSourceMap, uniqueID, mspUniqueIDSet );
	}

	size_t UMCImpl::RemoveImageSource( const std::string & uniqueID ) {
		return RemoveElementFromMap( mImageSourceMap, uniqueID, mspUniqueIDSet );
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

	UMCImpl::UMCImpl()
		: mspUniqueIDSet( new UniqueIDSet() )
		, mspUniqueIDGenerator( UniqueIDGeneratorImpl::CreateUniqueIDGenerator( mspUniqueIDSet ) ) { }

}

namespace UMC {
	spIUMC IUMC::CreateEmptyUMC() {
		INT_UMC::UMCImpl * ptr = new INT_UMC::UMCImpl();
		return shared_ptr< INT_UMC::UMCImpl >( ptr );
	}
}
