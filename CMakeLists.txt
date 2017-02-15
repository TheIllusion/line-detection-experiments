cmake_minimum_required(VERSION 3.5)
project(line_segment_detection_experiments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package (OpenCV REQUIRED)
include_directories ( ${OpenCV_INCLUDE_DIRS} )

set(SOURCE_FILES main.cpp lsd_line_segment_detector.cpp lsd_line_segment_detector.h parameters.h lbd_line_detector.cpp lbd_line_detector.h selective_search.cpp selective_search.h seeds_superpixel.h seeds_superpixel.cpp simple_blob_detector.cpp simple_blob_detector.h)
add_executable(line_segment_detection_experiments ${SOURCE_FILES})

target_link_libraries(line_segment_detection_experiments ${OpenCV_LIBS})