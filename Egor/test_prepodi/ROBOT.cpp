
#include "ROBOT.h"
#pragma once

Servo servo_arm;
Servo servo_finger;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

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

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } 
  else {
    Serial.println("No TCS34725 found ... check your connections");
    //while (1);
  }
  
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

Robot::get_color() {
  // https://robotchip.ru/obzor-datchik-tsveta-na-tcs3472/
  // example Adafruit_TCS34725.h/tcs34725
  
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
}

Robot::get_distanse() {
  // https://github.com/Ni3nayka/sketch/blob/main/arduino/исходники/distanse_IK/distanse_IK.ino
  return (32*pow(analogRead(SENSOR_DISTANSE)*0.0048828125, -1.10));
}
