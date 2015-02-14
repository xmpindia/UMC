#ifndef UMCImpl_h__
#define UMCImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IUMC.h"
#include "UMCFwdDeclarations_I.h"
#include <map>
#include "interfaces/ISource.h"

namespace INT_UMC {

	class UMCImpl : public IUMC {
	public:
		UMCImpl();
		virtual spISource AddVideoSource( const char * uniqueID, size_t length = npos );
		virtual spISource AddAudioSource( const char * uniqueID, size_t length = npos );
		virtual spISource AddStillImageSource( const char * uniqueID, size_t length = npos );
		virtual spIOutput AddOutput( const char * uniqueID, size_t length = npos );

		virtual std::string SerializeToBuffer() const;

		virtual size_t SourceCount() const;
		virtual size_t VideoSourceCount() const;
		virtual size_t AudioSourceCount() const;
		virtual size_t StillImageSourceCount() const;

		virtual SourceList GetAllSources();
		virtual cSourceList GetAllSources() const;
		virtual SourceList GetVideoSources();
		virtual cSourceList GetVideoSources() const;
		virtual SourceList GetAudioSources();
		virtual cSourceList GetAudioSources() const;
		virtual SourceList GetStillImageSources();
		virtual cSourceList GetStillImageSources() const;

		virtual spISource GetSource( const char * uniqueID, size_t length = npos );
		virtual spcISource GetSource( const char * uniqueID, size_t length = npos ) const;

		virtual void RemoveAllSources();
		virtual void RemoveSource( const char * uniqueID, size_t length = npos );

		virtual size_t OutputCount() const;

		virtual OutputList GetOutputs();
		virtual cOutputList GetOutputs() const;
		
		virtual spIOutput GetOutput( const char * uniqueID, size_t length = npos );
		virtual spcIOutput GetOutput( const char * uniqueID, size_t length = npos ) const;

		virtual void RemoveAllOutputs();
		virtual void RemoveOutput( const char * uniqueID, size_t length = npos );

	protected:
		spISource AddSource( const char * uniqueID, size_t length, ISource::eSourceTypes sourceType );
		void UpdateCount( ISource::eSourceTypes sourceType, bool removed = true );
		SourceList GetSources( ISource::eSourceTypes sourceType );
		cSourceList GetSources( ISource::eSourceTypes sourceType ) const;

		typedef std::map< const std::string, spISource > SourceMap;
		
		SourceMap			mSourceMap;
		size_t				mVideoSourceCount;
		size_t				mAudioSourceCount;
		size_t				mImageSourceCount;

		typedef std::map< const std::string, spIOutput > OutputMap;

		OutputMap			mOutputMap;
	};
}

#endif  // UMCImpl_h__
