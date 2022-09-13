#pragma once

long int enc_L = 0, enc_R = 0;
long int enc_L_save = 0, enc_R_save = 0;
bool enc_L_sensor_1_real,enc_L_sensor_2_real,enc_L_sensor_1_last,enc_L_sensor_2_last;
bool enc_R_sensor_1_real,enc_R_sensor_2_real,enc_R_sensor_1_last,enc_R_sensor_2_last;

void print_enc() {
  Serial.print(enc_L);
  Serial.print(" ");
  Serial.println(enc_R);
}

void enc_operating_L() {
  if (enc_L_sensor_2_real!=enc_L_sensor_1_last) enc_L++;
  else enc_L--;
  enc_L_sensor_1_last = enc_L_sensor_1_real;
  enc_L_sensor_2_last = enc_L_sensor_2_real;
}

void enc_operating_R() {
  if (enc_R_sensor_2_real!=enc_R_sensor_1_last) enc_R++;
  else enc_R--;
  enc_R_sensor_1_last = enc_R_sensor_1_real;
  enc_R_sensor_2_last = enc_R_sensor_2_real;
}

void attachInterrupt_L_1() {
  enc_L_sensor_1_real = (!enc_L_sensor_1_real);
  enc_operating_L();
}
void attachInterrupt_L_2() {
  enc_L_sensor_2_real = (!enc_L_sensor_2_real);
  enc_operating_L();
}
void attachInterrupt_R_1() {
  enc_R_sensor_1_real = (!enc_R_sensor_1_real);
  enc_operating_R();
}
void attachInterrupt_R_2() {
  enc_R_sensor_2_real = (!enc_R_sensor_2_real);
  enc_operating_R();
}

void setup_attachInterrupt() { 
  // I-t   0  1  2  3  4  5
  // pin   2  3 21 20 19 18
  attachInterrupt(2, attachInterrupt_L_1, CHANGE);
  attachInterrupt(3, attachInterrupt_L_2, CHANGE);
  attachInterrupt(4, attachInterrupt_R_1, CHANGE);
  attachInterrupt(5, attachInterrupt_R_2, CHANGE);
  enc_L_sensor_1_real = digitalRead(21);
  enc_L_sensor_2_real = digitalRead(20);
  enc_R_sensor_1_real = digitalRead(19);
  enc_R_sensor_2_real = digitalRead(18);
  enc_L_sensor_1_last = enc_L_sensor_1_real;
  enc_L_sensor_2_last = enc_L_sensor_2_real;
  enc_R_sensor_1_last = enc_R_sensor_1_real;
  enc_R_sensor_2_last = enc_R_sensor_2_real;
}
