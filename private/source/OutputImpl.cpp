// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/OutputImpl.h"
#include "implHeaders/TrackImpl.h"	//TODO: remove this and VideoTrackImp and AudioTrackImpl. Remove next 2 lines also
#include "interfaces/IVideoTrack.h"
#include "interfaces/IAudioTrack.h"
#include "interfaces/IUniqueIDGenerator.h"
#include "interfaces/IUMC.h"

#include "UMCDefines_I.h"
#include "utils/Utils.h"

#include <assert.h>

namespace INT_UMC {

	const std::string & OutputImpl::GetUniqueID() const {
		return mUniqueID;
	}

	spITrack OutputImpl::GetTrack( const std::string & uniqueID ) {
		spITrack track = GetVideoTrack( uniqueID );
		if ( track ) return track;
		track = GetAudioTrack( uniqueID );
		return track;
	}

	spcITrack OutputImpl::GetTrack( const std::string & uniqueID ) const {
		return const_cast< OutputImpl *>( this )->GetTrack( uniqueID );
	}

	IOutput::TrackList OutputImpl::GetAllTracks() {
		TrackList list;
		AppendToListFromMap< spITrack, VideoTrackMap >( list, mVideoTrackMap );
		AppendToListFromMap< spITrack, AudioTrackMap >( list, mAudioTrackMap );
		return list;
	}

	IOutput::cTrackList OutputImpl::GetAllTracks() const {
		cTrackList list;
		AppendToListFromMap< spcITrack, VideoTrackMap >( list, mVideoTrackMap );
		AppendToListFromMap< spcITrack, AudioTrackMap >( list, mAudioTrackMap );
		return list;
	}

	INode::eNodeTypes OutputImpl::GetNodeType() const {
		return kNodeTypeOutput;
	}

	spcINode OutputImpl::GetDecendantNode( const std::string & id ) const {
		return const_cast< OutputImpl * >( this )->GetDecendantNode( id );
	}

