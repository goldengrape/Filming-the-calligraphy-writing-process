//
//  main.cpp
//  combine_char
//
//  Created by GoldenGrape on 2020/6/18.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "gif.h"
#include "CLI_parser.hpp"

using namespace std;
using namespace cv;

const char* keys=
{
    "{help        |   | print this message}"
    "{@input0   |   | input video file 0}"
    "{@input1   |   | input video file 1}"
    "{@input2   |   | input video file 2}"
    "{@input3   |   | input video file 3}"
    "{@output   |   | output gif file }"
};


int main(int argc, const char * argv[]) {
    vector<String> file_list;
    String output_filename;
   CommandLineParser parser(argc, argv, keys);
    
    //    命令行解析, 如果只是问help, 就结束
    if(get_CLI(parser,file_list,output_filename))return 0;
    
// 测试用文件名
//    file_list.push_back("/Volumes/macTF/书法视频/挑选/MAH01015_char.gif.MP4");
//    file_list.push_back("/Volumes/macTF/书法视频/挑选/MAH01023_char.gif.MP4");
//    file_list.push_back("/Volumes/macTF/书法视频/挑选/MAH01029_char.gif.MP4");
//    file_list.push_back("/Volumes/macTF/书法视频/挑选/MAH01039_char.gif.MP4");
//    output_filename="/Volumes/macTF/书法视频/挑选/MAH01039_char4.gif";
    
    String output_file2=output_filename+".MP4";
    VideoCapture cap;
    
    //    初始化设置GIF文件
    int delta=50;
    int width=240, height=240;
    int delay=5;
    
    GifWriter g;
    GifBegin(&g, output_filename.c_str(), width, height, delay);
    
    //    初始化视频文件和图片文件
    VideoWriter oVideoWriter(output_filename+".MP4", VideoWriter::fourcc('m', 'p', '4', 'v'),
    100/delay, Size(width,height), true);
    
//    设置四个分区
    vector<Rect> ROI_list;
    ROI_list.push_back(Rect(0,0,width,height));
    ROI_list.push_back(Rect(width,0,width,height));
    ROI_list.push_back(Rect(0,height,width,height));
    ROI_list.push_back(Rect(width,height,width,height));
    
//    重排列帧序数
    vector<int> idx_list;
    idx_list.push_back(400);
    for (int i=1;i<400;i++){
        idx_list.push_back(i);
    }
//    初始化循环内变量
      Mat whole_frame(Size(width*2,height*2), CV_8UC3,Scalar(255,255,255)); // 如果定义放在外面, 是有字的画面开始
    Mat frame, small_frame;
    int pos_now, max_file;
    
//    按重拍顺序逐一帧处理
    for (int idx_pointer=0;
         idx_pointer<idx_list.size();
         idx_pointer+=2){
        int idx=idx_list[idx_pointer];
//           Mat whole_frame(Size(width*2,height*2), CV_8UC3,Scalar(255,255,255)); // 如果定义放在里面则是白屏开始
//        逐步送入新的画面
        if(idx <delta*1){
            max_file=1;
        }else if (idx <delta*2){
            max_file=2;
        }else if (idx <delta*3){
            max_file=3;
        }else {
            max_file=4;
        }
//      按画面总量分
    for(int i=0; i<max_file; i++){
    cap.open(file_list[i]);
    pos_now=
    ((idx-i*delta)<cap.get(CAP_PROP_FRAME_COUNT))?(idx-i*delta):cap.get(CAP_PROP_FRAME_COUNT)-1;
    cap.set(CAP_PROP_POS_FRAMES,pos_now);
    cap.read(frame);
    frame.copyTo(whole_frame(ROI_list[i]));
//        cap.release();
        
    }
//        缩小至目标size
        resize(whole_frame, small_frame,Size(width,height));
//        写入gif或显示
//        imshow("video", small_frame);
//        if(waitKey(20)==27)break;
        Mat bgra_frame;
        cvtColor(small_frame, bgra_frame, COLOR_BGR2RGBA);
        GifWriteFrame(&g, bgra_frame.data, width, height, delay);
        oVideoWriter.write(small_frame);

//        进度条
     cout << flush << '\r' <<idx*100/idx_list.size() << "%  ";

                       }
                       cout << flush << '\r' ;
                       cout << "save to "<< output_filename<< endl;
    GifEnd(&g);
    cap.release();
    oVideoWriter.release();
    imwrite(output_filename+".jpg", small_frame);

    return 0;
}
