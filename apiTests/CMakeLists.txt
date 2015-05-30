cmake_minimum_required (VERSION 2.8.6)

project(APITestCases)

if(NOT DEFINED COMMON_BUILD_SHARED_DIR)
	set(COMMON_BUILD_SHARED_DIR "${PROJECT_SOURCE_DIR}/../build")
endif()

include(${COMMON_BUILD_SHARED_DIR}/SharedConfig.cmake)

set(UMC_PUBLIC_DIR "${PROJECT_SOURCE_DIR}/../public")
set(UMC_PUBLIC_INCLUDE_DIR "${UMC_PUBLIC_DIR}/include")
set(UMC_PUBLIC_SOURCE_DIR "${UMC_PUBLIC_DIR}/source")


set(API_TEST_CASES_DIR "${PROJECT_SOURCE_DIR}")

# include public header files and source files.
file(GLOB_RECURSE PUBLIC_UMC_HEADERS ${UMC_PUBLIC_INCLUDE_DIR}/*.h)
source_group("Public\\Headers\\UMC" FILES ${PUBLIC_UMC_HEADERS})
file(GLOB_RECURSE PUBLIC_UMC_SOURCES ${UMC_PUBLIC_SOURCE_DIR}/*.cpp)
source_group("Public\\Sources\\UMC" FILES ${PUBLIC_UMC_SOURCES})


#include all unit test cases
file(GLOB_RECURSE API_TEST_CASES_HEADERS ${API_TEST_CASES_DIR}/*.h)
source_group("Tests\\Headers" FILES ${API_TEST_CASES_HEADERS})
file(GLOB_RECURSE API_TEST_CASES_SOURCES ${API_TEST_CASES_DIR}/*.cpp)
source_group("Tests\\Sources" FILES ${API_TEST_CASES_SOURCES})

list(APPEND UMC_FILES 
	${PUBLIC_UMC_HEADERS}
	${PUBLIC_UMC_SOURCES}
)

list( APPEND TEST_FILES ${API_TEST_CASES_HEADERS} ${API_TEST_CASES_SOURCES} )

include_directories( ${PROJECT_SOURCE_DIR})
include_directories(${UMC_PUBLIC_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../imports/cppunit/include)

set(XMPTOOLKIT_INCLUDE "${PROJECT_SOURCE_DIR}/../imports/XMPToolkit/public/include")
link_directories(${XMPTOOLKIT_INCLUDE}/../libraries/${OS_FOLDER_NAME}/${BUILD_CONFIGURATION})

add_executable( APITests ${UMC_FILES} ${TEST_FILES} )
add_dependencies( APITests CPPUnitStatic UMC)

add_custom_command( TARGET APITests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${XMPTOOLKIT_INCLUDE}/../libraries/${OS_FOLDER_NAME}/${BUILD_CONFIGURATION} ${PROJECT_BINARY_DIR}/${BUILD_CONFIGURATION}
)

set(LIB_ADOBEXMP "AdobeXMP")

target_link_libraries( APITests
	${PROJECT_BINARY_DIR}/../imports/cppunit/${BUILD_CONFIGURATION}/${STATIC_LIB_PREFIX}CPPUnitStatic.${STATIC_LIB_EXTENSION}
	${PROJECT_BINARY_DIR}/../private/${BUILD_CONFIGURATION}/${STATIC_LIB_PREFIX}UMC.${STATIC_LIB_EXTENSION}
)

if ( UNIX AND APPLE )
	set_target_properties( APITests PROPERTIES LINK_FLAGS 
		"-Wl,-F${XMPTOOLKIT_INCLUDE}/../libraries/${OS_FOLDER_NAME}/${BUILD_CONFIGURATION}" )
	target_link_libraries( APITests "-framework ${LIB_ADOBEXMP}" )
else()
	target_link_libraries( APITests ${LIB_ADOBEXMP} )
endif()

if (UNIX OR APPLE)
	set_target_properties(APITests PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${BUILD_CONFIGURATION}" )
endif()
