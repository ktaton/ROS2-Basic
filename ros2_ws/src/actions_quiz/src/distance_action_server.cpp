#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <std_msgs/msg/float64.hpp>
#include "actions_quiz_msg/action/distance.hpp"

using Distance = actions_quiz_msg::action::Distance;
using GoalHandleDistance = rclcpp_action::ServerGoalHandle<Distance>;

class DistanceActionServer : public rclcpp::Node {
public:
    DistanceActionServer() : Node("distance_action_server") {
        action_server_ = rclcpp_action::create_server<Distance>(
            this,
            "distance_as",
            std::bind(&DistanceActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&DistanceActionServer::handle_cancel, this, std::placeholders::_1),
            std::bind(&DistanceActionServer::handle_accepted, this, std::placeholders::_1)
        );

        odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom", 10, std::bind(&DistanceActionServer::odom_callback, this, std::placeholders::_1));

        distance_pub_ = this->create_publisher<std_msgs::msg::Float64>("/total_distance", 10);
        RCLCPP_INFO(this->get_logger(), "Action Server Ready");
    }

private:
    rclcpp_action::Server<Distance>::SharedPtr action_server_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr distance_pub_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;

    double total_distance_ = 0.0;
    double last_x_ = 0.0, last_y_ = 0.0;
    bool first_odom_ = true;

    void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
        double x = msg->pose.pose.position.x;
        double y = msg->pose.pose.position.y;

        if (first_odom_) {
            last_x_ = x;
            last_y_ = y;
            first_odom_ = false;
            return;
        }

        double dx = x - last_x_;
        double dy = y - last_y_;
        total_distance_ += sqrt(dx * dx + dy * dy);

        last_x_ = x;
        last_y_ = y;
    }

    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID &uuid,
        std::shared_ptr<const Distance::Goal> goal) {
        RCLCPP_INFO(this->get_logger(), "Goal received: %d seconds", goal->seconds);
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleDistance> goal_handle) {
        RCLCPP_INFO(this->get_logger(), "Goal cancelled");
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void handle_accepted(const std::shared_ptr<GoalHandleDistance> goal_handle) {
        std::thread{std::bind(&DistanceActionServer::execute, this, goal_handle)}.detach();
    }

    void execute(const std::shared_ptr<GoalHandleDistance> goal_handle) {
        auto goal = goal_handle->get_goal();
        auto feedback = std::make_shared<Distance::Feedback>();
        auto result = std::make_shared<Distance::Result>();

        total_distance_ = 0.0;
        first_odom_ = true;

        rclcpp::Rate rate(1.0);
        for (int i = 0; i < goal->seconds && rclcpp::ok(); ++i) {
            feedback->current_dist = total_distance_;
            goal_handle->publish_feedback(feedback);

            std_msgs::msg::Float64 msg;
            msg.data = total_distance_;
            distance_pub_->publish(msg);

            rate.sleep();
        }

        result->status = true;
        result->total_dist = total_distance_;
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Action finished");
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DistanceActionServer>());
    rclcpp::shutdown();
    return 0;
}
