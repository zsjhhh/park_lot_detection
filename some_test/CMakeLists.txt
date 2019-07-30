cmake_minimum_required(VERSION 2.8.3)
project(slam)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-O3" )

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

find_package( OpenCV REQUIRED ) 

## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES slam
#  CATKIN_DEPENDS ros_cpp std_msgs
#  DEPENDS system_lib
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
# include
  ${OpenCV_INCLUDE_DIRS} 
  ${catkin_INCLUDE_DIRS}
  "/usr/include/eigen3"
)

add_executable(eigen src/00_eigenMatrix.cpp)
## Specify libraries to link a library or executable target against
target_link_libraries(eigen
  ${catkin_LIBRARIES}
)

add_executable(geometry src/01_geometry.cpp)
target_link_libraries(geometry
  ${catkin_LIBRARIES}
)


add_executable(imagetransform src/02_ImageTransform.cpp)
target_link_libraries(imagetransform
  ${OpenCV_LIBS}
  ${catkin_LIBRARIES}
)

add_executable(imgtrans src/03_ImageTrans2.cpp)
target_link_libraries(imgtrans
  ${OpenCV_LIBS}
  ${catkin_LIBRARIES}
)

