#include <Wire.h>
#include <iarduino_HC_SR04.h>
#include <iarduino_I2C_Motor.h>
#include <iarduino_I2C_Bumper.h>
iarduino_I2C_Bumper bum(0x0C);
iarduino_I2C_Motor mot_R(0x0A);
iarduino_I2C_Motor mot_L(0x0B);
iarduino_HC_SR04 hcsr(12, 11);
void setup() {
  bum.begin();
  mot_L.begin();
  mot_R.begin();
  mot_L.setDirection(false);
  mot_R.setDirection(true);
}
unsigned long int f = 1, s = 0;
void loop() {
  if (hcsr.distance() > 40) {
    mot_L.setSpeed( 100, MOT_PWM);
    mot_R.setSpeed(-100, MOT_PWM);
    f = 0;
  }
  else {
    if (f == 0) {
      mot_L.setSpeed( 40, MOT_PWM);
      mot_R.setSpeed(-40, MOT_PWM);
      delay(175);
      f = 1;
    }
    mot_L.setSpeed(0, MOT_PWM);
    mot_R.setSpeed(0, MOT_PWM);
    delay(100);
    s = millis();
    while ((bum.getLineDigital(1) == 1 || bum.getLineDigital(2) == 1 || bum.getLineDigital(3) == 1 || bum.getLineDigital(4) == 1 || bum.getLineDigital(5) == 1 || bum.getLineDigital(6) == 1 || bum.getLineDigital(7) == 1 || bum.getLineDigital(8) == 1 || bum.getLineDigital(9) == 1) || millis() - s < 1000) {
      mot_L.setSpeed(100, MOT_PWM);
      mot_R.setSpeed(100, MOT_PWM);
    }
    mot_L.setSpeed(100, MOT_PWM);
    mot_R.setSpeed(100, MOT_PWM);
    delay(20);
    mot_L.setSpeed(-100, MOT_PWM);
    mot_R.setSpeed(-100, MOT_PWM);
    delay((millis() - s) + 20);
    mot_L.setSpeed( 40, MOT_PWM);
    mot_R.setSpeed(-40, MOT_PWM);
    delay(200);
  }
}
