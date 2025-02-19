#include "lineProcessor.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

#include "position.hpp"

void LineProcessor::calculatePreciseBaseStationCoordinates(
    std::shared_ptr<Position> &baseStationPosition,
    std::shared_ptr<Position> &baseStationTruePosition) {
    baseStationPosition->setX(baseStationTruePosition->getX() -
                              baseStationPosition->getX());
    baseStationPosition->setY(baseStationTruePosition->getY() -
                              baseStationPosition->getY());
}

void LineProcessor::calculatePreciseReceiverCoordinates(
    std::shared_ptr<Position> &receiverPosition,
    std::shared_ptr<Position> &baseStationPosition) {
    receiverPosition->setX(receiverPosition->getX() +
                           baseStationPosition->getX());
    receiverPosition->setY(receiverPosition->getY() +
                           baseStationPosition->getY());
}

std::string LineProcessor::processPrecisePosition(
    std::shared_ptr<Position> &receiverPosition,
    std::shared_ptr<Position> &baseStationPosition,
    std::shared_ptr<Position> &baseStationTruePosition) {
    std::stringstream processedLine;

    calculatePreciseBaseStationCoordinates(baseStationPosition,
                                           baseStationTruePosition);
    calculatePreciseReceiverCoordinates(receiverPosition, baseStationPosition);

    processedLine << receiverPosition->getTimestamp() << ' ' << std::fixed
                  << std::setprecision(2) << receiverPosition->getX() << ' '
                  << receiverPosition->getY();

    return processedLine.str();
}

std::string LineProcessor::processPrecisePosition(
    std::shared_ptr<Position> &receiverPosition,
    std::shared_ptr<Position> &absoluteBaseStationPosition) {
    std::stringstream processedLine;

    calculatePreciseReceiverCoordinates(receiverPosition,
                                        absoluteBaseStationPosition);

    processedLine << receiverPosition->getTimestamp() << ' ' << std::fixed
                  << std::setprecision(2) << receiverPosition->getX() << ' '
                  << receiverPosition->getY();

    return processedLine.str();
}