#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string getLineTimestamp(string &line);
double getX(string &line);
double getY(string &line);
double calculateCorrectionX(double &baseStationX, double &baseStationTrueX);
double calculateCorrectionY(double &baseStationY, double &baseStationTrueY);
double calculatePreciseX(double &receiverX, double &correctionX);
double calculatePreciseY(double &receiverY, double &correctionY);

string processFileLine(string &receiverLine, string &baseStationLine,
                       string &baseStationTruePosition) {
    stringstream processedLine;

    string receiverLineTimestamp = getLineTimestamp(receiverLine);

    double receiverX = getX(receiverLine);
    double receiverY = getY(receiverLine);

    double baseStationX = getX(baseStationLine);
    double baseStationY = getY(baseStationLine);

    double baseStationTrueX = getX(baseStationTruePosition);
    double baseStationTrueY = getY(baseStationTruePosition);

    double correctionX = calculateCorrectionX(baseStationX, baseStationTrueX);
    double correctionY = calculateCorrectionY(baseStationY, baseStationTrueY);

    double preciseX = calculatePreciseX(receiverX, correctionX);
    double preciseY = calculatePreciseY(receiverY, correctionY);

    processedLine << receiverLineTimestamp << ' ' << std::fixed
                  << std::setprecision(2) << preciseX << ' ' << preciseY;

    return processedLine.str();
}

string processMessageLine(string &messageLine, string &correctionData) {
    stringstream processedLine;

    string receiverLineTimestamp = getLineTimestamp(messageLine);

    double messageX = getX(messageLine);
    double messageY = getY(messageLine);

    double correctionX = getX(correctionData);
    double correctionY = getY(correctionData);

    double preciseX = calculatePreciseX(messageX, correctionX);
    double preciseY = calculatePreciseY(messageY, correctionY);

    processedLine << receiverLineTimestamp << ' ' << std::fixed
                  << std::setprecision(2) << preciseX << ' ' << preciseY;

    return processedLine.str();
}

string getLineTimestamp(string &line) { return line.substr(0, 19); }

double getX(string &line) { return stod(line.substr(20, 4)); }

double getY(string &line) { return stod(line.substr(25, 4)); }

double calculateCorrectionX(double &baseStationX, double &baseStationTrueX) {
    return baseStationTrueX - baseStationX;
}

double calculateCorrectionY(double &baseStationY, double &baseStationTrueY) {
    return baseStationTrueY - baseStationY;
}

double calculatePreciseX(double &receiverX, double &correctionX) {
    return receiverX + correctionX;
}

double calculatePreciseY(double &receiverY, double &correctionY) {
    return receiverY + correctionY;
}