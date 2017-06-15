#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
//#include <stdio.h>
//#include <string.h>

const char* ssid     = "AIndustriosa";
const char* password = "workshop";

struct ResponseData {
  char resp[10];
  char stat[10];
};

ResponseData rData;

DynamicJsonBuffer jsonBuffer(60);


void setup() {

    Serial.begin(115200);
    delay(10);
  
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
  
}

void loop() {
   
    if((WiFi.status() == WL_CONNECTED)) {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        http.begin("http://192.168.1.47/dos/"); //HTTP

        Serial.print("[HTTP] GET...\n");
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

                if(httpCode == HTTP_CODE_OK) {
                    JsonObject& root = jsonBuffer.parseObject(http.getString());
                    if (root.success()) {
                      strcpy(rData.resp, root["response"]);
                      strcpy(rData.stat, root["status"]);
                      Serial.println(rData.resp);
                      Serial.println(rData.stat);
                     }else{
                      Serial.println("JSON parsing failed!");
                    }
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

