//
//  Warp_one_frame.cpp
//  calligraphy
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include "Warp_one_frame.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void warp_one_frame(Mat &frame,
Mat &warpd,
Mat &H,
int &width,
int &height,
Mat &combine_frame,
VideoWriter &oVideoWriter,
VideoWriter &o2VideoWriter,
Rect &ROI,
Rect &ROI_left,
Rect &ROI_right){
    warpPerspective(frame, warpd, H, Size(width,height));
    oVideoWriter.write(warpd);
    frame(ROI).copyTo(combine_frame(ROI_left));
    warpd.copyTo(combine_frame(ROI_right));
    o2VideoWriter.write(combine_frame);
}

