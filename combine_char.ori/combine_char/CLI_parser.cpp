//
//  CLI_parser.cpp
//  combine_char
//
//  Created by GoldenGrape on 2020/6/18.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include "CLI_parser.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

bool get_CLI(
CommandLineParser &parser,
vector<String> &file_list,
             String &output_filename){
    parser.about("change video color and contrast");
       //If requires help show
       if (parser.has("help"))
       {
           parser.printMessage();
           return true;
       }
       
    for (int i=0; i<4; i++){
        String fname=parser.get<String>(i);
        cout << i<<fname<<endl;
    file_list.push_back(fname);
        
    }
       if (parser.has("@output")){
           output_filename=parser.get<String>("@output");
       }else{
           output_filename=
           file_list[3].substr(0,file_list[3].length()-4)+
           "_4_char.gif";
       }
       
       

       
       return false;
}


