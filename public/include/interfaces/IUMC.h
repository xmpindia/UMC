#ifndef IUMC_h__
#define IUMC_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include <vector>

namespace UMC {
	class IUMC {
	public:
		typedef std::vector< spISource > SourceList;
		typedef std::vector< spcISource > cSourceList;

		typedef std::vector< spIOutput > OutputList;
		typedef std::vector< spcIOutput > cOutputList;

		virtual spISource AddVideoSource( const char * uniqueID, size_t length = npos ) = 0;
		virtual spISource AddAudioSource( const char * uniqueID, size_t length = npos ) = 0;
		virtual spISource AddFrameSource( const char * uniqueID, size_t length = npos ) = 0;

		virtual spIOutput AddOutput( const char * uniqueID, size_t length = npos ) = 0;

		virtual size_t SourceCount() const = 0;
		virtual size_t VideoSourceCount() const = 0;
		virtual size_t AudioSourceCount() const = 0;
		virtual size_t FrameSourceCount() const = 0;

		virtual SourceList GetAllSources() = 0;
		virtual cSourceList GetAllSources() const = 0;
		virtual SourceList GetVideoSources() = 0;
		virtual cSourceList GetVideoSources() const = 0;
		virtual SourceList GetAudioSources() = 0;
		virtual cSourceList GetAudioSources() const = 0;
		virtual SourceList GetFrameSources() = 0;
		virtual cSourceList GetFrameSources() const = 0;

		virtual spISource GetSource( const char * uniqueID, size_t length = npos ) = 0;
		virtual spcISource GetSource( const char * uniqueID, size_t length = npos ) const = 0;

		virtual void RemoveAllSources() = 0;
		virtual void RemoveSource( const char * uniqueID, size_t length = npos ) = 0;

		virtual size_t OutputCount() const = 0;

		virtual OutputList GetOutputs() = 0;
		virtual cOutputList GetOutputs() const = 0;

		virtual spIOutput GetOutput( const char * uniqueID, size_t length = npos ) = 0;
		virtual spcIOutput GetOutput( const char * uniqueID, size_t length = npos ) const = 0;

		virtual void RemoveAllOutputs() = 0;
		virtual void RemoveOutput( const char * uniqueID, size_t length = npos ) = 0;

		virtual std::string SerializeToBuffer() const = 0;

		static spIUMC CreateEmptyUMC();
		static spIUMC CreateUMCFromBuffer( const char * buffer, size_t bufferSize = npos );

		virtual ~IUMC() = 0;
	};

	inline IUMC::~IUMC() {}
}
#endif  // IUMC_h__
