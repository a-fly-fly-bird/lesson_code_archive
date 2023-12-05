cmake_minimum_required(VERSION 3.0.2)
project(eigen_learn)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(helloworld src/helloworld.cpp)
target_link_libraries(helloworld ${EIGEN3_DIR})

add_executable(dynamic_resize src/dynamic_resize.cpp)
target_link_libraries(dynamic_resize ${EIGEN3_DIR})

add_executable(matrix_array src/matrix_array.cpp)
target_link_libraries(matrix_array ${EIGEN3_DIR})

add_executable(block src/block.cpp)
target_link_libraries(block ${EIGEN3_DIR})
