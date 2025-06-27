#include "rclcpp/rclcpp.hpp"
#include "services_quiz_srv/srv/spin.hpp"

using namespace std::chrono_literals;

class RotateClient : public rclcpp::Node {
public:
    RotateClient() : Node("rotate_client_node") {
        client_ = this->create_client<services_quiz_srv::srv::Spin>("/rotate");

        while (!client_->wait_for_service(1s)) {
            RCLCPP_INFO(this->get_logger(), "Waiting for service...");
        }

        auto request = std::make_shared<services_quiz_srv::srv::Spin::Request>();
        request->direction = "right";
        request->angular_velocity = 0.2;
        request->time = 10;

        auto result = client_->async_send_request(request);
        result.wait();

        if (result.get()->success)
            RCLCPP_INFO(this->get_logger(), "Rotation success");
        else
            RCLCPP_INFO(this->get_logger(), "Rotation failed");

        rclcpp::shutdown();
    }

private:
    rclcpp::Client<services_quiz_srv::srv::Spin>::SharedPtr client_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    std::make_shared<RotateClient>();
    rclcpp::spin_some(rclcpp::Node::make_shared("dummy")); // For shutdown()
    return 0;
}
