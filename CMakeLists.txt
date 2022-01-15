cmake_minimum_required(VERSION 3.16)
project(slam)

set(CMAKE_CXX_STANDARD 14)

add_executable(slam main.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})