cmake_minimum_required(VERSION 2.8.6)

project(UMCSDK)

add_subdirectory(./private)
add_subdirectory( ./samples)
add_subdirectory(./imports/cppunit)
add_subdirectory(./unitTests)
add_subdirectory(./apiTests)