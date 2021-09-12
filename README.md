# ESP32-Board-Info-WiFiScan
Scans for WiFi networks and outputs result to the serial monitor along with ESP32 MAC address and other info.
  
  Outputs the MAC address of ESP
  and for each network found; Channel, RSSI, BSSID, Encryption Type and SSID
  
  To show hidden networks edit the WiFiScan.h file (found in the WiFi library) and set show_hidden = true  
      
  i.e.   int16_t scanNetworks(bool async = false, bool show_hidden = true, bool passive = true, uint32_t max_ms_per_chan = 300, uint8_t channel = 0);
  
  Based on the original WiFiScan example from Espressif
