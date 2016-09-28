#
# CMakeLists.txt
#
# Copyright (C) 2016 Ammon Smith and Bradley Cai
# Available for use under the terms of the MIT License.
#

cmake_minimum_required(VERSION 2.6)
project(ucrcourse C)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)

add_subdirectory(src)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Compile flags
add_definitions("-ansi -Wall -Wextra -pedantic -Wshadow -Wmissing-prototypes")

if(NOT ${APPLE})
    add_definitions("-D_XOPEN_SOURCE=500")
endif()

# Check header files
include(CheckIncludes)

