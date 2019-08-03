cmake_minimum_required(VERSION 3.11)

project(cpppackets)
enable_testing()

# Set compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

# Set directories
set(OMI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/omi)
set(EXAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/example)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Build example projects
add_subdirectory(example/pcap)

# Tests
add_subdirectory(tests)
