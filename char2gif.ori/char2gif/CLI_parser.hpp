//
//  CLI_parser.hpp
//  char2gif
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#ifndef CLI_parser_hpp
#define CLI_parser_hpp

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


bool get_CLI(
             CommandLineParser &parser,
             String &filename,
             String &output_filename);
#endif /* CLI_parser_hpp */
