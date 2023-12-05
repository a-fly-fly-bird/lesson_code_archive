cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(ndt_test)

find_package(PCL REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARIES_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(ndt src/ndt.cpp)
target_link_libraries(ndt ${PCL_LIBRARIES})