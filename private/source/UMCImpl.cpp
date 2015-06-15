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

#include "utils/UMCAndXMPMapping.h"

#include "XMPCore/Interfaces/IXMPMetadata.h"

namespace INT_UMC {


	UMCImpl::UMCImpl() {
		auto first = CreateUniqueIDAndReferenceTracker();
		auto second = CreateUniqueIDGenerator( first );
		Init( first, second, INode::kNodeTypeUMC );
	}


	UMCImpl::UMCImpl( const spIXMPStructureNode & metadata )
		: NodeImpl( metadata )
	{
		auto first = CreateUniqueIDAndReferenceTracker();
		auto second = CreateUniqueIDGenerator( first );
		Init( first, second, INode::kNodeTypeUMC );
	}

	spIVideoSource UMCImpl::AddVideoSource() {
		spIVideoSource source = CreateVideoSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator );
		CreateEquivalentXMPNodes( mXMPStructureNode, mVideoSources, kVideoSourcesPair, mSources, kSourcesPair);
		AddElementToMap( mVideoSourceMap, source, shared_from_this(), mVideoSources );
		return source;
	}

	spIVideoSource UMCImpl::AddVideoSource( const std::string & buffer ) {
		spIXMPStructureNode node = ParseRDF( buffer );
		return AddVideoSource( node );
	}

	spIVideoSource UMCImpl::AddVideoSource( const spIXMPStructureNode & node ) {
		auto actualNode = TryToGetActualNode( node, kVideoSourcesPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIVideoSource source = CreateVideoSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, actualNode );
		CreateEquivalentXMPNodes( mXMPStructureNode, mVideoSources, kVideoSourcesPair, mSources, kSourcesPair);
		AddElementToMap( mVideoSourceMap, source, shared_from_this(), mVideoSources );
		return source;
	}

	spIAudioSource UMCImpl::AddAudioSource() {
		spIAudioSource source = CreateAudioSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator );
		CreateEquivalentXMPNodes( mXMPStructureNode, mAudioSources, kAudioSourcesPair, mSources, kSourcesPair);
		AddElementToMap( mAudioSourceMap, source, shared_from_this(), mAudioSources );
		return source;
	}

	spIAudioSource UMCImpl::AddAudioSource( const std::string & buffer ) {
		spIXMPStructureNode node = ParseRDF( buffer );
		return AddAudioSource( node );
	}

	spIAudioSource UMCImpl::AddAudioSource( const spIXMPStructureNode & node ) {
		auto actualNode = TryToGetActualNode( node, kAudioSourcesPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIAudioSource source = CreateAudioSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, actualNode );
		CreateEquivalentXMPNodes( mXMPStructureNode, mAudioSources, kAudioSourcesPair, mSources, kSourcesPair );
		AddElementToMap( mAudioSourceMap, source, shared_from_this(), mAudioSources );
		return source;
	}

	spIVideoFrameSource UMCImpl::AddVideoFrameSource( const spIVideoSource & videoSource ) {
		spIVideoFrameSource source = CreateVideoFrameSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, videoSource );
		CreateEquivalentXMPNodes( mXMPStructureNode, mVideoFrameSources, kVideoFrameSourcesPair, mSources, kSourcesPair );
		AddElementToMap( mVideoFrameSourceMap, source, shared_from_this(), mVideoFrameSources );
		return source;
	}

	spIVideoFrameSource UMCImpl::AddVideoFrameSource( const std::string & buffer ) {
		spIXMPStructureNode node = ParseRDF( buffer );
		return AddVideoFrameSource( node );
	}

	UMC::spIVideoFrameSource UMCImpl::AddVideoFrameSource( const spIXMPStructureNode & node ) {
		auto actualNode = TryToGetActualNode( node, kVideoFrameSourcesPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIVideoFrameSource source = CreateVideoFrameSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, spIVideoSource(), actualNode );
		CreateEquivalentXMPNodes( mXMPStructureNode, mVideoFrameSources, kVideoFrameSourcesPair, mSources, kSourcesPair );
		AddElementToMap( mVideoFrameSourceMap, source, shared_from_this(), mVideoFrameSources );
		return source;
	}

	spIImageSource UMCImpl::AddImageSource() {
		spIImageSource source = CreateImageSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator );
		CreateEquivalentXMPNodes( mXMPStructureNode, mImageSources, kImageSourcesPair, mSources, kSourcesPair);
		AddElementToMap( mImageSourceMap, source, shared_from_this(), mImageSources );
		return source;
	}

	spIImageSource UMCImpl::AddImageSource( const std::string & buffer ) {
		spIXMPStructureNode node = ParseRDF( buffer );
		return AddImageSource( node );
	}

	spIImageSource UMCImpl::AddImageSource( const spIXMPStructureNode & node ) {
		auto actualNode = TryToGetActualNode( node, kImageSourcesPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIImageSource source = CreateImageSource( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, actualNode );
		CreateEquivalentXMPNodes( mXMPStructureNode, mImageSources, kImageSourcesPair, mSources, kSourcesPair );
		AddElementToMap( mImageSourceMap, source, shared_from_this(), mImageSources );
		return source;
	}

	spISource UMCImpl::AddSource( const std::string & buffer ) {
		spIXMPStructureNode parentNode = ParseRDF( buffer );
		const NamespacePropertyNamePair * pairs[4] = { &kVideoSourcesPair, &kAudioSourcesPair, &kImageSourcesPair, &kVideoFrameSourcesPair };
		size_t matchedIndex = GetMatchingIndexForActualNode( parentNode, &pairs[0], (size_t) 4 );

		switch( matchedIndex ) {
		case 0:
			return AddVideoSource( parentNode );
		case 1:
			return AddAudioSource( parentNode );
		case 2:
			return AddImageSource( parentNode );
		case 3:
			return AddVideoFrameSource( parentNode );
		default:
			THROW_PARSING_ERROR;
		}
		return spISource();
	}

	spIOutput UMCImpl::AddOutput() {
		spIOutput output = CreateOutput( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator );
		CreateEquivalentXMPNodes( mXMPStructureNode, mOutputs, kOutputsPair );
		AddElementToMap( mOutputMap, output, shared_from_this(), mOutputs );
		return output;
	}

	spIOutput UMCImpl::AddOutput( const std::string & buffer ) {
		spIXMPStructureNode node = ParseRDF( buffer );
		return AddOutput( node );
	}

	UMC::spIOutput UMCImpl::AddOutput( const spIXMPStructureNode & node ) {
		auto actualNode = TryToGetActualNode( node, kOutputsPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIOutput output = CreateOutput( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, actualNode );
		CreateEquivalentXMPNodes( mXMPStructureNode, mOutputs, kOutputsPair );
		AddElementToMap( mOutputMap, output, shared_from_this(), mOutputs );
		return output;
	}

	bool UMCImpl::ValidateXMPNode() const {
		return true;
	}

	UMC::pINode UMCImpl::GetNode() {
		return this;
	}

	UMC::pcINode UMCImpl::GetNode() const {
		return this;
	}

	size_t UMCImpl::SourceCount() const {
		return mVideoSourceMap.size() +
			mAudioSourceMap.size() +
			mVideoFrameSourceMap.size() +
			mImageSourceMap.size();
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
		AppendToListFromMap< spISource >( list, mVideoSourceMap );
		AppendToListFromMap< spISource >( list, mAudioSourceMap );
		AppendToListFromMap< spISource >( list, mVideoFrameSourceMap );
		AppendToListFromMap< spISource >( list, mImageSourceMap );
		return list;
	}

	IUMC::cSourceList UMCImpl::GetAllSources() const {
		cSourceList list;
		AppendToListFromMap< spcISource >( list, mVideoSourceMap );
		AppendToListFromMap< spcISource >( list, mAudioSourceMap );
		AppendToListFromMap< spcISource >( list, mVideoFrameSourceMap );
		AppendToListFromMap< spcISource >( list, mImageSourceMap );
		return list;
	}

	IUMC::VideoSourceList UMCImpl::GetAllVideoSources() {
		return CreateListFromMap< spIVideoSource >( mVideoSourceMap );
	}

	IUMC::cVideoSourceList UMCImpl::GetAllVideoSources() const {
		return CreateListFromMap< spcIVideoSource >( mVideoSourceMap );
	}

	IUMC::AudioSourceList UMCImpl::GetAllAudioSources() {
		return CreateListFromMap< spIAudioSource >( mAudioSourceMap );
	}

	IUMC::cAudioSourceList UMCImpl::GetAllAudioSources() const {
		return CreateListFromMap< spcIAudioSource >( mAudioSourceMap );
	}

	IUMC::VideoFrameSourceList UMCImpl::GetAllVideoFrameSources() {
		return CreateListFromMap< spIVideoFrameSource >( mVideoFrameSourceMap );
	}

	IUMC::cVideoFrameSourceList UMCImpl::GetAllVideoFrameSources() const {
		return CreateListFromMap< spcIVideoFrameSource >( mVideoFrameSourceMap );
	}

	IUMC::ImageSourceList UMCImpl::GetAllImageSources() {
		return CreateListFromMap< spIImageSource >( mImageSourceMap );
	}

	IUMC::cImageSourceList UMCImpl::GetAllImageSources() const {
		return CreateListFromMap< spcIImageSource >( mImageSourceMap );
	}

	spISource UMCImpl::GetSource( const std::string & uniqueID ) {
		spISource node = GetElementFromMap< spISource >( mVideoSourceMap, uniqueID );
		if ( node ) return node;
		node = GetElementFromMap< spISource >( mAudioSourceMap, uniqueID );
		if ( node ) return node;
		node = GetElementFromMap< spISource >( mVideoFrameSourceMap, uniqueID );
		if ( node ) return node;
		node = GetElementFromMap< spISource >( mImageSourceMap, uniqueID );
		return node;
	}

	spcISource UMCImpl::GetSource( const std::string & uniqueID ) const {
		return const_cast< UMCImpl *>( this )->GetSource( uniqueID );
	}

	spIVideoSource UMCImpl::GetVideoSource( const std::string & uniqueID ) {
		return GetElementFromMap< spIVideoSource >( mVideoSourceMap, uniqueID );
	}

	spcIVideoSource UMCImpl::GetVideoSource( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIVideoSource >( mVideoSourceMap, uniqueID );
	}

	spIAudioSource UMCImpl::GetAudioSource( const std::string & uniqueID ) {
		return GetElementFromMap< spIAudioSource >( mAudioSourceMap, uniqueID );
	}

	spcIAudioSource UMCImpl::GetAudioSource( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIAudioSource >( mAudioSourceMap, uniqueID );
	}

	spIVideoFrameSource UMCImpl::GetVideoFrameSource( const std::string & uniqueID ) {
		return GetElementFromMap< spIVideoFrameSource >( mVideoFrameSourceMap, uniqueID );
	}

	spcIVideoFrameSource UMCImpl::GetVideoFrameSource( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIVideoFrameSource >( mVideoFrameSourceMap, uniqueID );
	}

	spIImageSource UMCImpl::GetImageSource( const std::string & uniqueID ) {
		return GetElementFromMap< spIImageSource >( mImageSourceMap, uniqueID );
	}

	spcIImageSource UMCImpl::GetImageSource( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIImageSource >( mImageSourceMap, uniqueID );
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
				for ( ; it2 != it2End; it2++ ) {
					size_t actualReferenceCount = it2->second->GetReferenceCount();
					size_t expectedReferenceCount( 0 );
					try {
						expectedReferenceCount = videoSourceReferences.at( it2->second->GetUniqueID() );
					} catch ( std::out_of_range & ) {
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
		count += ClearMap( mVideoFrameSourceMap, mVideoFrameSources );
		count += ClearMap( mVideoSourceMap, mVideoSources );
		count += ClearMap( mAudioSourceMap, mAudioSources );
		count += ClearMap( mImageSourceMap, mImageSources );
		assert( expectedCount == count );
		return count;
	}

	size_t UMCImpl::RemoveAllVideoSources() {
		bool safeToClear = SafeToClearMap( mVideoSourceMap );
		if ( safeToClear )
			return ClearMap( mVideoSourceMap, mVideoSources );
		else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
	}

	size_t UMCImpl::RemoveAllAudioSources() {
		bool safeToClear = SafeToClearMap( mAudioSourceMap );
		if ( safeToClear )
			return ClearMap( mAudioSourceMap, mAudioSources );
		else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
	}

	size_t UMCImpl::RemoveAllVideoFramesSources() {
		bool safeToClear = SafeToClearMap( mVideoFrameSourceMap );
		if ( safeToClear )
			return ClearMap( mVideoFrameSourceMap, mVideoFrameSources );
		else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
	}

	size_t UMCImpl::RemoveAllImageSources() {
		bool safeToClear = SafeToClearMap( mImageSourceMap );
		if ( safeToClear )
			return ClearMap( mImageSourceMap, mImageSources );
		else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
	}

	size_t UMCImpl::RemoveSource( const std::string & uniqueID ) {
		size_t count = TryAndRemoveElementFromMap( mVideoSourceMap, uniqueID, mVideoSources );
		if ( count != 0 ) return count;
		count = TryAndRemoveElementFromMap( mAudioSourceMap, uniqueID, mAudioSources );
		if ( count != 0 ) return count;
		count = TryAndRemoveElementFromMap( mVideoFrameSourceMap, uniqueID, mVideoFrameSources );
		if ( count != 0 ) return count;
		count = TryAndRemoveElementFromMap( mImageSourceMap, uniqueID, mImageSources );
		return count;
	}

	size_t UMCImpl::RemoveVideoSource( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mVideoSourceMap, uniqueID, mVideoSources );
	}

	size_t UMCImpl::RemoveAudioSource( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mAudioSourceMap, uniqueID, mAudioSources );
	}

	size_t UMCImpl::RemoveVideoFrameSource( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mVideoFrameSourceMap, uniqueID, mVideoFrameSources );
	}

	size_t UMCImpl::RemoveImageSource( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mImageSourceMap, uniqueID, mImageSources );
	}

	size_t UMCImpl::OutputCount() const {
		return mOutputMap.size();
	}

	IUMC::OutputList UMCImpl::GetAllOutputs() {
		return CreateListFromMap< spIOutput >( mOutputMap );
	}

	IUMC::cOutputList UMCImpl::GetAllOutputs() const {
		return CreateListFromMap< spcIOutput >( mOutputMap );
	}

	spIOutput UMCImpl::GetOutput( const std::string & uniqueID ) {
		return GetElementFromMap< spIOutput > ( mOutputMap, uniqueID );
	}

	spcIOutput UMCImpl::GetOutput( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIOutput >( mOutputMap, uniqueID );
	}

	size_t UMCImpl::RemoveAllOutputs() {
		bool safeToClear = SafeToClearMap( mOutputMap );
		if ( safeToClear )
			return ClearMap( mOutputMap, mOutputs );
		else {
			THROW_NODE_IS_REFERENCED( "remove" );
			return 0;
		}
	}

	size_t UMCImpl::RemoveOutput( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap< OutputMap >( mOutputMap, uniqueID, mOutputs );
	}

	std::string UMCImpl::SerializeToBuffer() const {
		return SerializeXMP();
	}

	INode::eNodeTypes UMCImpl::GetNodeType() const {
		return INode::kNodeTypeUMC;
	}

	spcINode UMCImpl::GetDecendantNode( const std::string & uniqueID ) const {
		return const_cast< UMCImpl * >( this )->GetDecendantNode( uniqueID );
	}

	spINode UMCImpl::GetDecendantNode( const std::string & uniqueID ) {
		spINode node = GetChildNode( uniqueID );
		if ( node ) return node;
		node = GetDecendantFromMap< VideoSourceMap >( mVideoSourceMap, uniqueID );
		if ( node ) return node;
		node = GetDecendantFromMap< AudioSourceMap >( mAudioSourceMap, uniqueID );
		if ( node ) return node;
		node = GetDecendantFromMap< VideoFrameSourceMap >( mVideoFrameSourceMap, uniqueID );
		if ( node ) return node;
		node = GetDecendantFromMap< ImageSourceMap >( mImageSourceMap, uniqueID );
		if ( node ) return node;
		node = GetDecendantFromMap< OutputMap >( mOutputMap, uniqueID );
		return node;
	}

	spcINode UMCImpl::GetChildNode( const std::string & uniqueID ) const {
		return const_cast< UMCImpl * >( this )->GetChildNode( uniqueID );
	}

	spINode UMCImpl::GetChildNode( const std::string & uniqueID ) {
		spINode node = mVideoSourceMap.find( uniqueID )->second;
		if ( node ) return node;
		node = mAudioSourceMap.find( uniqueID )->second;
		if ( node ) return node;
		node = mVideoFrameSourceMap.find( uniqueID )->second;
		if ( node ) return node;
		node = mImageSourceMap.find( uniqueID )->second;
		if ( node ) return node;
		node = mOutputMap.find( uniqueID )->second;
		return node;
	}

	INode::NodeList UMCImpl::GetAllChildren() {
		NodeList list;
		AppendToListFromMap< spINode >( list, mVideoSourceMap );
		AppendToListFromMap< spINode >( list, mAudioSourceMap );
		AppendToListFromMap< spINode >( list, mVideoFrameSourceMap );
		AppendToListFromMap< spINode >( list, mImageSourceMap );
		AppendToListFromMap< spINode >( list, mOutputMap );
		return list;
	}

	INode::cNodeList UMCImpl::GetAllChildren() const {
		cNodeList list;
		AppendToListFromMap< spcINode >( list, mVideoSourceMap );
		AppendToListFromMap< spcINode >( list, mAudioSourceMap );
		AppendToListFromMap< spcINode >( list, mVideoFrameSourceMap );
		AppendToListFromMap< spcINode >( list, mImageSourceMap );
		AppendToListFromMap< spcINode >( list, mOutputMap );
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

	pINodeI UMCImpl::GetInternalNode() {
		return this;
	}

	pcINodeI UMCImpl::GetInternalNode() const {
		return this;
	}

	void UMCImpl::CleanUpOnRemovalFromDOM() { }

	void UMCImpl::SetUpOnAdditionToDOM() { }

	void UMCImpl::SyncInternalStuffToXMP() const {
		CallSyncUMCToXMPOnMapElements( mVideoSourceMap );
		CallSyncUMCToXMPOnMapElements( mAudioSourceMap );
		CallSyncUMCToXMPOnMapElements( mVideoFrameSourceMap );
		CallSyncUMCToXMPOnMapElements( mImageSourceMap );
		CallSyncUMCToXMPOnMapElements( mOutputMap );
	}

	void UMCImpl::SyncXMPToInternalStuff() {
		mSources = TryToGetStructNode( mXMPStructureNode, kSourcesPair );
		mOutputs = TryToGetArrayNode( mXMPStructureNode, kOutputsPair );
		if ( mSources ) {
			mVideoSources = TryToGetArrayNode( mSources, kVideoSourcesPair );
			mAudioSources = TryToGetArrayNode( mSources, kAudioSourcesPair );
			mImageSources = TryToGetArrayNode( mSources, kImageSourcesPair );
			mVideoFrameSources = TryToGetArrayNode( mSources, kVideoFrameSourcesPair );
		}

		PopulateMapFromXMPArrayNode( this, &UMCImpl::AddVideoSource, mVideoSources );
		PopulateMapFromXMPArrayNode( this, &UMCImpl::AddAudioSource, mAudioSources );
		PopulateMapFromXMPArrayNode( this, &UMCImpl::AddVideoFrameSource, mVideoFrameSources );
		PopulateMapFromXMPArrayNode( this, &UMCImpl::AddImageSource, mImageSources );
		PopulateMapFromXMPArrayNode( this, &UMCImpl::AddOutput, mOutputs );
	}

	NS_XMPCORE::spIXMPStructureNode UMCImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	const std::string & UMCImpl::GetUniqueID() const {
		return NodeImpl::GetUniqueID();
	}

	wpcINode UMCImpl::GetParentNode() const {
		return NodeImpl::GetParentNode();
	}

	wpINode UMCImpl::GetParentNode() {
		return NodeImpl::GetParentNode();
	}

	size_t UMCImpl::GetReferenceCount() const {
		return NodeImpl::GetReferenceCount();
	}

	std::string UMCImpl::Serialize() const {
		return NodeImpl::SerializeXMP();
	}

	spICustomData UMCImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return NodeImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData UMCImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return NodeImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	bool UMCImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return NodeImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

}

namespace UMC {
	spIUMC IUMC::CreateEmptyUMC() {
		INT_UMC::UMCImpl * ptr = new INT_UMC::UMCImpl();
		return shared_ptr< INT_UMC::UMCImpl >( ptr );
	}

	spIUMC IUMC::CreateUMCFromBuffer( const std::string & buffer ) {
		NS_XMPCORE::spIXMPStructureNode node = INT_UMC::ParseRDF( buffer );
		auto retVal = std::make_shared< INT_UMC::UMCImpl >( node );
		retVal->SyncXMPToUMC();
		return retVal;
	}

	bool IUMC::RegisterCustomNodeHandler( const std::string & customNameSpace, const std::string & customName, const spICustomDataHandler & customDataHandler ) {
		return INT_UMC::ICustomDataHandlerRegistry::GetInstance()->RegisterHandler( customNameSpace, customName, customDataHandler );
	}

}
