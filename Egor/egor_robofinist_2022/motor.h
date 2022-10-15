#pragma once

#include "encoder.h"

#define PWM_L  10
#define DIR_L  12
#define PWM_R  11
#define DIR_R  13

#define Hz_in_cm_enc

void motors(long int speed_L, long int speed_R) {
  digitalWrite(DIR_L,speed_L>=0);
  analogWrite(PWM_L,map(constrain(abs(speed_L),0,100),0,100,0,255));
  digitalWrite(DIR_R,speed_R>=0);
  analogWrite(PWM_R,map(constrain(abs(speed_R),0,100),0,100,0,255));
}

void setup_motor() {
  pinMode(PWM_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
}
