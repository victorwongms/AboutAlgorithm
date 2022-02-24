cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME HeapAlgorithm)
project(PROJECT_NAME)

set(CXX_STANDARD_REQUIRED 11)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/main.cpp)

include_directories(${INCLUDE_DIR})

add_executable(heapAlgorithm ${SOURCE_FILES})