
#include "ROBOT.h"
#pragma once

Servo servo_arm;
Servo servo_finger;

Robot::setup() {
  pinMode(PWM_1,OUTPUT);
  pinMode(PWM_2,OUTPUT);
  pinMode(DIR_1,OUTPUT);
  pinMode(DIR_2,OUTPUT);
  servo_arm.attach(SERVO_PIN_ARM);
  servo_finger.attach(SERVO_PIN_FINGER);
  
  servo_arm.write(SERVO_ARM_UP); 
  servo_finger.write(SERVO_FINGER_TAKE);
  motor(0,0);
  delay(1000);
}


Robot::arm_take() {
  Robot::servo_finger_run(SERVO_FINGER_TAKE,SERVO_FINGER_DROP);
  Robot::servo_arm_run(SERVO_ARM_UP,SERVO_ARM_DOWN);
  Robot::servo_finger_run(SERVO_FINGER_DROP,SERVO_FINGER_TAKE);
  Robot::servo_arm_run(SERVO_ARM_DOWN,SERVO_ARM_UP);
}

Robot::arm_drop() {
  Robot::servo_arm_run(SERVO_ARM_UP,SERVO_ARM_DOWN);
  Robot::servo_finger_run(SERVO_FINGER_TAKE,SERVO_FINGER_DROP);
  Robot::servo_arm_run(SERVO_ARM_DOWN,SERVO_ARM_UP);
  Robot::servo_finger_run(SERVO_FINGER_DROP,SERVO_FINGER_TAKE);
}

Robot::servo_arm_run(int start, int finish) {
  int d = start>finish?-1:1;
  for (int i = start; i!=finish; i+=d) {
    servo_arm.write(i);
    delay(SERVO_TIME_DELTA);
  }
}

Robot::servo_finger_run(int start, int finish) {
  int d = start>finish?-1:1;
  for (int i = start; i!=finish; i+=d) {
    servo_finger.write(i);
    delay(SERVO_TIME_DELTA);
  }
}

Robot::motor(int left, int right) {
  digitalWrite(DIR_1,left>0);
  analogWrite(PWM_1,map(constrain(abs(left),0,100),0,100,0,255));
  digitalWrite(DIR_2,right>0);
  analogWrite(PWM_2,map(constrain(abs(right),0,100),0,100,0,255));
}
