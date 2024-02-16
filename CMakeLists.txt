cmake_minimum_required(VERSION 3.14)
set (CMAKE_CXX_STANDARD 17)
project(LongNumber VERSION 1.0.0
    DESCRIPTION "Long Number realization"
    LANGUAGES CXX)
add_library(LongNumber SHARED LongNumber.cpp LongNumber.h)
add_executable(PiCounting main.cpp)
target_link_libraries(PiCounting PRIVATE LongNumber)
include(CTest)
add_subdirectory(tests)
enable_testing()