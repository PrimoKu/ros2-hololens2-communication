#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <geometry_msgs/msg/pose.hpp>

namespace Ros2Unity {

    class RobotPublisher : public rclcpp::Node {

    private:
        rclcpp::Publisher<geometry_msgs::msg::Pose>::SharedPtr marker_pub, pick_pub, place_pub;

    public:
        RobotPublisher(const std::string& name);
        void publish(std::string topic_name, geometry_msgs::msg::Pose pose);
    };
}