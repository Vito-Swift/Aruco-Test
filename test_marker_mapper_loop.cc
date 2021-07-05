//
// Created by Vito Wu on 2021/6/29.
//

// include from standard c++
#include <iostream>
#include <memory>
#include <numeric>

// include from opencv lib
#include <opencv2/highgui/highgui.hpp>

// include from aruco lib
#include <aruco/cameraparameters.h>
#include <aruco/dictionary.h>
#include <aruco/markerlabeler.h>

// include from marker mapper lib
#include "marker_mapper/markermapper.h"

char camera_param_file[] = "../out_camera_data.xml";
float marker_size = 0.5;
int ref_marker_id = 10;
int frame_increment = 1000;
std::string out_basename = "markermapper";

cv::Point3f mean3f(const std::vector<cv::Point3f> points) {
    cv::Point3f sum = std::accumulate(points.begin(), points.end(),
                                      cv::Point3f(0.0f, 0.0f, 0.0f),
                                      std::plus<cv::Point3f>());
    cv::Point3f mean(sum.x / points.size(), sum.y / points.size(), sum.z / points.size());
    return mean;
}

int main(int argc, char **argv) {
    cv::Mat frameimg;
    cv::VideoCapture cap;
    cap.open("udp://0.0.0.0:8000/");
    aruco::CameraParameters camera_params;
    camera_params.readFromXMLFile(camera_param_file);


    char key = 0;
    float total_batch_num = 0;
    float fail_batch_num = 0;
    do {
        // config aruco marker mapper
        std::shared_ptr<aruco_mm::MarkerMapper> arucoMarkerMapper;
        arucoMarkerMapper = aruco_mm::MarkerMapper::create();
        arucoMarkerMapper->setParams(camera_params, marker_size, ref_marker_id);
        arucoMarkerMapper->getMarkerDetector().setDictionary("ARUCO");

        total_batch_num = total_batch_num + 1.0;
        printf("Start processing\n");
        for (int i = 0; i < frame_increment; i++) {
            cap >> frameimg;
            if (key == 27)
                break;
            arucoMarkerMapper->process(frameimg, i, true);
            key = cv::waitKey(1);
        }

        printf("Processing on a group of image...\n");

        // optimize the marker place and save the result to files
        try {
            arucoMarkerMapper->optimize();
            std::vector<int> idlist;
            std::cout << "==========================================" << std::endl;
            arucoMarkerMapper->getMarkerMap().getIdList(idlist);
            for (int i = 0; i < idlist.size(); ++i) {
                cv::Point3f mean = mean3f(arucoMarkerMapper->getMarkerMap().getMarker3DInfo(idlist[i]).points);
                std::cout << "ArUco index: " << idlist[i] << "\t"
                          << "Point: (" << mean.x << ", " << mean.y << ", " << mean.z << ")" << std::endl;
            }
            std::cout << "==========================================" << std::endl;
        } catch (std::invalid_argument &e) {
            fail_batch_num = fail_batch_num +  1.0;
            std::cerr << e.what() << std::endl;
        }

        std::cout << "Failing ratio: " << fail_batch_num / total_batch_num << std::endl;
    } while (cap.grab() && key != 27);
}