/*
  Idea:
    - Controlling Traffic Light System over Serial Monitor (Noline Ending)
      - '0': Stop ALL led
      - '2': Blink led Yellow warning SLOW SPEED
      - '3': Traffic Light works with three Color

  Wiring:
      - Traffic Light 1:
          - G1 = 3
          - Y1 = 4
          - R1 = 5
          - GND1 = GND
      - Traffic Light 2:
          - G2 = 6
          - Y2 = 7
          - R2 = 8
          - GND2 = GND

*/

#include "khoiApp.h"

khoiApp khoiApp1;

void setup(){
  Serial.begin(115200);
  khoiApp1.setup();
}

void loop(){
  kxnTaskManager.run(millis());
  checkSerial();
}

void checkSerial(){
  if(Serial.available()){
    char tt = Serial.read();
    switch (tt) {
    case '0':
      khoiApp1.stop();
      break;

    case '3':
      if(khoiApp1.isThreeColor_Idle()){
        khoiApp1.startThreeColor();
      }
      break;

    case '2':
      if(khoiApp1.isBlinkYellowColor_Idle()){
        khoiApp1.startBlinkYellowColor();
      }
      
      break;
    }
  }
}
