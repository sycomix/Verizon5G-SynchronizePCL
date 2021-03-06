//////////////////////////////////////////////////////////////
//
// Programmer: Victoria Albanese
// Filename: concatenate.cpp
//
// Purpose: Tutorial code taken from the below source
// http://pointclouds.org/documentation/tutorials/concatenate_clouds.php
//
//////////////////////////////////////////////////////////////

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

int main(int argc, char** argv)
{
    // Verify that the program was called with the correct arguments
    if (argc != 2)
    {
        std::cerr << "please specify command line arg '-f' or '-p'" << std::endl;
        exit(0);
    }

    // Define 3 input clouds and 2 output clouds
    pcl::PointCloud<pcl::PointXYZ> cloud_a, cloud_b, cloud_c;
    pcl::PointCloud<pcl::Normal> n_cloud_b;
    pcl::PointCloud<pcl::PointNormal> p_n_cloud_c;

    // Fill in the cloud height and width data
    cloud_a.width  = 5;
    cloud_a.height = cloud_b.height = n_cloud_b.height = 1;
    cloud_a.points.resize (cloud_a.width * cloud_a.height);
    if (strcmp(argv[1], "-p") == 0)
    {
        cloud_b.width  = 3;
    	cloud_b.points.resize (cloud_b.width * cloud_b.height);
    }
    else{
    	n_cloud_b.width = 5;
    	n_cloud_b.points.resize (n_cloud_b.width * n_cloud_b.height);
    }

    // Fill clouds a, b, and n_b with random points
    for (size_t i = 0; i < cloud_a.points.size (); ++i)
    {
    	cloud_a.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
    	cloud_a.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
    	cloud_a.points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
    }
    if (strcmp(argv[1], "-p") == 0)
    {
    	for (size_t i = 0; i < cloud_b.points.size (); ++i)
        {
      	    cloud_b.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
      	    cloud_b.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
      	    cloud_b.points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
    	}
    }
    else
    {
        for (size_t i = 0; i < n_cloud_b.points.size (); ++i)
        {
            n_cloud_b.points[i].normal[0] = 1024 * rand () / (RAND_MAX + 1.0f);
      	    n_cloud_b.points[i].normal[1] = 1024 * rand () / (RAND_MAX + 1.0f);
      	    n_cloud_b.points[i].normal[2] = 1024 * rand () / (RAND_MAX + 1.0f);
    	}
    }

    // Print the clouds to the screen
    std::cerr << "Cloud A: " << std::endl;
    for (size_t i = 0; i < cloud_a.points.size (); ++i)
    {
    	std::cerr << "    " << cloud_a.points[i].x;
	std::cerr << " "    << cloud_a.points[i].y;
	std::cerr << " "    << cloud_a.points[i].z << std::endl;
    }
    std::cerr << "Cloud B: " << std::endl;
    if (strcmp(argv[1], "-p") == 0)
    {
        for (size_t i = 0; i < cloud_b.points.size (); ++i)
	{
            std::cerr << "    " << cloud_b.points[i].x;
	    std::cerr << " "    << cloud_b.points[i].y;
	    std::cerr << " "    << cloud_b.points[i].z << std::endl;
	}
    }
    else
    {
    	for (size_t i = 0; i < n_cloud_b.points.size (); ++i)
	{
	    std::cerr << "    " << n_cloud_b.points[i].normal[0]; 
	    std::cerr << " "    << n_cloud_b.points[i].normal[1];
	    std::cerr << " "    << n_cloud_b.points[i].normal[2] << std::endl;
	}
    }

    // Copy the point cloud data
    if (strcmp(argv[1], "-p") == 0)
    {
    	cloud_c  = cloud_a;
    	cloud_c += cloud_b;
        std::cerr << "Cloud C: " << std::endl;
    	for (size_t i = 0; i < cloud_c.points.size (); ++i)
	{
      	    std::cerr << "    " << cloud_c.points[i].x;
	    std::cerr << " "    << cloud_c.points[i].y;
	    std::cerr << " "    << cloud_c.points[i].z << " " << std::endl;
	}
    }
    else
    {
    	pcl::concatenateFields (cloud_a, n_cloud_b, p_n_cloud_c);
    	std::cerr << "Cloud C: " << std::endl;
    	for (size_t i = 0; i < p_n_cloud_c.points.size (); ++i)
	{
 	    std::cerr << "    " << p_n_cloud_c.points[i].x; 
	    std::cerr << " "    << p_n_cloud_c.points[i].y;
	    std::cerr << " "    << p_n_cloud_c.points[i].z;
	    std::cerr << " "    << p_n_cloud_c.points[i].normal[0];
	    std::cerr << " "    << p_n_cloud_c.points[i].normal[1]; 
	    std::cerr << " "    << p_n_cloud_c.points[i].normal[2] << std::endl;
	}
    }

    return (0);
}

//////////////////////////////////////////////////////////////

