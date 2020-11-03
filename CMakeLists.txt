cmake_minimum_required(VERSION 3.16)
project("getopt"
        VERSION 0.1
        DESCRIPTION "A portable implementation of getopt"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(getopt STATIC ./src/getopt.cpp)
target_include_directories(getopt PUBLIC include)

add_subdirectory(test)