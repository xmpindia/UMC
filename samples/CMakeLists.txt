cmake_minimum_required (VERSION 2.8.6)

project(Samples)

if(NOT DEFINED COMMON_BUILD_SHARED_DIR)
	set(COMMON_BUILD_SHARED_DIR "${PROJECT_SOURCE_DIR}/../build")
endif()

MESSAGE( STATUS " COMMON_BUILD_SHARED_DIR: " ${COMMON_BUILD_SHARED_DIR} )
set( PROJECT_ROOT ${PROJECT_SOURCE_DIR})
set(XMPTOOLKIT_INCLUDE "${PROJECT_SOURCE_DIR}/../imports/XMPToolkit/public/include")
set(UMC_PUBLIC_DIR "${PROJECT_SOURCE_DIR}/../public")
set(UMC_PUBLIC_INCLUDE_DIR "${UMC_PUBLIC_DIR}/include")
set(UMC_PUBLIC_SOURCE_DIR "${UMC_PUBLIC_DIR}/source")
set(SAMPLES_BUILD_DIR "${COMMON_BUILD_SHARED_DIR}/samples/")

# include public header files and source files.
file(GLOB_RECURSE PUBLIC_UMC_HEADERS ${UMC_PUBLIC_INCLUDE_DIR}/*.h)
source_group("Public\\Headers\\UMC" FILES ${PUBLIC_UMC_HEADERS})
file(GLOB_RECURSE PUBLIC_UMC_SOURCES ${UMC_PUBLIC_SOURCE_DIR}/*.cpp)
source_group("Public\\Sources\\UMC" FILES ${PUBLIC_UMC_SOURCES})

list(APPEND UMC_FILES 
	${PUBLIC_UMC_HEADERS}
	${PUBLIC_UMC_SOURCES}
)

include(${COMMON_BUILD_SHARED_DIR}/SharedConfig.cmake)
include(${PROJECT_SOURCE_DIR}/../CommonDefines.cmake)

include_directories(${XMPTOOLKIT_INCLUDE})
include_directories(${PUBLIC_UMC_HEADERS})
include_directories(${PUBLIC_UMC_SOURCES})

link_directories(${XMPTOOLKIT_INCLUDE}/../libraries/${OS_FOLDER_NAME}/${BUILD_CONFIGURATION})

add_subdirectory(${PROJECT_ROOT}/AddingExtensions ${SAMPLES_BUILD_DIR}/AddingExtensions/build${POSTFIX})
add_subdirectory(${PROJECT_ROOT}/AddingSources ${SAMPLES_BUILD_DIR}/AddingSources/build${POSTFIX})

