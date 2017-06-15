#include <ESP8266WiFi.h>            
#include <ArduinoJson.h>
#include "FS.h"

 const char* apName = "";
 const char* apPassw = "";
  
bool loadConfig() {
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

 
  std::unique_ptr<char[]> buf(new char[size]);

  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return false;
  }

  apName = json["apName"];
  apPassw = json["apPassw"];


  Serial.print("Loaded apName: ");
  Serial.println(apName);
  Serial.print("Loaded apPassw: ");
  Serial.println(apPassw);
  return true;
}

bool saveConfig() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["apName"] = "AMYAP";
  json["apPassw"] = "workshop.";

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  return true;
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("Mounting FS...");

  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }


  /*if (!saveConfig()) {
    Serial.println("Failed to save config");
  } else {
    Serial.println("Config saved");
  }*/

  if (!loadConfig()) {
    Serial.println("Failed to load config");
  } else {
    Serial.println("Config loaded");
    
    Serial.println("Connecvting to ap");
    WiFi.begin(apName, apPassw);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
    
  }
}

void loop() {
}
