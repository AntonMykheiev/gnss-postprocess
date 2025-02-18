#ifndef SAPOS_CLIENT_HPP
#define SAPOS_CLIENT_HPP

#include <string>
#include <string_view>

class SaposClient {
   private:
    std::string saposCorrectionData = "2025 01 19 13 31 37 0.01 -0.12";

   public:
    std::string_view receiveSaposCorrectionData();
};

#endif