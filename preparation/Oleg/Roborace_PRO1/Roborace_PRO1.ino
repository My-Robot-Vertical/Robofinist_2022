#include "Roborace.h"

void setup() {
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
int max1, max2, min1, min2, sr1.1, sr2.1, sr1.2, sr2.2;
void loop() {
  max1 = max1 < robot.get_IK_left () ? robot.get_IK_left() : max1;
  max2 = max2 < robot.get_IK_right() ? robot.get_IK_left() : max2;
  min1 = min1 > robot.get_IK_left () ? robot.get_IK_left() : min1;
  min2 = min2 > robot.get_IK_right() ? robot.get_IK_left() : min2;
  sr1.1 = (max1 + min1) / 2;
  sr2.1 = (max2 + min2) / 2;
  sr1.2 = map(robot.get_IK_left (), max1, min1, 0, 1023);
  sr2.2 = map(robot.get_IK_left (), max2, min2, 0, 1023);
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
    li();
  }
  if (c == 4) {
    robot.motors(0, 0);
  }
}
void li() {

}
