cmake_minimum_required(VERSION 3.0.0)
project(Algorithm VERSION 0.1.0)
# set(CMAKE_BUILD_TYPE Release)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_CXX_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ${LIB_DIR})

include_directories(${INCLUDE_DIR})

# add_executable(Algorithm ${SRC_DIR}/LinearList.cpp)
add_executable(AlgorithmTest ${PROJECT_SOURCE_DIR}/main.cpp)
