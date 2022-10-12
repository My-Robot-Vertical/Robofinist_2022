#pragma once

#include "MOTORS.h"
#include "ENCODERS.h"
#include "SENSORZ.h"

Robot robot;

void setup_robot(){ 
  attachInterrupt(2, test_1, CHANGE);
  attachInterrupt(3, test_2, CHANGE);
  attachInterrupt(4, test_3, CHANGE);
  attachInterrupt(5, test_4, CHANGE);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG2, OUTPUT);
  pinMode(PIN_ECHO2, INPUT);
  pinMode(Speed_PinR, OUTPUT);
  pinMode(Speed_PinL, OUTPUT);
  pinMode(Tern_PinR, OUTPUT);
  pinMode(Tern_PinL, OUTPUT);
  LST=digitalRead(18);
  LST2=digitalRead(19);
  LST3=digitalRead(20);
  LST4=digitalRead(21);
  CST = LST;
  CST2 = LST2;
  CST3 = LST3;
  CST4 = LST4;
}
