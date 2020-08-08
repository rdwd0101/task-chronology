cmake_minimum_required(VERSION 3.1)
project(cpp-chronology)

# compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_definitions(-std=c++11)

add_subdirectory(cpp-chronology-lib)
add_subdirectory(cpp-chronology-lib-tests)
add_subdirectory(cpp-chronology-gui)
