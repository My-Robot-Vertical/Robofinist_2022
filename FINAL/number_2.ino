#include  "easy_arduino_navigator.h"
Navigator navigator(RIGHT_ARM_RULE);
#define ud servo_arm
#define arm servo_finger
#define front UZ_front
#define right1 UZ_right
float number_2_kd = 1;
int number_2_s = 1125;
int number_2_gf = 5000;
int number_2_d = 30;
int number_2_r = 13;
int number_2_f = 0;
void number_2_1() {
  navigator.set_start(0, 0, NAVIGATOR_DIR_E);
  navigator.set_finish(4, 4, NAVIGATOR_DIR_E);
  while (1) {
    number_2_move1((front.distance() < number_2_d), (right1.distance() < number_2_d));
    if (number_2_f == 1)break;
  }
}

void number_2_2() {
}
void number_2_move1(bool forward_wall, bool side_wall) {
  int number_2_t = navigator.next_move(forward_wall, side_wall);
  if (number_2_t == NAVIGATOR_END) {
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    number_2_f = 1;
  }
  if (number_2_t == NAVIGATOR_MOVE_FORWARD) {
    unsigned long int number_2_ss = millis();
    int number_2_U, number_2_d1[3] = {number_2_r, number_2_r, number_2_r}, number_2_d2;
    while (millis() - number_2_ss < number_2_gf) {
      number_2_d2 = right1.distance();
      if (number_2_d2 < number_2_r + 5) {
        number_2_d1[0] = number_2_d1[1];
        number_2_d1[1] = number_2_d1[2];
        number_2_d1[2] = right1.distance();
        number_2_d2 = (number_2_d1[0] + number_2_d1[1] + number_2_d1[2]) / 3;
        number_2_U = (number_2_r - right1.distance()) * number_2_kd;
        mot_R.setSpeed(40 + number_2_U, MOT_PWM);
        mot_L.setSpeed(40 - number_2_U, MOT_PWM);
      }
      else {
        mot_R.setSpeed(40, MOT_PWM);
        mot_L.setSpeed(40, MOT_PWM);
      }
    }
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    delay(number_2_s);
  }
  if (number_2_t == NAVIGATOR_MOVE_LEFT) {
    mot_R.setSpeed( 40, MOT_PWM);
    mot_L.setSpeed(-40, MOT_PWM);
    delay(number_2_s);
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    delay(number_2_s);
  }
  if (number_2_t == NAVIGATOR_MOVE_RIGHT) {
    mot_R.setSpeed(-40, MOT_PWM);
    mot_L.setSpeed( 40, MOT_PWM);
    delay(number_2_s);
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    delay(number_2_s);
  }
  if (number_2_t == NAVIGATOR_MOVE_LEFT_AND_FORWARD) {
    mot_R.setSpeed( 40, MOT_PWM);
    mot_L.setSpeed(-40, MOT_PWM);
    delay(number_2_s);
    mot_R.setSpeed(40, MOT_PWM);
    mot_L.setSpeed(40, MOT_PWM);
    delay(number_2_gf);
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    delay(number_2_s);
  }
  if (number_2_t == NAVIGATOR_MOVE_RIGHT_AND_FORWARD) {
    mot_R.setSpeed(-40, MOT_PWM);
    mot_L.setSpeed( 40, MOT_PWM);
    delay(number_2_s);
    mot_R.setSpeed(40, MOT_PWM);
    mot_L.setSpeed(40, MOT_PWM);
    delay(number_2_gf);
    mot_R.setSpeed(0, MOT_PWM);
    mot_L.setSpeed(0, MOT_PWM);
    delay(number_2_s);
  }
}
