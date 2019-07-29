cmake_minimum_required(VERSION 2.8.3)
project(yolo_ps)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  darknet_ros_msgs
  image_transport
  message_generation
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

find_package(cmake_modules REQUIRED)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
add_definitions(${EIGEN_DEFINITIONS})

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(subscribe_and_publish src/Sub_Pub.cpp)
add_dependencies(subscribe_and_publish ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
add_dependencies(subscribe_and_publish ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(subscribe_and_publish ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
