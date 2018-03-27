//
//  main.cpp
//  CSI4133_Lab04
//
//  Created by joseph lefebvre on 2017-10-16.
//  Copyright © 2017 joseph lefebvre. All rights reserved.
//

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define maxHueValue = 360 ;

cv::Mat pic2_Orig ;
cv::Mat pic3_Orig ;
cv::Mat pic2_HSV ;
cv::Mat pic3_HSV ;
cv::Mat yellow_SquareBGR , red_SquareBGR, violet_SquareBGR ;

static void on_hue_pic2_trackbar(int , void*) ;

static void on_hue_pic3_trackbar(int , void*) ;

static void trackbar_square_choice(int, void*) ;

cv::Mat isolateHueRange(cv::Mat , int , int) ;


int main(int argc, const char * argv[]) {
    
    std::string path = "/Users/joseph-lef/Computer Science/Fall 2017/CSI4133/CSI4133_Lab4_7374469/Images/" ;
    
    
    /* HSV colour space characteristics
    H - is hue or the dominate wavelength of each colour
         hue is preserved under varying levels Illumination
    S - saturation is the purity / shades of the colour
    
    V - is the intensity of the image , showing the difference between brightly
          illuminated images and less brightly illuminated images
     */
    
    pic2_Orig = cv::imread("Picture2.png") ;
    pic3_Orig = cv::imread("Picture3.png") ;
    
    cv::cvtColor(pic2_Orig, pic2_HSV, cv::COLOR_BGR2HSV) ;
    cv::cvtColor(pic3_Orig, pic3_HSV, cv::COLOR_BGR2HSV) ;
    
    
    // Create hue Value trackbar for pic2_HSV
    int hue_slider_pic2 = 100 ;
    cv::namedWindow("Processed_Hue Pic2") ;
    cv::imshow("Processed_Hue Pic2", pic2_HSV);
    char hue_trackbarPic2[10] ;
    cv::createTrackbar(hue_trackbarPic2, "Processed_Hue Pic2", &hue_slider_pic2, 360 ,on_hue_pic2_trackbar) ;
    
    //Create hue Value trackbar for pic3_HSV
    int hue_slider_pic3 = 100 ;
    cv::namedWindow("Processed_Hue Pic3") ;
    cv::imshow("Processed_Hue Pic3", pic3_HSV);
    char hue_trackbarPic3[10] ;
    cv::createTrackbar(hue_trackbarPic3, "Processed_Hue Pic3", &hue_slider_pic3, 360 ,on_hue_pic3_trackbar) ;
    
    
    std::cout << "matType pic2 " << pic2_HSV.type() << std::endl ;
    
    
    
    // Display HSV images and arrange
//    cv::namedWindow("pic2_HSV");
//    cv::moveWindow("pic2_HSV", pic2_Orig.cols+45, 0) ;
//    
//    cv::namedWindow("pic3_HSV");
//    cv::moveWindow("pic3_HSV", pic3_Orig.cols+45, pic2_Orig.rows) ;
//    
    cv::imshow("pic2_RGB", pic2_Orig) ;
    cv::imshow("pic3_RGB", pic3_Orig) ;
//    
//    cv::imshow("pic2_HSV", pic2_HSV) ;
    cv::imwrite(path+"pic2_HSV"+".png", pic2_HSV);
    cv::imwrite(path+"pic3_HSV"+".png", pic3_HSV);
//    cv::imshow("pic3_HSV", pic3_HSV) ;
    
    cv::waitKey() ;
    
    
    // --- Part B -----
    //
    
    
    
    cv::namedWindow("pic2_Colour_Detection_Yel") ;
    cv::moveWindow("pic2_Colour_Detection_Yel", 800, 0) ;
    cv::Mat yellowSquare = isolateHueRange(pic2_HSV,35,36) ;
    cv::imwrite(path+"yelSquareRaw"+".png",yellowSquare );
    imshow("pic2_Colour_Detection_Yel", yellowSquare ) ;
    
    cv::namedWindow("pic2_Colour_Detection_Red") ;
    cv::moveWindow("pic2_Colour_Detection_Red", 800, 250) ;
    cv::Mat redSquare = isolateHueRange(pic2_HSV,0,0) ;
    cv::imwrite(path+"redSquare_Raw"+".png", redSquare );
    imshow("pic2_Colour_Detection_Red", redSquare) ;
    
    cv::namedWindow("pic2_Colour_Detection_Violet") ;
    cv::moveWindow("pic2_Colour_Detection_Violet", 800, 500) ;
    cv::Mat violetSquare = isolateHueRange(pic2_HSV,147,148) ;
    cv::imwrite(path+"violetSquare_Raw"+".png",violetSquare );
    imshow("pic2_Colour_Detection_Violet", violetSquare ) ;
    
    int erosion_size_yellow = 2 ;
    cv::Mat erosion_kernel_yellow = cv::getStructuringElement(0, cv::Size(2*erosion_size_yellow+1,2*erosion_size_yellow+1),
                                                              cv::Point(erosion_size_yellow,erosion_size_yellow));
    int erosion_size_red = 10 ;
    cv::Mat erosion_kernel_red = cv::getStructuringElement(0, cv::Size(2*erosion_size_red+1,2*erosion_size_red+1),
                                                              cv::Point(erosion_size_red,erosion_size_red));
    
    int erosion_size_violet = 1 ;
    cv::Mat erosion_kernel_violet = cv::getStructuringElement(0, cv::Size(2*erosion_size_violet+1,2*erosion_size_violet+1),
                                                           cv::Point(erosion_size_violet,erosion_size_violet));
    
    int dialation_violet_size = 3 ;
    cv::Mat dialation_kernel_violet = cv::getStructuringElement(0, cv::Size(2*dialation_violet_size+1,2*dialation_violet_size+1),
                                                              cv::Point(dialation_violet_size,dialation_violet_size));
    
    int dialation_yellow_size = 2 ;
    cv::Mat dialation_yellow = getStructuringElement( 0,
                                                     cv::Size( 2*dialation_yellow_size + 1, 2*dialation_yellow_size+1 ),
                                                     cv::Point( dialation_yellow_size, dialation_yellow_size ) );
    int dialation_red_size = 10 ;
    cv::Mat dialation_red = getStructuringElement( 0,
                                                     cv::Size( 2*dialation_red_size + 1, 2*dialation_red_size+1 ),
                                                     cv::Point( dialation_red_size, dialation_red_size ) );
    
    
    cv::erode(yellowSquare, yellow_SquareBGR, erosion_kernel_yellow) ;
    cv::dilate(yellow_SquareBGR, yellow_SquareBGR, dialation_yellow) ;
    cv::cvtColor(yellow_SquareBGR, yellow_SquareBGR, CV_HSV2BGR) ;
    cv::imwrite(path+"yellowSquareBGR_FINAL"+".png", yellow_SquareBGR );
    cv::imshow("Yellow Square", yellow_SquareBGR);
    
    cv::erode(redSquare, red_SquareBGR, erosion_kernel_red) ;
    cv::dilate(red_SquareBGR, red_SquareBGR, dialation_red) ;
    cv::cvtColor(red_SquareBGR, red_SquareBGR, CV_HSV2BGR) ;
    cv::imwrite(path+"redSquareBGR_FINAL"+".png", red_SquareBGR );
    cv::imshow("Red Square", red_SquareBGR) ;
    
    //cv::erode(violetSquare, violet_SquareBGR, erosion_kernel_violet) ;
    cv::dilate(violetSquare, violet_SquareBGR, dialation_kernel_violet) ;
    cv::cvtColor(violet_SquareBGR, violet_SquareBGR, CV_HSV2BGR) ;
    cv::imwrite(path+"violetSquareBGR_FINAL"+".png", violet_SquareBGR );
    cv::imshow("Violet Square", violet_SquareBGR) ;
    
    int square_choice = 0 ;
    cv::namedWindow("Detected_Squares") ;
    cv::moveWindow("Deteceted_Squares", 1280/2, 800/2);
   // int& sq_choice = square_choice ;
    
    cv::createTrackbar("Color["+std::to_string(square_choice), "Detected_Squares", &square_choice, 2 ,trackbar_square_choice) ;
    trackbar_square_choice(0, 0);
    
   // cv::erode(,  ,  )
    
    
    cv::waitKey() ;
    
    
    
    
    std::cout << "Hello, World!\n";
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


static void trackbar_square_choice(int squar_choice, void*){
    
    if(squar_choice == 0){
        cv::imshow("Detected_Squares", yellow_SquareBGR) ;
        
        
    }else if (squar_choice == 1){
        cv::imshow("Detected_Squares", red_SquareBGR) ;
    }else{
        cv::imshow("Detected_Squares", violet_SquareBGR) ;
    }
        
    
        
}

static void on_hue_pic2_trackbar(int hue_slider, void*){
    
    cv::Mat CopyPicHue ;
    pic2_HSV.copyTo(CopyPicHue) ;
    cv::MatIterator_<cv::Vec3b> it, end;
    
    std::cout << "Hue_slider vale Pic2 = " << hue_slider << std::endl ;
    
    for( it = CopyPicHue.begin<cv::Vec3b>(), end = CopyPicHue.end<cv::Vec3b>(); it != end; ++it)
    {
        if((*it)[0] != hue_slider ) {
            (*it)[0] = 0 ;
            (*it)[1] = 0 ;
            (*it)[2] = 0 ;
        }
    }
    
    cv::imshow("Processed_Hue Pic2",CopyPicHue) ;
    
}

static void on_hue_pic3_trackbar(int hue_slider, void*){
    
    cv::Mat CopyPicHue ;
    pic3_HSV.copyTo(CopyPicHue) ;
    
    cv::MatIterator_<cv::Vec3b> it, end;
    
    std::cout << "Hue_slider vale Pic3 = " << hue_slider << std::endl ;
    
    for( it = CopyPicHue.begin<cv::Vec3b>(), end = CopyPicHue.end<cv::Vec3b>(); it != end; ++it)
    {
        
        if((*it)[0] != hue_slider ) {
            (*it)[0] = 0 ;
            (*it)[1] = 0 ;
            (*it)[2] = 0 ;
        }
        
    }
    
    cv::imshow("Processed_Hue Pic3",CopyPicHue) ;
    
}

