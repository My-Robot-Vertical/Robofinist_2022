#include "Roborace.h"

void setup(){
  Serial.begin(9600);
  setup_robot();
  robot.take();
  delay(500);
  robot.drop();
}
void loop(){
  
}
