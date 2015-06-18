#ifndef TestUtils_h__
#define TestUtils_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"
#include <iostream>
#include <fstream>

#include <string>
#include <utility>
#include <limits.h>
#include <climits>
#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#include <windows.h>
#include <direct.h>
#include "Shlwapi.h"
#else
#include <sys/stat.h>
#endif


////////////////////////////////////////

#ifdef __APPLE__
#include <stdlib.h>
#include <mach-o/dyld.h>
#undef TRUE
#undef FALSE
#endif

namespace TestUtils {
	#if WIN32
	#define FILENAME_PATH_MAX _MAX_PATH
	#else
	#define FILENAME_PATH_MAX _POSIX_PATH_MAX
	#endif

	UMC::spIUMC CreateDefaultUMC();

	inline const char Separator( void )
	{
	#ifdef WIN32
		return '\\';
	#else
		return '/';
	#endif
	}

	inline std::string
	GetExecutablePath( void )
	{
		char dir[FILENAME_PATH_MAX + 1] = { '\0' };
	#ifdef WIN32
		return GetModuleFileName(NULL, dir, sizeof(dir)) == 0 ? "" : dir;
	#elif  __APPLE__
		char resolvedDir[FILENAME_PATH_MAX + 1] = { '\0' };
		uint32_t size = sizeof(dir);
		if ( _NSGetExecutablePath( dir, &size ) == 0 )
		{
			if( realpath( dir, resolvedDir ) != NULL )
			{
				return resolvedDir;
			}else
				return "";
		}else
			return "";
	#else
		return ::readlink("/proc/self/exe", dir, sizeof(dir)) == -1 ? "" : dir;
	#endif
	}

	inline std::string
	Dirname( const std::string &filename )
	{
		std::string::size_type n = filename.rfind( Separator() );
		if ( n == std::string::npos )
			return std::string();
		return filename.substr( 0, n );
	}

	inline std::string
	GetExecutableDir( void )
	{
		return Dirname( GetExecutablePath() );
	}


	inline std::string
	Join( const std::string &path1, const std::string &path2 )
	{
		return path1 + Separator() + path2;	
	}


	inline std::string
	GetMaterialDir( void )
	{
		std::string binDir = GetExecutableDir();
		std::string apiTests = Dirname(binDir);
		return Join(apiTests, "material");
	}

	inline std::string
	ReadTextFileIntoString( const std::string filename )
	{
		std::ifstream is(filename);
		std::string s( ( std::istreambuf_iterator<char>( is ) ), std::istreambuf_iterator<char>() );
		return s;
	}
}
#endif  // TestUtils_h__
