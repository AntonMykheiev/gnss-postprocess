# gnss-postprocess

The program processes GNSS (Global Navigation Satellite System) data from receiver and base station observations. It performs data correction using predefined base station coordinates and real-time UDP messages.

Functionality:

1. File-Based Data Processing (processFileData)
    - Reads GNSS observation data from inputReceiver.obs and inputBaseStation.obs.
    - Applies coordinate corrections based on a predefined base station position.
    - Outputs corrected data to processed.pos.
    
2. UDP-Based Data Processing (processUdpConnectionData)
    - Listens for incoming GNSS data over UDP on port 12345.
    - Applies coordinate corrections using real-time SAPOS correction data.
    - Sends back the corrected data over UDP.
    
3. Data Correction (lineProcessor.cpp).
    - Extracts timestamps and coordinates from data lines.
    - Computes coordinate corrections using base station and receiver data.
    - Produces precise GNSS positions.

This program is designed for GNSS data correction, ensuring higher positioning accuracy.