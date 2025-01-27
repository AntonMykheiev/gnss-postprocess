#include <asio.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "clients/saposClient.cpp"
#include "clients/udpClient.cpp"
#include "lineProcessor.cpp"

using namespace std;
using asio::ip::udp;

int processFileData() {
    ifstream receiverFile("./input/inputReceiver.obs");
    ifstream baseStationFile("./input/inputBaseStation.obs");
    ofstream processedFile("./result/processed.pos");

    if (!receiverFile.is_open()) {
        throw runtime_error("Failed to open inputReceiver.obs");
    }
    if (!baseStationFile.is_open()) {
        throw runtime_error("Failed to open inputBaseStation.obs");
    }
    if (!processedFile.is_open()) {
        throw runtime_error("Failed to open processed.pos");
    }

    string reseiverLine;
    string baseStationLine;

    // Mocked base station true position
    string baseStationTruePosition = "2025 01 19 13 31 37 0.03 0.11";

    while (getline(receiverFile, reseiverLine)) {
        if (getline(baseStationFile, baseStationLine)) {
            processedFile << processFileLine(reseiverLine, baseStationLine,
                                             baseStationTruePosition)
                          << "\n";
        } else {
            processedFile << reseiverLine << "\n";
        }
    }

    receiverFile.close();
    processedFile.close();

    return 0;
}

int processUdpConnectionData() {
    bool stillRunning;
    string receivedMessage;
    string correctionData = receiveSaposCorrectionData();

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

            string message =
                processMessageLine(receivedMessage, correctionData);

            std::cout << "PROCESSED LINE: " << message << std::endl;

            sendMessage(message);

            stillRunning = true;
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;

            stillRunning = false;
        }
    } while (stillRunning);

    return 0;
}

int processData(int& dataSourceIndex) {
    switch (dataSourceIndex) {
        case 0:
            return processFileData();
        case 1:
            return processUdpConnectionData();
        default:
            throw runtime_error("Wrong data source index!");
    }
}