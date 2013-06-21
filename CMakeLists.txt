cmake_minimum_required (VERSION 2.6)

# Add modules used by this project to the module path
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "cmake/Modules/")
set(LLVM_DIR "cmake/Modules/")

# C++ 2011 flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -ggdb -W -Wall")

#C 99 flag
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb -W -Wall")
cmake_minimum_required (VERSION 2.6)

################################################################################
##                                  PROJECT                                   ##
################################################################################

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

################################################################################
##                                LIBRARIES                                   ##
################################################################################

# Add libraries
set (CMAKE_PREFIX_PATH "/usr/lib/llvm")
set (LLVM_ROOT "/usr/lib/llvm")
find_package(LLVM)

if( NOT LLVM_FOUND )
  message(FATAL_ERROR "LLVM package can't be found. Set CMAKE_PREFIX_PATH variable to LLVM's installation prefix.")
endif()

include_directories( ${LLVM_INCLUDE_DIRS} "src/" )
link_directories( ${LLVM_LIBRARY_DIRS} )

llvm_map_components_to_libraries(REQ_LLVM_LIBRARIES all)

target_link_libraries(piouc ${REQ_LLVM_LIBRARIES})

################################################################################
##                                 INSTALL                                    ##
################################################################################

#Add install targets
install (TARGETS piouc DESTINATION bin)
install (FILES "bin/PiouPiouConfig.h"
         DESTINATION include)


################################################################################
##                                  TESTS                                     ##
################################################################################

#Enable tests
enable_testing()

#Compile tests
set (TEST_SRC ${SOURCE_FILES})
file(GLOB_RECURSE UNWANTED_FILES src/Compiler.cpp SRC)
list (REMOVE_ITEM TEST_SRC ${UNWANTED_FILES})

set (ILLFORMED_LEXER_DIR "tests/illformed_lexer")
add_executable (illformed_lexer_test "${ILLFORMED_LEXER_DIR}/test.cpp" ${TEST_SRC} )

set (ILLFORMED_PARSER_DIR "tests/illformed_parser")
add_executable (illformed_parser_test "${ILLFORMED_PARSER_DIR}/test.cpp" ${TEST_SRC} )

#Run tests
add_test (NAME RunIllformedLexerTest WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/${ILLFORMED_LEXER_DIR}" COMMAND "illformed_lexer_test")

add_test (NAME RunIllformedParserTest WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/${ILLFORMED_PARSER_DIR}" COMMAND "illformed_parser_test")
