#include<iostream>
#include<thread>

#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>

#include<pcl/registration/ndt.h>
#include<pcl/filters/approximate_voxel_grid.h>

#include<pcl/visualization/pcl_visualizer.h>

using namespace std::chrono_literals;

int main(int argc, char** argv){
  pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  if(pcl::io::loadPCDFile<pcl::PointXYZ>("../resources/room_scan1.pcd", *target_cloud) == -1){
    PCL_ERROR("Could not read file 1.\n");
    return -1;
  }
  std::cout << "Loaded " << target_cloud->size() << "data points from room_scan1.pcd" << std::endl;

  pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  if(pcl::io::loadPCDFile<pcl::PointXYZ>("../resources/room_scan2.pcd", *input_cloud) == -1){
    PCL_ERROR("Could not read file 2.\n");
    return -1;
  }
  std::cout << "Loaded " << input_cloud->size() << "data points from room_scan2.pcd" << std::endl;

  pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::ApproximateVoxelGrid<pcl::PointXYZ> approximate_voxel_filter;
  approximate_voxel_filter.setLeafSize(0.2, 0.2, 0.2);
  approximate_voxel_filter.setInputCloud(input_cloud);
  approximate_voxel_filter.filter(*filtered_cloud);
  std::cout << "Filterd cloud contains " << filtered_cloud->size() << "data points from room_scan2.pcd" << std::endl;

  pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ> ndt;
  ndt.setTransformationEpsilon(0.001);
  ndt.setStepSize(0.05);
  ndt.setResolution(1.0);
  ndt.setMaximumIterations(50);
  ndt.setInputSource(filtered_cloud);
  ndt.setInputTarget(target_cloud);

  Eigen::AngleAxisf init_rotation(0.6931, Eigen::Vector3f::UnitZ());
  Eigen::Translation3f init_translation(1.79387, 0, 0);
  Eigen::Matrix4f init_guess = (init_translation * init_rotation).matrix();

  pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  ndt.align(*output_cloud, init_guess);

  std::cout << "Normal Distributions Transform has converged:" << ndt.hasConverged() << "score:" << ndt.getFitnessScore() << std::endl;

  pcl::transformPointCloud(*input_cloud, *output_cloud, ndt.getFinalTransformation());

  pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
  viewer->setBackgroundColor(0, 0, 0);

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> target_color(target_cloud, 255, 0, 0);
  viewer->addPointCloud<pcl::PointXYZ>(target_cloud, target_color, "target cloud");
  viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "target cloud");

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> output_color(output_cloud, 0, 255, 0);
  viewer->addPointCloud<pcl::PointXYZ>(output_cloud, output_color, "output cloud");
  viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "output cloud");

  viewer->addCoordinateSystem(1.0, "global");
  viewer->initCameraParameters();

  if(!viewer->wasStopped()){
    viewer->spinOnce(100000000);
    std::this_thread::sleep_for(100000000ms);
  }

  return 0;
}
