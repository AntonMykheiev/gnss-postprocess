#include "lineProcessor.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

std::string_view LineProcessor::getLineTimestamp(std::string_view line) {
    return line.substr(0, 19);
}

double LineProcessor::getXCoordinate(std::string_view line) {
    return std::strtod(line.substr(20, 4).data(), 0);
}

double LineProcessor::getYCoordinate(std::string_view line) {
    return std::strtod(line.substr(25, 4).data(), 0);
}

double LineProcessor::calculateCorrectionValue(
    double &baseStationCoordinate, double &baseStationTrueCoordinate) {
    return baseStationTrueCoordinate - baseStationCoordinate;
}

double LineProcessor::calculatePreciseCoordinate(double &receiverCoordinate,
                                                 double &correctionCoordinate) {
    return receiverCoordinate + correctionCoordinate;
}

std::string LineProcessor::processFileLine(
    std::string_view receiverLine, std::string_view baseStationLine,
    std::string_view baseStationTruePosition) {
    std::stringstream processedLine;

    std::string_view receiverLineTimestamp = getLineTimestamp(receiverLine);

    double receiverX = getXCoordinate(receiverLine);
    double receiverY = getYCoordinate(receiverLine);

    double baseStationX = getXCoordinate(baseStationLine);
    double baseStationY = getYCoordinate(baseStationLine);

    double baseStationTrueX = getXCoordinate(baseStationTruePosition);
    double baseStationTrueY = getYCoordinate(baseStationTruePosition);

    double correctionX =
        calculateCorrectionValue(baseStationX, baseStationTrueX);
    double correctionY =
        calculateCorrectionValue(baseStationY, baseStationTrueY);

    double preciseX = calculatePreciseCoordinate(receiverX, correctionX);
    double preciseY = calculatePreciseCoordinate(receiverY, correctionY);

    processedLine << receiverLineTimestamp << ' ' << std::fixed
                  << std::setprecision(2) << preciseX << ' ' << preciseY;

    return processedLine.str();
}

std::string LineProcessor::processMessageLine(std::string_view messageLine,
                                              std::string_view correctionData) {
    std::stringstream processedLine;

    std::string_view receiverLineTimestamp = getLineTimestamp(messageLine);

    double messageX = getXCoordinate(messageLine);
    double messageY = getYCoordinate(messageLine);

    double correctionX = getXCoordinate(correctionData);
    double correctionY = getYCoordinate(correctionData);

    double preciseX = calculatePreciseCoordinate(messageX, correctionX);
    double preciseY = calculatePreciseCoordinate(messageY, correctionY);

    processedLine << receiverLineTimestamp << ' ' << std::fixed
                  << std::setprecision(2) << preciseX << ' ' << preciseY;

    return processedLine.str();
}