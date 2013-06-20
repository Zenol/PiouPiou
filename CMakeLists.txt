cmake_minimum_required (VERSION 2.6)

# Add modules used by this project to the module path
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "cmake/Modules/")
set(LLVM_DIR "cmake/Modules/")

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
configure_file (
    "src/PiouPiouConfig.h.in"
    "bin/PiouPiouConfig.h"
)

# Locate headers files
include_directories (src bin)

# Set output directory
set (EXECUTABLE_OUTPUT_PATH bin)

# Add files that should be compiled
file(GLOB_RECURSE SOURCE_FILES src/*.cpp SRC)

# Add executable :
add_executable (piouc ${SOURCE_FILES})

# Add libraries
set (CMAKE_PREFIX_PATH "/usr/lib/llvm")
set (LLVM_ROOT "/usr/lib/llvm")
find_package(LLVM)

if( NOT LLVM_FOUND )
  message(FATAL_ERROR "LLVM package can't be found. Set CMAKE_PREFIX_PATH variable to LLVM's installation prefix.")
endif()

include_directories( ${LLVM_INCLUDE_DIRS} )
link_directories( ${LLVM_LIBRARY_DIRS} )

llvm_map_components_to_libraries(REQ_LLVM_LIBRARIES all)

target_link_libraries(piouc ${REQ_LLVM_LIBRARIES})

#Add install targets
install (TARGETS piouc DESTINATION bin)
install (FILES "bin/PiouPiouConfig.h"
         DESTINATION include)
