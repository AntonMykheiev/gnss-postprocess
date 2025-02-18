#ifndef DATA_PROCESSOR_HPP
#define DATA_PROCESSOR_HPP

#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>

#include "lineProcessor.hpp"
#include "saposClient.hpp"
#include "udpClient.hpp"
#pragma once

class DataProcessor {
   private:
    std::ifstream receiverFile;
    std::ifstream baseStationFile;
    std::ofstream processedFile;
    std::string receiverLine;
    std::string baseStationLine;
    std::shared_ptr<LineProcessor> lineProcessor;
    std::shared_ptr<SaposClient> saposClient;
    std::shared_ptr<UdpClient> udpClient;

   public:
    explicit DataProcessor(std::shared_ptr<LineProcessor> lineProcessor,
                           const std::string_view receiverPath,
                           const std::string_view baseStationPath,
                           const std::string_view processedPath);

    explicit DataProcessor(std::shared_ptr<LineProcessor> lineProcessor,
                           std::shared_ptr<SaposClient> saposClient,
                           std::shared_ptr<UdpClient> udpClient);

    void processFileData();
    void processUdpConnectionData();
};

#endif