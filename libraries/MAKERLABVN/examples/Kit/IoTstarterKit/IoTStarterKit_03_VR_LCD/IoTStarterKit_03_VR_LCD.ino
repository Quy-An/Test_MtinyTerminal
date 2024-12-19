/*
  Title:  Potentiomenter and LCD
  Author: Thanh Tam
  Date: 5/6/2024
  Description: Read value of potentiometer and show on LCD
              - Virtual Pin V1 (Gauge) on Blynk for Potentiometer
*/
// Step 1: Get this infomation from Blynk.cloud
#define BLYNK_TEMPLATE_ID "Copy_BLYNK_TEMPLATE_ID_From_BlynkCloud"
#define BLYNK_TEMPLATE_NAME "Copy_BLYNK_TEMPLATE_NAME_From_BlynkCloud"
#define BLYNK_AUTH_TOKEN "Copy_BLYNK_AUTH_TOKEN_From_BlynkCloud"

// Step 2: include library
#include "BlynkGate.h"
#include "MKL_LiquidCrystal_I2C.h"
// Step 3: Setup WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MakerLab.vn";  // Key in your wifi name (Bandwidth 2.4Ghz). You can check with your smart phone for your wifi name
char pass[] = "";             // Key in your wifi password.

#define POTEN_MAX_VALUE 692
#define POTEN_MIN_VALUE 0
#define POTEN_PIN A2

unsigned long intervalLCD = 0;
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastTimeSend = 0;

int valuePotentiometer = 0;
int mapValue = 0;
int percent = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("Start BlynkGate I2C"));
  lcd.init();
  lcd.backlight();
  // Step 4: begin BlynkGate
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  // DO NOT using delay
  readPotentiometer();
  if (millis() - intervalLCD > 500) {
    showOnLCD();
    intervalLCD = millis();
  }
  // Try using millis() and use "Blynk.virtualWrite" at least 10s at a time to avoid spamming the server
  if (millis() - lastTimeSend >= 10000) {
    lastTimeSend = millis();
    Blynk.virtualWrite(1, percent);
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
}


void readPotentiometer() {
  valuePotentiometer = analogRead(POTEN_PIN);
  mapValue = map(valuePotentiometer, POTEN_MIN_VALUE, POTEN_MAX_VALUE, 0, 255);
  mapValue = constrain(mapValue, 0, 255);
  percent = map(mapValue, 0, 255, 0, 100);
}

void showOnLCD() {
  lcd.setCursor(1, 0);
  lcd.print("IoT StarterKit");
  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.setCursor(7, 1);
  if (valuePotentiometer / 10 == 0) {  // valuePotentiometer la so co 1 chu so
    lcd.print(valuePotentiometer);
    lcd.print("  ");
  } else if (valuePotentiometer / 100 == 0) {  // valuePotentiometer la so co 2 chu so
    lcd.print(valuePotentiometer);
    lcd.print(" ");
  } else {  // valuePotentiometer la so co 3 chu so
    lcd.print(valuePotentiometer);
  }
  lcd.setCursor(12, 1);
  if (percent < 10) {
    lcd.print("  ");
  } else if (percent < 100) {
    lcd.print(" ");
  }
  lcd.print(percent);
  lcd.print("%");
}