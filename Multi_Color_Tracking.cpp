//
//  main.cpp
//  CSI4133_FinalProject_Dev
//
//  Created by joseph lefebvre on 2017-11-26.
//  Copyright © 2017 joseph lefebvre. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
//#include <opencv2/tracking.hpp>
//#include <opencv2/core/ocl.hpp>

using namespace cv ;

cv::Mat isolateHueRange(cv::Mat , int  , int );

RNG rng(12345);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::cout << "/**********************" << std::endl ;
    std::cout << "/*" << std::endl ;
    std::cout << "/* Final Project\n/*Joseph LeFebvre\n/*7374469\n/*" << std::endl ;
    std::cout << "/**********************" << std::endl ;
    
    std::vector<std::string> videos;
    
    Mat CircleTest = imread("/Users/joseph-lef/Computer Science/Fall 2017/CSI4133/CSI4133_Lab5/CSI4133_Lab05_Development/circles_target.jpg", 0) ;
    videos.push_back("video3.avi");
    videos.push_back("video2.avi");
    videos.push_back("video1.avi");
    
    while (! videos.empty()) {
        std::string videoName = videos.back() ;
        videos.pop_back() ;
        int videoId = 1 ;

        
        std::cout << "Video being processed: " << videoName << std::endl ;

        Mat origFrame ,origFrame_gray, origFrame_circles, origFrame_HSV ;
        
    
        VideoCapture cap(videoName) ;
        if (!cap.isOpened()) {
            std::cout << "VideoFile not found" << std::endl ;
            continue ;
        }
        
        // --- Some properties of the video ---
        int fpsVideo = cap.get(CV_CAP_PROP_FPS) ;
        int frameWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH) ;
        int frameHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        int numFrames = cap.get(CV_CAP_PROP_FRAME_COUNT) ;
        
        // ------------------------------------
