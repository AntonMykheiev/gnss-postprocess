#include <iostream>
#include "dataProcessor.hpp"

int main() {
    int choice = 0;

    std::cout << "Choose an option:\n"
              << "1. File post-processing\n"
              << "2. UDP message processing\n"
              << "3. Exit programm.\n";

    std::cin >> choice;

    switch (choice) {
        case 1:
            processFileData();

            break;
        case 2:
            processUdpConnectionData();

            break;
        case 3:
            std::cout << "Goodbye!";

            break;
        default:
            std::cout << "Bad choise, try again!\n";
    }

    return 0;
}