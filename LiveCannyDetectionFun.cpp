//
//  main.cpp
//  HonoursProject_TestingEnvironment
//
//  Created by joseph lefebvre on 2018-01-29.
//  Copyright © 2018 joseph lefebvre. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold = 50;
int const max_lowThreshold = 100;
int Ratio = 3;
int kernel_size = 3;
String window_name = "Edge Map";

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );
    
    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*Ratio, kernel_size );
    
    /// Using Canny's output as a mask, we display our result
    dst = Scalar::all(0);
    
    src.copyTo( dst, detected_edges);
    imshow( window_name, dst );
}


/** @function main */
int main( int argc, char** argv )
{
    /// Load an image
    
    VideoCapture cap(0) ;
    std::cout << cap.isOpened() << std::endl ;
    if (!cap.isOpened()) {
        std::cout << "VideoFile not found" << std::endl ;
    }
    
    
    
    String pathtoData = "/Users/josephlefebvre/Honours_Project/ViewnyxData/VYX_MIN50_SAMPLE_FRAMES/" ;
    
    //    src = imread(pathtoData+"MIN50__1000012"+".png") ;
    /// Create a window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    /// Create a Trackbar for user to enter threshold
    createTrackbar( "Low Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
    
    while(true){
        
        cap >> src ;
        //imshow("MyFace", src) ;
        int lowThres_copy = lowThreshold ;
        
        
        /// Create a matrix of the same type and size as src (for dst)
        dst.create( src.size(), src.type() );
        
        /// Convert the image to grayscale
        cvtColor( src, src_gray, CV_BGR2GRAY );
        CannyThreshold(0, 0);
        
        
        /// Show the image
        
        if (lowThres_copy != lowThreshold ){
            CannyThreshold(0, 0);
        }
        waitKey(1);
    }
    /// Wait until user exit program by pressing a key
    waitKey(0);
    
    return 0;
}

