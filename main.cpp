#include <iostream>

#include "dataProcessor.hpp"
#include "lineProcessor.hpp"
#include "saposClient.hpp"
#include "udpClient.hpp"

int main() {
    int choice = 0;

    std::cout << "Choose an option:\n"
              << "1. File post-processing\n"
              << "2. UDP message processing\n"
              << "3. Exit programm.\n";

    std::cin >> choice;

    switch (choice) {
        case 1: {
            DataProcessor dataProcessor(
                std::make_shared<LineProcessor>(), "./input/inputReceiver.obs",
                "./input/inputBaseStation.obs", "./result/processed.pos");

            dataProcessor.processFileData();

            break;
        }
        case 2: {
            DataProcessor dataProcessor(std::make_shared<LineProcessor>(),
                                        std::make_shared<SaposClient>(),
                                        std::make_shared<UdpClient>());

            dataProcessor.processUdpConnectionData();

            break;
        }
        case 3:
            std::cout << "Goodbye!";

            break;
        default:
            std::cout << "Bad choise, try again!\n";
    }

    return 0;
}