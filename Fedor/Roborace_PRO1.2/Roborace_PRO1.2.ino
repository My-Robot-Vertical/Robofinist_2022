#include "Roborace.h"

void setup(){
  Serial.begin(9600);
  setup_robot();
  robot.turn(180);
}
void loop(){
  //Serial.print(Encoder_Right);
  //Serial.print("_______");
  //Serial.println(Encoder_Left);
}
