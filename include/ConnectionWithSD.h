#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SD.h>

ESP8266WiFiMulti wifiMulti; // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

class ConnectionWithSD
{
private:
    bool connectionStatus;

public:
    ConnectionWithSD();
    ~ConnectionWithSD();
    void setup();
    void connect();
    void scanNetworks();
    bool status() { return connectionStatus; }
};

void ConnectionWithSD::connect()
{
    // WiFi.mode(WIFI_STA);
    // WiFi.begin(ssid, password);
    Serial.print("Connecting...");
    while (wifiMulti.run() != WL_CONNECTED)
    { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
        delay(500);
        Serial.print('.');
        digitalWrite(LED_MAIN, !digitalRead(LED_MAIN));
    };
    connectionStatus = true;
    Serial.println();
    Serial.print("Connected to: ");
    Serial.println(WiFi.SSID());
    Serial.print("Device IP Address: ");
    Serial.println(WiFi.localIP());
};

void ConnectionWithSD::setup()
{
    wifiMulti.addAP(ssid1, password1);
    wifiMulti.addAP(ssid2, password2);
};

void ConnectionWithSD::scanNetworks()
{
    int numSsid = WiFi.scanNetworks();
    if (numSsid == -1)
    {
        Serial.println("Couldn't get a wifi connection");
        while (true)
            ;
    };
    for (int thisNet = 0; thisNet < numSsid; thisNet++)
    {
        Serial.print(thisNet + 1);
        Serial.print(") ");
        Serial.print(WiFi.SSID(thisNet));
        Serial.println(WiFi.RSSI(thisNet));
    };
};
ConnectionWithSD::ConnectionWithSD(){
    connectionStatus = false;
}

ConnectionWithSD::~ConnectionWithSD(){
    connectionStatus = false;
    wifiMulti.cleanAPlist();
};