//
//  frame_corner.hpp
//  calligraphy
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#ifndef frame_corner_hpp
#define frame_corner_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void get_frame_corner(const Mat &frame,const Rect &ROI,vector<Point> &corner);

#endif /* frame_corner_hpp */
