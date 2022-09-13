#include <Trackduino.h>

//#include <Serv>10){
#define PIN_TRIG IN1
#define PIN_ECHO IN2
#define PIN_TRIG2 IN3
#define PIN_ECHO2 IN4
#define Hz_in_cm_enc (-140)
#define Hz_in_gradus_enc (-23)
#define enc_end_move_porog 10
#define motor_move_enc_K (-0.4)//0.4
#define stabiling_robot_time 1000

long int enc = 0;
long int enc2 = 0;
bool LST,LST2,CST2,CST,LST3,LST4,CST4,CST3;
long int Mem,Mem2,MemEncRight,MemEncLeft;
int dr,dl,E,d1,d2,ras=7;
int MO = 25;

void setup() { 
  Trackduino.setup();
  Serial.begin(9600);
  while(Trackduino.BTN_right()==0);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG2, OUTPUT);
  pinMode(PIN_ECHO2, INPUT);
  pinMode(IN5, INPUT);
  pinMode(IN6, INPUT);
  //servo.attach(OUT1);
  attachInterrupt(4, test_3, CHANGE);
  attachInterrupt(5, test_4, CHANGE);
  attachInterrupt(2, test_1, CHANGE);
  attachInterrupt(3, test_2, CHANGE);
  LST=digitalRead(18);
  LST2=digitalRead(19);
  LST3=digitalRead(20);
  LST4=digitalRead(21);
  CST = LST;
  CST2 = LST2;
  CST3 = LST3;
  CST4 = LST4;
  //enc_back();
  //Ser_UltraZ();
  //OBESD();
  //Trackduino.stop_motor(1);
  //Trackduino.stop_motor(2);
}
void loop (){
  print_enc();
  in();
  black_line();
  MAP();
  //labirint();
  //if(abs(MemEncRight)<4400){kegly();}else{Trackduino.stop_motor(1);Trackduino.stop_motor(2);}
  /*Serial.print(dr);
  Serial.print("_______");
  Serial.println(dl);*/
}
void in(){
  dr=analogRead(IN5);
  dl=analogRead(IN6);
}
void test_3() {
  CST2 = (!LST2);
  qwerty();
}
void test_4() {
  CST = (!LST);
  qwerty();
}
void test_1() {
  CST4 = (!LST4);
  qwerty2();
}
void test_2() {
  CST3 = (!LST3);
  qwerty2();
}

void qwerty() {
  /*if (CST != LST && CST==1) {
    if(CST2 != CST) {
      enc--;
    }
    else {
      enc++;
    }
  }*/
  if (LST==CST2) enc++;
  else enc--;
  
  LST = CST;
  LST2 = CST2;
  if (abs(enc+enc2)>2000000) {
    Trackduino.RGB_purple();
    motors(0,0); 
    while(1);
  }
}
void qwerty2() {
  if (LST3==CST4) enc2--;
  else enc2++;
  LST3 = CST3;
  LST4 = CST4;
  if (abs(enc+enc2)>2000000) {
    Trackduino.RGB_purple();
    motors(0,0); 
    while(1);
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
void motors(long int M1,long int M2){
   Trackduino.motor(1,constrain(M1,-100,100));
   Trackduino.motor(2,constrain(M2*1.2,-100,100));
}
void kegly(){
  Serial.print(enc);
  Serial.println(enc2);
  if(UltraZ()>25)
  {
    motors(25,-25);
    if(abs(enc)>4400){MemEncRight=enc;return;}
  }
  else
  {
    MemEncRight=enc;
    MemEncLeft=enc2;
    enc-=enc;
    enc2-=enc2;
    Serial.print(enc);
    Serial.println(enc2);
    //robot_turn(enc);
    enc_back();
    while(UltraZ()<25)
    {
      motors(25,-25);
    }
    enc=MemEncRight;
    enc2=MemEncLeft;
   }
    /*if(abs(enc)>1000){Trackduino.RGB_white();}
    else if (abs(enc)>850){Trackduino.RGB_yellow();}
    else if (abs(enc)>700){Trackduino.RGB_turquoise();}
    else if (abs(enc)>500){Trackduino.RGB_purple();}
    else if (abs(enc)>400){Trackduino.RGB_blue();}
    else if (abs(enc)>200){Trackduino.RGB_green();}
    else if (abs(enc)>100){Trackduino.RGB_red();}*/
}
void rel(){
  E=(dr-dl);
  if(E<70){P(0.01);}else{P(0.1);}
}
void P(float k){
  in();
  long int E = k*(dr-dl);
  E=E*E*E;
  if(E>0){motors(constrain(MO-E,-20,100),MO);}else{motors(MO,constrain(MO+E,-20,100));}
}
void re(){ 
 if(dl<500){motors(0,40);}else{motors(40,0);}
}
void MAP(){
  d1 = map(dr,28,655,0,100);
  d2 = map(dl,24,485,0,100); 
}
void P_UltraZ(){
  int R = (UltraR()-ras);
  motors(MO+R,MO-R);
}
void labirint()
{
  if (UltraZ()<10){if(UltraR()>10){motors(25,10);}else{motors(-20,20);delay(1000);}}else{P_UltraZ();}
}
void print_enc(){
  Serial.print(enc2);
  Serial.print(" ");
  Serial.println(enc);
}
void motors_P_move() {
  while(abs(enc)>enc_end_move_porog && abs(enc2)>enc_end_move_porog) {
    motors(enc*motor_move_enc_K,enc2*motor_move_enc_K);
    print_enc();
  }
  unsigned long int time = millis();
  while(time+stabiling_robot_time>millis()) {
    motors(enc*motor_move_enc_K,enc*motor_move_enc_K);
    print_enc();
  }
  motors(0,0);
}
void robot_turn(int gradus) {
  enc = Hz_in_gradus_enc*(-gradus);
  enc2 = Hz_in_gradus_enc*gradus;
  motors_P_move();
}
void robot_run(int cm) {
  enc = Hz_in_cm_enc*cm;
  enc2 = Hz_in_cm_enc*cm;
  motors_P_move();
}
void enc_back(){
  while(dr<300){motors(25,25);print_enc();in();}
  print_enc();
  while(abs(enc)>30||abs(enc2)>30){motors(constrain(enc*(-1),-30,30),constrain(enc2*(-1),-28,30));print_enc();}
  motors(0,0);
}
void Ser_UltraZ(){
  for(int i=0;i<30;i++){
    UltraZ();
    Serial.println(UltraZ());
  }
}
void black_line(){
  while(UltraZ()>15){
    P(0.5);
    UltraZ();
  }
  OBESD();
  P(0.5);
}
  void OBESD(){
  motors(10,40/1.2);
  delay(300);
  motors(30,30/1.2);
  delay(300);
  motors(40,10/1.2);
  delay(300);
  motors(40,10/1.2);
  delay(300);
  motors(30,30/1.2);
  delay(300);
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
