cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Define project name
project(SLAMin CXX)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "version: ${OpenCV_VERSION}")
message(STATUS "libraries: ${OpenCV_LIBS}")
message(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")

file(GLOB src_files 
     "src/*.cpp"
)
set(SOURCES ${src_files})
set(LIBRARY_NAME processing_engine)
add_subdirectory(matplotplusplus)

add_library(${LIBRARY_NAME} include/features.hpp ${SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(main app/main.cpp)
target_link_libraries(processing_engine ${OpenCV_LIBS})
target_link_libraries(processing_engine ${Open3DHelper})
target_link_libraries(processing_engine matplot)

target_link_libraries(main PRIVATE ${LIBRARY_NAME})
