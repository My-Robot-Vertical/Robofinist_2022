#include "ROBOT.h"

Robot robot;

void setup() {
  robot.setup();
  /*robot.arm_take();
  delay(1000);
  robot.arm_drop();
  delay(1000);*/
  //robot.motor(100,100);
  //delay(1000);
  robot.motor(0,0);
  Serial.begin(9600);
}

void loop() {
  /*int e = analogRead(A0) - analogRead(A1);
  e /= 20;
  int M = 50;
  robot.motor(M+e,M-e);*/
  //Serial.println(analogRead(A3));
  Serial.println(robot.get_color());
}
