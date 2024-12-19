/**
 * Tilte: Bluetooth Car R1
 * Author: Mika
 * Date: 05/17/2024
 * Version: v1.0
 * Purpose: This code is for reference
*/

// INCLUDE LIBRARIES
#include "MKL_Dabble.h"
#include <SoftwareSerial.h>
#include "Makerlabvn_SimpleMotor.h"

// DEFINE
#define PIN_IN1 4
#define PIN_IN2 5
#define PIN_IN3 6
#define PIN_IN4 7
#define PIN_TX_BLE 2
#define PIN_RX_BLE 3
#define SPEED 100

// OBJECT INITIALIZATION
Makerlabvn_SimpleMotor demoMotor(PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4);
SoftwareSerial mySerial(PIN_TX_BLE, PIN_RX_BLE);


void setup() {
  // put your setup code here, to run once:
  demoMotor.car_stop();    // Let the car stop
  mySerial.begin(115200);  // Initialize mySerial baudrate communication
  Serial.begin(115200);    // Initialize Serial baudrate communication
  Dabble.begin(mySerial);  // Initialize Dabble baudrate communication
}


void loop() {
  // put your main code here, to run repeatedly:
  Dabble.processInput();             // Receive information from Dabble app
  if (GamePad.isUpPressed()) {       // When UP BUTTON is pressed
    demoMotor.car_fw(SPEED, SPEED);  // Let the car go foward
  } else {
    if (GamePad.isDownPressed()) {     // When DOWN BUTTON is pressed
      demoMotor.car_bw(SPEED, SPEED);  // Let the car go backward
    } else {
      if (GamePad.isLeftPressed()) {   // When LEFT BUTTON is pressed
        demoMotor.car_rotateL(SPEED);  // Let the car turn left
      } else {
        if (GamePad.isRightPressed()) {  // When RIGHT BUTTON is pressed
          demoMotor.car_rotateR(SPEED);  // Let the car turn right
        } else {                         // When no button is pressed
          demoMotor.car_stop();          // Let the car stop
        }
      }
    }
  }
}