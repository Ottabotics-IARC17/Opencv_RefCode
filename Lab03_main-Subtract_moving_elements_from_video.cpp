//
//  main.cpp
//  CSI4133_Lab03
//
//  Created by joseph lefebvre on 2017-10-05.
//  Copyright © 2017 joseph lefebvre. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp> 


cv::Mat isolateHueRange(cv::Mat , int , int) ;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    cv::VideoCapture cap("park.avi");
    if (!cap.isOpened()) {
        std::cout << "VideoFile not found" << std::endl ;
    }
    
    int fpsVideo = cap.get(CV_CAP_PROP_FPS) ;
    int frameWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH) ;
    int frameHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int numFrames = cap.get(CV_CAP_PROP_FRAME_COUNT) ;
    
    cv::Mat frameOrig1 ;
    cv::Mat frameOrig2 ;
    cv::Mat frameGrey1 ;
    cv::Mat frameGrey2 ;
    cv::Mat pixelDiffFrame ;
    cv::Mat thresholdedFrame ;
    
    cv::VideoWriter videoMaker("outputThres.mp4",CV_FOURCC('M','P','4','V'),fpsVideo,cv::Size(frameWidth,frameHeight),0);
        int frameCounter =0  ;
    
    while(true){
        
        cap >> frameOrig1 ;
        
        cap >> frameOrig2 ;
        
        if(frameOrig2.empty() || frameOrig1.empty()){
            break;
        }
        
        cv::cvtColor(frameOrig1, frameGrey1, CV_RGB2GRAY);
        cv::cvtColor(frameOrig2, frameGrey2, CV_RGB2GRAY);
        
        pixelDiffFrame = cv::abs(frameGrey2 - frameGrey1 ) ;
        
        cv::threshold(pixelDiffFrame, thresholdedFrame, 35, 255, CV_THRESH_BINARY);
       
        cv::imshow("IndivFrame", thresholdedFrame);
        cv::waitKey(10);
        
        videoMaker << thresholdedFrame ;
        
        frameCounter ++ ;
        std::cout << "Frame qriter : " << frameCounter << std::endl  ;
        
    }
        
    cap.release() ;
        
    
    


}
