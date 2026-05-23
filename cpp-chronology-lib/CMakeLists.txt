cmake_minimum_required(VERSION 3.15)
project(cpp-chronology-lib)
find_package(Boost REQUIRED COMPONENTS system filesystem)

# compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_definitions(-std=c++17)

# source files
SET(SOURCES 
    "utils/utils.cpp"
    "database/DatabaseWrapper.cpp"
    "database/WorklogDb.cpp")

# target
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Boost::headers Boost::system Boost::filesystem)
target_link_libraries(${PROJECT_NAME} uuid sqlite3)
