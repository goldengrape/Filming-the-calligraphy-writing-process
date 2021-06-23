//
//  CLI_parser.cpp
//  calligraphy
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include "CLI_parser.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

bool get_CLI(CommandLineParser &parser,
             String &filename,
             String &output_filename,
             String &output_filename2){
    
    parser.about("change video color and contrast");
    //If requires help show
    if (parser.has("help"))
    {
        parser.printMessage();
        return true;
    }
    
    filename= parser.get<String>("@input");
    if (parser.has("@output")){
        output_filename=parser.get<String>("@output");
    }else{
        output_filename=
        filename.substr(0,filename.length()-4)+
        "_char.MP4";
    }
    
    if (parser.has("@output2")){
        output_filename=parser.get<String>("@output2");
    }else{
        output_filename2=
        filename.substr(0,filename.length()-4)+
        "_small.MP4";
    }

    
    return false;
}
