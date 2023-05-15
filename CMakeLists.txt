cmake_minimum_required(VERSION 3.8)
project(ros2_hololens2_communication)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

include_directories(include)
add_library(ros_tcp_connector SHARED src/robot_publisher.cpp src/robot_subscriber.cpp src/ros_tcp_connector.cpp)
ament_target_dependencies(ros_tcp_connector rclcpp std_msgs geometry_msgs)

add_executable(pub src/robot_publisher_node.cpp)
target_link_libraries(pub ros_tcp_connector)
ament_target_dependencies(pub rclcpp std_msgs geometry_msgs)

add_executable(sub src/robot_subscriber_node.cpp)
target_link_libraries(sub ros_tcp_connector)
ament_target_dependencies(sub rclcpp std_msgs geometry_msgs)

add_executable(tcp src/ros_tcp_connector_node.cpp)
target_link_libraries(tcp ros_tcp_connector)
ament_target_dependencies(tcp rclcpp std_msgs geometry_msgs)


install(DIRECTORY include/ DESTINATION include)
install(TARGETS ros_tcp_connector LIBRARY DESTINATION lib)
install(TARGETS pub sub tcp DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
