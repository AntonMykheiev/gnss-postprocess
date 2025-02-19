#ifndef LINE_PROCESSOR_HPP
#define LINE_PROCESSOR_HPP

#include <memory>
#include <string>
#include <string_view>

#include "position.hpp"
class LineProcessor {
   private:
    void calculatePreciseBaseStationCoordinates(
        std::shared_ptr<Position> &baseStationPosition,
        std::shared_ptr<Position> &baseStationTruePosition);
    void calculatePreciseReceiverCoordinates(
        std::shared_ptr<Position> &receiverPosition,
        std::shared_ptr<Position> &baseStationPosition);

   public:
    explicit LineProcessor() = default;
    std::string processPrecisePosition(
        std::shared_ptr<Position> &receiverPosition,
        std::shared_ptr<Position> &baseStationPosition,
        std::shared_ptr<Position> &baseStationTruePosition);

    std::string processPrecisePosition(
        std::shared_ptr<Position> &receiverPosition,
        std::shared_ptr<Position> &absoluteBaseStationPosition);
};

#endif