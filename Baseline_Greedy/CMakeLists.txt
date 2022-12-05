cmake_minimum_required(VERSION 3.0)

project(BaselineGreedy)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src blg_src)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(BLG ${blg_src})

set(CMAKE_CXX_COMPILER      "g++" )

set(CMAKE_CXX_FLAGS   "-std=c++11")
