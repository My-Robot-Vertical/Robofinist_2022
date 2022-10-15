//Подключение библиотек

#include <Wire.h>

#include <iarduino_I2C_Bumper.h>
iarduino_I2C_Bumper bum(0x0C);

#include <iarduino_I2C_Motor.h>
iarduino_I2C_Motor mot_R (0x0A);
iarduino_I2C_Motor mot_L (0x0B);

#include <Servo.h>
Servo arm;
Servo ud;

#include  "easy_arduino_navigator.h"
Navigator navigator(RIGHT_ARM_RULE);

#include <iarduino_HC_SR04.h>
iarduino_HC_SR04 front (12, 11);
iarduino_HC_SR04 right1(2,   7);

//Объявление библиотек

float i, j;
float M0 = 40;
float kP    = 3 + 0.125 * (M0 - 20);
float kD    = M0 * M0 / 250;
float kd = 1;
int c, f;
int s = 1125;
int gf = 4750;
int d = 30;
int r = 15;
void setup() {
  //Подключение моторов

  mot_R.begin();
  mot_L.begin();
  mot_R.setDirection(true);
  mot_L.setDirection(false);

  //Подключение датчиков линии

  bum.begin();

  //Настройка направления сервомоторов

  ud.attach(9);
  ud.write(40);

  arm.attach(3);
  arm.write(180);

  delay(1000);
  ud.detach();
  arm.detach();

  //лабиринт

  navigator.set_start(0, 0, NAVIGATOR_DIR_E);
  navigator.set_finish(3, 3, NAVIGATOR_DIR_E);
}
void loop() {
  if (c == 0) {//езда до линии
    c = 1;
  }
  if (c == 1) {//езда по линии
    c = 2;
  }
  if (c == 2) {//езда по лабиринту
    move1((front.distance() < d), (right1.distance() < d));
  }
  if (c == 3) {//езда до линии с инверсией
    c = 4;
  }
  if (c == 4) {//езда по линии с инверсией
    if ( bum.getLineSum() >= 5 ) {
      bum.setLineType(BUM_LINE_CHANGE);
    }
    i  = bum.getErrPID();
    float P  =  i * kP;
    float D  = (i - j) * kD;
    float PD = P + D;
    mot_R.setSpeed(M0 - PD, MOT_PWM);
    mot_L.setSpeed(M0 + PD, MOT_PWM);
  }
  if (c == 5) {//кегильринг
    c = 6;
  }
  if (c == 7) {//возрат назад
    c = 8;
  }
}
void move1(bool forward_wall, bool side_wall) {
  int t = navigator.next_move(forward_wall, side_wall);
  if (t == NAVIGATOR_END) {
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
  }
  if (t == NAVIGATOR_MOVE_FORWARD) {
    unsigned long int ss = millis();
    int U, d1[3] = {r, r, r}, d2;
    while (millis() - ss < gf) {
      d2 = right1.distance();
      if (d2 < r + 5) {
        d1[0] = d1[1];
        d1[1] = d1[2];
        d1[2] = right1.distance();
        d2 = (d1[0] + d1[1] + d1[2]) / 3;
        U = (r - right1.distance()) * kd;
        mot_R.setSpeed(40 + U, MOT_PWM);
        mot_L.setSpeed(40 - U, MOT_PWM);
      }
      else {
        mot_R.setSpeed(40, MOT_PWM);
        mot_L.setSpeed(40, MOT_PWM);
      }
    }
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    delay(s);
  }
  if (t == NAVIGATOR_MOVE_LEFT) {
    mot_R.setSpeed( 40, MOT_PWM);
    mot_L.setSpeed(-40, MOT_PWM);
    delay(s);
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    delay(s);
  }
  if (t == NAVIGATOR_MOVE_RIGHT) {
    mot_R.setSpeed(-40, MOT_PWM);
    mot_L.setSpeed( 40, MOT_PWM);
    delay(s);
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    delay(s);
  }
  if (t == NAVIGATOR_MOVE_LEFT_AND_FORWARD) {
    mot_R.setSpeed( 40, MOT_PWM);
    mot_L.setSpeed(-40, MOT_PWM);
    delay(s);
    mot_R.setSpeed(40, MOT_PWM);
    mot_L.setSpeed(40, MOT_PWM);
    delay(gf);
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    delay(s);
  }
  if (t == NAVIGATOR_MOVE_RIGHT_AND_FORWARD) {
    mot_R.setSpeed(-40, MOT_PWM);
    mot_L.setSpeed( 40, MOT_PWM);
    delay(s);
    mot_R.setSpeed(40, MOT_PWM);
    mot_L.setSpeed(40, MOT_PWM);
    delay(gf);
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    delay(s);
  }
}
