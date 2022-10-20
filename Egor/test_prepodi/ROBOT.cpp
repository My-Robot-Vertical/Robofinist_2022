
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
  Robot::servo_arm_run(SERVO_ARM_DOWN,SERVO_ARM_UP);//*/
  //servo_arm.write(SERVO_ARM_DOWN);
  //delay(2000);
  //servo_arm.write(SERVO_ARM_UP);
}

Robot::arm_drop() {
  Robot::servo_arm_run(SERVO_ARM_UP,SERVO_ARM_DOWN);
  Robot::servo_finger_run(SERVO_FINGER_TAKE,SERVO_FINGER_DROP);
  Robot::servo_arm_run(SERVO_ARM_DOWN,SERVO_ARM_UP);
  Robot::servo_finger_run(SERVO_FINGER_DROP,SERVO_FINGER_TAKE);
}

Robot::arm_mega_drop() {
  Robot::servo_arm_run(SERVO_ARM_UP,SERVO_ARM_MEGA_DOWN);
  Robot::servo_finger_run(SERVO_FINGER_TAKE,SERVO_FINGER_DROP);
  Robot::backward_millis(1000);
  Robot::servo_arm_run(SERVO_ARM_MEGA_DOWN,SERVO_ARM_UP);
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
  analogWrite(PWM_1,map(constrain(abs(left),0,100),0,100,0,250));
  digitalWrite(DIR_2,right>0);
  analogWrite(PWM_2,map(constrain(abs(right),0,100),0,100,0,250));
}

Robot::get_color() {
  // https://robotchip.ru/obzor-datchik-tsveta-na-tcs3472/
  // example Adafruit_TCS34725.h/tcs34725
  
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  if (1) {
    Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");
  }

  if (r+g+b<1000) return 0; // black 
  else if (r>800 && g>800) {
    if (b>800) return 1; // white
    else return 2; // yellow 
  }
  else if (g>r && g>b) return 3; // green
  else if (r>g && r>b) return 4; // red
  else return 5; // blue 
  /*
   * R: 759 G: 2005 B: 1253 - green
   * R: 1617 G: 2241 B: 1900 - white +
   * R: 257 G: 297 B: 242 - black +
   * R: 2292 G: 2784 B: 987 - yellow + 
   * R: 318 G: 653 B: 863 - blue
   * R: 1035 G: 410 B: 354 - red
   * */
}

Robot::get_distanse() {
  // https://github.com/Ni3nayka/sketch/blob/main/arduino/исходники/distanse_IK/distanse_IK.ino
  int T = 10, sum = 0;
  for (int i = 0; i<T; i++) sum += analogRead(SENSOR_DISTANSE);
  sum /= T;
  sum = 32*pow(sum*0.0048828125, -1.10); 
  //if (sum>100) return 100;
  return sum;
}

Robot::PID() {
  int e = analogRead(SENSOR_IK_L) - analogRead(SENSOR_IK_R);
  e /= 10;
  int M = MOTOR_SPEED;
  Robot::motor(M-e,M+e);
}

Robot::PID_do_perecresta(bool f=0) {
  while (analogRead(SENSOR_IK_R)<400||analogRead(SENSOR_IK_L)<400) Robot::PID();
  //Robot::motor(MOTOR_SPEED,MOTOR_SPEED);
  //while (analogRead(SENSOR_IK_R)>400&&analogRead(SENSOR_IK_L)>400) Robot::PID();
  if (f) Robot::PID_millis(1000);
  else Robot::forward_millis(1000);
}

Robot::PID_millis( long int d) {
  for (unsigned long int t = millis(); t+d>millis();) {
    Robot::PID();
  }
  Robot::stop_motor();
}

Robot::forward_millis( long int d) {
  Robot::motor(MOTOR_SPEED,MOTOR_SPEED);
  delay(d);
  Robot::stop_motor();
}

Robot::backward_millis( long int d) {
  Robot::motor(-MOTOR_SPEED,-MOTOR_SPEED);
  delay(d);
  Robot::motor(MOTOR_SPEED,MOTOR_SPEED);
  delay(50);
  Robot::motor(0,0);
}

Robot::stop_motor() {
  Robot::motor(-MOTOR_SPEED,-MOTOR_SPEED);
  delay(50);
  Robot::motor(0,0);
}

Robot::turn_left_perecrestok() {
  Robot::motor(-MOTOR_SPEED,MOTOR_SPEED);
  while (analogRead(SENSOR_IK_L)>400);
  delay(50);
  while (analogRead(SENSOR_IK_L)<400);
  delay(50);
  while (analogRead(SENSOR_IK_L)>400);
  delay(100);
  Robot::motor(MOTOR_SPEED,-MOTOR_SPEED);
  delay(50);
  Robot::motor(0,0);
}

Robot::turn_right_perecrestok() {
  Robot::motor(MOTOR_SPEED,-MOTOR_SPEED);
  while (analogRead(SENSOR_IK_R)>400);
  delay(50);
  while (analogRead(SENSOR_IK_R)<400);
  delay(50);
  while (analogRead(SENSOR_IK_R)>400);
  delay(100);
  Robot::motor(-MOTOR_SPEED,MOTOR_SPEED);
  delay(50);
  Robot::motor(0,0);
}

Robot::turn_left_millis( long int d) {
  Robot::motor(-MOTOR_SPEED,MOTOR_SPEED);
  bool flag = 0;
  for (unsigned long int t = millis(); t+d>millis() && !flag;) {
    if (Robot::get_distanse()<i_see_object) flag = 1;
  }
  Robot::motor(MOTOR_SPEED,-MOTOR_SPEED);
  delay(50);
  Robot::motor(0,0);
  return flag;
}

Robot::turn_right_millis( long int d) {
  Robot::motor(MOTOR_SPEED,-MOTOR_SPEED);
  bool flag = 0;
  for (unsigned long int t = millis(); t+d>millis() && !flag;) {
    if (Robot::get_distanse()<i_see_object){
      flag = 1;
      delay(100);
    }
  }
  Robot::motor(-MOTOR_SPEED,MOTOR_SPEED);
  delay(50);
  Robot::motor(0,0);
  return flag;
}
