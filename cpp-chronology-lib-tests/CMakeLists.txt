cmake_minimum_required(VERSION 3.1)
project(cpp-chronology-lib-tests)

# compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_definitions(-std=c++11)

# source files
SET(SOURCES "main.cpp")

# target
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} cpp-chronology-lib gtest)
target_include_directories(${PROJECT_NAME} PRIVATE 2d-hotlaps-lib)
