cmake_minimum_required(VERSION 3.0)

project(LinearDeterministicGreedy)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ldg_src)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(LDG ${ldg_src})

set(CMAKE_CXX_COMPILER      "g++" )

set(CMAKE_CXX_FLAGS   "-std=c++11")
