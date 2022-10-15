#include "Roborace.h"

void setup(){
  Serial.begin(9600);
  setup_robot();
  //robot.turn(180);
}
void loop(){
  Serial.print(Encoder_Right);
  Serial.print("_______");
  Serial.println(Encoder_Left);
}
/*void P(bool turn){
  int MO = 30;
  float k=0.1;
  if (turn){k*-1;}else{;}
  int E=bum.getLineAnalog(4)-bum.getLineAnalog(6);
  robot.motors(MO-E,MO+E);
}*/
