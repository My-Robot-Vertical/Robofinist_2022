#include "e-motor.h"
#include "device.h"

void setup() { 
  Serial.begin(9600);
  setup_attachInterrupt();
  setup_motor();

  //robot_run(10);
  //robot_turn(90);
  //robot_run(70);
  //robot_turn(-360);
}
void loop() { 
  //print_enc();
  //Serial.println(IK_sensor_read(2));
  int e = get_IK_error();
  motors(50+e,50-e);
}
