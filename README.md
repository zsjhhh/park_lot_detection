# park_lot_detection
谢XF的工作 
需要的各个包，darknet由于大小关系上传不完整，需要下新的
darknet_ros https://github.com/leggedrobotics/darknet_ros


# 启动车位检测
1.source devel/setup.bash
2.roscore
3.roslaunch astra_launch astra.launch   #启动奥比中光摄像头
4.roslaunch darknet_ros yolo_ps.launch  #启动车位T字检测
5.rosrun yolo_ps subscribe_and_publish  #解算车位中心位置z。（接收T字坐标进行解算）

# 启动yolo_ps_ros
1.打开摄像头
2.ros.yaml中修改图像话题
3.roslaunch darknet_ros yolo_ps.launch 

