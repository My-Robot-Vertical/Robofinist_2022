#include "Roborace.h"

void setup(){
  Serial.begin(9600);
  setup_robot();
  take();
  delay(3000);
  drop();
}
void loop(){
  
}
