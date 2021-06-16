cmake_minimum_required(VERSION 3.10)

project(ray_tracer LANGUAGES CXX VERSION 0.1)

add_compile_options(-std=c++17)

add_library(compiler_warnings INTERFACE)

include(cmake/CompilerWarnings.cmake)
enable_compiler_warnings(compiler_warnings)

include(cmake/StaticAnalyzer.cmake)

include_directories(src)

add_subdirectory(src)

option(COMPILE_TESTS "Compile unit tests" OFF)

if(COMPILE_TESTS)
    add_compile_options(-DUNIT_TEST)
    add_subdirectory(test)
    add_subdirectory(lib/googletest)
endif()

