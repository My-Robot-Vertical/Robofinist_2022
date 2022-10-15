#include <Trackduino.h>

#define PIN_TRIG IN1
#define PIN_ECHO IN2
#define PIN_TRIG2 IN3
#define PIN_ECHO2 IN4
#define ras 3
#define MO 25

void setup() {
Trackduino.setup();
Serial.begin(9600);
pinMode(PIN_TRIG, OUTPUT);
pinMode(PIN_ECHO, INPUT);
pinMode(PIN_TRIG2, OUTPUT);
pinMode(PIN_ECHO2, INPUT);
Ser_UltraZ();
}
void loop(){
  logic();
  Serial.println(lor());
  Serial.println(lof());
}
void logic(){
 if(lof()>5){
  P_UltraR();
  }
  else{
    if(lor()>5){
      P_UltraR();
    }
    else{
      left();
    }
  }
}
int UltraZ(){
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  return pulseIn(PIN_ECHO, HIGH) / 59.2;
}
int UltraR(){
  digitalWrite(PIN_TRIG2, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG2, LOW);
  return pulseIn(PIN_ECHO2, HIGH) / 59.2;
}
int lof(){
  int f=0;
  for(int i=0;i<3;i++){
    f+=UltraZ();
  }
  f/=3;
  return f;
}
int lor(){
  int r=0;
  for(int i=0;i<3;i++){
    r+=UltraZ();
  }
  r/=3;
  return r;
}
void Ser_UltraZ(){
  for(int i=0;i<30;i++){
    UltraZ();
    UltraR();
  }
}
void motors(long int M1,long int M2){
   Trackduino.motor(1,constrain(M1,20,100));
   Trackduino.motor(2,constrain(M2,20,100));
}
void P_UltraR(){
  int R = (UltraR()-ras);
  motors(MO+R,MO-R);
}
void left(){
  Trackduino.motor(1,-40);
  Trackduino.motor(2,40);
  delay(500);
}
