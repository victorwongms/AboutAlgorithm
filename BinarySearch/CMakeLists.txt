cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME BinarySearch)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/main.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})