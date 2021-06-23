//
//  contour_char.hpp
//  char2gif
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#ifndef contour_char_hpp
#define contour_char_hpp

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
void contour_char(Mat &frame,
                  Rect &ROI);

#endif /* contour_char_hpp */
