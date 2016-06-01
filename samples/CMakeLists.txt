cmake_minimum_required (VERSION 2.8.6)

project(Samples)

if(NOT DEFINED COMMON_BUILD_SHARED_DIR)
	set(COMMON_BUILD_SHARED_DIR "${PROJECT_SOURCE_DIR}/../build")
endif()

set(XMPTOOLKIT_INCLUDE "${PROJECT_SOURCE_DIR}/../imports/XMPToolkit/public/include")

include(${COMMON_BUILD_SHARED_DIR}/SharedConfig.cmake)
include(${PROJECT_SOURCE_DIR}/../CommonDefines.cmake)

include_directories(${XMPTOOLKIT_INCLUDE})
link_directories(${XMPTOOLKIT_INCLUDE}/../libraries/${OS_FOLDER_NAME}/${BUILD_CONFIGURATION})

add_executable( CreatingAndSerializingMetadata ${PUBLIC_XMPTOOLKIT_FILES} CreatingAndSerializingMetadata.cpp )

add_custom_command( TARGET CreatingAndSerializingMetadata POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${XMPTOOLKIT_INCLUDE}/../libraries/${OS_FOLDER_NAME}/${BUILD_CONFIGURATION} ${PROJECT_BINARY_DIR}/${BUILD_CONFIGURATION}
)

set(LIB_ADOBEXMP "XMPCore")
if ( UNIX AND APPLE )
	set_target_properties( CreatingAndSerializingMetadata PROPERTIES LINK_FLAGS 
		"-Wl,-F${XMPTOOLKIT_INCLUDE}/../libraries/${OS_FOLDER_NAME}/" )
	target_link_libraries( CreatingAndSerializingMetadata "-framework ${LIB_ADOBEXMP}" )
else()
	target_link_libraries( CreatingAndSerializingMetadata ${LIB_ADOBEXMP} )
endif()

if (UNIX AND NOT APPLE)
	set_target_properties(CreatingAndSerializingMetadata PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${BUILD_CONFIGURATION}" )
endif()

if (UNIX AND APPLE)
	set_target_properties(CreatingAndSerializingMetadata PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}" )
endif()
