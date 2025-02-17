#include <string>
#include <string_view>
#pragma once

class LineProcessor {
   private:
    std::string_view getLineTimestamp(std::string_view line);
    double getXCoordinate(std::string_view line);
    double getYCoordinate(std::string_view line);
    double calculateCorrectionValue(double &baseStationCoordinate,
                                    double &baseStationTrueCoordinate);
    double calculatePreciseCoordinate(double &receiverCoordinate,
                                      double &correctionCoordinate);

   public:
    explicit LineProcessor() = default;
    std::string processFileLine(std::string_view receiverLine,
                                std::string_view baseStationLine,
                                std::string_view baseStationTruePosition);
    std::string processMessageLine(std::string_view messageLine,
                                   std::string_view correctionData);
};