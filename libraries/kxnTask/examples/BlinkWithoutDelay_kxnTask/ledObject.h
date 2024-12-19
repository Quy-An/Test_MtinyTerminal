#pragma once

#include "kxnTask.h"

DEFINE_TASK_STATE(ledObject){
    ledObject_ON,
    ledObject_OFF,
};

CREATE_TASK(ledObject)
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
    case ledObject_ON:
        digitalWrite(pin, 1);
        kDelay(timeOn);
        setState(ledObject_OFF);
        break;

    case ledObject_OFF:
        digitalWrite(pin, 0);
        kDelay(timeOff);
        setState(ledObject_ON);
        break;

    default:
        break;
    }
}

void start()
{
    kxnTaskManager.add(this);
    setState(ledObject_ON);
}

void stop()
{
    digitalWrite(pin, 0);
    kDelay(0);
    setStateIdle();
}

// END_CREATE_TASK
END