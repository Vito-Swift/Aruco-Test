//
// Created by Vito Wu on 2021/6/23.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "aruco/aruco.h"
#include "cvdrawingutils.h"

int main() {
    aruco::MarkerDetector MDetector;
    cv::VideoCapture cap("rtp://172.31.0.2:8000/", cv::CAP_FFMPEG);
    if (!cap.isOpened()) {
        printf("error\n");
        return -1;
    }

    //std::vector<aruco::Marker> Markers;
    cv::Mat inputImage, inputImageGrey, inputImageCpy;
//    aruco::CameraParameters;

    int waitTime = 0;
    int refId = 0;
    bool isVideo = false;
    while (true) {
        cap >> inputImage;

        cv::imshow("webcam", inputImage);
        if (cv::waitKey(1) == 27) {
            break;
        }
    }
    cv::destroyAllWindows();
    return 0;
}