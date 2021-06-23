//
//  main.cpp
//  calligraphy
//
//  Created by GoldenGrape on 2020/6/17.
//  Copyright © 2020 goldengrape. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "frame_corner.hpp"
#include "CLI_parser.hpp"
#include "Homography.hpp"
#include "Warp_one_frame.hpp"

using namespace std;
using namespace cv;

const char* keys=
{
    "{help      |   | print this message}"
    "{@input i  |   | input video file}"
    "{@output o |   | output video file}"
    "{@output2  |   | output video file2}"
};


int main(int argc, const char * argv[]) {
//    初始化
    String filename, output_filename, output_filename2;
    VideoCapture cap;
    CommandLineParser parser(argc, argv, keys);
    Mat frame,warpd;
    vector<Point> corner;
    int width=800, height=800;

//    命令行解析, 如果只是问help, 就结束
    if(get_CLI(parser,filename,output_filename,output_filename2))return 0;
    
 
//    测试用文件
//    filename="/Volumes/macTF/书法视频/挑选/渊.MP4";
//    output_filename="/Volumes/macTF/书法视频/挑选/渊.MP4_char.MP4";
//    output_filename2="/Volumes/macTF/书法视频/挑选/渊.MP4_small.MP4";
    
//    初始化读写文件
    cap.open(filename);
    float total_frame=(float) cap.get(CAP_PROP_FRAME_COUNT);

    int fps=30;
    VideoWriter oVideoWriter(output_filename, VideoWriter::fourcc('m', 'p', '4', 'v'),
    fps, Size(width,height), true);
    
    
    VideoWriter o2VideoWriter(output_filename2, VideoWriter::fourcc('m', 'p', '4', 'v'),
    fps, Size(width*2,height), true);
    
    Mat combine_frame=Mat::zeros(Size(width*2,height), CV_8UC3);
    Rect ROI_left=Rect(0,0,width,height);
    Rect ROI_right=Rect(width,0,height,height);

//    找到标记方块的四角
    Rect ROI=Rect(320,0,width,height);
    for(int i=0; i<3; i++){
            cap.read(frame);
        }
    get_frame_corner(frame, ROI, corner);
 
//    计算变换矩阵
    Mat H;
    int rotation=2;
    get_Homography(corner,width,height,rotation,H);
    cout<<setiosflags(ios::fixed)<<setprecision(2);

//    重排列帧
    vector<int> frame_idx;
    int delta_frame=1;
    frame_idx.push_back(total_frame-2);
    frame_idx.push_back(total_frame-1);

    for (int i=0; i<total_frame; i+=delta_frame){
        frame_idx.push_back(i);
    }
    
//    处理每一帧
    for (int idx=0; idx<frame_idx.size();idx++){
        cap.set(CAP_PROP_POS_FRAMES,frame_idx[idx]);
        cap.read(frame);
        warp_one_frame(frame,warpd,H,width,height,combine_frame,oVideoWriter,o2VideoWriter,ROI,ROI_left,ROI_right);
        
    cout << flush << '\r' <<frame_idx[idx]/total_frame*100 << "%  ";

}
cout << flush << '\r' ;
cout << "save to "<< output_filename<< endl;
    cout << "save to "<< output_filename2<< endl;

cap.release();
oVideoWriter.release();
o2VideoWriter.release();

return 0;
}
