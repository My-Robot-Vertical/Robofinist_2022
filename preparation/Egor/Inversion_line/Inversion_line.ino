#include <Wire.h>               

#include <iarduino_I2C_Motor.h>   
iarduino_I2C_Motor mot_R(0x0A);     
iarduino_I2C_Motor mot_L(0x0B);   

#include <iarduino_I2C_Bumper.h>
iarduino_I2C_Bumper bum(0x0C);  

int M = 50;

#define IK_K 0.04
#define porog_IK 500

void setup(){       
  delay(500); 
  Serial.begin(9600);
  mot_R.begin();
  mot_L.begin();
  bum.begin();

  mot_R.setDirection(true);
  mot_L.setDirection(false);
  
  mot_R.setSpeed( 0, MOT_PWM);
  mot_L.setSpeed( 0, MOT_PWM);

  inversia();
  
}
void loop() { 
  //Serial.println(getErrorPid(1));
}

void inversia() {
  bool black_kvadrat = 0;
  for (int i = 0; i<2; i++) {
    while (black_kvadrat && test_not_end_white_kvadrat() || !black_kvadrat && test_not_end_black_kvadrat()) {
      int e = getErrorPid(black_kvadrat);
      motor(M+e,M-e);
    }
    black_kvadrat = (!black_kvadrat);
  }
  motor(0,0);
}

bool test_not_end_black_kvadrat() {
  return bum.getLineAnalog(1)>porog_IK || bum.getLineAnalog(9)>porog_IK;
}

bool test_not_end_white_kvadrat() {
  return bum.getLineAnalog(1)<porog_IK || bum.getLineAnalog(9)<porog_IK;
}

int getErrorPid(bool black_kvadrat) { 
  return (int(bum.getLineAnalog(2)>>4) - int(bum.getLineAnalog(8)>>4))*(int(black_kvadrat)*2-1); //*IK_K;
}

void motor(int a, int b) {
  mot_R.setSpeed(a, MOT_PWM);
  mot_L.setSpeed(b, MOT_PWM);
}
