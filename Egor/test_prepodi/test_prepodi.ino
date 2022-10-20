#include "ROBOT.h"

Robot robot;

int color = 0;

//bool point[3] = {1,1,1};
int COUNTER = 1;
int OBJECT = 0;
int BOX = 0;

void setup() {
  Serial.begin(9600);
  robot.setup();
  robot.PID_do_perecresta();
  robot.forward_millis(300);
  while (COUNTER<=3 && OBJECT<6) work();
}

void work() {
  if (!find_object()) {
    COUNTER++;
    if (COUNTER>3) return;
    /*robot.PID_do_perecresta();
    
    //robot.turn_right_millis(1400);
    robot.motor(MOTOR_SPEED,-MOTOR_SPEED);
    delay(1400);
    robot.motor(-MOTOR_SPEED,MOTOR_SPEED);
    delay(50);
    robot.motor(0,0);*/
    robot.turn_left_perecrestok();
    robot.PID_do_perecresta(1);
    robot.turn_right_perecrestok();
    robot.PID_do_perecresta(1);
    robot.turn_right_perecrestok();
    robot.PID_do_perecresta(1);
    robot.forward_millis(300);
    BOX = 0;
  }
  else {
    OBJECT++;
    robot.turn_left_perecrestok();
    robot.PID_do_perecresta(1);
    robot.PID_do_perecresta(1);
    robot.PID_do_perecresta(1);
    
    if (BOX==0) {
      robot.forward_millis(3500);
      robot.arm_mega_drop();
    }
    else {
      robot.forward_millis(2000);
      robot.arm_drop();
    }
    BOX = 1;
    
    robot.turn_left_perecrestok();
    robot.PID_do_perecresta(1);
    robot.PID_do_perecresta(1);
    robot.PID_do_perecresta(1);
    robot.PID_do_perecresta();
    robot.forward_millis(300);
    
  }
}

bool find_object() {
  bool f = 1;
  if (robot.get_distanse()<i_see_object) eat(300);
  else if (robot.turn_right_millis(700)) eat(500);
  else if (robot.turn_left_millis(1500)) eat(600);
  else f = 0;
  robot.turn_left_perecrestok();
  return f;
}

void eat(int t) {
  int a = 320;
  robot.forward_millis(t);
  color = robot.get_color();
  robot.backward_millis(a);
  robot.arm_take();
  if (t-a>=0) robot.backward_millis(t-a);
  else robot.forward_millis(a-t);
}




void loop() {
  /*robot.arm_take();
  delay(1000);
  robot.arm_drop();
  delay(1000);*/
  //robot.motor(100,100);
  //delay(1000);
  //robot.motor(100,100);
  //robot.motor(0,0);
  //robot.arm_take();
  //robot.PID_do_perecresta();
  /*robot.turn_left_perecrestok();
  robot.PID_do_perecresta();
  robot.turn_right_perecrestok();
  robot.PID_do_perecresta();*/
  //Serial.println(M+e);
  //Serial.println(robot.get_color());
}
