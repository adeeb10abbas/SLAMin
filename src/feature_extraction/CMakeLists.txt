find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

set(fx_source_files 
features.cpp
)

add_library(feature_extraction ${fx_source_files})