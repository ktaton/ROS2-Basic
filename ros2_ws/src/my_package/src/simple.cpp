#include "rclcpp/rclcpp.hpp"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("ObiWan");
  // We create a Rate Object of 2Hz
  rclcpp::WallRate loop_rate(2);

  // Endless loop until ctrl+c
  while (rclcpp::ok()) {
    RCLCPP_INFO(node->get_logger(),
                "Help me Obi-Wan kenobi, you're my only hope");
    rclcpp::spin_some(node);
    // We sleep the needed time to maintain the Rate fixed above
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  return 0;
}
// This program creates an endless loop that repeats itself 2 times per second
// (2Hz) until somebody presses ctrl+C in the shell