	spINode OutputImpl::GetDecendantNode( const std::string & id ) {
		auto node = GetChildNode( id );
		if ( node ) return node;
		node = GetDecendantFromMap< spINode, VideoTrackMap >( mVideoTrackMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap< spINode, AudioTrackMap >( mAudioTrackMap, id );
		return node;
	}

	spcINode OutputImpl::GetChildNode( const std::string & id ) const {
		return const_cast< OutputImpl * >( this )->GetChildNode( id );
	}

	spINode OutputImpl::GetChildNode( const std::string & id ) {
		return GetTrack( id );
	}

	INode::NodeList OutputImpl::GetAllChildren() {
		NodeList list;
		AppendToListFromMap< spINode, VideoTrackMap >( list, mVideoTrackMap );
		AppendToListFromMap< spINode, AudioTrackMap >( list, mAudioTrackMap );
		return list;
	}

	INode::cNodeList OutputImpl::GetAllChildren() const {
		cNodeList list;
		AppendToListFromMap< spcINode, VideoTrackMap >( list, mVideoTrackMap );
		AppendToListFromMap< spcINode, AudioTrackMap >( list, mAudioTrackMap );
		return list;
	}

	INode::NodeList OutputImpl::GetAllDecendants() {
		NodeList list;
		AppendDecendantsFromMapToList< spINode >( list, mVideoTrackMap );
		AppendDecendantsFromMapToList< spINode >( list, mAudioTrackMap );
		return list;
	}

	INode::cNodeList OutputImpl::GetAllDecendants() const {
		cNodeList list;
		AppendDecendantsFromMapToList< spcINode >( list, mVideoTrackMap );
		AppendDecendantsFromMapToList< spcINode >( list, mAudioTrackMap );
		return list;
	}

	spIVideoTrack OutputImpl::AddVideoTrack() {
		const std::string & uniqueIDStr = mspUniqueIDGenerator->GenerateUniqueID( INode::kNodeTypeOutput );

		spIVideoTrack track; /*TODO = std::make_shared
			<
			TrackImpl, ITrack::eTrackTypes, const spUniqueIDSet &, spIUniqueIDGenerator &, const spIOutput &
			> ( std::move( trackType ), mspUniqueIDSet, mspUniqueIDGenerator, shared_from_this() );*/
		AddElementToMap( mVideoTrackMap, uniqueIDStr, track, mspUniqueIDSet );
		return track;
	}

	spIAudioTrack OutputImpl::AddAudioTrack() {
		const std::string & uniqueIDStr = mspUniqueIDGenerator->GenerateUniqueID( INode::kNodeTypeOutput );

		spIAudioTrack track;/* TODO= std::make_shared
			<
			TrackImpl, ITrack::eTrackTypes, const spUniqueIDSet &, spIUniqueIDGenerator &, const spIOutput &
			> ( std::move( trackType ), mspUniqueIDSet, mspUniqueIDGenerator, shared_from_this() );*/
		AddElementToMap( mAudioTrackMap, uniqueIDStr, track, mspUniqueIDSet );
		return track;
	}

	void OutputImpl::SetName( const std::string & name ) {
		mName = name;
	}

	std::string OutputImpl::GetName() const {
		return mName;
	}

	void OutputImpl::SetTitle( const std::string & title ) {
		mTitle = title;
	}

	std::string OutputImpl::GetTitle() const {
		return mTitle;
	}

	void OutputImpl::SetCanvasAspectRatio( const AspectRatio & canvasAspectRatio ) {
		mCanvasAspectRatio = canvasAspectRatio;
	}

	AspectRatio OutputImpl::GetCanvasAspectRatio() const {
		return mCanvasAspectRatio;
	}

	void OutputImpl::SetImageAspectRatio( const AspectRatio & imageAspectRatio ) {
		mImageAspectRatio = imageAspectRatio;
	}

	AspectRatio OutputImpl::GetImageAspectRatio() const {
		return mImageAspectRatio;
	}

	void OutputImpl::SetVideoEditRate( const EditRate & videoEditRate ) {
		mVideoEditRate = videoEditRate;
	}

	EditRate OutputImpl::GetVideoEditRate() const {
		return mVideoEditRate;
	}

	void OutputImpl::SetAudioEditRate( const EditRate & audioEditRate ) {
		mAudioEditRate = audioEditRate;
	}

	EditRate OutputImpl::GetAudioEditRate() const {
		return mAudioEditRate;
	}

	spcIAudioTrack OutputImpl::GetAudioTrack( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIAudioTrack >( mAudioTrackMap, uniqueID );
	}

	spIAudioTrack OutputImpl::GetAudioTrack( const std::string & uniqueID ) {
		return GetElementFromMap< spIAudioTrack >( mAudioTrackMap, uniqueID );
	}

	size_t OutputImpl::RemoveAllTracks() {
		size_t count( 0 );
		count = RemoveAllVideoTracks();
		count += RemoveAllAudioTracks();
		return count;
	}

	size_t OutputImpl::RemoveAllVideoTracks() {
		size_t expectedCount = mVideoTrackMap.size();
		size_t count = ClearMap( mVideoTrackMap, mspUniqueIDSet );
		assert( count == expectedCount );
		return count;
	}

	size_t OutputImpl::RemoveAllAudioTracks() {
		size_t expectedCount = mAudioTrackMap.size();
		size_t count = ClearMap( mAudioTrackMap, mspUniqueIDSet );
		assert( count == expectedCount );
		return count;
	}

	size_t OutputImpl::RemoveTrack( const std::string & uniqueID ) {
		size_t count = RemoveVideoTrack( uniqueID );
		if ( count > 0 ) return count;
		count = RemoveAudioTrack( uniqueID );
		return count;
	}

	size_t OutputImpl::RemoveVideoTrack( const std::string & uniqueID ) {
		return RemoveElementFromMap( mVideoTrackMap, uniqueID, mspUniqueIDSet );
	}

	size_t OutputImpl::RemoveAudioTrack( const std::string & uniqueID ) {
		return RemoveElementFromMap( mAudioTrackMap, uniqueID, mspUniqueIDSet );
	}

	spcINode OutputImpl::GetParentNode() const  {
		return spcIUMC( mwpUMC );
	}

	spINode OutputImpl::GetParentNode() {
		return spIUMC( mwpUMC );
	}

	size_t OutputImpl::TrackCount() const {
		return mVideoTrackMap.size() + mAudioTrackMap.size();
	}

	size_t OutputImpl::VideoTrackCount() const {
		return mVideoTrackMap.size();
	}

	size_t OutputImpl::AudioTrackCount() const {
		return mAudioTrackMap.size();
	}

	IOutput::VideoTrackList OutputImpl::GetAllVideoTracks() {
		return CreateListFromMap< spIVideoTrack >( mVideoTrackMap );
	}

	IOutput::cVideoTrackList OutputImpl::GetAllVideoTracks() const {
		return CreateListFromMap< spcIVideoTrack >( mVideoTrackMap );
	}

	spcIVideoTrack OutputImpl::GetVideoTrack( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIVideoTrack >( mVideoTrackMap, uniqueID );
	}

	spIVideoTrack OutputImpl::GetVideoTrack( const std::string & uniqueID ) {
		return GetElementFromMap< spIVideoTrack >( mVideoTrackMap, uniqueID );
	}

	IOutput::AudioTrackList OutputImpl::GetAllAudioTracks() {
		return CreateListFromMap< spIAudioTrack >( mAudioTrackMap );
	}

	IOutput::cAudioTrackList OutputImpl::GetAllAudioTracks() const {
		return CreateListFromMap< spcIAudioTrack >( mAudioTrackMap );
	}

	OutputImpl::OutputImpl( const std::string & uniqueID, const spUniqueIDSet & uniqueIDSet,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIUMC & parent )
		: mUniqueID( uniqueID )
		, mCanvasAspectRatio( 1 )
		, mImageAspectRatio( 1 )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 1 )
		, mwpUMC( parent)
		, mspUniqueIDSet( uniqueIDSet )
		, mspUniqueIDGenerator( uniqueIDGenerator )
	{
		if ( !parent ) THROW_PARENT_CANT_BE_NULL;
		if ( !mspUniqueIDSet ) THROW_UNIQUE_ID_MAP_CANT_BE_NULL;
		if ( !mspUniqueIDGenerator ) THROW_UNIQUE_ID_GENERATOR_CANT_BE_NULL;
	}

}
