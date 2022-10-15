#pragma once

#define PIN_TRIG 3
#define PIN_ECHO 4

/*if (abs(enc+enc2)>10000) {
    Trackduino.RGB_purple(); 
    while(1);
  }*/


#define IK_sensor_quantity 2
const int IK_sensor_pin[IK_sensor_quantity] = {A9,A8};
const int IK_sensor_min[IK_sensor_quantity] = {530,350};
const int IK_sensor_max[IK_sensor_quantity] = {985,940};

int IK_sensor_read(int number) {
  number--;
  return constrain(map(analogRead(IK_sensor_pin[number]),IK_sensor_min[number],IK_sensor_max[number],0,100),0,100);
}

int get_IK_error() {
  return IK_sensor_read(1) -  IK_sensor_read(2);
}
 
void setip_device() {
  /*pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(IN5, INPUT);
  pinMode(IN6, INPUT);*/
}

int UltraZ()
{
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  return pulseIn(PIN_ECHO, HIGH) / 59.2;
}
