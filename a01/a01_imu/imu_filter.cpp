#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include "eigen3/Eigen/Dense"
#include "opencv2/core/eigen.hpp"

class kalman_filter {
 private:
  Eigen::MatrixXd A;
  Eigen::MatrixXd P;
  Eigen::MatrixXd Q;
  Eigen::MatrixXd R;
  Eigen::MatrixXd H;
  bool isinitized = false;

 public:
  kalman_filter();
  Eigen::MatrixXd predictAndupdate(Eigen::MatrixXd x, Eigen::MatrixXd z);
  ~kalman_filter();
};

kalman_filter::kalman_filter() {
  A = Eigen::MatrixXd(3, 3);
  A << 1, 0, 0, 0, 1, 0, 0, 0, 1;

  H = Eigen::MatrixXd(3, 3);
  H << 1, 0, 0, 0, 1, 0, 0, 0, 1;

  Q = Eigen::MatrixXd(3, 3);
  Q << 0.03, 0, 0, 0, 0.03, 0, 0, 0, 0.03;

  R = Eigen::MatrixXd(3, 3);
  R << 3.65, 0, 0, 0, 3.65, 0, 0, 0, 3.65;
}

class SubscriberAndPublisher {
 private:
  ros::NodeHandle n;
  ros::Subscriber imu_info_sub;
  ros::Publisher IMU_kalman_pub;
  bool first = true;

 public:
  SubscriberAndPublisher() {
    imu_info_sub = n.subscribe("/imu/data_raw", 10,
                               &SubscriberAndPublisher::imuInfoCallback, this);
    IMU_kalman_pub = n.advertise<sensor_msgs::Imu>("/imu_kalman", 10);
  }
  void imuInfoCallback(const sensor_msgs::Imu::ConstPtr& msg) {
    if (first) {
      double a_x_m = msg->linear_acceleration.x;
      double a_y_m = msg->linear_acceleration.y;
      double a_z_m = msg->linear_acceleration.z;
      Eigen::MatrixXd X;
      X << a_x_m, a_y_m, a_z_m;
      sensor_msgs::Imu M;
      M.linear_acceleration.x = a_x_m;
      M.linear_acceleration.y = a_y_m;
      M.linear_acceleration.z = a_z_m;
      M.header = msg->header;
      IMU_kalman_pub.publish(M);
      first = false;
      std::cout << "first farm" << std::endl;
    } else {
      double a_x_m = msg->linear_acceleration.x;
      double a_y_m = msg->linear_acceleration.y;
      double a_z_m = msg->linear_acceleration.z;
      Eigen::MatrixXd X;
      Eigen::MatrixXd z;
      z = Eigen::MatrixXd(3, 1);
      z << a_x_m, a_y_m, a_z_m;
      kalman_filter kf;
      Eigen::MatrixXd x_new = kf.predictAndupdate(X, z);
      X = z;
      double a_x, a_y, a_z;
      a_x = x_new(0, 0);
      a_y = x_new(1, 0);
      a_z = x_new(2, 0);
      sensor_msgs::Imu M;
      M.linear_acceleration.x = a_x_m;
      M.linear_acceleration.y = a_y_m;
      M.linear_acceleration.z = a_z_m;
      M.header = msg->header;
      // std::ofstream output;
      std::cout << "linear_acceleration.x = " << a_x
           << "linear_acceleration.y = " << a_y
           << "linear_acceleration.z = " << a_z << std::endl;
      IMU_kalman_pub.publish(M);
    }
  }
};

kalman_filter::~kalman_filter() {}

Eigen::MatrixXd kalman_filter::predictAndupdate(Eigen::MatrixXd x,
                                                Eigen::MatrixXd z) {
  if (!isinitized) {
    P = Eigen::MatrixXd(3, 3);
    P << 1, 0, 0, 0, 1, 0, 0, 0, 1;
    isinitized = true;
  }
  x = A * x;
  P = A * P * (A.transpose()) + Q;
  Eigen::MatrixXd K =
      P * (H.transpose() * (H * P * (H.transpose()) + R).inverse());
  x = x + K * (z - H * x);
  int x_size = x.size();
  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(x_size, x_size);
  P = (I - K * H) * P;
  return x;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "subscriber_and_publisher");
  SubscriberAndPublisher SPAObject;
  ros::spin();
  return 0;
}