//        
//        cv::VideoWriter outputVideo1("/Users/joseph-lef/Computer Science/Fall 2017/CSI4133/CSI4133_FinalProject/CSI4133_FinalProject_7374469 /Output/outputTracker1.mp4",CV_FOURCC('M','P','4','V'),fpsVideo,cv::Size(frameWidth,frameHeight),0);
//        
//        cv::VideoWriter outputVideo2("/Users/joseph-lef/Computer Science/Fall 2017/CSI4133/CSI4133_FinalProject/CSI4133_FinalProject_7374469 /Output/outputTracker2.mp4",CV_FOURCC('M','P','4','V'),fpsVideo,cv::Size(frameWidth,frameHeight),0);
//        
//        cv::VideoWriter outputVideo3("/Users/joseph-lef/Computer Science/Fall 2017/CSI4133/CSI4133_FinalProject/CSI4133_FinalProject_7374469 /Output/outputTracker3.mp4",CV_FOURCC('M','P','4','V'),fpsVideo,cv::Size(frameWidth,frameHeight),0);

        
        
        
        std::cout << "Film Properties:\nfpsVideo = " << fpsVideo << "\nnumFrmes = "
        << numFrames << "\nFrame Height = " << frameHeight << "\nFrame Width = " << frameWidth << std::endl ;
        
            std::vector<std::pair<int, int> > colorRanges ;
            // Possible HSV ranges for different Colours
            std::pair<int,int> greenRange ;
            std::pair<int,int> yellowRange ;
            std::pair<int,int> blueRange ;
            std::pair<int,int> navyblueRange ;
            greenRange = std::make_pair(118/2,122/2) ;
        Scalar greenLow = Scalar(40,100,100) ;
        Scalar greenHigh = Scalar(75,255,255) ;
        Scalar yellowLow = Scalar(19,100,100);
        Scalar yellowHigh = Scalar(30,255,255);
        Scalar blueLow = Scalar(95,70,0) ;
        Scalar blueHigh = Scalar(100,255,255) ;
        
            colorRanges.push_back(greenRange);
            colorRanges.push_back(yellowRange);
            colorRanges.push_back(blueRange);
        
        while(true){
        
        // Detect Red Circles .....
            
            cap >> origFrame ;
            
            cv::cvtColor(origFrame , origFrame_HSV, cv::COLOR_BGR2HSV) ;
            
            
            if (origFrame.empty()) {
                std::cout << "Current Frame is Empty, entire video was processed" << std::endl ;
                break ;
            }
            // Frame that holds result of opencv inrange function which thresholds the image based
            // on a range of values.
            
            Mat frameInRange ;// isolateHueRange(<#cv::Mat inputHSVImage#>, <#int startHue#>, <#int endHue#>)
            
            // Codes Refs from https://stackoverflow.com/questions/29156091/opencv-edge-border-detection-based-on-color
            
            std::vector<Mat> channels ;
            split(origFrame_HSV,channels) ;
            
            cv::Mat H = channels[0];
            cv::Mat S = channels[1];
            cv::Mat V = channels[2];

            cv::Mat shiftedH = H.clone();
            int shift = 25; // in openCV hue values go from 0 to 180 (so have to be doubled to get to 0 .. 360) because of byte range from 0 to 255
            for(int j=0; j<shiftedH.rows; ++j)
                for(int i=0; i<shiftedH.cols; ++i)
                {
                    shiftedH.at<unsigned char>(j,i) = (shiftedH.at<unsigned char>(j,i) + shift)%180;
                }
              // We Split up the H values of the image into separate single channel images

            // When detected Red its values swing around the circle representing hue values, shifting them down
            // allows us to detect Red more accuratley
            
            // --- Code Ref Done -----------------------------
            //imshow("H_V1",H );
            //imshow("ShiftedH",shiftedH) ;
            
            cv::Mat cannyH;
            
            // specifically coded for red special case because Hue vales swing around circle
            Mat ShiftedH_Red_InRange ;
            inRange(shiftedH ,0+shift,4+shift,ShiftedH_Red_InRange) ;
            //imshow("ShiftH_REed", ShiftedH_Red_InRange) ;
            
            //imshow("H_V2",H );
            
            Mat green_InRange ;
            inRange(origFrame_HSV,greenLow,greenHigh, green_InRange);
            
            Mat blue_InRange ;
            inRange(origFrame_HSV, blueLow , blueHigh, blue_InRange) ;
            
            Mat yellow_InRange ;
            inRange(origFrame_HSV,yellowLow,yellowHigh,yellow_InRange) ;
            //imshow("yellowInrange", yellow_InRange) ;
            
            //imshow("GreenDectection", green_InRange) ;
            //imshow("YellowDetection", yellow_InRange) ;
            waitKey(1) ;
            
    
            Mat ShiftH_Red_E_D;
            
            erode(ShiftedH_Red_InRange, ShiftH_Red_E_D, getStructuringElement(MORPH_ELLIPSE,Size(15,15))) ;
            dilate(ShiftH_Red_E_D, ShiftH_Red_E_D, getStructuringElement(MORPH_ELLIPSE,Size(15,15))) ;
            dilate(ShiftH_Red_E_D, ShiftH_Red_E_D, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
            erode(ShiftH_Red_E_D, ShiftH_Red_E_D, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
            
            
            
        //    Mat green_InRange_ED;
            
            erode(green_InRange, green_InRange, getStructuringElement(MORPH_ELLIPSE,Size(8,8))) ;
            dilate(green_InRange, green_InRange, getStructuringElement(MORPH_ELLIPSE,Size(8,8))) ;
            dilate(green_InRange, green_InRange, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
            erode(green_InRange, green_InRange, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
            
       //     Mat yellow_InRange_ED;
            
            erode(yellow_InRange, yellow_InRange, getStructuringElement(MORPH_ELLIPSE,Size(10,10))) ;
            dilate(yellow_InRange, yellow_InRange, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
//            dilate(yellow_InRange, yellow_InRange, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
//            erode(yellow_InRange, yellow_InRange, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
            
            
            erode(blue_InRange, blue_InRange, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
            dilate(blue_InRange, blue_InRange, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
            dilate(blue_InRange, blue_InRange, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
            erode(blue_InRange, blue_InRange, getStructuringElement(MORPH_ELLIPSE,Size(5,5))) ;
            
            
            
            
            
//
            //int minDistanceBetweenCircles = origFrame_gray.rows/8 ;
//            std::cout << "Red Frame # of Channeles = "<< frameInRange.channels() << std::endl  ;
            
//            imshow("ShiftedH_Red_Eroded",ShiftH_Red_E_D) ;
//            waitKey(1) ;
            
            Mat Canny_On_Red ;
            cv::Canny(ShiftH_Red_E_D, Canny_On_Red, 150, 120);
            
            Mat Canny_On_green ;
            cv::Canny(green_InRange, Canny_On_green, 150, 120);
            
            Mat Canny_On_Yellow ;
            cv::Canny(yellow_InRange, Canny_On_Yellow, 150, 120);
            //imshow("CannyYelloe", Canny_On_Yellow) ;
            
            Mat Canny_On_Blue ;
            cv::Canny(blue_InRange, Canny_On_Blue, 150, 120);
            
           // imshow("CannyonRed", Canny_On_Red) ;
            waitKey(1);
            
            
            // ------ Ref from https://docs.opencv.org/3.3.0/df/d0d/tutorial_find_contours.html
            
            //Mat canny_output;
            std::vector<std::vector<Point> > contoursRed;
            std::vector<std::vector<Point> > contoursGreen;
            std::vector<std::vector<Point> > contoursBlue;
            std::vector<std::vector<Point> > contoursYellow;
            std::vector<Vec4i> hierarchyRed;
            std::vector<Vec4i> hierarchyGreen;
            std::vector<Vec4i> hierarchyBlue;
            std::vector<Vec4i> hierarchyYellow;
            
            //Canny( src_gray, canny_output, thresh, thresh*2, 3 );
            findContours( Canny_On_Red, contoursRed, hierarchyRed, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0) );
            findContours( Canny_On_green, contoursGreen, hierarchyGreen, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0) );
            findContours( Canny_On_Yellow, contoursYellow, hierarchyYellow, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0) );
            findContours( Canny_On_Blue, contoursBlue, hierarchyBlue, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0) );
            Mat drawingRed = Mat::zeros( Canny_On_Red.size(), CV_8UC3 );
            Mat drawingGreen = Mat::zeros( Canny_On_green.size(), CV_8UC3 );
            Mat drawingYellow = Mat::zeros( Canny_On_Yellow.size(), CV_8UC3 );
            Mat drawingBlue = Mat::zeros( Canny_On_Blue.size(), CV_8UC3 );
            //imshow("Drawing_Mat",drawing) ;
            
            // ----- Ref from https://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/bounding_rects_circles/bounding_rects_circles.html
            
            std::vector<std::vector<Point> > contours_polyRed( contoursRed.size() );
            std::vector<Rect> boundRectRed( contoursRed.size() );
            std::vector<Point2f>centerRed( contoursRed.size() );
            std::vector<float>radiusRed( contoursRed.size() );
            
            std::vector<std::vector<Point> > contours_polyGreen( contoursGreen.size() );
            std::vector<Rect> boundRectGreen( contoursGreen.size() );
            std::vector<Point2f>centerGreen( contoursGreen.size() );
            std::vector<float>radiusGreen( contoursGreen.size() );
            
            std::vector<std::vector<Point> > contours_polyYellow( contoursYellow.size() );
            std::vector<Rect> boundRectYellow( contoursYellow.size() );
            std::vector<Point2f>centerYellow( contoursYellow.size() );
            std::vector<float>radiusYellow( contoursYellow.size() );
            
            std::vector<std::vector<Point> > contours_polyBlue( contoursBlue.size() );
            std::vector<Rect> boundRectBlue( contoursBlue.size() );
            std::vector<Point2f>centerBlue( contoursBlue.size() );
            std::vector<float>radiusBlue( contoursBlue.size() );
         
            // --- Draw Red contours around canny detected edges and draw rectangels
            
           // waitKey() ;
            for( size_t i = 0; i< contoursRed.size(); i++ )
            {
                approxPolyDP( Mat(contoursRed[i]), contours_polyRed[i], 3, true );
                boundRectRed[i] = boundingRect( Mat(contours_polyRed[i]) );
                minEnclosingCircle( (Mat)contours_polyRed[i], centerRed[i], radiusRed[i] );
                Scalar color = Scalar(0,0,255);
                drawContours( drawingRed, contoursRed, (int)i, color, 2, 8, hierarchyRed, 0, Point() );
                //HoughCircles(I, <#OutputArray circles#>, <#int method#>, <#double dp#>, <#double minDist#>)
            }
            
            
            for( int i = 0; i< contoursRed.size(); i++ )
            {
                //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                Scalar color = Scalar(0,0,255) ;
                drawContours( drawingRed, contours_polyRed, i, color, 1, 8, std::vector<Vec4i>(), 0, Point() );
                rectangle( drawingRed, boundRectRed[i].tl(), boundRectRed[i].br(), color, 2, 8, 0 );
                //rectangle( origFrame, boundRectRed[i].tl(), boundRectRed[i].br(), color, 2, 8, 0 );
                
                rectangle( origFrame,Point((int)centerRed[i].x - 30,(int)centerRed[i].y - 30),Point((int)centerRed[i].x+30,(int)centerRed[i].y+30) , color, 2, 8, 0 )  ;
                //int x = boundRect[i].br().x - boundRect[i].br().x
                //Point bottomRight = boundRectRed[i].br() ;
                
                std::ostringstream coordinate;
                coordinate << "(" << boundRectRed[i].br().x << "," << boundRectRed[i].br().y << ")" << "\nRed";
                putText(origFrame,coordinate.str(), boundRectRed[i].br(), FONT_HERSHEY_PLAIN, 1, color,1,LINE_8,false) ;
                
              // circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
            }
            
            // --- Draw Green contours around canny detected edges and draw rectangels
            
            
            for( size_t i = 0; i< contoursGreen.size(); i++ )
            {
                approxPolyDP( Mat(contoursGreen[i]), contours_polyGreen[i], 3, true );
                boundRectGreen[i] = boundingRect( Mat(contours_polyGreen[i]) );
                minEnclosingCircle( (Mat)contours_polyGreen[i], centerGreen[i], radiusGreen[i] );
                Scalar color = Scalar(0,0,255);
                drawContours( drawingGreen, contoursGreen, (int)i, color, 2, 8, hierarchyGreen, 0, Point() );
                //HoughCircles(I, <#OutputArray circles#>, <#int method#>, <#double dp#>, <#double minDist#>)
            }
            
            
            for( int i = 0; i< contoursGreen.size(); i++ )
            {
                //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                Scalar color = Scalar(0,0,255) ;
                drawContours( drawingGreen, contours_polyGreen, i, color, 1, 8, std::vector<Vec4i>(), 0, Point() );
                rectangle( drawingGreen, boundRectGreen[i].tl(), boundRectGreen[i].br(), color, 2, 8, 0 );
                //rectangle( origFrame, boundRectGreen[i].tl(), boundRectGreen[i].br(), color, 2, 8, 0 );
                //int x = boundRect[i].br().x - boundRect[i].br().x
                Point bottomRight = boundRectGreen[i].br() ;
                rectangle( origFrame,Point((int)centerGreen[i].x - 30,(int)centerGreen[i].y - 30),Point((int)centerGreen[i].x+30,(int)centerGreen[i].y+30) , color, 2, 8, 0 )  ;
                //rectangle( origFrame,Point(centerGreen[i].x - 30,centerGreen[i].y - 30),Point(centerGreen[i].x+30,centerGreen[i].y+30),color, 2, 8, 0 )  ;
                std::ostringstream coordinate;
                coordinate << "(" << boundRectGreen[i].br().x << "," << boundRectGreen[i].br().y << ")" << "\nGreen" ;
                putText(origFrame,coordinate.str(), boundRectGreen[i].br(), FONT_HERSHEY_PLAIN, 1, color,1,LINE_8,false) ;
                
                //circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
            }
            
            // --- Draw Yellow contours around canny detected edges and draw rectangels
            
            for( size_t i = 0; i< contoursYellow.size(); i++ )
            {
                approxPolyDP( Mat(contoursYellow[i]), contours_polyYellow[i], 3, true );
                boundRectYellow[i] = boundingRect( Mat(contours_polyYellow[i]) );
                minEnclosingCircle( (Mat)contours_polyYellow[i], centerYellow[i], radiusYellow[i] );
                Scalar color = Scalar(0,0,255);
                drawContours( drawingYellow, contoursYellow, (int)i, color, 2, 8, hierarchyYellow, 0, Point() );
                //HoughCircles(I, <#OutputArray circles#>, <#int method#>, <#double dp#>, <#double minDist#>)
            }
            
            
            for( int i = 0; i< contoursYellow.size(); i++ )
            {
                //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                Scalar color = Scalar(0,0,255) ;
                drawContours( drawingYellow, contours_polyYellow, i, color, 1, 8, std::vector<Vec4i>(), 0, Point() );
                rectangle( drawingYellow, boundRectYellow[i].tl(), boundRectYellow[i].br(), color, 2, 8, 0 );
                //rectangle( origFrame, boundRectYellow[i].tl(), boundRectYellow[i].br(), color, 2, 8, 0 );
                //int x = boundRect[i].br().x - boundRect[i].br().x
                rectangle( origFrame,Point((int)centerYellow[i].x - 30,(int)centerYellow[i].y - 30),Point((int)centerYellow[i].x+30,(int)centerYellow[i].y+30) , color, 2, 8, 0 )  ;
                std::ostringstream coordinate;
                coordinate << "(" << boundRectYellow[i].br().x << "," << boundRectYellow[i].br().y << ")" << "\nYellow" ;
                putText(origFrame,coordinate.str(), boundRectYellow[i].br(), FONT_HERSHEY_PLAIN, 1, color,1,LINE_8,false) ;
                
                //circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
            }
            
           // --- Draw Blue contours around canny detected edges and draw rectangels
            
            for( size_t i = 0; i< contoursBlue.size(); i++ )
            {
                approxPolyDP( Mat(contoursBlue[i]), contours_polyBlue[i], 3, true );
                boundRectBlue[i] = boundingRect( Mat(contours_polyBlue[i]) );
                minEnclosingCircle( (Mat)contours_polyBlue[i], centerBlue[i], radiusBlue[i] );
                Scalar color = Scalar(0,0,255);
                drawContours( drawingBlue, contoursBlue, (int)i, color, 2, 8, hierarchyBlue, 0, Point() );
                //HoughCircles(I, <#OutputArray circles#>, <#int method#>, <#double dp#>, <#double minDist#>)
            }
            
        
            
            for( int i = 0; i< contoursBlue.size(); i++ )
            {
                //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                Scalar color = Scalar(0,0,255) ;
                drawContours( drawingBlue, contours_polyBlue, i, color, 1, 8, std::vector<Vec4i>(), 0, Point() );
                rectangle( drawingYellow, boundRectBlue[i].tl(), boundRectBlue[i].br(), color, 2, 8, 0 );
                //rectangle( origFrame, boundRectBlue[i].tl(), boundRectBlue[i].br(), color, 2, 8, 0 );
                //int x = boundRect[i].br().x - boundRect[i].br().x
                rectangle( origFrame,Point((int)centerBlue[i].x - 30,(int)centerBlue[i].y - 30),Point((int)centerBlue[i].x+30,(int)centerBlue[i].y+30) , color, 2, 8, 0 )  ;
                std::ostringstream coordinate;
                coordinate << "(" << boundRectBlue[i].br().x << "," << boundRectBlue[i].br().y << ")" << "\nBlue" ;
                putText(origFrame,coordinate.str(), boundRectBlue[i].br(), FONT_HERSHEY_PLAIN, 1, color,1,LINE_8,false) ;
                
                //circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
            }

            //HoughCircles(drawing, drawing_circleDetection, <#int method#>, <#double dp#>, <#double minDist#>)
            namedWindow( "Contours", WINDOW_AUTOSIZE );
            moveWindow("Contours", 600, 200) ;
            namedWindow("DetctionAlgoEachFrame",WINDOW_AUTOSIZE) ;
            moveWindow("DetectionAlgoEachFrame", 600, 400) ;
            imshow("DetectionAlgoEachFrame", origFrame) ;
            //imshow( "Contours", drawingRed );
            //imshow("Circle_detection_on_contours",drawing_CircleDetection) ;
            waitKey(1) ;
            
            // ------
//            switch (videoId) {
//                case 1:
//                    outputVideo1 << origFrame ;
//                    break;
//                case 2 :
//                    outputVideo2 << origFrame  ;
//                    break ;
//                case 3:
//                    outputVideo3 << origFrame ;
//                    break ;
//                default:
//                    break;
//            }
            
            
        
        }
       videoId = videoId +1  ;
    
    }
    return 0;
}

cv::Mat isolateHueRange(cv::Mat inputHSVImage, int startHue , int endHue) {
    
    cv::Mat isolateHueImage ;
    inputHSVImage.copyTo(isolateHueImage) ;
    cv::MatIterator_<cv::Vec3b> it, end ;
    
    
    for( it = isolateHueImage.begin<cv::Vec3b>(), end = isolateHueImage.end<cv::Vec3b>(); it != end; ++it)
    {
        //        if( startHue == 0){
        //            if( (*it)[0] != startHue) {
        //                (*it)[0] = 0 ;
        //                (*it)[1] = 0 ;
        //                (*it)[2] = 0 ;
        //            }
        //        }else {
        if(!((*it)[0] >= startHue && (*it)[0] <= endHue)){
            (*it)[0] = 0 ;
            (*it)[1] = 0 ;
            (*it)[2] = 0 ;
        }
        //}
    }
    
    
    return isolateHueImage ;
    
}
