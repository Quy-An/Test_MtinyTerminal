#include "ledObject.h"
#include "blynkLedObject.h"
#include "quocled.h"

ledObject myLed1;
ledObject myLed2;

quocled quocled;

void setup(){
    Serial.begin(9600);
    myLed1.setup(13, 500, 500);
    myLed2.setup(12, 100, 900);

    quocled.setPin(11);
    quocled.setup();
    quocled.start();

    myLed1.start();
    myLed2.start();
}

void loop(){
    kxnTaskManager.run(millis());
    checkSerial();
}

void checkSerial(){
    if(Serial.available()){
        char tempChar = Serial.read();

        switch (tempChar)
        {
        case '1':
            myLed1.start();
            break;
        
        case '2':
            myLed1.stop();
            break;
        
        default:
            break;
        }
    }
}