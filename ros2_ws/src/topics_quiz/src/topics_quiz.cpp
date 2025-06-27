#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cmath>
#include <algorithm>

class TopicsQuizNode : public rclcpp::Node
{
public:
    TopicsQuizNode() : Node("topics_quiz_node"), avoiding_(false)
    {
        cmd_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
        scan_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 10,
            std::bind(&TopicsQuizNode::scan_callback, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "topics_quiz_node started.");
    }

private:
    void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        const auto &ranges = msg->ranges;
        int size = ranges.size();
        if (size < 10) return;

        float front = get_average_range(ranges, size / 2, 10);
        float left = get_average_range(ranges, 5 * size / 6, 10);
        float right = get_average_range(ranges, size / 6, 10);

        float critical_distance = 2.0;
        float safe_distance = 1.0;

        geometry_msgs::msg::Twist cmd;

        if (front < critical_distance)
        {
            RCLCPP_WARN(this->get_logger(), "TOO CLOSE: Obstacle at %.2f m. Stopping and turning.", front);
            cmd.linear.x = 0.0;
            cmd.angular.z = 10.0;  // Sharper turn
            avoiding_ = true;
        }
        else if (avoiding_)
        {
            if (front < safe_distance)
            {
                RCLCPP_INFO(this->get_logger(), "Avoiding obstacle at %.2f m. Continuing turn.", front);
                cmd.linear.x = 0.0;
                cmd.angular.z = 5.0;  // Continue strong turn
            }
            else
            {
                RCLCPP_INFO(this->get_logger(), "Path cleared. Moving forward.");
                cmd.linear.x = 0.4;
                cmd.angular.z = 0.0;
                avoiding_ = false;
            }
        }
        else if (right < safe_distance)
        {
            RCLCPP_INFO(this->get_logger(), "Right too close (%.2f m). Turning left.", right);
            cmd.linear.x = 0.0;
            cmd.angular.z = -5.0;
            avoiding_ = true;
        }
        else if (left < safe_distance)
        {
            RCLCPP_INFO(this->get_logger(), "Left too close (%.2f m). Turning right.", left);
            cmd.linear.x = 0.0;
            cmd.angular.z = 5.0;
            avoiding_ = true;
        }
        else
        {
            cmd.linear.x = 0.4;
            cmd.angular.z = 0.0;
            RCLCPP_INFO(this->get_logger(), "Path clear. Moving forward.");
        }

        cmd_pub_->publish(cmd);
    }

    float get_average_range(const std::vector<float> &ranges, int center, int window)
    {
        int start = std::max(0, center - window);
        int end = std::min(static_cast<int>(ranges.size()), center + window);
        float sum = 0.0;
        int count = 0;

        for (int i = start; i < end; ++i)
        {
            if (std::isfinite(ranges[i]))
            {
                sum += ranges[i];
                count++;
            }
        }

        return count > 0 ? sum / count : 30.0f;
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub_;
    bool avoiding_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TopicsQuizNode>());
    rclcpp::shutdown();
    return 0;
}


