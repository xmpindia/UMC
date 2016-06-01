cmake_minimum_required (VERSION 2.8.6)

project(CPPUnitStaticLibrary)

if(NOT DEFINED COMMON_BUILD_SHARED_DIR)
	set(COMMON_BUILD_SHARED_DIR "${PROJECT_SOURCE_DIR}/../../build")
endif()

include(${COMMON_BUILD_SHARED_DIR}/SharedConfig.cmake)

set( CPPUNIT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include" )
set( CPPUNIT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/source" )

#include all the headers and source files
file( GLOB_RECURSE CPPUNIT_HEADERS ${CPPUNIT_INCLUDE_DIR}/*.h )
source_group( "Headers" FILES ${CPPUNIT_HEADERS})
file( GLOB_RECURSE CPPUNIT_SOURCES ${CPPUNIT_SOURCE_DIR}/*.cpp )
source_group( "Sources" FILES ${CPPUNIT_SOURCES})

list( APPEND CPPUNIT_FILES
	${CPPUNIT_HEADERS}
	${CPPUNIT_SOURCES}
)

include_directories( ${CPPUNIT_INCLUDE_DIR} )

add_library( CPPUnitStatic STATIC ${CPPUNIT_FILES} )

if (UNIX AND NOT APPLE)
	set_target_properties(CPPUnitStatic PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${BUILD_CONFIGURATION}" )
endif()
if (UNIX AND APPLE)
	set_target_properties(CPPUnitStatic PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}" )
endif()
