#ifndef UDP_CLIENT_HPP
#define UDP_CLIENT_HPP

#include <string_view>

class UdpClient {
   public:
    void sendMessage(std::string_view message);
};

#endif