#!/bin/bash

roslaunch ur_modern_driver ur5_bringup.launch limited:=true robot_ip:=192.168.0.102 [reverse_port:=REVERSE_PORT] &
sleep 4

roslaunch ur5_moveit_config ur5_moveit_planning_execution.launch limited:=true &
sleep 4

roslaunch ur5_moveit_config moveit_rviz.launch config:=true &
sleep 4

rosrun obstacle_plan shape_pose_init.py &
sleep 5

roslaunch realsense2_camera rs_rgbd.launch &
sleep 4

exit 0

