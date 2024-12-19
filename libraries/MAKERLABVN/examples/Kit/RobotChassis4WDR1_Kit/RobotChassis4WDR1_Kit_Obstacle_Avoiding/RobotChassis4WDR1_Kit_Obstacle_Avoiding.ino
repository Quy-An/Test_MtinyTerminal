/**
 * Tilte: Obstacle Avoiding Car R1
 * Author: Mika
 * Date: 05/17/2024
 * Version: v1.0
 * Purpose: This code is for reference
*/

// Include libraries
#include <MKL_HCSR04.h>
#include <Makerlabvn_SimpleMotor.h>
#include <Servo.h>

// Define
#define ANGLE_L 180  // The left side of the car for rc servo motor rotate
#define ANGLE_C 90   // The middle side of the car for rc servo motor rotate
#define ANGLE_R 0    // The right side of the car for rc servo motor rotate
#define DELAYSERVO 500   // Define the servo's delay time
#define MOTORSPEED 30    // Define the car's speed
#define DELAYROTATE 500  // Define the delaytime for the car rotates
#define DELAYBW 400      // Define the delaytime for the car goes back

// Object initialization
Makerlabvn_SimpleMotor Driver(4, 5, 6, 7);
MKL_HCSR04 Scaner(9, 10);
Servo Rotater;

// Variable
int distance;                       // The variable stores the distance value
const int threshold_distance = 30;  // Variable that specifies the distance threshold to the obstacle
enum {                              // Specifies 4 car's states
  RB_FF,
  RB_BB,
  RB_RL,
  RB_RR,
};
int RB_state = RB_FF;  // Specifies the fist car's state is going forward

void setup() {
  // put your setup code here, to run once:
  Rotater.attach(8);       // Initialize the control pin of rc servo
  Rotater.write(ANGLE_C);  // For the ultrasonic sensor to look forward
  delay(DELAYSERVO);       // Wait for the motor to rotate for about DELAYSERVO
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (RB_state) {
    /**
     * Consider variable RB_state:
     * - RB_FF: go foward
     * - RB_RL: turn left
     * - RB_RR: turn right
     */
    case RB_FF:
      go_F();
      break;
    case RB_RL:
      rotate_L();
      break;
    case RB_RR:
      rotate_R();
      break;
  }
}

// Function
void go_F() {
  // In case the ultrasonic sensor is at an angle that does not look straight ahead of the car
  if (Rotater.read() != ANGLE_C) {
    // Return the ultrasonic sensor to the middle
    Rotater.write(ANGLE_C);
    // Wait for the rc servo to rotate
    delay(DELAYSERVO);
  }
  // In case of encountering obstacles
  if (Ultradistance_Scan() < threshold_distance) {
    Driver.car_stop();  // Let the car stop
    RB_state = RB_RL;   // Change the vehicle's status to turn left
    // And if there are no obstacles
  } else {
    Driver.car_fw(MOTORSPEED, MOTORSPEED);  // Let the car run straight
  }
}

void rotate_L() {
  // Turn the rc servo to the left side of the car
  Rotater.write(ANGLE_L);
  // Wait for the rc servo to rotate
  delay(DELAYSERVO);
  // In case of encountering obstacles
  if (Ultradistance_Scan() < threshold_distance) {
    Driver.car_stop();  // Let the car stop
    RB_state = RB_RR;   // Change the vehicle's status to turn left
    // And if there are no obstacles
  } else {
    Rotater.write(ANGLE_C);          // Turn the rc servo to the middle side of the car
    delay(DELAYSERVO);               // Wait for the rc servo to rotate
    Driver.car_rotateL(MOTORSPEED);  // Let the car turn left
    delay(DELAYROTATE);              // Wait for the car to rotate
    Driver.car_stop();               // Let the car stop
    RB_state = RB_FF;                // Change the vehicle's status to go forward
  }
}

void rotate_R() {
  // Turn the rc servo to the left side of the car
  Rotater.write(ANGLE_R);
  // Wait for the rc servo to rotate
  delay(DELAYSERVO);

  // In case of encountering obstacles
  if (Ultradistance_Scan() < threshold_distance) {
    Rotater.write(ANGLE_C);                 // Turn the rc servo to the middle side of the car
    delay(DELAYSERVO);                      // Wait for the rc servo to rotate
    Driver.car_bw(MOTORSPEED, MOTORSPEED);  // Let the car go backward
    delay(DELAYBW);                         // Wait for the car to go backward
    Driver.car_stop();                      // Let the car stop
    RB_state = RB_RL;                       // Change the vehicle's status to turn left

    // And if there are no obstacles
  } else {
    Rotater.write(ANGLE_C);          // Turn the rc servo to the middle side of the car
    delay(DELAYSERVO);               // Wait for the rc servo to rotate
    Driver.car_rotateR(MOTORSPEED);  // Let the car turn right
    delay(DELAYROTATE);              // Wait for the car to rotate
    RB_state = RB_FF;                // Change the vehicle's status to go foward
  }
}

int Ultradistance_Scan() {
  distance = Scaner.dist();  // Store the measured value in the distance variable
  delay(60);                 // Scanning interval
  return distance;           // Returns the value of the distance variable
}