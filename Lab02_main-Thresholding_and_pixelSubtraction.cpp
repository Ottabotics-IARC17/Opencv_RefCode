//
//  main.cpp
//  CSI4133_Lab02
//
//  Created by joseph lefebvre on 2017-10-04.
//  Copyright © 2017 joseph lefebvre. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <random>
#include <ctime>

cv::Mat video1_image1 ;
cv::Mat video1_image2 ;
cv::Mat video1_image3 ;

cv::Mat video2_image1 ;
cv::Mat video2_image2 ;
cv::Mat video2_image3 ;

cv::Mat v1_pixelDiff ;
cv::Mat v2_pixelDiff ;
cv::Mat v1_thresholdV1 ;
cv::Mat v2_thresholdV2 ;

void display_image_safely(cv::Mat inputArray, const cv::String &winname) {
    
    if(!inputArray.empty()){
        cv::imshow(winname,inputArray);
    }else{
        std::cout << "image for window: " << winname << " not found" << std::endl ;
    }
    
}

int randCoordinate(){
    int r =  rand() % 1000 ;
    std::cout << "R value " << r << std::endl ;
    return r ; }

//Function Implement Trackbar for thresholding of VIDEO1

static void on_thres_trackbar_v1(int slider, void*){
    
    std::cout << "Value of CV_THRESH_BINARY enum " << CV_THRESH_BINARY << std::endl ;
    std::cout << "slider valueV1 " << slider << std::endl  ;
    cv::threshold(v1_pixelDiff, v1_thresholdV1, slider, 255, CV_THRESH_BINARY);
    cv::imshow("Video1 - Thresholding of pixelDiff", v1_thresholdV1);
    
    std::string path = "/Users/joseph-lef/Computer Science/Fall 2017/CSI4133/CSI4133_Lab2/CSI4133_Lab02submission_7374469/ThresholdImages/video1/" ;
    cv::imwrite(path+"ThresholdingVideo1_ThresValue="+std::to_string(slider)+".png", v1_thresholdV1);
   
    
}

//Function Implement Trackbar for thresholding of VIDEO2

