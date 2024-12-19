/*
  Title:  Button, Led and LCD demo
  Author: Daniel Hoang
  Date:   5/6/2024
  Description: Using button to turn on or turn off the led and show on LCD
              - Virtual Pin V0 (Switch) on Blynk for button
*/
#define BLYNK_TEMPLATE_ID "Copy_BLYNK_TEMPLATE_ID_From_BlynkCloud"
#define BLYNK_TEMPLATE_NAME "Copy_BLYNK_TEMPLATE_NAME_From_BlynkCloud"
#define BLYNK_AUTH_TOKEN "Copy_BLYNK_AUTH_TOKEN_From_BlynkCloud"

#define BUTTON_PIN A3
#define LED_PIN 11

// Step 2: include library
#include "BlynkGate.h"
#include "MKL_LiquidCrystal_I2C.h"
#include "MKL_OneButton.h"

// Step 3: Setup WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MakerLab.vn";  // Key in your wifi name (Bandwidth 2.4Ghz). You can check with your smart phone for your wifi name
char pass[] = "";             // Key in your wifi password.

unsigned long intervalLCD = 0;
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

MKL_OneButton myButton(BUTTON_PIN, true, true);

unsigned long lastTimeSend = 0;
int ledState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  Serial.println(F("Start BlynkGate I2C"));

  lcd.init();
  lcd.backlight();

  myButton.attachClick(ledToggle);

  // Step 4: begin BlynkGate
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  // DO NOT using delay
  myButton.tick();
  updateLedState();
  if (millis() - intervalLCD > 500) {
    showOnLCD();
    intervalLCD = millis();
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
      ledState = 1;
    } else {
      ledState = 0;
    }
  }
}

void ledToggle() {
  ledState = !ledState;
  Blynk.virtualWrite(0, ledState);
}

void updateLedState() {
  digitalWrite(LED_PIN, ledState);
}

void showOnLCD() {
  lcd.setCursor(1, 0);
  lcd.print("IoT StarterKit");
  lcd.setCursor(0, 1);
  lcd.print("LED STATUS: ");
  lcd.setCursor(12, 1);
  if (ledState == 1) {
    lcd.print("ON ");
  } else {
    lcd.print("OFF");
  }
  lcd.print("   ");
}