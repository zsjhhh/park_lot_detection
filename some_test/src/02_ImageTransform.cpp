
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <opencv2/opencv.hpp>

using namespace cv;

int main( int argc, char** argv){

    Point2f src_points1[]={
        Point2f(206,25),
        Point2f(109,22),
        Point2f(105,125),
        Point2f(215,126)};

    Point2f dst_points1[]={

        // Point2f(160,0),
        // Point2f(260,0),
        // Point2f(260,100),
        // Point2f(160,100)};
        Point2f(160,800),
        Point2f(260,800),
        Point2f(260,700),
        Point2f(160,700)};

    Point2f src_points2[]={
        Point2f(199,134),
        Point2f(195,24),
        Point2f(91,17),
        Point2f(83,132)};

    Point2f dst_points2[]={

        // Point2f(320,240),
        // Point2f(420,240),
        // Point2f(420,340),
        // Point2f(320,340)};

        Point2f(320,560),
        Point2f(420,560),
        Point2f(420,460),
        Point2f(320,460)};
    
     Point2f src_points3[]={
        Point2f(61,191),
        Point2f(260,159),
        Point2f(198,53),
        Point2f(78,65)};

    Point2f dst_points3[]={
       
        // Point2f(240,560),
        // Point2f(340,560),
        // Point2f(340,660),
        // Point2f(240,660)

        Point2f(360,240),
        Point2f(260,240),
        Point2f(260,140),
        Point2f(360,140)
        };

     Point2f src_points4[]={
        Point2f(61,131),
        Point2f(211,192),
        Point2f(250,77),
        Point2f(140,44)};

    Point2f dst_points4[]={
        // Point2f(80,560),
        // Point2f(180,560),
        // Point2f(180,660),
        // Point2f(80,660)};
        Point2f(80,240),
        Point2f(180,240),
        Point2f(180,140),
        Point2f(80,140)};

     Point2f src_points5[]={
        Point2f(79,36),
        Point2f(82,104),
        Point2f(175,131),
        Point2f(170,41)};

    Point2f dst_points5[]={

        // Point2f(0, 240),
        // Point2f(75, 252),
        // Point2f(100,340),
        // Point2f(0,340)};
        Point2f(0, 560),
        Point2f(75, 548),
        Point2f(100, 460),
        Point2f(0, 460)};

    
    Mat M1 = getPerspectiveTransform(src_points1,dst_points1);
    Mat M2 = getPerspectiveTransform(src_points2,dst_points2);
    Mat M3 = getPerspectiveTransform(src_points3,dst_points3);
    Mat M4 = getPerspectiveTransform(src_points4,dst_points4);
    Mat M5 = getPerspectiveTransform(src_points5,dst_points5);

    Mat image1 = imread("/home/zsj/catkin_ws/src/slam/src/1.jpg",0); 
    Mat image2 = imread("/home/zsj/catkin_ws/src/slam/src/2.jpg",0); 
    Mat image3 = imread("/home/zsj/catkin_ws/src/slam/src/3.jpg",0); 
    Mat image4 = imread("/home/zsj/catkin_ws/src/slam/src/4.jpg",0); 
    Mat image5 = imread("/home/zsj/catkin_ws/src/slam/src/5.jpg",0); 

    int dst_width = 600;
    int dst_height = 800;

    Mat imageTransform1, imageTransform2, imageTransform3, imageTransform4, imageTransform5;
    warpPerspective(image1, imageTransform1, M1, Size(dst_width, dst_height), INTER_LINEAR);
    warpPerspective(image2, imageTransform2, M2, Size(dst_width, dst_height), INTER_LINEAR);
    warpPerspective(image3, imageTransform3, M3, Size(dst_width, dst_height), INTER_LINEAR);
    warpPerspective(image4, imageTransform4, M4, Size(dst_width, dst_height), INTER_LINEAR);
    warpPerspective(image5, imageTransform5, M5, Size(dst_width, dst_height), INTER_LINEAR);

    namedWindow("warped1", 0);
    imshow("warped1",imageTransform1);
    namedWindow("warped2", 0);
    imshow("warped2",imageTransform2);
    namedWindow("warped3", 0);
    imshow("warped3",imageTransform3);
    namedWindow("warped4", 0);
    imshow("warped4",imageTransform4);
    namedWindow("warped5", 0);
    imshow("warped5",imageTransform5);
    Mat imageROI1 = imageTransform1(Rect(0, 532, 600, 266));
    Mat imageROI2 = imageTransform2(Rect(300, 266, 200, 366));
    Mat imageROI3 = imageTransform3(Rect(200, 0, 300, 300));
    Mat imageROI4 = imageTransform4(Rect(0, 0, 200, 300));
    Mat imageROI5 = imageTransform5(Rect(0, 260, 200, 330));

    namedWindow("ROI1", 0);
    imshow("ROI1",imageROI1);
    namedWindow("ROI2", 0);
    imshow("ROI2",imageROI2);
    namedWindow("ROI3", 0);
    imshow("ROI3",imageROI3);
    namedWindow("ROI4", 0);
    imshow("ROI4",imageROI4);
    namedWindow("ROI5", 0);
    imshow("ROI5",imageROI5);

    Mat dst(dst_height, dst_width, CV_8UC1, Scalar::all(0));
    // dst.setTo(0);
    imageROI1.copyTo(dst(Rect(0, 532, imageROI1.cols, imageROI1.rows)));
    imageROI2.copyTo(dst(Rect(350, 266, imageROI2.cols, imageROI2.rows)));
    imageROI3.copyTo(dst(Rect(200, 0, imageROI3.cols, imageROI3.rows)));
    imageROI4.copyTo(dst(Rect(0, 0, imageROI4.cols, imageROI4.rows)));
    imageROI5.copyTo(dst(Rect(0, 266, imageROI5.cols, imageROI5.rows)));

    // for(int i = 0; i < 800;i++)
    //     for(int j = 0; j < 800;j++){
    //         if(imageTransform1.at<uchar>(i, j)) dst.at<uchar>(i, j) = imageTransform1.at<uchar>(i, j);
    //         if(imageTransform2.at<uchar>(i, j)) dst.at<uchar>(i, j) = imageTransform2.at<uchar>(i, j);
    //     }

    namedWindow("b_dst", 0);
    imshow("b_dst", dst);
    waitKey(0);

    return 0;
}