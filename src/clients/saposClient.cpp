#include "saposClient.hpp"

#include <string_view>

std::string_view SaposClient::receiveSaposCorrectionData() {
    return saposCorrectionData;
}