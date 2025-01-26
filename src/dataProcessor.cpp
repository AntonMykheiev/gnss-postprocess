#include <fstream>
#include <string>

#include "lineProcessor.cpp"

using namespace std;

void processFileData() {
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

    string reseiverLogLine;
    string baseStationLogLine;

    while (getline(receiverFile, reseiverLogLine)) {
        if (getline(baseStationFile, baseStationLogLine)) {
            processedFile << processLine(reseiverLogLine, baseStationLogLine)
                          << "\n";
        } else {
            processedFile << reseiverLogLine << "\n";
        }
    }

    receiverFile.close();
    processedFile.close();
}