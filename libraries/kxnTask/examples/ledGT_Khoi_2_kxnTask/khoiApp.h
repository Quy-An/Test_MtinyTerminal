#ifndef khoiApp__H
#define khoiApp__H
#include "kxnTask.h"
#include "khoiGT.h"
#include "khoiBlink.h"

DEFINE_TASK_STATE(khoiApp){
  khoiApp_STATE_NOTHING
};

CREATE_TASK(khoiApp)

khoiGT khoiGT1;
khoiGT khoiGT2;

khoiBlink khoiBlinkY1, khoiBlinkY2;
void setup(){
  khoiGT1.setup();
  khoiGT1.startR();

  khoiGT2.setPin(6,7,8);
  khoiGT2.setup();
  khoiGT2.startG();

  khoiBlinkY1.setup(4, 2000, 2000);
  khoiBlinkY2.setup(7, 2000, 2000);

  khoiBlinkY1.stop();
  khoiBlinkY2.stop();

  this->start();

}

void start() {
  startThreeColor();
}

void startThreeColor(){
  khoiGT1.startR();
  khoiGT2.startG();
  khoiBlinkY1.stop();
  khoiBlinkY2.stop();
  kxnTaskManager.add(this);
}

void startBlinkYellowColor(){
  khoiGT1.stop();
  khoiGT2.stop();
  khoiBlinkY1.start();
  khoiBlinkY2.start();
  kxnTaskManager.add(this);
}

uint8_t isThreeColor_Idle(){
  if(khoiGT1.isStateIdle() && khoiGT2.isStateIdle()){
    return true;
  }
  return false;
}

uint8_t isBlinkYellowColor_Idle(){
  if(khoiBlinkY1.isStateIdle() && khoiBlinkY2.isStateIdle()){
    return true;
  }
  return false;
}

void stop() {
  khoiGT1.stop();
  khoiGT2.stop();
  khoiBlinkY1.stop();
  khoiBlinkY2.stop();
  setStateIdle();
}

END

#endif