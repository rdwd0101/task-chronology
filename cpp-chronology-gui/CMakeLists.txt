cmake_minimum_required(VERSION 3.1)
project(cpp-chronology-gui)

# compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_definitions(-std=c++11)

#includes
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0 gtkmm-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# source files
SET(SOURCES "main.cpp" "mainWindow.cpp")

# target
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(cpp-chronology-gui ${GTK3_LIBRARIES} glog)
