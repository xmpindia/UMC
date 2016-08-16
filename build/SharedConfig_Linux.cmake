add_definitions(-DUNIX_ENV=1)

set (OS_FOLDER_NAME "i80386linux_x64")
set (BUILD_CONFIGURATION "")
string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_CONFIGURATION)

set(STATIC_LIB_PREFIX "lib")
set(STATIC_LIB_EXTENSION "a")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

function( GetFullSharedLibraryName shortName fullName )
	set( fullName ${shortName}.dll)
endfunction( GetFullSharedLibraryName )
