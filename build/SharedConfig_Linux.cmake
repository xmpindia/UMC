add_definitions(-DUNIX_ENV=1)

set (OS_FOLDER_NAME "i80386linux_x64")
if ( (${CMAKE_BUILD_TYPE} STREQUAL "Debug") OR (${CMAKE_BUILD_TYPE} STREQUAL "debug") )
    set (BUILD_CONFIGURATION "debug")
else()
    set (BUILD_CONFIGURATION "release")
endif()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BUILD_CONFIGURATION})

function( GetFullSharedLibraryName shortName fullName )
	set( fullName ${shortName}.dll)
endfunction( GetFullSharedLibraryName )
