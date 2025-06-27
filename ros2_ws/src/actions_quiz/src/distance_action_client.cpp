#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include "actions_quiz_msg/action/distance.hpp"

using Distance = actions_quiz_msg::action::Distance;
using GoalHandleDistance = rclcpp_action::ClientGoalHandle<Distance>;

class DistanceActionClient : public rclcpp::Node {
public:
    DistanceActionClient() : Node("distance_action_client") {
        client_ = rclcpp_action::create_client<Distance>(this, "distance_as");
        send_goal();
    }

    void send_goal() {
        if (!client_->wait_for_action_server()) {
            RCLCPP_ERROR(this->get_logger(), "Action server not available");
            return;
        }

        auto goal_msg = Distance::Goal();
        goal_msg.seconds = 20;

        auto send_goal_options = rclcpp_action::Client<Distance>::SendGoalOptions();
        send_goal_options.feedback_callback =
            std::bind(&DistanceActionClient::feedback_callback, this, std::placeholders::_1, std::placeholders::_2);
        send_goal_options.result_callback =
            std::bind(&DistanceActionClient::result_callback, this, std::placeholders::_1);

        client_->async_send_goal(goal_msg, send_goal_options);
    }

private:
    rclcpp_action::Client<Distance>::SharedPtr client_;

    void feedback_callback(
        GoalHandleDistance::SharedPtr,
        const std::shared_ptr<const Distance::Feedback> feedback) {
        RCLCPP_INFO(this->get_logger(), "Current distance: %.2f", feedback->current_dist);
    }

    void result_callback(const GoalHandleDistance::WrappedResult &result) {
        RCLCPP_INFO(this->get_logger(), "Final result: %.2f", result.result->total_dist);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DistanceActionClient>());
    rclcpp::shutdown();
    return 0;
}
