#include "dataProcessor.hpp"

#include <asio.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>

#include "lineProcessor.hpp"

using asio::ip::udp;

DataProcessor::DataProcessor(std::shared_ptr<LineProcessor> lineProcessor,
                             const std::string_view receiverPath,
                             const std::string_view baseStationPath,
                             const std::string_view processedPath)
    : lineProcessor(std::move(lineProcessor)),
      receiverFile(receiverPath),
      baseStationFile(baseStationPath),
      processedFile(processedPath) {
    if (!receiverFile.is_open()) {
        throw std::runtime_error("Failed to open receiver file");
    }

    if (!baseStationFile.is_open()) {
        throw std::runtime_error("Failed to open base station file");
    }

    if (!processedFile.is_open()) {
        throw std::runtime_error("Failed to open processed file");
    }
}

DataProcessor::DataProcessor(std::shared_ptr<LineProcessor> lineProcessor,
                             std::shared_ptr<SaposClient> saposClient,
                             std::shared_ptr<UdpClient> udpClient)
    : lineProcessor(std::move(lineProcessor)),
      saposClient(std::move(saposClient)),
      udpClient(std::move(udpClient)) {}

void DataProcessor::processFileData() {
    // Mocked base station true position
    std::string_view baseStationTruePosition = "2025 01 19 13 31 37 0.03 0.11";

    while (getline(receiverFile, receiverLine)) {
        if (getline(baseStationFile, baseStationLine)) {
            processedFile << lineProcessor->processFileLine(
                                 receiverLine, baseStationLine,
                                 baseStationTruePosition)
                          << "\n";
        } else {
            processedFile << receiverLine << "\n";
        }
    }
}

void DataProcessor::processUdpConnectionData() {
    bool stillRunning = true;
    std::string receivedMessage;
    std::string_view correctionData = saposClient->receiveSaposCorrectionData();

    while (stillRunning) {
        try {
            asio::io_context ioContext;

            udp::socket socket(ioContext, udp::v4());
            socket.bind(udp::endpoint(udp::v4(), 12345));

            std::cout << "Waiting for a message..." << std::endl;

            char data[1024];

            udp::endpoint senderEndpoint;

            size_t length =
                socket.receive_from(asio::buffer(data), senderEndpoint);

            std::cout << "Received message: " << std::string(data, length)
                      << std::endl;
            std::cout << "Sender address: "
                      << senderEndpoint.address().to_string() << std::endl;
            std::cout << "Sender port: " << senderEndpoint.port() << std::endl;

            receivedMessage = std::string(data, length);

            std::string message = lineProcessor->processMessageLine(
                receivedMessage, correctionData);

            std::cout << "PROCESSED LINE: " << message << std::endl;

            udpClient->sendMessage(message);

            stillRunning = true;
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;

            stillRunning = false;
        }
    }
}