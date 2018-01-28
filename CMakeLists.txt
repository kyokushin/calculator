cmake_minimum_required(VERSION 3.0)

project(Calculator)

set(build_tests TRUE CACHE BOOL "enable to build tests")

set( CMAKE_CXX_STANDARD 11)
set( CMAKE_DEBUG_POSTFIX d)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

add_subdirectory(src)
if(${build_tests})
	add_subdirectory(test)
endif()
