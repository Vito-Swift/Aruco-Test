//
// Created by Vito Wu on 2021/6/23.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include "aruco/aruco.h"

int main() {
    aruco::MarkerDetector MDetector;
    cv::VideoCapture vc;
    std::vector<aruco::Marker> Markers;
    printf("hi\n");
    return 0;
}