cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)

# Define project name
project(SLAMin)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "version: ${OpenCV_VERSION}")
message(STATUS "libraries: ${OpenCV_LIBS}")
message(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")

add_subdirectory(src)