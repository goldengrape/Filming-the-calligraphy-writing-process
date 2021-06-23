//
//  frame_corner.cpp
//  calligraphy
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include "frame_corner.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void get_frame_corner(const Mat &frame,
                  const Rect &ROI,
                  vector<Point> &corner){
    Mat bw_frame;
    vector<vector<Point> > contours;
    vector<Point> cs, cs_convex;
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours0;

//    图像转换成黑白
    cvtColor(frame,bw_frame,COLOR_BGR2GRAY);
    threshold(bw_frame, bw_frame, 120, 255, THRESH_BINARY);
//    imshow("bw",bw_frame);
//    waitKey(0);
//    找到contours
    findContours( bw_frame(ROI), contours0, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(ROI.x, ROI.y));
//    检索每一个contours
    for( size_t k = 0; k < contours0.size(); k++ )
//        面积足够大时
    if(contourArea(contours0[k])>=100000){
//        拟合多边形
    approxPolyDP(Mat(contours0[k]), cs, 50, true);
//        如果是四边形
        if (cs.size()==4){
//            如果还和凸四边形面积相等
            convexHull(cs, cs_convex);
            if (contourArea(cs)==contourArea(cs_convex)) {
                corner=cs_convex;
            }
        }
    }
}
