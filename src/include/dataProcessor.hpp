#ifndef DATA_P
#define DATA_P

// Call this function if you want to process data from pre-uploaded file
// inputReceiver.obs
void processFileData();

// Call this function if you need to run a UDP server for receiving messages
// with navi data for live processing
void processUdpConnectionData();

#endif