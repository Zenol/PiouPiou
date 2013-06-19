cmake_minimum_required (VERSION 2.6)

# C++ 2011 flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -ggdb -W -Wall")

#C 99 flag
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb -W -Wall")
cmake_minimum_required (VERSION 2.6)

# Project name.
project (PiouPiou)

# The version number.
set (PiouPiou_VERSION_MAJOR 1)
set (PiouPiou_VERSION_MINOR 0)
set (PiouPiou_VERSION_MICRO 0)

# Generate the PiouPiouConfig.hpp file
#configure_file (
#    "src/PiouPiouConfig.h.in"
#    "bin/PiouPiouConfig.h"
#)

# Locate headers files
include_directories (src bin)

# Set output directory
set (EXECUTABLE_OUTPUT_PATH bin)

# Add files that should be compiled
file(GLOB_RECURSE SOURCE_FILES src/*.cpp SRC)

# Add executable :
add_executable (piouc ${SOURCE_FILES})

