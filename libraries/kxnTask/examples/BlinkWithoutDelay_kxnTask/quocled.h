#pragma once

#include "kxnTask.h"

DEFINE_TASK_STATE(quocled){
    quocled_ON,
    quocled_OFF,
};

CREATE_TASK(quocled)
/*Add your variable here*/
uint8_t pin;
void setup()
{
    /*Add your code setup here*/
    pinMode(pin, OUTPUT);
    stop();
}

void loop()
{
    switch (getState())
    {
    case quocled_ON:
        /*code*/
        digitalWrite(pin, 1);
        kDelay(100);
        setState(quocled_OFF);
        break;

    case quocled_OFF:
        /*code*/
        digitalWrite(pin, 0);
        kDelay(100);
        setState(quocled_ON);
        break;

    default:
        break;
    }
}

void setPin(int tempPin){
  this->pin = tempPin;
}

void start()
{
    kxnTaskManager.add(this);
    setState(quocled_ON);
}

void stop()
{
    kDelay(0);
    setStateIdle();
}

END