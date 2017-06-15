#include <ESP8266WiFi.h>
#include <pgmspace.h>

//https://github.com/esp8266/Arduino/blob/ea302aab05480ad36c076b618abb642b1eb1893b/hardware/esp8266com/esp8266/cores/esp8266/pgmspace.h
//https://github.com/esp8266/Arduino/blob/master/cores/esp8266/pgmspace.cpp
//https://github.com/esp8266/Arduino/blob/master/doc/PROGMEM.rst

static const char xyz[] PROGMEM = "flash %i";
//PSTR(x)==> static const char __c[] PROGMEM =xxx

//FPSTR(pstr_pointer) ==> const __FlashStringHelper * (pstr_pointer)
//    Pilla la string en FLas y hace un cast al tipo __FlashStringHelper
    
//F(string_literal) ==> (FPSTR(PSTR(string_literal)))

char buff[50];

void setup() {
Serial.begin(115200);
}

void loop() {
  
delay(2000);
Serial.println(FPSTR(xyz)); 
//printf_P(xyz, 6); // use printf with PROGMEM string
sprintf_P(buff,xyz,5);
Serial.println(buff);
Serial.println(F("--- Inline String en Flash ----"));
}


