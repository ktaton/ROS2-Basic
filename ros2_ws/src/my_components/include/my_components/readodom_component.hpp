#ifndef MY_COMPONENTS_READODOM_COMPONENT_HPP_
#define MY_COMPONENTS_READODOM_COMPONENT_HPP_

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"

namespace my_components {

class OdomSubscriber : public rclcpp::Node {
public:
  explicit OdomSubscriber(const rclcpp::NodeOptions & options)
  : Node("odom_subscriber", options)
  {
    subscription_ = this->create_subscription<nav_msgs::msg::Odometry>(
      "/odom", 10,
      std::bind(&OdomSubscriber::topic_callback, this, std::placeholders::_1));
  }

private:
  void topic_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "Received Odometry: Position x: %f, y: %f",
                msg->pose.pose.position.x, msg->pose.pose.position.y);
  }

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription_;
};

}  // namespace my_components

#endif  // MY_COMPONENTS_READODOM_COMPONENT_HPP_
