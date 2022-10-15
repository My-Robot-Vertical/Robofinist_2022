#pragma once

#include <Servo.h>
Servo Aservo;
Servo Fservo;

void servo(bool i,int servo,int base) {
  if (i) {
    for(int z = base; z!=servo; z+0){
      if(servo>base){z++;}else{z--;};
      Aservo.write(z); 
      delay(30);
    }
  }
  else {
    for(int z = base;z!=servo;z+0){
      if(servo>base){z++;}else{z--;};
      Fservo.write(z);
      delay(30);
    }
  }
}
void take() {
  servo(1,90,180);
  servo(0,0,90);
  servo(1,180,90);
  servo(0,90,0);
}
void drop() {
  servo(0,0,90);
  servo(1,90,180);
  servo(0,90,0);
  servo(1,180,90);
}
