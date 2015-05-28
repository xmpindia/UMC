add_definitions(-DMAC_ENV=1)

set (OS_FOLDER_NAME "Mac")
set (TOLOWER ${CMAKE_BUILD_TYPE} BUILD_CONFIGURATION)

set(STATIC_LIB_PREFIX "lib")
set(STATIC_LIB_EXTENSION "a")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

function( GetFullSharedLibraryName shortName fullName )
    set( fullName ${shortName}.a)
endfunction( GetFullSharedLibraryName )
