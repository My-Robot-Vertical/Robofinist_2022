#include "ROBOT.h"

Robot robot;

void setup() {
  robot.setup();
  robot.arm_take();
  delay(1000);
  robot.arm_drop();
  delay(1000);
  robot.motor(100,100);
  delay(1000);
  robot.motor(0,0);
}

void loop() {
  
}
