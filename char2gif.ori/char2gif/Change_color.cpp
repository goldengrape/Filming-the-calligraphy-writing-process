//
//  Change_color.cpp
//  char2gif
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include "Change_color.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void change_color(Mat &frame,
                  Mat &changed,
                  Mat &color_ft,
                  Mat &color_bg){
    int R=8;
    cvtColor(frame, changed, COLOR_BGR2GRAY);
    changed.convertTo(changed, -1,2,80 );
    changed.convertTo(changed, -1,1,-128);
    changed.convertTo(changed, -1,2,0);
    Mat th;
    threshold(changed, th, 200, 255, 1);
    dilate(th,th,getStructuringElement(MORPH_ELLIPSE, Size(R, R)) );
    erode(th,th,getStructuringElement(MORPH_ELLIPSE, Size(R, R)) );
    cvtColor(changed, changed, COLOR_GRAY2BGR);
    color_ft.copyTo(changed,th);
    bitwise_not(th, th);
    color_bg.copyTo(changed,th);
    cvtColor(changed, changed, COLOR_BGR2RGBA);

}
