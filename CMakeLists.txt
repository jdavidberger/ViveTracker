project(ViveTracker C CXX)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)

include(package.cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS} -std=c++14")

option(USE_ASAN "Use Address and UB sanitizers" OFF)
option(USE_PROFILER "Enable Profiling" OFF)
option(BUILD_EXAMPLES "Build the example applications" OFF)
option(BUILD_TESTS "Build the unit tests" OFF)

IF(USE_PROFILER)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -pg")
ENDIF()

IF(USE_ASAN)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fstack-check -fsanitize=undefined")
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=integer -Werror=inconsistent-missing-override")
    endif()
    MESSAGE("ASAN enabled")
ENDIF()

SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS}")

add_library(ViveTracker STATIC ViveTracker.cpp)

target_link_libraries(ViveTracker)

if(BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()
