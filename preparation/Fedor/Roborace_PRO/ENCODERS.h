#pragma once

bool LST,LST2,LST3,LST4,CST,CST2,CST4,CST3;
long int Encoder_Right,Encoder_Left;

void enc(){
  if (LST!=CST2) Encoder_Left--;
  else Encoder_Left++;
  LST = CST;
  LST2 = CST2;
}
void enc2() {
  if (LST3==CST4) Encoder_Right--;
  else Encoder_Right++;
  LST3 = CST3;
  LST4 = CST4;
}
void test_1() {
  CST4 = (!LST4);
  enc2();
}
void test_2() {
  CST3 = (!LST3);
  enc2();
}
void test_3() {
  CST2 = (!LST2);
  enc();
}
void test_4() {
  CST = (!LST);
  enc();
}
