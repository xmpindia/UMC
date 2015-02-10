cmake_minimum_required (VERSION 2.8.6)

project(UMCStaticLibrary)

if(NOT DEFINED COMMON_BUILD_SHARED_DIR)
	set(COMMON_BUILD_SHARED_DIR "${PROJECT_SOURCE_DIR}/../build")
endif()

set(XMPTOOLKIT_INCLUDE "${PROJECT_SOURCE_DIR}/../imports/XMPToolkit/public/include")

include(${COMMON_BUILD_SHARED_DIR}/SharedConfig.cmake)
include(${PROJECT_SOURCE_DIR}/../CommonDefines.cmake)

set(UMC_PUBLIC_DIR "${PROJECT_SOURCE_DIR}/../public")
set(UMC_PUBLIC_INCLUDE_DIR "${UMC_PUBLIC_DIR}/include")
set(UMC_PUBLIC_SOURCE_DIR "${UMC_PUBLIC_DIR}/source")

set(UMC_PRIVATE_DIR "${PROJECT_SOURCE_DIR}/../private")
set(UMC_PRIVATE_INCLUDE_DIR "${UMC_PRIVATE_DIR}/include")
set(UMC_PRIVATE_SOURCE_DIR "${UMC_PRIVATE_DIR}/source")

# include public header files and source files.
file(GLOB_RECURSE PUBLIC_UMC_HEADERS ${UMC_PUBLIC_INCLUDE_DIR}/*.h)
source_group("Public\\Headers\\UMC" FILES ${PUBLIC_UMC_HEADERS})
file(GLOB_RECURSE PUBLIC_UMC_SOURCES ${UMC_PUBLIC_SOURCE_DIR}/*.cpp)
source_group("Public\\Sources\\UMC" FILES ${PUBLIC_UMC_SOURCES})

#include private header files and source files.
file(GLOB_RECURSE PRIVATE_UMC_HEADERS ${UMC_PRIVATE_INCLUDE_DIR}/*.h)
source_group("Private\\Headers\\UMC" FILES ${PRIVATE_UMC_HEADERS})
file(GLOB_RECURSE PRIVATE_UMC_SOURCES ${UMC_PRIVATE_SOURCE_DIR}/*.cpp)
source_group("Private\\Sources\\UMC" FILES ${PRIVATE_UMC_SOURCES})


list(APPEND UMC_FILES 
	${PUBLIC_UMC_HEADERS}
	${PUBLIC_UMC_SOURCES}
	${PRIVATE_UMC_HEADERS}
	${PRIVATE_UMC_SOURCES}
)

include_directories(${XMPTOOLKIT_INCLUDE})
include_directories(${UMC_PUBLIC_INCLUDE_DIR})
include_directories(${UMC_PRIVATE_INCLUDE_DIR})

add_library( UMC STATIC ${PUBLIC_XMPTOOLKIT_FILES} ${UMC_FILES} )