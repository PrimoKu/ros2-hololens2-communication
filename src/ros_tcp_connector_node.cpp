#include <ros2_hololens2_communication/ros_tcp_connector.hpp>


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    boost::asio::io_context io_context;

    try {
        Ros2Unity::TcpServer TcpServer(io_context, 3333);
        io_context.run();
    } catch (std::exception& e) {
        io_context.stop();
        throw;
    }
    return 0;
}