#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
using namespace std;

// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <ros/time.h>
#include <ros/duration.h>

// #include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>



ros::Publisher pub_boject;

void 
transf (const sensor_msgs::PointCloud2ConstPtr& input)
{

  // Create a container for the data.
  sensor_msgs::PointCloud2 env_pcd;

  // Do data processing here...
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
  
  // pcl_conversions::toPCL(*input, *cloud);
  pcl::fromROSMsg(*input, *cloud);

  // PointCloudT to ROS msg pointcloud2
  pcl::toROSMsg(*cloud, env_pcd);

  env_pcd.header.frame_id = "base_link";

  ros::Rate loop_rate(0.2);
  while (ros::ok())
  {
    // Publish the data.
    pub_boject.publish (env_pcd);
    ROS_INFO_STREAM("The pointcloud copy from D435i have publish success!");

    ros::spinOnce();
    loop_rate.sleep();
  }
       

  // Publish the data.
  pub_boject.publish (env_pcd);

//   ROS_INFO_STREAM("The scene pcd topic publish success!");
}

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "change_frequence");
  ros::NodeHandle nh;

  // Create a ROS subscriber for the input point cloud
//   ros::Subscriber sub = nh.subscribe ("/cloud_pcd", 15, transf);
  ros::Subscriber sub = nh.subscribe ("/camera/depth_registered/points", 2, transf);


  // Create a ROS publisher for the output point cloud
  pub_boject = nh.advertise<sensor_msgs::PointCloud2> ("/pcd_frome_d435i", 2000);
  
  
  // ros::Rate loop_rate(0.007);
  // the topic rate
  ros::spin();
  
}



