#include <asio.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

#include "lineProcessor.hpp"
#include "saposClient.hpp"
#include "udpClient.hpp"

using asio::ip::udp;

void processFileData() {
    std::ifstream receiverFile("./input/inputReceiver.obs");
    std::ifstream baseStationFile("./input/inputBaseStation.obs");
    std::ofstream processedFile("./result/processed.pos");

    if (!receiverFile.is_open()) {
        throw std::runtime_error("Failed to open inputReceiver.obs");
    }
    if (!baseStationFile.is_open()) {
        throw std::runtime_error("Failed to open inputBaseStation.obs");
    }
    if (!processedFile.is_open()) {
        throw std::runtime_error("Failed to open processed.pos");
    }

    std::string receiverLine;
    std::string baseStationLine;

    // Mocked base station true position
    std::string_view baseStationTruePosition = "2025 01 19 13 31 37 0.03 0.11";

    while (getline(receiverFile, receiverLine)) {
        if (getline(baseStationFile, baseStationLine)) {
            processedFile << processFileLine(receiverLine, baseStationLine,
                                             baseStationTruePosition)
                          << "\n";
        } else {
            processedFile << receiverLine << "\n";
        }
    }
}

void processUdpConnectionData() {
    bool stillRunning = false;
    std::string receivedMessage;
    std::string_view correctionData = receiveSaposCorrectionData();

    do {
        try {
            asio::io_context io_context;

            udp::socket socket(io_context, udp::v4());
            socket.bind(udp::endpoint(udp::v4(), 12345));

            std::cout << "Waiting for a message..." << std::endl;

            char data[1024];

            udp::endpoint sender_endpoint;

            size_t length =
                socket.receive_from(asio::buffer(data), sender_endpoint);

            std::cout << "Received message: " << std::string(data, length)
                      << std::endl;
            std::cout << "Sender address: "
                      << sender_endpoint.address().to_string() << std::endl;
            std::cout << "Sender port: " << sender_endpoint.port() << std::endl;

            receivedMessage = std::string(data, length);

            std::string message =
                processMessageLine(receivedMessage, correctionData);

            std::cout << "PROCESSED LINE: " << message << std::endl;

            sendMessage(message);

            stillRunning = true;
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;

            stillRunning = false;
        }
    } while (stillRunning);
}