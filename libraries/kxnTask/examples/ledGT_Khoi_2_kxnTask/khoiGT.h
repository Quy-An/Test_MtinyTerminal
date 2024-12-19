#ifndef khoiGT__H
#define khoiGT__H
#include "kxnTask.h"

DEFINE_TASK_STATE(khoiGT){
  khoiGT_ON_R,
  khoiGT_ON_Y,
  khoiGT_ON_G,
  khoiGT_OFF,
};

CREATE_TASK(khoiGT)
uint8_t pinG = 3;
uint8_t pinY = 4;
uint8_t pinR = 5;

uint32_t timeON_G = 3000;                 // ms
uint32_t timeON_Y = 1000;                 //ms
uint32_t timeON_R = timeON_G + timeON_Y;  // ms

void setup() {
  // put your setup code here, to run once:
  pinMode(pinG, OUTPUT);
  pinMode(pinY, OUTPUT);
  pinMode(pinR, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (getState()) {
    case khoiGT_ON_R:
      digitalWrite(pinR, 1);
      digitalWrite(pinY, 0);
      digitalWrite(pinG, 0);

      setState(khoiGT_ON_G);
      kDelay(timeON_R);
      break;

    case khoiGT_ON_G:
      digitalWrite(pinR, 0);
      digitalWrite(pinY, 0);
      digitalWrite(pinG, 1);

      setState(khoiGT_ON_Y);
      kDelay(timeON_G);
      break;

    case khoiGT_ON_Y:
      digitalWrite(pinR, 0);
      digitalWrite(pinY, 1);
      digitalWrite(pinG, 0);

      setState(khoiGT_ON_R);
      kDelay(timeON_Y);
      break;
  }
}

void startR(){
  setState(khoiGT_ON_R);
  kxnTaskManager.add(this);
}

void startY(){
  setState(khoiGT_ON_Y);
  kxnTaskManager.add(this);
}

void startG(){
  setState(khoiGT_ON_G);
  kxnTaskManager.add(this);
}

void start() {
  setState(khoiGT_ON_R);
  kxnTaskManager.add(this);
}

void setPin(uint8_t pin__G, uint8_t pin__Y, uint8_t pin__R){
  this->pinG = pin__G;
  this->pinY = pin__Y;
  this->pinR = pin__R;

}

void stop() {
  digitalWrite(pinR, 0);
  digitalWrite(pinY, 0);
  digitalWrite(pinG, 0);
  kDelay(0);
  setStateIdle();
}

END

#endif