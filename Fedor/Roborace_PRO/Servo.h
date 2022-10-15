#pragma once

#include <Servo.h>
Servo Aservo;
Servo Fservo;

void take(){
  Aservo.write(90);
  delay(1000);
  Fservo.write(0);
  delay(1000);
  Aservo.write(180);
  delay(1000);
  Fservo.write(90);
}
void drop(){
  Fservo.write(0);
  delay(1000);
  Aservo.write(90);
  delay(1000);
  Fservo.write(90);
}
