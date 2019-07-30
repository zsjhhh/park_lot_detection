
#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main( int argc, char** argv){

    Point2f src_points1[]={
        Point2f(96,272),
        Point2f(164,396),
        Point2f(384,394),
        Point2f(521,231)};

    Point2f dst_points1[]={
        Point2f(5,10-0.5)*80,
        Point2f(4,10-1.5)*80,
        Point2f(2,10-1.5)*80,
        Point2f(0,10-0)*80};

    Point2f src_points2[]={
        Point2f(600,140),
        Point2f(22,158),
        Point2f(182,260),
        Point2f(512,253)};

    Point2f dst_points2[]={
        Point2f(5,10-0.5)*80,
        Point2f(5,10-7)*80,
        Point2f(4,10-5)*80,
        Point2f(4,10-1.5)*80};
    
     Point2f src_points3[]={
        Point2f(373,276),
        Point2f(251,197),
        Point2f(160,233),
        Point2f(159,293)};

    Point2f dst_points3[]={
        Point2f(5,10-7)*80,
        Point2f(4,10-9)*80,
        Point2f(2.5,10-9)*80,
        Point2f(2.5,10-8)*80
        };

     Point2f src_points4[]={
        Point2f(316,221),
        Point2f(338,146),
        Point2f(260,38),
        Point2f(105,115)};

    Point2f dst_points4[]={
        Point2f(2.5,10-7)*80,
        Point2f(2.5,10-8)*80,
        Point2f(1,10-9)*80,
        Point2f(0,10-7)*80};

     Point2f src_points5[]={
        Point2f(165,283),
        Point2f(438,332),
        Point2f(570,186),
        Point2f(47,210)};

    Point2f dst_points5[]={
        Point2f(1, 10-2)*80,
        Point2f(1.5, 10-5)*80,
        Point2f(0, 10-7)*80,
        Point2f(0, 10-0)*80};


    Mat M1 = getPerspectiveTransform(src_points1,dst_points1);
    Mat M2 = getPerspectiveTransform(src_points2,dst_points2);
    Mat M3 = getPerspectiveTransform(src_points3,dst_points3);
    Mat M4 = getPerspectiveTransform(src_points4,dst_points4);
    Mat M5 = getPerspectiveTransform(src_points5,dst_points5);

    Mat image1 = imread("/home/zsj/Desktop/pic_0325/back.jpg",0); 
    Mat image2 = imread("/home/zsj/Desktop/pic_0325/right.jpg",0); 
    Mat image3 = imread("/home/zsj/Desktop/pic_0325/front_right.jpg",0); 
    Mat image4 = imread("/home/zsj/Desktop/pic_0325/front_left.jpg",0); 
    Mat image5 = imread("/home/zsj/Desktop/pic_0325/left.jpg",0); 

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
    Mat imageROI2 = imageTransform2(Rect(200, 200, 400, 500));
    Mat imageROI3 = imageTransform3(Rect(200, 0, 400, 300));
    Mat imageROI4 = imageTransform4(Rect(0, 0, 300, 300));
    Mat imageROI5 = imageTransform5(Rect(0, 200, 200, 500));

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
    
    imageROI1.copyTo(dst(Rect(0, 532, imageROI1.cols, imageROI1.rows)));
    imageROI2.copyTo(dst(Rect(200, 200, imageROI2.cols, imageROI2.rows)));
    imageROI5.copyTo(dst(Rect(0, 200, imageROI5.cols, imageROI5.rows)));
    imageROI4.copyTo(dst(Rect(0, 0, imageROI4.cols, imageROI4.rows)));
    imageROI3.copyTo(dst(Rect(200, 0, imageROI3.cols, imageROI3.rows)));
    
    imwrite("./result.jpg", dst);

    namedWindow("b_dst", 0);
    imshow("b_dst", dst);
    waitKey(0);

    //publish panorama
    ros::init(argc, argv, "slam");
    ros::NodeHandle nd;
    ros::Publisher pano_pub = nd.advertise<std_msgs::String>("panorama", 1000);
    ros::Rate loop_rate(10);
    int count = 0;

    while (ros::ok())
    {
        std_msgs::String msg;

        std::stringstream ss;
        ss << "hello world" << count;
        msg.data = ss.str();
        ROS_INFO("%s", msg.data.c_str());
        pano_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }

    return 0;
}