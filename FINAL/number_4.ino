void number_4() {
  arm.attach(3);
  ud.attach(9);
  for (int number_4_i = 180; number_4_i > 100; number_4_i--) {
    arm.write(number_4_i);
    delay(500 / 80);
  }
  delay(1000);
  for (int number_4_i = 40; number_4_i < 120; number_4_i++) {
    ud.write(number_4_i);
    delay(500 / 80);
  }
  delay(1000);
  for (int number_4_i = 100; number_4_i < 170; number_4_i++) {
    arm.write(number_4_i);
    delay(500 / 70);
  }
  delay(1000);
  for (int number_4_i = 120; number_4_i > 40; number_4_i--) {
    ud.write(number_4_i);
    delay(500 / 80);
  }
  delay(1000);
  while (1)arm.write(170);
  ud.detach();
}
