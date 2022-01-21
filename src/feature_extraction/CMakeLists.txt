find_package(OpenCV REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(fx_source_files 
features.cpp
)

add_library(feature_extraction ${fx_source_files})