/*
  Title:  Advanced Demo
  Author: Thanh Tam
  Date: 5/6/2024
  Description: Combine all sensor, show on LCD and write into Blynk
              - Virtual Pin V0 (Switch) on Blynk for button
              - Virtual Pin V1 (Gauge)  on Blynk for Potentiometer
              - Virtual Pin V2 (Chart)  on Blynk for LDR sensor
*/
// Step 1: Get this infomation from Blynk.cloud
#define BLYNK_TEMPLATE_ID "Copy_BLYNK_TEMPLATE_ID_From_BlynkCloud"
#define BLYNK_TEMPLATE_NAME "Copy_BLYNK_TEMPLATE_NAME_From_BlynkCloud"
#define BLYNK_AUTH_TOKEN "Copy_BLYNK_AUTH_TOKEN_From_BlynkCloud"

// Step 2: include library
#include "BlynkGate.h"
#include "MKL_LiquidCrystal_I2C.h"
#include "MKL_OneButton.h"
// Step 3: Setup WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MakerLab.vn";  // Key in your wifi name (Bandwidth 2.4Ghz). You can check with your smart phone for your wifi name
char pass[] = "";             // Key in your wifi password.

#define POTEN_MAX_VALUE 692
#define POTEN_MIN_VALUE 0

#define LDR_MIN_VALUE 0
#define LDR_MAX_VALUE 692

#define SETPOINT 60
#define OFFSET   5

#define LDR_PIN A1
#define POTEN_PIN A2
#define BUTTON_PIN A3
#define BUZZER_PIN 10
#define LED_PIN 11


unsigned long intervalLCD = 0;
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);
MKL_OneButton myButton(BUTTON_PIN, true, true);

unsigned long lastTimeSend = 0;

bool ledState = false;

int valuePotentiometer = 0;
int brightness = 0;
int brightnessPercent = 0;

int valueLDR = 0;
int lightPercent = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("Start BlynkGate I2C"));
  pinMode(BUZZER_PIN, OUTPUT);
  myButton.attachClick(ledStateToggle);
  lcd.init();
  lcd.backlight();
  // Step 4: begin BlynkGate
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  // DO NOT using delay
  myButton.tick();
  ledControl();
  readPotentiometer();
  readLDR();
  if(millis() - intervalLCD > 500){
    showOnLCD();
    intervalLCD = millis();
  }
  // Try using millis() and use "Blynk.virtualWrite" at least 10s at a time to avoid spamming the server
  if (millis() - lastTimeSend >= 10000) {
    lastTimeSend = millis();
    Blynk.virtualWrite(1, brightnessPercent);
    Blynk.virtualWrite(2, valueLDR);
    // Step 6: Send Virtual pin Value
  }
}

// Step 5: Get Virtual pin Value
BLYNK_WRITE_DEFAULT() {
  // double myDouble = param.asFloat();
  // String myString = param.asString();
  int myInt = param.asInt();

  Serial.print("input V");
  Serial.print(request.pin);
  Serial.print(": ");
  Serial.println(myInt);
  if (request.pin == 0) {
    if (myInt == 1) {
      ledState = true;
    } else {
      ledState = false;
    }
  }
}

void ledStateToggle() {
  ledState = !ledState;
  buzzer();
  Blynk.virtualWrite(0, ledState);
}

void ledControl() {
  if (ledState) {
    analogWrite(LED_PIN, brightness);
  } else {
    analogWrite(LED_PIN, 0);
  }
}

void readPotentiometer() {
  valuePotentiometer = analogRead(POTEN_PIN);
  brightness = map(valuePotentiometer, POTEN_MIN_VALUE, POTEN_MAX_VALUE, 0, 255);
  brightness = constrain(brightness, 0, 255);
  brightnessPercent = map(brightness, 0, 255, 0, 100);
}

void readLDR() {
  valueLDR = analogRead(LDR_PIN);
  lightPercent = map(valueLDR, LDR_MAX_VALUE, LDR_MIN_VALUE, 0, 100);
}

void showOnLCD() {
  lcd.setCursor(0, 0);
  lcd.print("LED: ");
  lcd.setCursor(5, 0);
  if (ledState) {
    lcd.print("ON ");
  } else {
    lcd.print("OFF");
  }
  lcd.setCursor(12, 0);
  if (brightnessPercent < 10) {
    lcd.print("  "); 
  } else if (brightnessPercent < 100) {
    lcd.print(" ");
  }
  lcd.print(brightnessPercent);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("LIGHT: ");
  lcd.setCursor(8, 1);
  if (lightPercent > (SETPOINT + OFFSET)) {
    lcd.print("Bright");
  } else if(lightPercent < (SETPOINT - OFFSET)){
    lcd.print("Dark  ");
  }
}

void buzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
  digitalWrite(BUZZER_PIN, LOW);
}
