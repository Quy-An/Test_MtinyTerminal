/**
 * Tilte: Line Tracking Car R1 With 3 Sensor
 * Author: Mika
 * Date: 05/18/2024
 * Version: v1.0
 * Purpose: This code is for reference
*/

// INCLUDE LIBRARIES
#include "Makerlabvn_SimpleMotor.h"

// DEFINE
#define PIN_OUT1 A1     //! A1
#define PIN_OUT2 A2     //! A2
#define PIN_OUT3 A3     //! A3
#define PIN_IN1 4       //! D4
#define PIN_IN2 5       //! D5
#define PIN_IN3 6       //! D6
#define PIN_IN4 7       //! D7
#define DELAY_CAR 1000  //Set delay time for the car


// OBJECT INITIALIZATION
Makerlabvn_SimpleMotor demoMotor(PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4);

// VARIABLE
const float threshold_right = 0.5;  // Threshold of the right sensor
const float threshold_left = 0.5;   // Threshold of the left sensor
const float threshold_mid = 0.5;    // Threshold of the mid sensor
int last_lost_dir;                  // The variable stores the value of the vehicle's state before losing the line
const int left_dir = 1;             // The variable stores the states that the vehicle is on the left side of the line
const int right_dir = 0;            // The variable stores the states that the vehicle is on the right side of the line
const int speedForward = 35;        // The variable stores the vehicle's speed value when run with fast speed
const int speedForwardlow = 15;     // The variable stores the vehicle's speed value when run with low speed
const int speedStop = 0;            // The variable stores the vehicle's speed value when stop

/* RUN ONCE TIME WHEN START */
void setup() {
  last_lost_dir = left_dir;  // Set the state variable before losing the line
  // Let the car stop about DELAY_CAR
  demoMotor.car_stop();
  delay(DELAY_CAR);
}
/* RUN LOOP AFTER SETUP RUN */
void loop() {
  // Store the value read from the sensor into a variable
  int eye_Left_Value = digitalRead(A3);
  int eye_Right_Value = digitalRead(A1);
  int eye_Mid_Value = digitalRead(A2);
  // When the Mid sensor read the line
  if ((eye_Mid_Value > threshold_mid)) {

    demoMotor.car_fw(speedForward, speedForward);  // Let the car go forward

  } else {
    // When the Left and the Mid sensor read the line, but the Right doesn't
    if ((eye_Left_Value > threshold_left) && (eye_Right_Value < threshold_right) && (eye_Mid_Value > threshold_mid)) {

      demoMotor.car_fw(speedForwardlow, speedForward);  // Let the car go forward to the left

    } else {
      // When the Right and the Mid sensor read the line, but the Left doesn't
      if ((eye_Left_Value < threshold_left) && (eye_Right_Value > threshold_right) && (eye_Mid_Value > threshold_mid)) {

        demoMotor.car_fw(speedForward, speedForwardlow);  // Let the car go forward to the right

      } else {
        // When the Left sensor read the line, but the Right and the Mid don't
        if ((eye_Left_Value > threshold_left) && (eye_Right_Value < threshold_right) && (eye_Mid_Value < threshold_mid)) {

          last_lost_dir = right_dir;  // Before losing the line, the car was on the right

          demoMotor.car_fw(speedStop, speedForward);  // Let the car turn LEFT
        } else {
          // When the Right sensor read the line, but the Left and the Mid don't
          if ((eye_Left_Value < threshold_left) && (eye_Right_Value > threshold_right) && (eye_Mid_Value < threshold_mid)) {

            last_lost_dir = left_dir;  // // Before losing the line, the car was on the left

            demoMotor.car_fw(speedForward, speedStop);  // Let the car turn RIGHT

          } else {
            // When the car lost the line
            if (last_lost_dir == left_dir) {  // If the car was on the left last time

              demoMotor.car_rotateR(speedForward);  // Let the car turn RIGHT

            } else {  // If the car was on the right last time

              demoMotor.car_rotateL(speedForward);  // Let the car turn LEFT
            }
          }
        }
      }
    }
  }
}