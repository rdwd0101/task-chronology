cmake_minimum_required(VERSION 3.15)
project(cpp-chronology-lib-tests)
find_package(Boost REQUIRED COMPONENTS system filesystem)

# compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_definitions(-std=c++17)

# source files
SET(SOURCES "main.cpp")

# target
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} cpp-chronology-lib gtest pthread Boost::system Boost::filesystem)
