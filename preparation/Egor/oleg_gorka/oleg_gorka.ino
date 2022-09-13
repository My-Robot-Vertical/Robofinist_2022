#include <Wire.h>               

#include <iarduino_I2C_Motor.h>   
iarduino_I2C_Motor mot_R(0x0A);     
iarduino_I2C_Motor mot_L(0x0B);   

#include <iarduino_I2C_Bumper.h>
iarduino_I2C_Bumper bum(0x0C);  

#define basic_speed 50
#define K_PID 10

#define test_perekrestok (bum.getLineAnalog(1)<1000&&bum.getLineAnalog(9)<1000)
                                                 
void setup(){       
  delay(500); 
  Serial.begin(9600);
  mot_R.begin();
  mot_L.begin();
  bum.begin();

  mot_R.setDirection(true);
  mot_L.setDirection(false);
  stop_motor();

  forward(2000);
  delay(1000);
  forward_perekrestok();
  delay(1000);
  forward(2000);
}

void PID() {
  int e = bum.getErrPID() * K_PID;
  mot_R.setSpeed( basic_speed - e, MOT_PWM);
  mot_L.setSpeed( basic_speed + e, MOT_PWM);
}

void forward_perekrestok() {
  while(test_perekrestok) {
    PID();
  }
  stop_motor();
}

void forward(int t) {
  unsigned long int time = millis();
  while(time+t>millis()) {
    mot_R.setSpeed(basic_speed, MOT_PWM);
    mot_L.setSpeed(basic_speed, MOT_PWM);
  }
  stop_motor();
}

void forward_PID(int t) {
  unsigned long int time = millis();
  while(time+t>millis()) {
    PID();
  }
  stop_motor();
}

void stop_motor() {
  mot_R.setSpeed( 0, MOT_PWM);
  mot_L.setSpeed( 0, MOT_PWM);
}

void loop(){ 
  Serial.println(test_perekrestok);
}
