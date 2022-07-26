cmake_minimum_required(VERSION 3.1)
project(cpp-chronology-lib)
find_package(Boost 1.71.0 COMPONENTS system filesystem) 
find_package(yaml-cpp)

# compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_definitions(-std=c++14)

# source files
SET(SOURCES "utils/utils.cpp" "providers/YamlDatabaseProvider.cpp" "managers/worklogDBManager.cpp")

# target
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Boost::system Boost::filesystem yaml-cpp)

