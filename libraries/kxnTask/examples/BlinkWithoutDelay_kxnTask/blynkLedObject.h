#pragma once

#include "kxnTask.h"

DEFINE_TASK_STATE(blynkLedObject){
    blynkLedObject_ON,
    blynkLedObject_OFF,
};

CREATE_TASK(blynkLedObject)
/*Add your variable here*/
uint8_t pin;
void setup(uint8_t q, float qe, float qr)
{
    /*Add your code setup here*/
    pinMode(pin, OUTPUT);
    stop();
}

void loop()
{
    switch (getState())
    {
    case blynkLedObject_ON:
        /*code*/
        digitalWrite(pin, 1);
        kDelay(0);
        setState(blynkLedObject_OFF);
        break;

    case blynkLedObject_OFF:
        /*code*/
        digitalWrite(pin, 1);
        kDelay(0);
        setState(blynkLedObject_ON);
        break;

    default:
        break;
    }
}

void start()
{
    kxnTaskManager.add(this);
    setState(blynkLedObject_ON);
}

void stop()
{
    kDelay(0);
    setStateIdle();
}

END