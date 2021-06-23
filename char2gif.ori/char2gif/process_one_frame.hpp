//
//  process_one_frame.hpp
//  char2gif
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#ifndef process_one_frame_hpp
#define process_one_frame_hpp

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void process_one_frame(Mat &frame,
                       Mat &matR,
                       int &frame_width,
                       int &frame_height,
                       Mat &color_ft,
                       Mat &color_bg);

#endif /* process_one_frame_hpp */
