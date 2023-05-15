# ROS2-HoloLens2 Communication
This is a ROS2 Galactic package developed for users who want to establish a TCP connection between external software interfaces and ROS2. It's written in C++ on the ROS2 side and is compatible with any programming language on the other side. The package provides functionality for receiving custom JSON strings from the other end of the connection and then can be deserialized by the user. In summary, the package offers a means for users to interface with ROS2 through TCP by receiving and processing custom JSON data.

## Compatibility
- ROS2 Galactic

## Structure

    ├── include                                      
    │   ├── ros2_hololens2_communication        # Folder for all header files
    │   │   ├── robot_publisher.hpp             # Simple ROS2 publisher
    │   │   ├── robot_subscriber.hpp            # Simple ROS2 subscriber
    │   │   └── ros_tcp_connector.hpp           # TCP Server class
    ├── launch
    │   └── ros2_hololens2_communication.xml    # ROS2 launch file for nodes
    ├── src
    │   ├── robot_pubisher.cpp                  # Publisher functions
    │   ├── robot_subscriber.cpp                # Subscriber functions
    │   ├── ros_tcp_connector.cpp               # TCP Server and connection
    │   └── ...
    └── ...

## Build
1. [Install ROS2 Galactic](https://docs.ros.org/en/galactic/Installation/Ubuntu-Install-Debians.html). This package currently supports only ROS2 Galactic.
2. Make sure that colcon and its extensions are installed:
   ```
   sudo apt install python3-colcon-common-extensions
   ```
3. Create a new ROS2 workspace:
   ```
   export COLCON_WS=~/workspace/ros_ur_driver
   mkdir -p $COLCON_WS/src
   ```
4. Pull relevant packages, install dependencies, compile, and source the workspace:
   ```
   cd $COLCON_WS
   git clone https://github.com/PrimoKu/ros2-hololens2-communication.git
   rosdep update --include-eol-distros
   rosdep install --ignore-src --from-paths src -y
   colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
   source install/setup.bash
   ```
5. Run the TCP server using launch file:
   ```
   ros2 launch ros2_hololen2_communication ros2_hololens2_communication.xml
   ``` 