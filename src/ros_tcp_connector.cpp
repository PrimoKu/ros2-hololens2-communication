#include "ros2_hololens2_communication/ros_tcp_connector.hpp"

namespace Ros2Unity {
    
    TcpConnection::TcpConnection(boost::asio::io_context& io_context) : socket_(io_context), pub_("pub") {}

    TcpConnection::pointer TcpConnection::create(boost::asio::io_context& io_context) {
        return TcpConnection::pointer(new TcpConnection(io_context));
    }

    tcp::socket& TcpConnection::socket() {
        return socket_;
    }

    void TcpConnection::handle_receive(const boost::system::error_code& ec, std::size_t bytes_transferred) {
        if (!ec)
        {
            std::cout << "Handle receive" << std::endl;
            std::string data = boost::asio::buffer_cast<const char*>(buffer_.data());
            data.erase(data.length() - (data.length() - bytes_transferred));
            buffer_.consume(bytes_transferred);
            boost::property_tree::ptree root;
            
            try {

                std::istringstream iss(data);
                boost::property_tree::read_json(iss, root);
                std::string topic_name = root.get<std::string>("topic");
                
                pos_msg.position.x = root.get<double>("position.x");
                pos_msg.position.y = root.get<double>("position.y");
                pos_msg.position.z = root.get<double>("position.z");
                pos_msg.orientation.x = root.get<double>("rotation.x");
                pos_msg.orientation.y = root.get<double>("rotation.y");
                pos_msg.orientation.z = root.get<double>("rotation.z");
                pos_msg.orientation.w = root.get<double>("rotation.w");
                pub_.publish(topic_name, pos_msg);

            } catch (const boost::property_tree::json_parser_error& e) {
                std::cerr << "Error parsing JSON data: " << e.what() << std::endl;
            }

        } else {
            std::cout << "Error: " << ec.message() << std::endl;
        }

        TcpConnection::start();
    }

    void TcpConnection::start() {
        std::cout << "Connection Start" << std::endl;
        boost::asio::async_read_until(socket_, buffer_, '\n',
            boost::bind(
                &TcpConnection::handle_receive, 
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
    }

    TcpServer::TcpServer(boost::asio::io_context& io_context, int tcp_port) : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), tcp_port)) {
        
        TcpServer::start_accept();
    }
    
    void TcpServer::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error) {
        if (!error)
        {
            new_connection->start();
        }

        TcpServer::start_accept();
    }

    void TcpServer::start_accept() {

        TcpConnection::pointer new_connection = TcpConnection::create(io_context_);

        acceptor_.async_accept(new_connection->socket(), 
            boost::bind(
                &TcpServer::handle_accept, 
                this, 
                new_connection, 
                boost::asio::placeholders::error
            )
        );
        
    }
    
}