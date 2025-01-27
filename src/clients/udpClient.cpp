#include <asio.hpp>
#include <iostream>

using asio::ip::udp;

void sendMessage(std::string& message) {
    try {
        asio::io_context io_context;

        udp::endpoint receiver_endpoint(
            asio::ip::address::from_string("127.255.255.1"), 12345);

        udp::socket socket(io_context, udp::v4());

        socket.send_to(asio::buffer(message), receiver_endpoint);

        std::cout << "Message sent: " << message << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}