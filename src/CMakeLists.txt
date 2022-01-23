
# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "version: ${OpenCV_VERSION}")
message(STATUS "libraries: ${OpenCV_LIBS}")
message(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")

add_subdirectory(feature_extraction)

set(slam_source_files main.cpp)
# Declare the executable target built from your sources
add_executable(slam ${slam_source_files})
# add_executable(helper, "src/helper.cpp")

# Link your application with OpenCV libraries
target_link_libraries(slam ${OpenCV_LIBS})
