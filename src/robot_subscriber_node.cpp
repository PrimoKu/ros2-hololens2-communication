#include <ros2_hololens2_communication/robot_subscriber.hpp>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Ros2Unity::RobotSubscriber>("pose_sub");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}