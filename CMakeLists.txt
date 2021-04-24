# Set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Project settings.
project(Coeus VERSION 1.0.0)

# Set C++ standard to C++14.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/prerequisites)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

option(BUILD_EXAMPLES "Build the example of Coeus." OFF)
if (${BUILD_EXAMPLES})
    message(STATUS "Building Examples")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif ()

option(BUILD_TESTS "Build the tests of Coeus." OFF)
if (${BUILD_TESTS})
    message(STATUS "Building Tests")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
    include(CTest)
    add_test(NAME System-Tests
            COMMAND system-tests
            )
endif ()