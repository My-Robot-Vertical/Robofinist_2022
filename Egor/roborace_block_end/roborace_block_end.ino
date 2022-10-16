#include <Wire.h>
#include <iarduino_I2C_Motor.h>
iarduino_I2C_Motor mot_R (0x0A);
iarduino_I2C_Motor mot_L (0x0B);

#define motor_speed 50
#define run_time 5000
#define stop_time 100

void setup() {
  mot_L.begin();
  mot_R.begin();
  mot_L.setDirection(false);
  mot_R.setDirection(true);
  delay(500);
}

void loop() {
  for (int i=-1; i<=1; i+=2) {
    motor(motor_speed*i);
    delay(run_time);
    motor(0);
    delay(stop_time);
  }
}

void motor(int M){
  mot_L.setSpeed(M,MOT_PWM);
  mot_R.setSpeed(M,MOT_PWM);
}
