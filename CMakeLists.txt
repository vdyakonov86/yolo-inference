cmake_minimum_required(VERSION 3.23)

option(WITH_OPENCV "build _YOLO_OPENCV" ON)

project(yolo LANGUAGES C CXX)

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_compile_options(-w)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Release")

add_compile_options(-D_YOLO_OPENCV)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/opencv SRCS)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/opencv)

add_executable(yolo ${SRCS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${OpenCV2_INCLUDE_DIRS})
target_link_libraries(yolo ${OpenCV_LIBRARIES})  
