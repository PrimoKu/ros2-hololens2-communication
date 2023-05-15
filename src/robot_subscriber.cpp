#include <ros2_hololens2_communication/robot_subscriber.hpp>

using std::placeholders::_1;

namespace Ros2Unity {

    RobotSubscriber::RobotSubscriber(const std::string& name) : Node(name) {
        marker_sub = this->create_subscription<geometry_msgs::msg::Pose>("marker_pose", 10, std::bind(&RobotSubscriber::callback, this, _1));
        pick_sub = this->create_subscription<geometry_msgs::msg::Pose>("pick_pose", 10, std::bind(&RobotSubscriber::callback, this, _1));
        place_sub = this->create_subscription<geometry_msgs::msg::Pose>("place_pose", 10, std::bind(&RobotSubscriber::callback, this, _1));
    }

    void RobotSubscriber::callback(const geometry_msgs::msg::Pose& pose) {
        std::cout << "Subscribe callback" << std::endl;
        std::cout << "Position: (" << pose.position.x << ", " << pose.position.y << ", " << pose.position.z << ")" << std::endl;
        std::cout << "Orientation: (" << pose.orientation.x << ", " << pose.orientation.y << ", " << pose.orientation.z << ", " << pose.orientation.w << ")" << std::endl;
    }
}

