cmake_minimum_required (VERSION 3.0)
project(code-for-blog)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall")

enable_testing()

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(MyTests test.cpp)
target_link_libraries(MyTests ${GTEST_BOTH_LIBRARIES})
target_link_libraries(MyTests ${CMAKE_THREAD_LIBS_INIT})

gtest_discover_tests(MyTests)

