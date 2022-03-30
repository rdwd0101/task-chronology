cmake_minimum_required(VERSION 3.1)
project(cpp-chronology-lib)
find_package(Boost 1.71.0 COMPONENTS system) 

# compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_definitions(-std=c++11)

# source files
SET(SOURCES "utils.cpp")

# target
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Boost::system)
