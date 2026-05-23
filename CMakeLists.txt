cmake_minimum_required(VERSION 3.15)
project(cpp-chronology)

# compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_definitions(-std=c++17)

add_subdirectory(cpp-chronology-lib)
add_subdirectory(cpp-chronology-lib-tests)
add_subdirectory(cpp-chronology-gui)
