cmake_minimum_required(VERSION 3.27)

project(libfsi VERSION 1.0 LANGUAGES C CXX)

add_library(fsi STATIC src/libfsi.c)
target_include_directories(fsi PUBLIC include)

option(LIBFSI_BUILD_TESTS "Build the tests" ON)

if (LIBFSI_BUILD_TESTS)
	add_subdirectory(test)
endif()
