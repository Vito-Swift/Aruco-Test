project(aruco_playground)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "/usr/local/include/opencv4")
find_package(OpenCV REQUIRED)
include_directories("/usr/local/include/aruco")
include_directories("/usr/local/include/maker_mapper")

add_executable(main main.cc)
target_link_libraries(main ${OpenCV_LIBS} aruco)

add_executable(calibration_camera calibration_camera.cc calibration_camera.hh)
target_link_libraries(calibration_camera ${OpenCV_LIBS})

add_executable(test_marker_mapper test_marker_mapper.cc)
target_link_libraries(test_marker_mapper aruco ${OpenCV_LIBS} marker_mapper)

add_executable(test_marker_mapper_loop test_marker_mapper_loop.cc)
target_link_libraries(test_marker_mapper_loop aruco ${OpenCV_LIBS} marker_mapper)

add_executable(test_astar astar.cc)