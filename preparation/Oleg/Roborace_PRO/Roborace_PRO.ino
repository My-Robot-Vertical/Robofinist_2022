#include "Roborace.h"

void setup(){
  Serial.begin(9600);
  setup_robot();
}
int c = 1;
int r = 10;
const int kol = 100;
int l[kol] = {0};
int n[kol] = {0};
int np = 0;
int I = 0;
void loop() {
  if (c == 1) {
    /*while (bum.getErrPID() != 0) {
      robot.motors(10, 10);
    }*/
    c = 2;
  }
  if (c == 2) {
    c = 3;
  }
  if (c == 3) {
    robot.run(10);
    lb();
  }
  if (c == 4) {
    robot.motors(0, 0);
  }
}
void lb() {
  if (robot.get_UZ_forward(r)) {
    if (robot.get_UZ_right(r)) {
      robot.turn(90);
      l[I] = 1;
      n[I] = np + 1;
      np = n[I];
    }
    if (robot.get_UZ_right(r)) {
      robot.run(r);
      l[I] = 2;
    }
  }
  else {
    if (robot.get_UZ_right(r)) {
      robot.turn(90);
      l[I] = 3;
      n[I] = np + 1;
      np = n[I];
    }
    if (robot.get_UZ_right(r)) {
      robot.turn(-90);
      l[I] = 4;
      n[I] = np - 1;
      np = n[I];
    }
  }
  I++;
}
