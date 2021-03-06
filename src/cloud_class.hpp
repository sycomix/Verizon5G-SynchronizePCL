////////////////////////////////////////////////////////////////
//
// Programmer: Victoria Albanese
// Filename: cloud_class.hpp
//
// Purpose: Declares a class which handles operations on the 
// pointclouds created by the Intel RealSense D435i sensors
//
////////////////////////////////////////////////////////////////

#ifndef CLOUD_CLASS_HPP
#define CLOUD_CLASS_HPP

#include <boost/filesystem.hpp>
#include <cstring>
#include <ctime> 
#include <pcl/features/normal_3d.h>
#include <pcl/io/obj_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/surface/gp3.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/transforms.h>
#include <ros/package.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <tf/transform_listener.h>

using namespace pcl;
using namespace std;
using namespace tf;

class Cloud 
{
    private: 

        // members
        PolygonMesh master_mesh;
	PointCloud<PointXYZ> master_cloud;
	PointCloud<PointXYZ> cloud_front;
	PointCloud<PointXYZ> cloud_back;
	PointCloud<PointXYZ> cloud_left;
	PointCloud<PointXYZ> cloud_right;
        bool front_initialized;
        bool back_initialized;
        bool left_initialized;
        bool right_initialized;
        ros::Publisher  cloud_pub;
        ros::Subscriber cloud_front_sub;
        ros::Subscriber cloud_back_sub;
        ros::Subscriber cloud_left_sub;
        ros::Subscriber cloud_right_sub;
        TransformListener tf_listener;
        int counter;
        string timestamp; 

        // functions
    	void cloud_front_callback(sensor_msgs::PointCloud2 msg);
        void cloud_back_callback(const sensor_msgs::PointCloud2 msg);
        void cloud_left_callback(const sensor_msgs::PointCloud2 msg);
        void cloud_right_callback(const sensor_msgs::PointCloud2 msg);
	void concatenate_clouds();
        void triangulate_clouds();
	bool initialized() { return front_initialized && back_initialized && left_initialized && right_initialized; }
        string get_timestamp();

    public:

        // functions
        Cloud();
        Cloud(ros::NodeHandle handle);
	void publish_master_cloud();	
        void output_file(string model_name = "model");
};

#endif // CLOUD_CLASS_HPP

////////////////////////////////////////////////////////////////
