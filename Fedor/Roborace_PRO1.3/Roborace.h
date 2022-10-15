#pragma once

#define Servo_Arm 9 
#define Servo_F 7

#include "MOTORS.h"
#include "ENCODERS.h"
#include "SENSORZ.h"
#include "Servo.h"

#include <Wire.h>
#include <iarduino_I2C_Bumper.h>
iarduino_I2C_Bumper bum(0x09); 
 
Robot robot;

void setup_robot(){ 
  Aservo.attach(Servo_Arm);
  Fservo.attach(Servo_F);
  attachInterrupt(0, test_1, CHANGE);
  attachInterrupt(1, test_2, CHANGE);
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
  pinMode(Servo_Arm, OUTPUT);
  pinMode(Servo_F, OUTPUT);
  LST=digitalRead(18);
  LST2=digitalRead(19);
  LST3=digitalRead(3);
  LST4=digitalRead(2);
  CST = LST;
  CST2 = LST2;
  CST3 = LST3;
  CST4 = LST4;
  while(!Serial){;}
  bum.begin(); 
}
