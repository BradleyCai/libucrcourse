# 
# CMakeLists.txt
# 
# Copyright (C) 2016 Ammon Smith and Bradley Cai
# Available for use under the terms of the MIT License.
#

include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/src")
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/include")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test TEST_SOURCES)

# Compile libraries
add_library(${PROJECT_NAME}_static STATIC ${SOURCES})
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} curl)

# Compile test binaries
add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
message(${CMAKE_BINARY_DIR})

