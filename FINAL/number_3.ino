int number_3_cout = 0;

bool number_3_flag = 0;

unsigned long int number_3_time;

void number_3_1() {
  
}

void number_3_2() {
  
}
void number_3_loop1() {
  number_3_P();
}
int number_3_ik_dat(int d) {
  return bum.getLineAnalog(d);
}
void number_3_P() {
  float k = 0.05;
  int MO = 50;
  int E;
  bool d;
  if (number_3_ik_dat(3) < 1000 && number_3_ik_dat(7) < 1000) {
    d = 0;
    if(!number_3_flag){
      number_3_cout++;
      number_3_flag=1;
    }
    else{
      number_3_flag=1;
    }
  }
  else {
    number_3_flag=0;
    d = 1;
  }
  if (d) {
    E = number_3_ik_dat(4) - number_3_ik_dat(6);
  }
  else {
    E = number_3_ik_dat(6) - number_3_ik_dat(4);
  }
  motor( MO + E * k , MO - E * k);
}
