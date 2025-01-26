#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "baseStation.cpp"

using namespace std;

string processLine(string &reseiverLogLine, string &baseStationLogLine);
string getLineTimestamp(string &line);
double getLineX(string &line);
double getLineY(string &line);
double calculatePreciseX(double &receiverX, double &baseStationX);
double calculatePreciseY(double &receiverY, double &baseStationY);

void processLogData()
{
    string reseiverLogLine;
    string baseStationLogLine;

    ifstream receiverFile("./input/inputReceiver.obs");
    ifstream baseStationFile("./input/inputBaseStation.obs");
    ofstream processedFile("./result/processed.pos");

    while (getline(receiverFile, reseiverLogLine))
    {
        getline(baseStationFile, baseStationLogLine);

        processedFile << processLine(reseiverLogLine, baseStationLogLine) << "\n";
    }

    receiverFile.close();
    processedFile.close();
}

string processLine(string &reseiverLogLine, string &baseStationLogLine)
{
    stringstream processedLine;

    string receiverLineTimestamp = getLineTimestamp(reseiverLogLine);
    string baseStationLimeTimestamp = getLineTimestamp(baseStationLogLine);

    if (receiverLineTimestamp == baseStationLimeTimestamp)
    {
        double receiverLineX = getLineX(reseiverLogLine);
        double receiverLineY = getLineY(reseiverLogLine);

        double baseStationX = getLineX(baseStationLogLine);
        double baseStationY = getLineY(baseStationLogLine);

        double preciseX = calculatePreciseX(receiverLineX, baseStationX);
        double preciseY = calculatePreciseY(receiverLineY, baseStationY);

        processedLine << receiverLineTimestamp << ' ' << std::fixed << std::setprecision(2) << preciseX << ' ' << preciseY;
    }
    else
    {
        processedLine << reseiverLogLine;
    }

    return processedLine.str();
}

string getLineTimestamp(string &line)
{
    return line.substr(0, 19);
}

double getLineX(string &line)
{
    return stod(line.substr(20, 4));
}

double getLineY(string &line)
{
    return stod(line.substr(25, 4));
}

double calculatePreciseX(double &receiverX, double &baseStationX)
{
    double correctionX = trueX - baseStationX;

    return receiverX + correctionX;
}

double calculatePreciseY(double &receiverY, double &baseStationY)
{
    double correctionY = trueY - baseStationY;

    return receiverY + correctionY;
}