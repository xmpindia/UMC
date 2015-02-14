// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/UMCImpl.h"
#include "implHeaders/SourceImpl.h"
#include "implHeaders/OutputImpl.h"

#include "utils/UMCToRDFConversion.h"

#include "XMPCore/Interfaces/IXMPDOMImplementationRegistry.h"
#include "XMPCore/Interfaces/IXMPCoreObjectFactory.h"
#include "XMPCore/Interfaces/IXMPDOMSerializer.h"

namespace INT_UMC {

	spISource UMCImpl::AddVideoSource( const char * uniqueID, size_t length /*= npos */ ) {
		return AddSource( uniqueID, length, ISource::kVideoSourceType );
	}

	spISource UMCImpl::AddAudioSource( const char * uniqueID, size_t length /*= npos */ ) {
		return AddSource( uniqueID, length, ISource::kAudioSourceType );
	}

	spISource UMCImpl::AddStillImageSource( const char * uniqueID, size_t length /*= npos */ ) {
		return AddSource( uniqueID, length, ISource::kStillImageSourceType );
	}

	spIOutput UMCImpl::AddOutput( const char * uniqueID, size_t length ) {
		//assert( length > 0 && uniqueID );
		std::string strID;
		if ( length == npos ) strID.assign( uniqueID ); else strID.assign( uniqueID, length );
		if ( mOutputMap.find( strID ) == mOutputMap.end() ) {
			spIOutput output = shared_ptr< IOutput >( new OutputImpl( uniqueID, length, shared_from_this() ) );
			mOutputMap[ strID ] = output;
			return output;
		} else {
			return spIOutput();
		}
	}

	std::string UMCImpl::SerializeToBuffer() const {
		using namespace NS_XMPCORE;
		auto sp = UMCToRDFConversion::Convert( shared_from_this() );
		auto serializer = IXMPDOMImplementationRegistry::GetDOMImplementationRegistry()->CreateSerializer( "rdf" );
		auto spString = serializer->Serialize( sp );
		return std::string( spString->c_str() );
	}

	size_t UMCImpl::SourceCount() const {
		return mSourceMap.size();
	}

	size_t UMCImpl::VideoSourceCount() const {
		return mVideoSourceCount;
	}

	size_t UMCImpl::AudioSourceCount() const {
		return mAudioSourceCount;
	}

	size_t UMCImpl::StillImageSourceCount() const {
		return mImageSourceCount;
	}

