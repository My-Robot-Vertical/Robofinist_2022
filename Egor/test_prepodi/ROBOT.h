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
#define SERVO_PIN_FINGER 11

#define SERVO_FINGER_TAKE   90
#define SERVO_FINGER_DROP   10
#define SERVO_ARM_UP        90
#define SERVO_ARM_DOWN      0
#define SERVO_ARM_MEGA_UP   90
#define SERVO_ARM_MEGA_DOWN 80
#define SERVO_TIME_DELTA    20

#define MOTOR_SPEED 80

#define i_see_object 20

#include <Wire.h>
#include "Adafruit_TCS34725.h"

class Robot {
  public:
    setup(); 
    motor(int left, int right);
    arm_take();
    arm_drop();
    arm_mega_drop();
    get_color();
    get_distanse();

    PID();
    PID_do_perecresta(bool f=0);
    PID_millis(long int d);
    forward_millis(long int d);
    backward_millis(long int d);
    stop_motor();

    turn_left_perecrestok();
    turn_right_perecrestok();
    turn_left_millis(long int d);
    turn_right_millis(long int d);
  private:
    servo_arm_run(int start, int finish);
    servo_finger_run(int start, int finish);
};
