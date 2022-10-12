#pragma once

#define PIN_TRIG 6
#define PIN_ECHO 7
#define PIN_TRIG2 3
#define PIN_ECHO2 5
#define ff 5

int massR[ff];
int massRS[ff];
int massF[ff];
int massFS[ff];
int massB[ff];
int massBS[ff];
int massW[ff];
int massWS[ff];

int UltraF() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  return pulseIn(PIN_ECHO, HIGH) / 59.2;
}
int UltraR() {
  digitalWrite(PIN_TRIG2, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG2, LOW);
  return pulseIn(PIN_ECHO2, HIGH) / 59.2;
}
int distR() {
  for (int i = 0; i < ff - 1; i++) {
    massR[i] = massR[i + 1];
  }
  massR[ff - 1] = UltraR();
  for (int i = 0; i < ff; i++) {
    massRS[i] = massR[i];
  }
  for (int j = 0; j < ff; j++) {
    for (int i = 0; i < ff - 1; i++) {
      if (massRS[i] > massRS[i + 1]) {
        int temp = massRS[i];
        massRS[i] = massRS[i + 1];
        massRS[i + 1] = temp;
      }
    }
  }
  return massRS[(ff - 1) / 2];
}
int distF() {
  for (int i = 0; i < ff - 1; i++) {
    massF[i] = massF[i + 1];
  }
  massF[ff - 1] = UltraF();
  for (int i = 0; i < ff; i++) {
    massFS[i] = massF[i];
  }
  for (int j = 0; j < ff; j++) {
    for (int i = 0; i < ff - 1; i++) {
      if (massFS[i] > massFS[i + 1]) {
        int temp = massFS[i];
        massFS[i] = massFS[i + 1];
        massFS[i + 1] = temp;
      }
    }
  }
  return massFS[(ff - 1) / 2];
}
int WBDR() {
  for (int i = 0; i < ff - 1; i++) {
    massW[i] = massW[i + 1];
  }
  massW[ff - 1] = analogRead(1);
  for (int i = 0; i < ff; i++) {
    massWS[i] = massW[i];
  }
  for (int j = 0; j < ff; j++) {
    for (int i = 0; i < ff - 1; i++) {
      if (massWS[i] > massWS[i + 1]) {
        int temp = massWS[i];
        massWS[i] = massWS[i + 1];
        massWS[i + 1] = temp;
      }
    }
  }
  return massWS[(ff - 1) / 2];
}
int WBDL() {
  for (int i = 0; i < ff - 1; i++) {
    massB[i] = massB[i + 1];
  }
  massB[ff - 1] = analogRead(1);
  for (int i = 0; i < ff; i++) {
    massBS[i] = massB[i];
  }
  for (int j = 0; j < ff; j++) {
    for (int i = 0; i < ff - 1; i++) {
      if (massBS[i] > massBS[i + 1]) {
        int temp = massBS[i];
        massBS[i] = massBS[i + 1];
        massBS[i + 1] = temp;
      }
    }
  }
  return massBS[(ff - 1) / 2];
}
