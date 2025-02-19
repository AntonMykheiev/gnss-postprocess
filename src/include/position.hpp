#ifndef POSITION_HPP
#define POSITION_HPP

#include <string>
#include <string_view>

class Position {
   private:
    std::string timestamp;
    double x;
    double y;
    void retreiveTimestampFromLine(std::string_view line);
    void retreiveXCoordinateFromLine(std::string_view line);
    void retreiveYCoordinateFromLine(std::string_view line);

   public:
    Position(std::string_view positionLine);
    std::string_view getTimestamp();
    double getX();
    double getY();
    void setTimestamp(std::string_view timestamp);
    void setX(double x);
    void setY(double y);
};

#endif