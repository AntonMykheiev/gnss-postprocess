#include <fstream>
#include <sstream>
#include <string>

#include "baseStation.cpp"

using namespace std;

string getLineTimestamp(string &line);
double getX(string &line);
double getY(string &line);
double calculatePreciseX(double &receiverX, double &baseStationX);
double calculatePreciseY(double &receiverY, double &baseStationY);

string processLine(string &receiverLine, string &baseStationLine) {
    stringstream processedLine;

    string receiverLineTimestamp = getLineTimestamp(receiverLine);

    double receiverX = getX(receiverLine);
    double receiverY = getY(receiverLine);

    double baseStationX = getX(baseStationLine);
    double baseStationY = getY(baseStationLine);

    double preciseX = calculatePreciseX(receiverX, baseStationX);
    double preciseY = calculatePreciseY(receiverY, baseStationY);

    processedLine << receiverLineTimestamp << ' ' << std::fixed
                  << std::setprecision(2) << preciseX << ' ' << preciseY;

    return processedLine.str();
}

string getLineTimestamp(string &line) { return line.substr(0, 19); }

double getX(string &line) { return stod(line.substr(20, 4)); }

double getY(string &line) { return stod(line.substr(25, 4)); }

double calculatePreciseX(double &receiverX, double &baseStationX) {
    double correctionX = trueX - baseStationX;

    return receiverX + correctionX;
}

double calculatePreciseY(double &receiverY, double &baseStationY) {
    double correctionY = trueY - baseStationY;

    return receiverY + correctionY;
}