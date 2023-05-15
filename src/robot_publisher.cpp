#include <ros2_hololens2_communication/robot_publisher.hpp>

namespace Ros2Unity {

    RobotPublisher::RobotPublisher(const std::string& name) : Node(name) {
        marker_pub = this->create_publisher<geometry_msgs::msg::Pose>("marker_pose", 10);
        pick_pub = this->create_publisher<geometry_msgs::msg::Pose>("pick_pose", 10);
        place_pub = this->create_publisher<geometry_msgs::msg::Pose>("place_pose", 10);
    }

    void RobotPublisher::publish(std::string topic_name, geometry_msgs::msg::Pose pose) {

        if(topic_name == "marker_pose") {
            marker_pub->publish(pose);    
        } else if(topic_name == "pick_pose") {
            pick_pub->publish(pose);
        } else if(topic_name == "place_pose") {
            place_pub->publish(pose);
        }
    }
}