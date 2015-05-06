// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/OutputImpl.h"
#include "interfaces/IVideoTrack.h"
#include "interfaces/IAudioTrack.h"
#include "interfaces/IUniqueIDGenerator.h"
#include "interfaces/IUMC.h"

#include "utils/Utils.h"

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
		node = GetDecendantFromMap( mVideoTrackMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap( mAudioTrackMap, id );
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

	size_t OutputImpl::GetReferenceCount() const {
		return mspUniqueIDAndReferenceTracker->GetReferenceCount( mUniqueID );
	}

	void OutputImpl::RemoveFromDOM() {
		ClearMap( mVideoTrackMap );
		ClearMap( mAudioTrackMap );
		mspUniqueIDAndReferenceTracker->RemoveUniqueID( mUniqueID );
	}

	void OutputImpl::AddToDOM( const spINode & parent ) {
		mspUniqueIDAndReferenceTracker->AddUniqueID( mUniqueID );
		if ( !parent ) THROW_PARENT_CANT_BE_NULL;
		spIUMC umcParent = ConvertNode< IUMC >( parent );
		if ( !umcParent ) THROW_PARENT_CANT_BE_NULL;
		mwpUMC = umcParent;
	}

	spIVideoTrack OutputImpl::AddVideoTrack() {
		spIVideoTrack track = CreateVideoTrack( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator );
		AddElementToMap( mVideoTrackMap, track, shared_from_this() );
		return track;
	}

	spIAudioTrack OutputImpl::AddAudioTrack() {
		spIAudioTrack track = CreateAudioTrack( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator );
		AddElementToMap( mAudioTrackMap, track, shared_from_this() );
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
		bool safeToClear( false );
		safeToClear = SafeToClearMap( mVideoTrackMap );
		if ( safeToClear ) SafeToClearMap( mAudioTrackMap ); else return 0;
		if ( safeToClear ) {
			size_t expectedCount = TrackCount();
			size_t count( 0 );
			count += ClearMap( mVideoTrackMap );
			count += ClearMap( mAudioTrackMap );
			assert( expectedCount == count );
			return count;
		}
		return 0;
	}

	size_t OutputImpl::RemoveAllVideoTracks() {
		if ( SafeToClearMap( mVideoTrackMap ) ) {
			return ClearMap( mVideoTrackMap );
		}
		return 0;
	}

	size_t OutputImpl::RemoveAllAudioTracks() {
		if ( SafeToClearMap( mAudioTrackMap ) ) {
			return ClearMap( mAudioTrackMap );
		}
		return 0;
	}

	size_t OutputImpl::RemoveTrack( const std::string & uniqueID ) {
		size_t count = RemoveVideoTrack( uniqueID );
		if ( count > 0 ) return count;
		count = RemoveAudioTrack( uniqueID );
		return count;
	}

	size_t OutputImpl::RemoveVideoTrack( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mVideoTrackMap, uniqueID );
	}

	size_t OutputImpl::RemoveAudioTrack( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mAudioTrackMap, uniqueID );
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

	OutputImpl::OutputImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mUniqueID( uniqueIDGenerator->GenerateUniqueID( INode::kNodeTypeOutput ) )
		, mCanvasAspectRatio( 1 )
		, mImageAspectRatio( 1 )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 1 )
		, mspUniqueIDAndReferenceTracker( uniqueIDAndReferenceTracker )
		, mspUniqueIDGenerator( uniqueIDGenerator )
	{
		if ( !mspUniqueIDAndReferenceTracker ) THROW_UNIQUE_ID_AND_REFERENCE_TRACKER_CANT_BE_NULL;
		if ( !mspUniqueIDGenerator ) THROW_UNIQUE_ID_GENERATOR_CANT_BE_NULL;
	}


	spIOutput CreateOutput( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< OutputImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}
}
