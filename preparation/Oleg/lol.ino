#include<Wire.h>
#include<iarduino_I2C_Motor.h>
#include<iarduino_I2C_Bumper.h>
#include <iarduino_HC_SR04.h>
iarduino_HC_SR04 hc1(12, 11);
iarduino_HC_SR04 hc2(9, 3);
iarduino_I2C_Motor mot_R(0x0A);
iarduino_I2C_Motor mot_L(0x0B);
iarduino_I2C_Bumper bum(0x0C);
float M0 = 60;
int f1 = 0;
int f = 0;
int c = 0;
void setup() {
  mot_R.begin();
  mot_L.begin();
  bum.begin();
  bum.setTurnSignal(BUM_TURN_AUTO);
  mot_R.setDirection(true);
  mot_L.setDirection(false);
  while (c == 0) {
    if (bum.getErrPID() != -4.50 && f1 == 0) {
      c = 1;
    }
    mot_R.setSpeed(40, MOT_PWM);
    mot_L.setSpeed(40, MOT_PWM);
  }
  mot_R.setSpeed(20, MOT_PWM);
  mot_L.setSpeed(20, MOT_PWM);
  delay(500);
}

void loop() {
  if (bum.getCross(3, 1000) && f1 == 0) {
    f1 = 1;
  }
  if (f1 == 1) {
    c++;
    f1 = 0;
  }
  while (c >= 2) {
    int m = millis();
    while (millis() - m < 1000) {
      int PID = bum.getErrPID() * 12;
      mot_R.setSpeed(M0 - PID, MOT_PWM);
      mot_L.setSpeed(M0 + PID, MOT_PWM);
    }
    while (millis() - m >= 1000) {
      mot_R.setSpeed(0, MOT_PWM);
      mot_L.setSpeed(0, MOT_PWM);
    }
  }
  if (hc1.distance() < 25 && f == 0 && millis() > 10) {
    f = 1;
  }
  while (f == 1) {
    while (hc2.distance() > 10) {
      mot_R.setSpeed(40, MOT_PWM);
      mot_L.setSpeed(60, MOT_PWM);
    }
    while (bum.getErrPID() == -4.50) {
      mot_R.setSpeed(70, MOT_PWM);
      mot_L.setSpeed(35, MOT_PWM);
    }
    if (bum.getErrPID() != -4.50) {
      f = 2;
    }
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
  }
  int PID = bum.getErrPID() * 12;
  mot_R.setSpeed(M0 - PID, MOT_PWM);
  mot_L.setSpeed(M0 + PID, MOT_PWM);
}
