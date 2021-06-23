//
//  process_one_frame.cpp
//  char2gif
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include "process_one_frame.hpp"
#include "Change_color.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
void process_one_frame(Mat &frame,
Mat &matR,
int &frame_width,
int &frame_height,
Mat &color_ft,
Mat &color_bg){
    warpAffine(frame, frame, matR,Size(frame_width,frame_height), INTER_LINEAR, BORDER_CONSTANT, Scalar(255,255,255));
             
    color_ft=frame.clone();

    change_color(frame,frame,color_ft,color_bg);
//               cvtColor(frame, frame, COLOR_BGR2RGBA);
}
