#pragma once

#include "ENCODERS.h"
#include "SENSORZ.h"

#define Speed_PinR 10//13
#define Speed_PinL 11//11
#define Tern_PinR 12//12
#define Tern_PinL 13//10

#define ugly_encoder_K 1.5
#define CM_ENC 286

void ser(){
  Serial3.print(Encoder_Left);
  Serial3.print(Encoder_Right);
}

class Robot {
  public:
    run(long int cm);
    turn(int gradus);
    motors(long int M1, long int M2);
    get_UZ_forward(int cm);
    get_UZ_right(int cm);
    get_IK_left();
    get_IK_right();
    get_IK_forward();
    get_IK_error();
    take();
    drop();
  //private:
};
Robot::motors(long int M1, long int M2) {
  digitalWrite(Tern_PinR, M2 < 0);
  digitalWrite(Tern_PinL, M1 < 0);
  analogWrite(Speed_PinR, map(constrain(abs(M2 * 1.4), 0, 100), 0, 100, 0, 255));
  analogWrite(Speed_PinL, map(constrain(abs(M1), 0, 100), 0, 100, 0, 255));
}
Robot::run(long int cm) {
  Encoder_Left=0;
  Encoder_Right=0;
  int k=0;
  if(cm>0){k=1;}else{k=-1;}
  while (abs(Encoder_Left)<CM_ENC*abs(cm)){
  int E = 0.01 * (Encoder_Right*ugly_encoder_K - Encoder_Left);
  Robot::motors(k*30+k*E,k*30-k*E);
  ser();
  }
  Robot::motors(0, 0);
  Encoder_Right=0;
  Encoder_Left=0;
}
Robot::turn(int gradus) {
  Encoder_Left=gradus*-44;
  Encoder_Right=gradus*30;
  while (abs(Encoder_Right)>0 || abs(Encoder_Left)>0){
  if (gradus > 0) {
    Robot::motors(constrain(Encoder_Left/-4,0,30),constrain(Encoder_Right/-4,-30,0));
    ser();
  }
  else {
    ser();
    Robot::motors(constrain(Encoder_Left/-4,-30,0),constrain(Encoder_Right/-4,0,30));
  }
  }
  Robot::motors(0, 0);
}
Robot::get_UZ_forward(int cm){
  if (cm>distF()){return 1;}else{return 0;}
}
Robot::get_UZ_right(int cm){
  if (cm>distR()){return 1;}else{return 0;}
}
Robot::get_IK_right(){
  return WBDR();
}
Robot::get_IK_left(){
  return WBDL();
}
Robot::get_IK_error(){
  return WBDR() - WBDL();
}
Robot::get_IK_forward(){
  return analogRead(5);
}
Robot::take(){
  take();
}
Robot::drop(){
  drop();
}
