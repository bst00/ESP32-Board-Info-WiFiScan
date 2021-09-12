/*
 *  This sketch scans for WiFi networks and outputs result to the serial monitor along with ESP32 MAC address and other info.
 *  
 *  Outputs the MAC address of ESP
 *  and for each network found; Channel, RSSI, BSSID, Encryption Type and SSID
 *  
 *  To show hidden networks edit the WiFiScan.h file and set show_hidden = true
 *  
 *  int16_t scanNetworks(bool async = false, bool show_hidden = true, bool passive = true, uint32_t max_ms_per_chan = 300, uint8_t channel = 0);
 *  
 *  Based on the original WiFiScan example from Espressif
 *  Bob Trevan  11-September-2021
 */
#include <WiFi.h>

uint32_t    chipId = 0;
const char* ChipModel = 0;
uint32_t    ChipRev = 0;
uint32_t    ChipCores = 0;

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////          Setup          //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println("         |===================================================|");
    Serial.println("         | Sketch:  ESP32-Info_WiFiScan                      |");
    Serial.println("         |===================================================|");

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
/////////////////////////////////////////////
//            Get ESP Chip Info            //
/////////////////////////////////////////////
    Serial.println("Getting Chip Info...");
    for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
    Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
    Serial.printf("This chip has %d cores\n", ESP.getChipCores());
    Serial.print("Chip ID: "); Serial.println(chipId);
    Serial.println();
    Serial.print("ESP32 Board MAC Address:  ");
    Serial.println(WiFi.macAddress());
    // Options are: 240 (default), 160,80, 40,20 and 10 Mhz
    // setCpuFrequencyMhz(240);
    int cpuSpeed = getCpuFrequencyMhz();
    Serial.println("Running at " + String(cpuSpeed) + "MHz");
}
//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////        Main Loop        //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
    Serial.println("scan start");
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
     Serial.println("scan done, will rescan in 3 minutes");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
        // Print RSSI, Channel, BSSID (Mac out Access Points) Encryption Type and SSID for each network found
        //  Laid out this way for neater output due to variable length SSID
        Serial.print(i + 1);
        Serial.print(":\tch:");
        Serial.print(WiFi.channel(i));
        Serial.print("\t");
        //Serial.print(WiFi.SSID(i).length());
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")dbm   ");
        //Serial.print(WiFi.BSSID(i));
        //Serial.print("");
        Serial.print(WiFi.BSSIDstr(i));
        Serial.print("  ");
        byte encryption = WiFi.encryptionType(i);
        Serial.print("Auth:");
        Serial.print(encryption,HEX);
        Serial.print("  ");
        byte encryptionType = WiFi.encryptionType(i);
        if( encryptionType ==  WIFI_AUTH_OPEN)
        Serial.print("OPEN         ");                          // <<<  Pad with spaces to help output format
        else if ( encryptionType ==  WIFI_AUTH_WEP)
        Serial.print("WEP    ");
        else if ( encryptionType ==  WIFI_AUTH_WPA_PSK)
        Serial.print("WPA_PSK    ");
        else if ( encryptionType ==  WIFI_AUTH_WPA2_PSK)
        Serial.print("WPA2_PSK    ");
        else if ( encryptionType ==  WIFI_AUTH_WPA_WPA2_PSK)
        Serial.print("WPA_WPA2_PSK  ");            
        else if ( encryptionType ==  WIFI_AUTH_WPA2_ENTERPRISE)
        Serial.print("WPA2_ENTERPRISE");
        Serial.print("\t");
        Serial.println(WiFi.SSID(i));
    }
         delay(10);
    }
        Serial.println("");
    // Wait a bit before scanning again
    delay(180000);
}
/* Sketch:  ESP32-Info_WiFiScan  */
/* Bob Trevan 11-September-2021  */       
