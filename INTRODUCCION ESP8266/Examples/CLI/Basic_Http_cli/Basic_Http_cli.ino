#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid     = "AIndustriosa";
const char* password = "workshop.";


void setup() {

    Serial.begin(115200);
    delay(10);
  
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

}

void loop() {
   
    if((WiFi.status() == WL_CONNECTED)) {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        http.begin("http://192.168.1.47/"); //HTTP
        http.addHeader("Content-Type", "application/json");

        Serial.print("[HTTP] GET...\n");
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            Serial.println();
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(10000);
}

