//
//  Change_color.hpp
//  char2gif
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#ifndef Change_color_hpp
#define Change_color_hpp

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void change_color(Mat &frame,
                  Mat &changed,
                  Mat &color_ft,
                  Mat &color_bg);


#endif /* Change_color_hpp */
