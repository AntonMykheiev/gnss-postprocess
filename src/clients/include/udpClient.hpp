#include <string_view>

#pragma once
class UdpClient {
   public:
    void sendMessage(std::string_view message);
};