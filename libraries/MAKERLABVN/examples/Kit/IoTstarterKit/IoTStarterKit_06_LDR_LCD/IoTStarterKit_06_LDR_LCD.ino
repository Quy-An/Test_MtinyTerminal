/*
  Title:  LDR and Buzzer demo
  Author: Daniel Hoang
  Date:   5/6/2024
  Description: Read value of the LDR sensor and write value into Blynk every 5s.
              - Virtual Pin V2 (Chart) on Blynk for LDR sensor
*/
// Step 1: Get this infomation from Blynk.cloud
#define BLYNK_TEMPLATE_ID "Copy_BLYNK_TEMPLATE_ID_From_BlynkCloud"
#define BLYNK_TEMPLATE_NAME "Copy_BLYNK_TEMPLATE_NAME_From_BlynkCloud"
#define BLYNK_AUTH_TOKEN "Copy_BLYNK_AUTH_TOKEN_From_BlynkCloud"

#define LDR_MIN_VALUE 0
#define LDR_MAX_VALUE 692

#define LDR_PIN A1


// Step 2: include library
#include "BlynkGate.h"
#include "MKL_LiquidCrystal_I2C.h"
// Step 3: Setup WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MakerLab.vn";  // Key in your wifi name (Bandwidth 2.4Ghz). You can check with your smart phone for your wifi name
char pass[] = "";             // Key in your wifi password.

unsigned long intervalLCD = 0;
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastTimeSend = 0;

int valueLDR = 0;
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
  readLDRSensor();
  if (millis() - intervalLCD > 500) {
    showOnLCD();
    intervalLCD = millis();
  }
  // Try using millis() and use "Blynk.virtualWrite" at least 10s at a time to avoid spamming the server
  if (millis() - lastTimeSend >= 10000) {
    lastTimeSend = millis();
    Blynk.virtualWrite(2, percent);
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

void readLDRSensor() {
  valueLDR = analogRead(LDR_PIN);
  mapValue = map(valueLDR, LDR_MAX_VALUE, LDR_MIN_VALUE, 0, 255);
  mapValue = constrain(mapValue, 0, 255);
  percent = map(mapValue, 0, 255, 0, 100);
}

void showOnLCD() {
  lcd.setCursor(1, 0);
  lcd.print("IoT StarterKit");
  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.setCursor(7, 1);
  if (valueLDR / 10 == 0) {             // valueLDR la so co 1 chu so
    lcd.print(valueLDR);
    lcd.print("  ");
  } else if (valueLDR / 100 == 0) {     // valueLDR la so co 2 chu so
    lcd.print(valueLDR); 
    lcd.print(" ");
  } else {                              // valueLDR la so co 3 chu so
    lcd.print(valueLDR);
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