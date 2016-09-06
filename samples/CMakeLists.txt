cmake_minimum_required (VERSION 3.5.2)

project(Samples)

if(NOT DEFINED COMMON_BUILD_SHARED_DIR)
	set(COMMON_BUILD_SHARED_DIR "${PROJECT_SOURCE_DIR}/../build")
endif()

set(XMPTOOLKIT_INCLUDE "${PROJECT_SOURCE_DIR}/../imports/XMPToolkit/public/include")

include(${COMMON_BUILD_SHARED_DIR}/SharedConfig.cmake)
include(${PROJECT_SOURCE_DIR}/../CommonDefines.cmake)

set( PROJECT_ROOT ${PROJECT_SOURCE_DIR})
set(SAMPLES_BUILD_DIR "${COMMON_BUILD_SHARED_DIR}/samples/")

link_directories(${XMPTOOLKIT_INCLUDE}/../libraries/${OS_FOLDER_NAME}/${BUILD_CONFIGURATION})


add_subdirectory(${PROJECT_ROOT}/AddingExtensions ${SAMPLES_BUILD_DIR}/AddingExtensions/build${POSTFIX})
add_subdirectory(${PROJECT_ROOT}/AddingSources ${SAMPLES_BUILD_DIR}/AddingSources/build${POSTFIX})
add_subdirectory(${PROJECT_ROOT}/AddingOutputs ${SAMPLES_BUILD_DIR}/AddingOutputs/build${POSTFIX})