	IUMC::SourceList UMCImpl::GetAllSources() {
		SourceList list;
		auto it = mSourceMap.begin();
		auto endIt = mSourceMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
		}
		return list;
	}

	IUMC::cSourceList UMCImpl::GetAllSources() const {
		cSourceList list;
		auto it = mSourceMap.begin();
		auto endIt = mSourceMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
			}
		return list;
	}

	IUMC::SourceList UMCImpl::GetVideoSources() {
		return GetSources( ISource::kVideoSourceType );
	}

	IUMC::cSourceList UMCImpl::GetVideoSources() const {
		return GetSources( ISource::kVideoSourceType );
	}

	IUMC::SourceList UMCImpl::GetAudioSources() {
		return GetSources( ISource::kAudioSourceType );
	}

	IUMC::cSourceList UMCImpl::GetAudioSources() const {
		return GetSources( ISource::kAudioSourceType );
	}

	IUMC::SourceList UMCImpl::GetStillImageSources() {
		return GetSources( ISource::kStillImageSourceType );
	}

	IUMC::cSourceList UMCImpl::GetStillImageSources() const {
		return GetSources( ISource::kStillImageSourceType );
	}

	spISource UMCImpl::GetSource( const char * uniqueID, size_t length /*= npos */ ) {
		//assert( length > 0 && uniqueID );
		std::string strID;
		if ( length == npos ) strID.assign( uniqueID ); else strID.assign( uniqueID, length );
		auto it = mSourceMap.find( strID );
		if ( it == mSourceMap.end() ) {
			return spISource();
		} else {
			return it->second;
		}
	}

	spcISource UMCImpl::GetSource( const char * uniqueID, size_t length /*= npos */ ) const {
		return const_cast< UMCImpl *>( this )->GetSource( uniqueID, length );
	}

	void UMCImpl::RemoveAllSources() {
		mSourceMap.clear();
		mVideoSourceCount = mAudioSourceCount = mImageSourceCount = 0;
	}

	void UMCImpl::RemoveSource( const char * uniqueID, size_t length /*= npos */ ) {
		//assert( length > 0 && uniqueID );
		std::string strID;
		if ( length == npos ) strID.assign( uniqueID ); else strID.assign( uniqueID, length );
		auto it = mSourceMap.find( strID );
		if ( it != mSourceMap.end() ) {
			UpdateCount( it->second->GetSourceType(), true );
			mSourceMap.erase( it );
		}
	}

	spISource UMCImpl::AddSource( const char * uniqueID, size_t length, ISource::eSourceTypes sourceType ) {
		//assert( length > 0 && uniqueID );
		std::string strID;
		if ( length == npos ) strID.assign( uniqueID ); else strID.assign( uniqueID, length );
		if ( mSourceMap.find( strID ) == mSourceMap.end() ) {
			spISource source = shared_ptr< ISource >( new SourceImpl( uniqueID, length, sourceType, shared_from_this() ) );
			mSourceMap[ strID ] = source;
			UpdateCount( sourceType, false );
			return source;
		} else {
			return spISource();
		}
	}

	void UMCImpl::UpdateCount( ISource::eSourceTypes sourceType, bool removed /*= true */ ) {
		switch( sourceType ) {
			case ISource::kVideoSourceType:
				removed ? mVideoSourceCount-- : mVideoSourceCount++;
				break;
			case ISource::kAudioSourceType:
				removed ? mAudioSourceCount-- : mAudioSourceCount++;
				break;
			case ISource::kStillImageSourceType:
				removed ? mImageSourceCount-- : mImageSourceCount++;
				break;
		}
	}

	IUMC::cSourceList UMCImpl::GetSources( ISource::eSourceTypes sourceType ) const {
		cSourceList list;
		auto it = mSourceMap.begin();
		auto endIt = mSourceMap.end();
		for ( ; it != endIt; it++ ) {
			if ( it->second->GetSourceType() == sourceType )
				list.push_back( it->second );
		}
		return list;
	}

	IUMC::SourceList UMCImpl::GetSources( ISource::eSourceTypes sourceType ) {
		SourceList list;
		auto it = mSourceMap.begin();
		auto endIt = mSourceMap.end();
		for ( ; it != endIt; it++ ) {
			if ( it->second->GetSourceType() == sourceType )
				list.push_back( it->second );
			}
		return list;
	}

	size_t UMCImpl::OutputCount() const {
		return mOutputMap.size();
	}

	IUMC::OutputList UMCImpl::GetOutputs() {
		OutputList list;
		auto it = mOutputMap.begin();
		auto endIt = mOutputMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
		}
		return list;
	}

	IUMC::cOutputList UMCImpl::GetOutputs() const {
		cOutputList list;
		auto it = mOutputMap.begin();
		auto endIt = mOutputMap.end();
		for ( ; it != endIt; it++ ) {
			list.push_back( it->second );
			}
		return list;
	}

	spIOutput UMCImpl::GetOutput( const char * uniqueID, size_t length /*= npos */ ) {
		//assert( length > 0 && uniqueID );
		std::string strID;
		if ( length == npos ) strID.assign( uniqueID ); else strID.assign( uniqueID, length );
		auto it = mOutputMap.find( strID );
		if ( it == mOutputMap.end() ) {
			return spIOutput();
		} else {
			return it->second;
		}
	}

	spcIOutput UMCImpl::GetOutput( const char * uniqueID, size_t length /*= npos */ ) const {
		return const_cast< UMCImpl *>( this )->GetOutput( uniqueID, length );
	}

	void UMCImpl::RemoveAllOutputs() {
		mOutputMap.clear();
	}

	void UMCImpl::RemoveOutput( const char * uniqueID, size_t length /*= npos */ ) {
		//assert( length > 0 && uniqueID );
		std::string strID;
		if ( length == npos ) strID.assign( uniqueID ); else strID.assign( uniqueID, length );
		auto it = mOutputMap.find( strID );
		if ( it != mOutputMap.end() ) {
			mOutputMap.erase( it );
		}
	}

	UMCImpl::UMCImpl()
		: mVideoSourceCount( 0 )
		, mAudioSourceCount( 0 )
		, mImageSourceCount( 0 ) {}

}

namespace UMC {
	spIUMC IUMC::CreateEmptyUMC() {
		pIUMC ptr = new INT_UMC::UMCImpl();
		return shared_ptr< IUMC >( ptr );
	}
}
