#include "ROBOT.h"

Robot robot;

/*
int color = 0;

//bool point[3] = {1,1,1};
int COUNTER = 1;
int OBJECT = 0;
int BOX = 0;*/

int case_color[2][3] = {{3,0,1},
                        {4,5,2}};
int work_line = 0; 

void setup() {
  Serial.begin(9600);
  robot.setup();
  robot_main();
  //robot.new_take();
  //robot.forward_millis(3500);
  //robot.arm_mega_drop();
}

void robot_main() {
  /*robot.PID_do_perecresta();
  robot.forward_millis(300);*/
  while (work_line<3) work();
  //robot.PID_do_perecresta();
  //find_object();
  //new_take();
}

void work() {
  robot.PID_do_perecresta();
  if (!find_object()) {
    work_line++;
    if (work_line>=3) return;
    
    robot.PID_do_perecresta(1);
    robot.turn_right_perecrestok();
    robot.PID_do_perecresta(1);
    robot.turn_right_perecrestok();
  }
  else {
    robot.PID_do_perecresta(1);
    robot.PID_do_perecresta(1);
    robot.PID_do_perecresta(1);

    int move_x = 0;
    bool z = 0;
    for (int i = 0; i<3; i++) {
      bool up = case_color[0][i]==robot.color;
      bool down = case_color[1][i]==robot.color;
      if (up||down) {
        z = up;
        move_x = i-work_line;
        break;
      }
    }

    if      (move_x>0) robot.turn_right_perecrestok();
    else if (move_x<0) robot.turn_left_perecrestok();
    for (int i = 0; i<abs(move_x); i++) robot.PID_do_perecresta(1);
    if      (move_x>0) robot.turn_left_perecrestok();
    else if (move_x<0) robot.turn_right_perecrestok();
    
    if (z) {
      //robot.forward_millis(3250);
      robot.forward_millis(3500);
      robot.arm_mega_drop();
    }
    else {
      //robot.forward_millis(1750);
      robot.forward_millis(2000);
      robot.arm_drop();
    }

    robot.motor(-MOTOR_SPEED,MOTOR_SPEED);
    delay(700);
    robot.turn_left_perecrestok();
    robot.PID_do_perecresta(1);
    
    if      (move_x>0) robot.turn_right_perecrestok();
    else if (move_x<0) robot.turn_left_perecrestok();
    for (int i = 0; i<abs(move_x); i++) robot.PID_do_perecresta(1);
    if      (move_x>0) robot.turn_left_perecrestok();
    else if (move_x<0) robot.turn_right_perecrestok();
    
    robot.PID_do_perecresta(1);
    robot.PID_do_perecresta(1);
    delay(1000);
    
  }
}

bool find_object() {
  bool f = 1;
  if (robot.get_distanse()<i_see_object) eat(300);
  else if (robot.turn_right_millis(600)) eat(500);
  else if (robot.turn_left_millis(1200)) eat(600);
  else f = 0;
  robot.turn_left_perecrestok();
  robot.turn_left_perecrestok();
  return f;
}

void eat(int t) {
  /*int a = 320;
  robot.forward_millis(t);
  color = robot.get_color();
  robot.backward_millis(a);
  robot.arm_take();
  if (t-a>=0) robot.backward_millis(t-a);
  else robot.forward_millis(a-t);*/
  robot.new_take();
  robot.backward_millis(500);
}

void loop() {
  Serial.println(robot.color);
}
