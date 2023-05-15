#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <geometry_msgs/msg/pose.hpp>

namespace Ros2Unity {

    class RobotSubscriber : public rclcpp::Node {

    private:
        rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr marker_sub, pick_sub, place_sub;

    public:
        RobotSubscriber(const std::string& name);
        void callback(const geometry_msgs::msg::Pose& pose);
    };
}