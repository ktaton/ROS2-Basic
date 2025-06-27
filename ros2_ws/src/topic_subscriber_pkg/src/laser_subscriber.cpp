#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <vector>
#include <algorithm>
#include <cmath>

class LaserSubscriber : public rclcpp::Node {
public:
  LaserSubscriber() : Node("laser_subscriber_node") {
    vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    scan_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
        "/scan", 10, std::bind(&LaserSubscriber::scan_callback, this, std::placeholders::_1));
  }

private:
  void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
    // Extract minimum distances in sectors
    float front_min = get_sector_min(msg, -10, 10);      // Front
    float left_min  = get_sector_min(msg, 60, 100);      // Left
    float right_min = get_sector_min(msg, -100, -60);    // Right

    auto vel_msg = geometry_msgs::msg::Twist();

    // Logic to avoid obstacle
    if (front_min > 1.0 && left_min > 1.0 && right_min > 1.0) {
      // Clear path
      vel_msg.linear.x = 0.3;
      vel_msg.angular.z = 0.0;
    } else if (front_min < 1.0) {
      // Obstacle ahead
      if (right_min > left_min) {
        vel_msg.linear.x = 0.0;
        vel_msg.angular.z = -0.5;  // Turn right
      } else {
        vel_msg.linear.x = 0.0;
        vel_msg.angular.z = 0.5;   // Turn left
      }
    } else if (right_min < 1.0) {
      // Obstacle on right → turn left
      vel_msg.linear.x = 0.0;
      vel_msg.angular.z = 0.5;
    } else if (left_min < 1.0) {
      // Obstacle on left → turn right
      vel_msg.linear.x = 0.0;
      vel_msg.angular.z = -0.5;
    } else {
      // Default forward
      vel_msg.linear.x = 0.2;
      vel_msg.angular.z = 0.0;
    }

    vel_pub_->publish(vel_msg);
  }

  float get_sector_min(const sensor_msgs::msg::LaserScan::SharedPtr msg, int angle_start_deg, int angle_end_deg) {
    int total_rays = msg->ranges.size();
    float angle_min_deg = msg->angle_min * 180.0 / M_PI;
    float angle_inc_deg = msg->angle_increment * 180.0 / M_PI;

    int start_idx = std::max(0, static_cast<int>((angle_start_deg - angle_min_deg) / angle_inc_deg));
    int end_idx = std::min(total_rays - 1, static_cast<int>((angle_end_deg - angle_min_deg) / angle_inc_deg));

    float min_dist = 10.0;
    for (int i = start_idx; i <= end_idx; ++i) {
      if (std::isfinite(msg->ranges[i])) {
        min_dist = std::min(min_dist, msg->ranges[i]);
      }
    }
    return min_dist;
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LaserSubscriber>());
  rclcpp::shutdown();
  return 0;
}
