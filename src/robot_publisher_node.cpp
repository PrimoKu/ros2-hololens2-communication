#include <ros2_hololens2_communication/robot_publisher.hpp>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Ros2Unity::RobotPublisher>("pose_pub");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}