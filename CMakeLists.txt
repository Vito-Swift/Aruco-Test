project(aruco_playground)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "/usr/local/include/opencv4")
find_package(OpenCV REQUIRED)
include_directories("/usr/local/include/aruco")

add_executable(main main.cc)
target_link_libraries(main ${OpenCV_LIBS} aruco)