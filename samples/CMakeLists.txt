cmake_minimum_required (VERSION 2.8.6)

project(Samples)

add_subdirectory(${PROJECT_ROOT}/AddingExtensions ${SAMPLES_BUILD_DIR}/AddingExtensions/build${POSTFIX})
add_subdirectory(${PROJECT_ROOT}/AddingSources ${SAMPLES_BUILD_DIR}/AddingSources/build${POSTFIX})
