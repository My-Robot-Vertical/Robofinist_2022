int number_1_cout = 0;

bool number_1_flag = 0;

unsigned long int number_1_time;

void number_1_1() {
  motor(30,30);
  delay(1000);
  number_1_loop1();
}
void number_1_2() {
  while(number_1_ik_dat(2)>2000&&number_1_ik_dat(8)>2000){
    number_1_P();
  }
  motor(40,40);
  delay(700);
  number_1_time = millis();
  number_1_loop1();
}
void number_1_loop1() {
  while (1) {
    if (!number_1_cout) {
      number_1_P();
      if(UZ_front.distance()<20&&number_1_time+4000<millis()){
        if(UZ_front.distance()>16){
          number_1_obyesd(); 
        }
        else{
          motor(-30,-30);
          delay(1500);
          motor(30,30);
          delay(1500);
          motor(0,0);
          delay(2000);
        }
      }
    }
    else {
      //number_1_P();
      motor(30,30);
      break;
    }
  }
  while (number_1_ik_dat(7) > 1000) {
    motor(10,30);
  }
  number_1_time = millis();
  while (number_1_time+1300 > millis()) {
    number_1_P();
  }
  motor(0,0);
}
int number_1_ik_dat(int d) {
  return bum.getLineAnalog(d);
}
void number_1_P() {
  double k = 0.01;
  int MO = 50;
  int E;
  int E1;
  if (number_1_ik_dat(3) < 2000 && number_1_ik_dat(7) < 2000) {
    number_1_cout = 1;
  }
  E1 = number_1_ik_dat(3) - number_1_ik_dat(7);
  E = number_1_ik_dat(4) - number_1_ik_dat(6);
  motor( MO + E * k + E1 * k , MO - E * k - E1 * k);
}
void number_1_obyesd(){
  motor(60,10);
  delay(700);
  motor(50,50);
  delay(800);
  motor(10,60);
  delay(700);
  motor(50,50);
  delay(700);
  motor(10,60);
  delay(700);
  motor(50,50);
  delay(800);
  while (number_1_ik_dat(4) > 1000) {
    motor(60,10);
  }
}
