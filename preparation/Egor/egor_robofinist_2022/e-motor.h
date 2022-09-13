#pragma once

#include "encoder.h"
#include "motor.h"

#define Hz_in_cm_enc (-140)
#define Hz_in_gradus_enc (-23)
#define enc_end_move_porog 10
#define motor_move_enc_K (-0.4)
#define stabiling_robot_time 1000


void motors_P_move() {
  while(abs(enc_L)>enc_end_move_porog && abs(enc_R)>enc_end_move_porog) {
    motors(enc_L*motor_move_enc_K,enc_R*motor_move_enc_K);
    print_enc();
  }
  unsigned long int time = millis();
  while(time+stabiling_robot_time>millis()) {
    motors(enc_L*motor_move_enc_K,enc_R*motor_move_enc_K);
    print_enc();
  }
  motors(0,0);
}

void robot_turn(int gradus) {
  enc_L = Hz_in_gradus_enc*(-gradus);
  enc_R = Hz_in_gradus_enc*gradus;
  motors_P_move();
}

void robot_run(int cm) {
  enc_L = Hz_in_cm_enc*cm;
  enc_R = Hz_in_cm_enc*cm;
  motors_P_move();
}
