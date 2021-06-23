//
//  Warp_one_frame.hpp
//  calligraphy
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#ifndef Warp_one_frame_hpp
#define Warp_one_frame_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void warp_one_frame( Mat &frame,
                    Mat &warpd,
                     Mat &H,
                     int &width,
                     int &height,
                    Mat &combine_frame,
                    VideoWriter &oVideoWriter,
                    VideoWriter &o2VideoWriter,
                    Rect &ROI,
                    Rect &ROI_left,
                    Rect &ROI_right);

#endif /* Warp_one_frame_hpp */