static void on_thres_trackbar_v2(int slider, void*){
    
    std::cout << "Value of CV_THRESH_BINARY enum " << CV_THRESH_BINARY << std::endl ;
    std::cout << "slider valueV2 " << slider << std::endl  ;
    cv::threshold(v2_pixelDiff, v2_thresholdV2, slider, 255, CV_THRESH_BINARY);
    cv::imshow("Video2 - Thresholding of pixelDiff", v2_thresholdV2);
    std::string path = "/Users/joseph-lef/Computer Science/Fall 2017/CSI4133/CSI4133_Lab2/CSI4133_Lab02submission_7374469/ThresholdImages/video2/";
    cv::imwrite(path+"ThresholdingVIDEO2_ThresValue="+std::to_string(slider)+".png", v2_thresholdV2);
    
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    

    // Read image from file, stored in same path as executable file
    
     video1_image1 = cv::imread("Img02_0076.bmp", CV_LOAD_IMAGE_COLOR);
     video1_image2 = cv::imread("Img02_0077.bmp", CV_LOAD_IMAGE_COLOR);
     video1_image3 = cv::imread("Img02_0078.bmp", CV_LOAD_IMAGE_COLOR);
    
     video2_image1 = cv::imread("park466.bmp", CV_LOAD_IMAGE_COLOR);
     video2_image2 = cv::imread("park467.bmp", CV_LOAD_IMAGE_COLOR);
     video2_image3 = cv::imread("park468.bmp", CV_LOAD_IMAGE_COLOR);
    
    //Part A display the images in orginal colour form
    
    cvNamedWindow("v1_image2", CV_WINDOW_NORMAL) ;
    cvNamedWindow("v1_image3", CV_WINDOW_NORMAL) ;
    cv::namedWindow("v1_image1",CV_WINDOW_NORMAL);
    
    cv::namedWindow("v2_image1",CV_WINDOW_NORMAL);
    cv::namedWindow("v2_image2",CV_WINDOW_NORMAL);
    cv::namedWindow("v2_image3",CV_WINDOW_NORMAL);
    
    cv::moveWindow("v1_image1", 0, 0);
    cv::moveWindow("v1_image2", video1_image1.cols, 0);
    cv::moveWindow("v1_image3", video1_image2.cols+video1_image1.cols, 0);
    
    cv::moveWindow("v2_image1", 0, video1_image1.rows+45);
    cv::moveWindow("v2_image2", video2_image1.cols, video1_image2.rows+45);
    cv::moveWindow("v2_image3", video2_image2.cols+video2_image1.cols , video1_image3.rows+45);
    
    //std::cout << "cols =" << video1_image1.cols << std::endl ;
    //std::cout << "rows =" << video1_image1.rows << std::endl ;
    
    display_image_safely(video1_image1, "v1_image1");
    display_image_safely(video1_image2, "v1_image2");
    display_image_safely(video1_image3, "v1_image3");
    
    display_image_safely(video2_image1, "v2_image1");
    display_image_safely(video2_image2, "v2_image2");
    display_image_safely(video2_image3, "v2_image3");
    
    cv::waitKey();
    
    // Part B - Convert all image from RGB 2 GRAY
    
    cv::cvtColor(video1_image1, video1_image1, CV_RGB2GRAY);
    cv::cvtColor(video1_image2, video1_image2, CV_RGB2GRAY);
    cv::cvtColor(video1_image3, video1_image3, CV_RGB2GRAY);
    
    cv::cvtColor(video2_image1, video2_image1, CV_RGB2GRAY);
    cv::cvtColor(video2_image2, video2_image2, CV_RGB2GRAY);
    cv::cvtColor(video2_image3, video2_image3, CV_RGB2GRAY);
    
    
    // Part C - Subtract pixel diff.

        // Difference between image 3 and image 1 of VIDEO1
    v1_pixelDiff = cv::abs(video1_image3 - video1_image1) ;
        // Difference between image 3 and imag 2 of VIDEO2
    v2_pixelDiff = cv::abs(video2_image3 - video2_image2) ;
    
   // Window for pixel diff VIDEO1  ;
    cv::namedWindow("v1_pixelDiff",CV_WINDOW_NORMAL);
    cv::moveWindow("v1_pixelDiff", 0 , video1_image1.rows+45+video2_image2.rows+45);
    cv::imshow("v1_pixelDiff", v1_pixelDiff);
    
    // Window fo pixel diff VIDEO2
    
    cv::namedWindow("v2_pixelDiff", CV_WINDOW_NORMAL) ;
    cv::moveWindow("v2_pixelDiff", 500, 50);
    cv::imshow("v2_pixelDiff", v2_pixelDiff) ;
    
    
    // Part d - Thresholding using trackbar
    
    
    // Threshold + Trackbar VIDEO 1
    int value_sliderV1 = 50;
    cv::namedWindow("Video1 - Thresholding of pixelDiff");
    cv::moveWindow("Video1 - Thresholding of pixelDiff",v1_pixelDiff.cols+50,video1_image1.rows+45+video2_image2.rows+45);
    char thresholdTrackbarV1[10] ;
    cv::createTrackbar(thresholdTrackbarV1, "Video1 - Thresholding of pixelDiff", &value_sliderV1, 100, on_thres_trackbar_v1);
    
    // Threshold + Trackbar VIDEO 2
    
    int value_sliderV2 = 50;
    cv::namedWindow("Video2 - Thresholding of pixelDiff");
    cv::moveWindow("Video2 - Thresholding of pixelDiff",500,50+v2_pixelDiff.rows);
    char thresholdTrackbarV2[10] ;
    cv::createTrackbar(thresholdTrackbarV2, "Video2 - Thresholding of pixelDiff", &value_sliderV2, 100, on_thres_trackbar_v2);
    
    
    on_thres_trackbar_v1(value_sliderV1, 0);
    
    on_thres_trackbar_v2(value_sliderV2, 0);
    
    
    
    
    cv::waitKey(0);
    
    srand( (int) time(0));
    display_image_safely(video1_image1, "v1_image1");
    cv::waitKey(randCoordinate());
    cv::moveWindow("v1_image1", randCoordinate(), randCoordinate());
    display_image_safely(video1_image1, "v1_image1");
    cv::waitKey(randCoordinate());
    display_image_safely(video1_image2, "v1_image2");
    cv::waitKey(randCoordinate());
    cv::moveWindow("v1_image2", randCoordinate(), randCoordinate());
    display_image_safely(video1_image2, "v1_image2");
    cv::waitKey(randCoordinate());
    display_image_safely(video1_image3, "v1_image3");
    cv::waitKey(randCoordinate());
    cv::moveWindow("v1_image3", randCoordinate(), randCoordinate());
    display_image_safely(video1_image3, "v1_image3");
    cv::waitKey(randCoordinate());
    display_image_safely(video2_image1, "v2_image1");
    cv::waitKey(randCoordinate());
    cv::moveWindow("v2_image1", randCoordinate(), randCoordinate());
    display_image_safely(video2_image1, "v2_image1");
    cv::waitKey(randCoordinate());
    display_image_safely(video2_image2, "v2_image2");
    cv::waitKey(randCoordinate());
    cv::moveWindow("v2_image2", randCoordinate(), randCoordinate());
    display_image_safely(video2_image2, "v2_image2");
    cv::waitKey(randCoordinate());
    display_image_safely(video2_image3, "v2_image3");
    cv::waitKey(randCoordinate());
    cv::moveWindow("v2_image3", randCoordinate(), randCoordinate());
    display_image_safely(video2_image3, "v2_image3");
    cv::waitKey(randCoordinate());
    
    
    //display_image_safely(v1_pixelDiff, "v1_pixelDiff");
    
//    cvNamedWindow("v1_image1", CV_WINDOW_NORMAL) ;

    
    
    
    
    
    
    
//    if(!video1_image.empty()){
//        
//        cv::imshow("Video1_test", video1_image);
//        cv::waitKey();
//    }else{
//        std::cout << "image not found" << std::endl ;
//    }
//    
//    if(!video1_image2.empty()){
//        
//        cv::imshow("Video2_test", video1_image2);
//        cv::waitKey();
//    }else{
//        std::cout << "image not found" << std::endl ;
//    }
    
    return 0;
    
}


















