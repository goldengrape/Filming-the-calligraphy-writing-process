//
//  Homography.hpp
//  calligraphy
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#ifndef Homography_hpp
#define Homography_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void get_Homography(
                    vector<Point> &corner,
                    int width, int height,
                    int rotation,
                    Mat &H);

#endif /* Homography_hpp */
