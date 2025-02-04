#include <asio.hpp>
#include <iostream>
#include <string_view>

using asio::ip::udp;

void sendMessage(std::string_view message) {
    try {
        asio::io_context ioContext;

        udp::endpoint receiverEndpoint(
            asio::ip::address::from_string("127.255.255.1"), 12345);

        udp::socket socket(ioContext, udp::v4());

        socket.send_to(asio::buffer(message), receiverEndpoint);

        std::cout << "Message sent: " << message << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}