#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "ros2_hololens2_communication/robot_publisher.hpp"
#include "ros2_hololens2_communication/robot_subscriber.hpp"

using namespace boost::asio;
using boost::asio::ip::tcp;

namespace Ros2Unity {

    class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
    
    private:
        tcp::socket socket_;
        boost::asio::streambuf buffer_;
        geometry_msgs::msg::Pose pos_msg;
        RobotPublisher pub_;
    public:

        typedef boost::shared_ptr<TcpConnection> pointer;

        TcpConnection(boost::asio::io_context& io_context);
        static pointer create(boost::asio::io_context& io_context);
        tcp::socket& socket();

        void start();

        void handle_receive(const boost::system::error_code& ec, std::size_t bytes_transferred);
    };

    class TcpServer {

    private:
        tcp::acceptor acceptor_;
        boost::asio::io_context& io_context_;

        char tcp_ip;
        int tcp_port;
    
    public:
        TcpServer(boost::asio::io_context& io_context, int tcp_port);
        
        void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error);

        void start_accept();
    };
}
