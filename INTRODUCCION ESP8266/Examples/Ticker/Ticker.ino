#include <Ticker.h>

Ticker flipper;
Ticker flipper2;

bool m1=false;
bool m2=false;

int count = 0;

void flip1()
{
  m1=true;
}

void flip2()
{
  m2=true;
}

void setup() {
  Serial.begin(115200);
  flipper.attach(2, flip1);
  flipper2.attach(3, flip2);
}

void loop() {
  if(m1){
    m1=false;
    Serial.println("m1");
    
  }else if(m2){
    m2=false;
    Serial.println("m2");
  }
}
