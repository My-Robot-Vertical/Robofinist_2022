#include <Trackduino.h>
#define PIN_TRIG IN1
#define PIN_ECHO IN2
int dr,dl,MO=25;
void setup(){
  Trackduino.setup();
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(IN5, INPUT);
  pinMode(IN6, INPUT);
  Ser_UltraZ();
}
void loop(){
  black_line();
}
void motors(long int M1,long int M2){
   Trackduino.motor(1,constrain(M1,-20,100));
   Trackduino.motor(2,constrain(M2,-20,100));
}
void in(){
  dr=analogRead(IN5);
  dl=analogRead(IN6);
}
void P(float k){
  in();
  long int E = k*(dr-dl);
  E=E*E*E;
  if(E>0){motors(MO-E,MO);}else{motors(MO,MO+E);}
}
void black_line(){
  while(lol()>30){
    P(0.4);
  }
  OBESD();
  P(0.5);
}
  void OBESD(){
  motors(10,40);
  delay(400);
  motors(30,30);
  delay(400);
  motors(40,10);
  delay(500);
  motors(40,10);
  delay(300);
  motors(30,30);
  delay(200);
}
int UltraZ(){
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  return pulseIn(PIN_ECHO, HIGH) / 59.2;
}
void Ser_UltraZ(){
  for(int i=0;i<30;i++){
    UltraZ();
    Serial.println(UltraZ());
  }
}
int lol(){
  int p=0;
  for(int i=0;i<3;i++){
    p+=UltraZ();
  }
  p/=3;
  Serial.println(p);
  return p;
}
