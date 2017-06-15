#include <ESP8266WiFi.h>

const char* ssid     = "AIndustriosa";
const char* password = "workshop";

uint8_t wifiCNT =0;

IPAddress ip(192, 168, 1, 20);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.print("Connecting to ");

  WiFi.config(ip,gateway, subnet,dns);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED && wifiCNT < 20) {
    delay(500);
    Serial.print(".");
    wifiCNT++;
  }
  Serial.println("WiFi connected");  
  
}
void loop() {
  delay(1000);
  Serial.println(WiFi.status());
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.subnetMask());
  Serial.println(WiFi.gatewayIP());

  /*if (WiFi.status() != WL_CONNECTED && wifiCNT < 10) {
    delay(500);
    Serial.print(".");
    wifiCNT++;
  }else{
    Serial.println(WiFi.status());
  }*/
}

