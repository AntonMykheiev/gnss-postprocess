#ifndef LINE_P
#define LINE_P

// This function processing a line with navi data from a pre-uploaded file
std::string processFileLine(std::string_view receiverLine,
                            std::string_view baseStationLine,
                            std::string_view baseStationTruePosition);

// This function processing a line with navi data from a UDP message
std::string processMessageLine(std::string_view messageLine,
                               std::string_view correctionData);

#endif