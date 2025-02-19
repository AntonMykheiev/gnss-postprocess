#include "position.hpp"

#include <iostream>
#include <string_view>

Position::Position(std::string_view positionLine) {
    retreiveTimestampFromLine(positionLine);
    retreiveXCoordinateFromLine(positionLine);
    retreiveYCoordinateFromLine(positionLine);
}

void Position::retreiveTimestampFromLine(std::string_view line) {
    timestamp = line.substr(0, 19);
}

void Position::retreiveXCoordinateFromLine(std::string_view line) {
    x = std::strtod(line.substr(20, 4).data(), 0);
}

void Position::retreiveYCoordinateFromLine(std::string_view line) {
    y = std::strtod(line.substr(25, 4).data(), 0);
}

std::string_view Position::getTimestamp() { return timestamp; }

double Position::getX() { return x; }

double Position::getY() { return y; }

void Position::setTimestamp(std::string_view timestamp) {
    this->timestamp = timestamp;
}

void Position::setX(double x) { this->x = x; }

void Position::setY(double y) { this->y = y; }