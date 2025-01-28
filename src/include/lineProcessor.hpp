#ifndef LINE_P
#define LINE_P

// This function processing a line with navi data from a pre-uploaded file
std::string processFileLine(std::string &receiverLine,
                            std::string &baseStationLine,
                            std::string_view baseStationTruePosition);

// This function processing a line with navi data from a UDP message
std::string processMessageLine(std::string &messageLine,
                               std::string_view correctionData);

#endif