#include <queue>

#include <ros/ros.h>
#include "std_msgs/String.h"

#include "std_msgs/Int64.h"
#include "std_msgs/Int64MultiArray.h"
#include <darknet_ros_msgs/BoundingBoxes.h>

#include "Eigen/Core"
#include "Eigen/Dense"
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues> 

//定义点的结构体
struct Point
{
    int x;
    int y;
};

//定义距离函数
double dist(Point p1,Point p2)
{
	int d=sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
	return d;
};

//ROS收发类
class SubscribeAndPublish
{
  //初始化p点坐标
  Point p,p1,z;
  std::queue<Point> q;
  int d;
  //int p;
  
public:
  SubscribeAndPublish()
  {
    //发布话题
    pub_ = n_.advertise<std_msgs::Int64MultiArray>("/yolo_ps/dot", 1);
 
    //接受话题
    sub_ = n_.subscribe("/darknet_ros/bounding_boxes", 1, &SubscribeAndPublish::callback, this);
  }
 
  void callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
  {
    //std_msgs::Int64 output;

    //初始化a点的横纵坐标（横d1，纵d2）,a(d1,d2)
    std_msgs::Int64 d1;
    std_msgs::Int64 d2;
    Point a;
    int m,n;
    //std_msgs::Int64MultiArray p;

    std_msgs::Int64MultiArray output;
    //int a1,b1;
  
    //输出检测框
    //std::cout<<"Bouding Boxes (header):" << msg->header <<std::endl;
    //std::cout<<"Bouding Boxes (image_header):" << msg->image_header <<std::endl;
    //std::cout<<"Bouding Boxes (Class):" << msg->bounding_boxes[0].Class <<std::endl;
    std::cout<<"Bouding Boxes (xmin):" << msg->bounding_boxes[0].xmin <<std::endl;
    std::cout<<"Bouding Boxes (xmax):" << msg->bounding_boxes[0].xmax <<std::endl;
    std::cout<<"Bouding Boxes (ymin):" << msg->bounding_boxes[0].ymin <<std::endl;
    std::cout<<"Bouding Boxes (ymax):" << msg->bounding_boxes[0].ymax <<std::endl;
    
    //计算bbx中心点a
    a.x = (msg->bounding_boxes[0].xmin + msg->bounding_boxes[0].xmax)/2;
    a.y = (msg->bounding_boxes[0].ymin + msg->bounding_boxes[0].ymax)/2;

    p = {a.x,a.y};

    //队列返回车位中心点（p）坐标和位姿
    if (q.size() < 2)
    //if (q.size() < 2 && a.x > 300)
    {
      q.push(p);
    }
    else if (q.size()==2)
    {
      //计算p1和p2之间距离d
      d = dist(q.front(),q.back());
      std::cout<<"p1-p2距离"<<d<<std::endl;

      //判断车位类型
        //if  t1<p<t2  为平行车位 深度84
          if (160<d && d<279)
          {
            //计算车位中心店坐标

            if (q.front().y < q.back().y)
            {
            //z ={(q.front().x + q.back().x)/2,(q.front().y + q.back().y)/2 + 42};
            m = (84 * (q.back().y - q.front().y))/d;
            n = (84 * (q.back().x - q.front().x))/d;

            z = {(q.back().x + q.front().x + m)/2,(q.back().y + q.front().y + n)/2};

            std::cout<<"test"<<std::endl;
            }
            else
            {
            //z ={(q.front().x + q.back().x)/2,(q.front().y + q.back().y)/2 + 42};
            m = (84 * (q.front().y - q.back().y))/d;
            n = (84 * (q.front().x - q.back().x))/d;

            z = {(q.back().x + q.front().x + m)/2,(q.back().y + q.front().y + n)/2};

            std::cout<<"test1"<<std::endl;

            }

          }


        //if  t3<p<t4  为垂直车位 深度196
          else if (86<d && d<139)
          {

            //计算车位中心店坐标
            if (q.front().y < q.back().y)
            {
            //z ={(q.front().x + q.back().x)/2,(q.front().y + q.back().y)/2 + 42};
            m = (196 * (q.back().y - q.front().y))/d;
            n = (196 * (q.back().x - q.front().x))/d;

            z = {(q.back().x + q.front().x + m)/2,(q.back().y + q.front().y + n)/2};

            std::cout<<"test2"<<std::endl;
            }
            else
            {
            //z ={(q.front().x + q.back().x)/2,(q.front().y + q.back().y)/2 + 42};
            m = (196 * (q.front().y - q.back().y))/d;
            n = (196 * (q.front().x - q.back().x))/d;

            z = {(q.back().x + q.front().x + m)/2,(q.back().y + q.front().y + n)/2};

            std::cout<<"test3"<<std::endl;

            }
            // z ={(q.front().x + q.back().x)/2,(q.front().y + q.back().y)/2 + 98};
            //std::cout<<"test2"<<std::endl;
          }


        //无效车位
   
      std::cout<<"test4"<<std::endl;
      //std::cout<<"q1 is :"<<q.front().data<<std::endl;
      //std::cout<<"q2 is :"<<q.back().data<<std::endl;

      q.push(p);

    }
    else
    {
      q.pop();
    }

    //发布车位中心点坐标和位姿

    //std::cout<<output;
    std::cout<<"中心点坐标"<<z.x<<","<<z.y<<std::endl;
    //pub_.publish(output);
 
  }
 
private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;
 
};
 

int main(int argc, char **argv)
{

  ros::Time::init();
  ros::init(argc, argv, "subscribe_and_publish");
  ros::Rate loop_rate(10);

  SubscribeAndPublish SAPObject;
  int count = 0;
  while (ros::ok())
  {
      //std::cout<<"开始循环"<<std::endl;
      ros::spinOnce();
      loop_rate.sleep();
  }
  return 0;
}
