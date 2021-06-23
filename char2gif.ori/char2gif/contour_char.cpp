//
//  contour_char.cpp
//  char2gif
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include "contour_char.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
void contour_char(Mat &frame,Rect &ROI){
    int R=100;
    Mat changed,th;
    cvtColor(frame, changed, COLOR_BGR2GRAY);
    changed.convertTo(changed, -1,2,150 );
    changed.convertTo(changed, -1,1,-128);
    changed.convertTo(changed, -1,2,0);
    threshold(changed, th, 200, 255, 1);
    dilate(th,th,getStructuringElement(MORPH_ELLIPSE, Size(R, R)) );
    ROI= boundingRect(th);
    
//    bitwise_not(th, th);
//    erode(th,th,getStructuringElement(MORPH_ELLIPSE, Size(R/2, R/2)) );
//    erode(th,th,getStructuringElement(MORPH_ELLIPSE, Size(R/2, R/2)) );
}
