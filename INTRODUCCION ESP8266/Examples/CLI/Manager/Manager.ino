#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>  

void setup() {
    Serial.begin(115200);
    WiFiManager wifiManager;
    //reset saved settings
    wifiManager.resetSettings();
    
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    //and goes into a blocking loop awaiting configuration
    wifiManager.autoConnect("AMyAP", "workshop");

    Serial.println("connected... :)");
}

void loop() {
    delay(100),
    Serial.println("OK");
    
}
