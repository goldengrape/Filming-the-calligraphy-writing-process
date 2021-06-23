//
//  main.cpp
//  char2gif
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "CLI_parser.hpp"
#include "Change_color.hpp"
#include "process_one_frame.hpp"
#include "contour_char.hpp"
#include "gif.h"

using namespace std;
using namespace cv;

const char* keys=
{
    "{help      |   | print this message}"
    "{@input i  |   | input video file}"
    "{@output o |   | output video file}"
};
int main(int argc, const char * argv[]) {
    //    初始化
    String filename,output_filename;
    String bg_file="/Volumes/macTF/书法视频/char2gif.ori/char2gif/bg.png";
    String ft_file="/Volumes/macTF/书法视频/char2gif.ori/char2gif/ft.png";
    VideoCapture cap;
    CommandLineParser parser(argc, argv, keys);
    Mat frame,changed, small_frame, bgra_frame;
    int width=240, height=240;
    
    //    命令行解析, 如果只是问help, 就结束
        if(get_CLI(parser,filename,output_filename))return 0;
        
     
////        测试用文件
//        filename=          "/Volumes/macTF/书法视频/原字/安.MP4";
//     output_filename=          "/Volumes/macTF/书法视频/原字/安.gif";
//    
//    打开视频文件
    cap.open(filename);
    int total_frame_count=cap.get(CAP_PROP_FRAME_COUNT);
    int frame_width=(int)cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height=(int)cap.get(CAP_PROP_FRAME_HEIGHT);
    
    int total_gif_count=200;
    int delay = 5;
    
//    初始化设置GIF文件
    GifWriter g;
    GifBegin(&g, output_filename.c_str(), width, height, delay);
    
    int delta_frame=total_frame_count/total_gif_count;
//    初始化视频文件和图片文件
    VideoWriter oVideoWriter(output_filename+".MP4", VideoWriter::fourcc('m', 'p', '4', 'v'),
    100/delay, Size(width,height), true);
    
//    重排列帧顺序
    vector<int> frame_idx;
    frame_idx.push_back(total_frame_count-1);
    for (int i=0; i<total_frame_count; i+=delta_frame){
        frame_idx.push_back(i);
    }
//    读取前景和背景图像
//    Mat color_bg(Size(frame_width,frame_height), CV_8UC4,Scalar(0,0,0,0));
//    Mat color_ft(Size(frame_width,frame_height), CV_8UC3,Scalar(0,0,0));
    
    Mat color_bg=imread(bg_file);
    Mat color_ft=imread(ft_file);
    
    resize(color_bg, color_bg, Size(frame_width,frame_height));
    resize(color_ft, color_ft, Size(frame_width,frame_height));

//    消除边角
    cap.set(CAP_PROP_POS_FRAMES,frame_idx[0]);
    cap.read(frame);
    Rect char_ROI;
    contour_char(frame, char_ROI);
//    imshow("hi",frame(char_ROI));
//    waitKey(0);
//    return 0;
//    旋转初始化
    Point2f center=Point2f(frame_width/2,frame_height/2);
    
    Mat matR=getRotationMatrix2D(center,45,0.8);
    
//    逐一处理帧
        for(int i=0; i<frame_idx.size(); i++)
        {
    cap.set(CAP_PROP_POS_FRAMES,frame_idx[i]);
            cap.read(frame);
            
            Mat tmp=color_bg.clone(); frame(char_ROI).copyTo(tmp(char_ROI));
            tmp.copyTo(frame);
            
            process_one_frame(frame,matR,frame_width,frame_height,color_ft,color_bg);

            resize(frame, bgra_frame, Size(width,height));
            
            GifWriteFrame(&g, bgra_frame.data, width, height, delay);
            cvtColor(bgra_frame, bgra_frame, COLOR_RGBA2BGR);
            oVideoWriter.write(bgra_frame);

            cout << flush << '\r' <<frame_idx[i]*100/total_frame_count << "%  ";

                }
                cout << flush << '\r' ;
                cout << "save to "<< output_filename<< endl;
    GifEnd(&g);
    cap.release();
    oVideoWriter.release();
    imwrite(output_filename+".png", bgra_frame);
    return 0;
}
