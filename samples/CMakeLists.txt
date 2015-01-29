cmake_minimum_required (VERSION 2.8.6)

project (Samples) 
message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")

if(NOT DEFINED COMMON_BUILD_SHARED_DIR)
	set(COMMON_BUILD_SHARED_DIR "${PROJECT_SOURCE_DIR}/../build")
endif()

include(${COMMON_BUILD_SHARED_DIR}/SharedConfig.cmake)
 
set(XMPTOOLKIT_INCLUDE "${PROJECT_SOURCE_DIR}/../XMPToolkit/public/include")
# include XMPCore and XMPCommon public header files and source files.
file (GLOB_RECURSE PUBLIC_XMPCOMMON_HEADERS ${XMPTOOLKIT_INCLUDE}/XMPCommon/*.h)
source_group("Public\\Headers\\XMPCommon" FILES ${PUBLIC_XMPCOMMON_HEADERS})
file (GLOB_RECURSE PUBLIC_XMPCORE_HEADERS ${XMPTOOLKIT_INCLUDE}/XMPCore/*.h)
source_group("Public\\Headers\\XMPCore" FILES ${PUBLIC_XMPCORE_HEADERS})
file (GLOB_RECURSE PUBLIC_XMPCOMMON_SOURCES ${XMPTOOLKIT_INCLUDE}/XMPCommon/*.cpp)
source_group("Public\\Sources\\XMPCommon" FILES ${PUBLIC_XMPCOMMON_SOURCES})
file (GLOB_RECURSE PUBLIC_XMPCORE_SOURCES ${XMPTOOLKIT_INCLUDE}/XMPCore/*.cpp)
source_group("Public\\Sources\\XMPCore" FILES ${PUBLIC_XMPCORE_SOURCES})

list(APPEND COMMON_SOURCE_FILES 
		${PUBLIC_XMPCOMMON_HEADERS}
		${PUBLIC_XMPCORE_HEADERS}
		${PUBLIC_XMPCOMMON_SOURCES}
		${PUBLIC_XMPCORE_SOURCES}
	)

include_directories(${XMPTOOLKIT_INCLUDE})
link_directories( ${CMAKE_BINARY_DIR}/${BUILD_CONFIGURATION} )

add_executable( CreatingAndSerializingMetadata ${COMMON_SOURCE_FILES} CreatingAndSerializingMetadata.cpp )

add_custom_command( TARGET CreatingAndSerializingMetadata PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${BUILD_CONFIGURATION}
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../XMPToolkit/public/libraries/${OS_FOLDER_NAME}/${BUILD_CONFIGURATION} ${CMAKE_BINARY_DIR}/${BUILD_CONFIGURATION}
)

set(LIB_ADOBEXMP "AdobeXMP")
target_link_libraries( CreatingAndSerializingMetadata ${LIB_ADOBEXMP})

