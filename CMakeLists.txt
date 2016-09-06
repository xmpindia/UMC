cmake_minimum_required(VERSION 3.5.2)

project(UMCSDK)

add_definitions(-DENABLE_CPP_DOM_MODEL=1)
add_subdirectory(./private)
add_subdirectory( ./samples)
add_subdirectory(./imports/cppunit)
add_subdirectory(./unitTests)
add_subdirectory(./apiTests)