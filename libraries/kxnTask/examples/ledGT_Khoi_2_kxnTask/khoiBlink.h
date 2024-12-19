#pragma once

#include "kxnTask.h"

DEFINE_TASK_STATE(khoiBlink){
    khoiBlink_ON,
    khoiBlink_OFF,
};

CREATE_TASK(khoiBlink)
uint8_t pin;
unsigned long timeOn;
unsigned long timeOff;

void setup(uint8_t pin_, unsigned long timeOn_, unsigned long timeOff_)
{
    pin = pin_;
    timeOn = timeOn_;
    timeOff = timeOff_;
    pinMode(pin, OUTPUT);
    stop();
}

void loop()
{
    switch (getState())
    {
    case khoiBlink_ON:
        digitalWrite(pin, 1);
        kDelay(timeOn);
        setState(khoiBlink_OFF);
        break;

    case khoiBlink_OFF:
        digitalWrite(pin, 0);
        kDelay(timeOff);
        setState(khoiBlink_ON);
        break;

    default:
        break;
    }
}

void start()
{
    kxnTaskManager.add(this);
    setState(khoiBlink_ON);
}

void stop()
{
    digitalWrite(pin, 0);
    kDelay(0);
    setStateIdle();
}

void runFast(){     // this function will be called without delay
  Serial.println("khoiBlink running");
}

END