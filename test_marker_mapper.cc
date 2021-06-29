//
// Created by Vito Wu on 2021/6/29.
//

// include from standard c++
#include <iostream>
#include <memory>

// include from opencv lib
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// include from aruco lib
#include <aruco/cameraparameters.h>
#include <aruco/dictionary.h>
#include <aruco/markerlabeler.h>

// include from marker mapper lib
#include "marker_mapper/markermapper.h"
#include "marker_mapper/debug.h"
#include "sglviewer.h"

char camera_param_file[] = "../out_camera_data.xml";
float marker_size = 0.5;
int ref_marker_id = 10;
int frame_increment = 1;
std::string out_basename = "markermapper";

int main(int argc, char **argv) {
    cv::Mat frameimg, frameimg_processed;
    cv::VideoCapture cap;
    cap.open("rtp://0.0.0.0:8000/");
    aruco::CameraParameters camera_params;
    camera_params.readFromXMLFile(camera_param_file);

    // config aruco marker mapper
    std::shared_ptr<aruco_mm::MarkerMapper> arucoMarkerMapper;
    arucoMarkerMapper = aruco_mm::MarkerMapper::create();
    arucoMarkerMapper->setParams(camera_params, marker_size, ref_marker_id);
    arucoMarkerMapper->getMarkerDetector().setDictionary("ARUCO");

    char key = 0;
    int frame_count = 0;
    do {
        cap >> frameimg;
        frameimg.copyTo(frameimg_processed);
        frame_count++;

        if (frame_count % frame_increment != 0)
            continue;

        arucoMarkerMapper->process(frameimg, frame_count);
        arucoMarkerMapper->drawDetectedMarkers(frameimg_processed);

        cv::imshow("display", frameimg_processed);

        key = cv::waitKey(1);
    } while (cap.grab() && key != 27);

    // optimize the marker place and save the result to files
    arucoMarkerMapper->optimize();
    arucoMarkerMapper->saveToPcd(out_basename + ".pcd", true);
    arucoMarkerMapper->saveFrameSetPosesToFile(out_basename + ".log");
    arucoMarkerMapper->getMarkerMap().saveToFile(out_basename + ".yml");

    // show the result in pcd viewer
    OpenCvMapperViewer Viewer;
    aruco::MarkerMap mmap;
    mmap.readFromFile(out_basename + ".yml");
    Viewer.setParams(mmap, 1.5, 1280, 960, "map_viewer");
    key = 0;
    while (key != 27)
        key = Viewer.show();
}