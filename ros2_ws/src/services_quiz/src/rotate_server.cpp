#include "rclcpp/rclcpp.hpp"
#include "services_quiz_srv/srv/spin.hpp"
#include "geometry_msgs/msg/twist.hpp"

using std::placeholders::_1;
using std::placeholders::_2;
using namespace std::chrono_literals;

class RotateServer : public rclcpp::Node {
public:
    RotateServer() : Node("rotate_server_node") {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
        service_ = this->create_service<services_quiz_srv::srv::Spin>(
            "/rotate", std::bind(&RotateServer::handle_service, this, _1, _2));
        RCLCPP_INFO(this->get_logger(), "Service server ready");
    }

private:
    void handle_service(
        const std::shared_ptr<services_quiz_srv::srv::Spin::Request> request,
        std::shared_ptr<services_quiz_srv::srv::Spin::Response> response)
    {
        geometry_msgs::msg::Twist msg;
        msg.linear.x = 0.0;
        msg.angular.z = (request->direction == "right" ? -1 : 1) * request->angular_velocity;

        rclcpp::Rate rate(10);
        int loops = request->time * 10;
        for (int i = 0; i < loops; ++i) {
            publisher_->publish(msg);
            rate.sleep();
        }

        // Stop the robot
        msg.angular.z = 0.0;
        publisher_->publish(msg);

        response->success = true;
        RCLCPP_INFO(this->get_logger(), "Rotation completed");
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Service<services_quiz_srv::srv::Spin>::SharedPtr service_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RotateServer>());
    rclcpp::shutdown();
    return 0;
}
