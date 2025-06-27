#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class VelocityPublisher : public rclcpp::Node {
public:
  VelocityPublisher() : Node("velocity_forwarder_node") {
    cmd_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    custom_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
        "/custom_vel", 10,
        std::bind(&VelocityPublisher::vel_callback, this, std::placeholders::_1));
  }

private:
  void vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg) {
    cmd_pub_->publish(*msg);
    RCLCPP_INFO(this->get_logger(), "Forwarding velocity: linear=%.2f angular=%.2f",
                msg->linear.x, msg->angular.z);
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr custom_sub_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VelocityPublisher>());
  rclcpp::shutdown();
  return 0;
}
