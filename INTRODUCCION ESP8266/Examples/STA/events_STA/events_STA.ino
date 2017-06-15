#include <ESP8266WiFi.h>
//ESP8266WIFISTA.h

const char* ssid     = "AIndustriosa";
const char* password = "workshop";

bool wifiConnected =false;

WiFiEventHandler stationConnectedHandler;

        
void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.print("Connecting to ");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  stationConnectedHandler = WiFi.onStationModeConnected(&onStationConnected);
  
}

void onStationConnected(const WiFiEventStationModeConnected& evt) {
  Serial.print("Station connected: ");
  wifiConnected=true;
}

void loop() {
  delay(1000);
  if(wifiConnected){
    Serial.println(WiFi.status());
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.subnetMask());
    Serial.println(WiFi.gatewayIP());
    Serial.println(WiFi.dnsIP(0));
    Serial.println(WiFi.RSSI());
  }
  
  /*if (WiFi.status() != WL_CONNECTED && wifiCNT < 10) {
    delay(500);
    Serial.print(".");
    wifiCNT++;
  }else{
    Serial.println(WiFi.status());
  }*/
}

