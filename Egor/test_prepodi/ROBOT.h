#pragma once

#include <Arduino.h>

#include <Servo.h>

#define PWM_1 5
#define PWM_2 6
#define DIR_1 4
#define DIR_2 7

#define SENSOR_IK_L A2
#define SENSOR_IK_R A3

#define SENSOR_DISTANSE A1

#define SERVO_PIN_ARM 10
#define SERVO_PIN_FINGER 3

#define SERVO_FINGER_TAKE 90
#define SERVO_FINGER_DROP 40
#define SERVO_ARM_UP      180
#define SERVO_ARM_DOWN    100
#define SERVO_TIME_DELTA  20

#include <Wire.h>
#include "Adafruit_TCS34725.h"

class Robot {
  public:
    setup(); 
    motor(int left, int right);
    arm_take();
    arm_drop();
    get_color();
    get_distanse();
  private:
    servo_arm_run(int start, int finish);
    servo_finger_run(int start, int finish);
};
