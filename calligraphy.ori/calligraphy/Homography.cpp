//
//  Homography.cpp
//  calligraphy
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include "Homography.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void get_Homography(vector<Point> &four_point,
                    int width, int height,
                    int rotation,
                    Mat &H){
//    计算4点投影的变换矩阵
    vector<Point2f> tmp_dst_point;
    int border=width/240*10;
    
//   不想把marker点放进去, 所以放在四角的外边.
    tmp_dst_point.push_back(Point2f(float(width+border),float(0-border)));
    tmp_dst_point.push_back(Point2f(float(width+border),float(height+border)));
    tmp_dst_point.push_back(Point2f(float(0-border),float(height+border)));
    tmp_dst_point.push_back(Point2f(float(0-border),float(0-border)));
    vector<Point2f> dst_point(tmp_dst_point.size());
    for (int i=0;i<tmp_dst_point.size();i++){
        dst_point[i]=tmp_dst_point[(i+rotation)%tmp_dst_point.size()];
    }
    
    H = findHomography(four_point,dst_point, 0);
}
