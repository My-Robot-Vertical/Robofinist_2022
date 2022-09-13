#include<Wire.h>
#include<iarduino_I2C_Motor.h>
#include<iarduino_I2C_Bumper.h>
iarduino_I2C_Motor mot_R(0x0A);
iarduino_I2C_Motor mot_L(0x0B);
iarduino_I2C_Bumper bum(0x0C);
float M0 = 60;
int f1 = 0;
int c = 0;
int s = 0;
int PID;
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
  if (bum.getCross(5, 1000) && f1 == 0 && millis() - s >= 6000) {
    f1 = 1;
  }
  if (f1 == 1) {
    c++;
    f1 = 0;
  }
  if (c == 2) {
    mot_R.setSpeed(40, MOT_PWM);
    mot_L.setSpeed(40, MOT_PWM);
    delay(3000);
    c = 3;
    s = millis();
  }
  while (c == 4) {
    int m = millis();
    while (millis() - m < 1000) {
      PID = bum.getErrPID() * 12;
      mot_R.setSpeed(M0 - PID, MOT_PWM);
      mot_L.setSpeed(M0 + PID, MOT_PWM);
    }
    while (millis() - m >= 1000) {
      mot_R.setSpeed(0, MOT_PWM);
      mot_L.setSpeed(0, MOT_PWM);
    }
  }
  PID = bum.getErrPID() * 12;
  mot_R.setSpeed(M0 - PID, MOT_PWM);
  mot_L.setSpeed(M0 + PID, MOT_PWM);
}
