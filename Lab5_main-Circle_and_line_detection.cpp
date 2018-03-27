//
//  main.cpp
//  CSI4133_Lab05_Development
//
//  Created by joseph lefebvre on 2017-11-01.
//  Copyright © 2017 joseph lefebvre. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp> 

using namespace cv ;

bool intersection(Point , Point , Point , Point, Point2f&);

Mat src, src_gray, src_edges  ;

int main(int argc, const char * argv[]) {
    
    std::string path = "/Users/joseph-lef/Computer Science/Fall 2017/CSI4133/CSI4133_Lab5/CSI4133_Lab05_7374469_Submission/Images/" ;
    // insert code here...
    
    Mat src_circles = imread("circles_target.jpg");
    
    if( !src_circles.data )
    { return -1; }
    Mat src_gray_circles ;
    cvtColor(src_circles, src_gray_circles, CV_BGR2GRAY) ;
    imwrite(path+"PartA/circlesTarget_GRAYSCALE_Only"+".png",src_gray_circles) ;
    GaussianBlur(src_gray_circles, src_gray_circles, Size(9,9),2,2) ;
    imwrite(path+"PartA/circlesTarget_GRAYSCALE_AND_GuassianBlur"+".png",src_gray_circles) ;
    std::vector<Vec3f> circles ;
    int minDistanceBetweenCircles = src_gray_circles.rows/16 ;
    std::cout << "Min dist between circles: " << minDistanceBetweenCircles << std::endl ;
    //imshow("ImageWithBLur", src_gray_circles) ;
    //cvWaitKey() ;
    HoughCircles(src_gray_circles, circles, CV_HOUGH_GRADIENT, 1, minDistanceBetweenCircles, 160,50, 0,0) ;
    std::cout << "Num Circles Detected = " << circles.size() << std::endl ;
    for( size_t i = 0; i < circles.size(); i++ )
    {
        
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle( src_circles, center, 3, Scalar(0,0,255), -1, 8, 0 );
        // circle outline
        circle( src_circles, center, radius, Scalar(0,255,0), 3, 8, 0 );
    }
    
    imshow("Hough_Circles Dectection", src_circles) ;
    imwrite(path+"PartA/Hough_Circle_Detection_ON_circles_target"+".png",src_circles) ;
    
    waitKey() ;
    
    src = imread("lines_target.jpg");
    
    if( !src.data )
    { return -1; }
    
    
    
    cvtColor(src, src_gray, CV_BGR2GRAY) ;
    
    GaussianBlur(src_gray, src_gray, Size(9,9),1,1) ;
    imwrite(path+"PartB/GuassianBlur_ON_linesTarget"+".png",src_gray) ;
    Canny(src_gray, src_edges,60, 250, 3);
    //cvtColor(src_edges, src_edges, CV_GRAY2BGR);
    imshow("CannyEdgeDetection",src_edges) ;
    imwrite(path+"PartB/CannyEdge_ON_linesTarget"+".png",src_edges) ;
    waitKey();
    
    std::vector<Vec2f> lines ;
    HoughLines(src_edges,lines,1,CV_PI/90,50,0,0) ;
    
    for( size_t i = 0; i < lines.size(); i++ )
    {
        std::cout << "LOOP1 , i = " << i << std::endl ;
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        std::cout << "(rho, theta): " << "("<<
        rho << ", " << theta << ")" <<  std::endl ;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        std::cout << "Pt1 ("<< pt1.x << ", " << pt1.y << ")" << std::endl ;
        std::cout << "Pt2 ("<< pt2.x << ", " << pt2.y << ")" << std::endl ;
        line( src, pt1, pt2, Scalar(0,255,0), 1, CV_AA);
//        imshow("LineDetection", src) ;
//        waitKey();
        size_t forloop2Stop = 0 ;
        std::cout << "Condition : " << (i > forloop2Stop)<< std::endl ;
        for (size_t j = i; j > forloop2Stop  ; j--) {
            std::cout << "\n\tLOOP2 , j = " << j << std::endl ;
            float rho2 = lines[j][0], theta2 = lines[j][1];
            Point pt1_copy, pt2_copy;
            Point2f intersec_Point ;
            double a2 = cos(theta2), b2 = sin(theta2);
            double x0_2 = a*rho2, y0_2 = b*rho2;
            pt1_copy.x = cvRound(x0_2 + 1000*(-b2));
            pt1_copy.y = cvRound(y0_2 + 1000*(a2));
            pt2_copy.x = cvRound(x0_2 - 1000*(-b2));
            pt2_copy.y = cvRound(y0_2 - 1000*(a2));
            
            std::cout << "\Pt1_copy ("<< pt1_copy.x << ", " << pt1_copy.y << ")" << std::endl ;
            std::cout << "\tPt2_copy ("<< pt2_copy.x << ", " << pt2_copy.y << ")" << std::endl ;
            
            if(intersection(pt1, pt2, pt1_copy, pt2_copy,intersec_Point)){
             std::cout << "\tIntersec ("<<intersec_Point.x << ", " << intersec_Point.y << ")" << std::endl ;
                circle( src, intersec_Point, 1, Scalar(0,0,255), -1, 8, 0 );

            }else{
                std::cout << "\tNo intersection" << std::endl ;
                // No intersection point on image, do nothing
                
            }
            
        
        }
        
    }
    std::cout << "Done processing" << std::endl ;
    imshow("LineDetection", src) ;
    imwrite(path+"PartB/HoughLineDectection_withIntersections"+".png",src) ;
    waitKey() ;
    

    
    return 0;
}

bool intersection(Point Line1_pt1, Point Line1_pt2, Point Line2_pt1, Point Line2_pt2, Point2f &intersec_Point) {
    double A1 = Line1_pt2.y - Line1_pt1.y ;
    double B1 = Line1_pt1.x - Line1_pt2.x ;
    double C1 = A1*Line1_pt1.x + B1*Line1_pt1.y ;
    
    double A2 = Line2_pt2.y - Line2_pt1.y ;
    double B2 = Line2_pt1.x - Line2_pt2.x ;
    double C2 = A2*Line2_pt1.x + B2*Line2_pt1.y ;

    double det = A1*B2 - A2*B1 ;
    if(det == 0 )  {
       return false ;
        // lines do not intersect , must be parrallel
    }else{
        intersec_Point.x = floorf((B2*C1 - B1*C2)/det);
        intersec_Point.y = floorf((A1*C2 - A2*C1)/det);
        if ( (intersec_Point.x >= std::min(Line1_pt1.x,Line1_pt2.x) &&
              intersec_Point.x <= std::max(Line1_pt1.x,Line1_pt2.x) )
            &&
            (intersec_Point.y >= std::min(Line1_pt1.y,Line1_pt2.y) &&
             intersec_Point.y <= std::max(Line1_pt1.y,Line1_pt2.y))){
                return true;
            }else{
                return false ;
            }
    }

}
  

    
    
    
//    Point2f d1 = p1 - o1;
//    Point2f d2 = p2 - o2;
    
//    float cross = d1.x*d2.y - d1.y*d2.x;
//    if (std::abs(cross) < /*EPS*/1e-8)
//        return false;
//    
//    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
//    r = o1 + d1 * t1;
 //   return true;

