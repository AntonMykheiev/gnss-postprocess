#include <gtest/gtest.h>

#include "lineProcessor.hpp"

// processFileLine testing
TEST(CoordinateProcessingTest, ProcessFileLine) {
    std::string receiverLine = "2025 01 19 13 31 37 0.01 0.12";
    std::string baseStationLine = "2025 01 19 13 31 37 0.02 0.15";
    std::string_view baseStationTruePosition = "2025 01 19 13 31 37 0.03 0.18";

    std::string expected = "2025 01 19 13 31 37 0.02 0.15";
    EXPECT_EQ(
        processFileLine(receiverLine, baseStationLine, baseStationTruePosition),
        expected);
}

// processMessageLine testing
TEST(CoordinateProcessingTest, ProcessMessageLine) {
    std::string messageLine = "2025 01 19 13 31 37 0.01 0.12";
    std::string_view correctionData = "2025 01 19 13 31 37 0.02 0.03";

    std::string expected = "2025 01 19 13 31 37 0.03 0.15";
    EXPECT_EQ(processMessageLine(messageLine, correctionData), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}