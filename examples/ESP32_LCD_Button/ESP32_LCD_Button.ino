/*
  board esp32 phiên bản 3.0.7
  thư viện LoRa phiên bản 0.8.0
 */

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "OneButton.h"

// khai báo kết nối chân Lora-Uno
const int NSS = 5;
const int RST = 13;
const int DIO0 = 14;

const int ButtonPin = 33;
OneButton button(ButtonPin, true);
unsigned long transTime;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  button.attachClick(attachClick);

  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Makerlab test");

  // khởi tạo Lora
  LoRa.setPins(NSS, RST, DIO0);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Thiết lập hệ số trải phổ (spreading factor). 
  // Giá trị SF càng cao, khoảng cách truyền càng xa 
  // nhưng tốc độ truyền dữ liệu càng chậm và ngược lại.
  LoRa.setSpreadingFactor(12);

  // Thiết lập băng thông tín hiệu.
  LoRa.setSignalBandwidth(125E3);
}


void loop() {
  button.tick();

  // kiểm tra có gói tin nào được nhận
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    unsigned long receiveTime = millis();
    // phản hồi
    // đọc các byte dữ liệu trong gói
    String receivedMessage = ""; 
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    // kiểm tra tin
    if(receivedMessage == "OKE1")
      Serial.println(receiveTime - transTime);
    else {
    // LCD
      // Serial.println(receivedMessage);
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print(LoRa.packetRssi());
      lcd.setCursor(7,1);
      lcd.print(receivedMessage);
    }

  }
}

void attachClick()
{
  // đóng gói dữ liệu và gửi
  LoRa.beginPacket();
  LoRa.print("2");
  LoRa.endPacket();
  transTime = millis();
}
