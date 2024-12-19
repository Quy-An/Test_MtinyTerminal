/*
  board esp32 phiên bản 3.0.7
  thư viện LoRa phiên bản 0.8.0
 */

#include <SPI.h>
#include <LoRa.h>
#include "OneButton.h"

// khai báo kết nối chân Lora-Uno
const int NSS = 10;
const int RST = 9;
const int DIO0 = 2;

int countSend = 0;

const int ButtonPin = 6;
const int LedPin = 7;

OneButton button(ButtonPin, true);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  // pinMode(ButtonPin, INPUT);
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, LOW);
  button.attachClick(attachClick);

  // khởi tạo Lora
  LoRa.setPins(NSS, RST, DIO0);

  if (!LoRa.begin(720E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Thiết lập hệ số trải phổ (spreading factor). 
  // Giá trị SF càng cao, khoảng cách truyền càng xa 
  // nhưng tốc độ truyền dữ liệu càng chậm và ngược lại.
  LoRa.setSpreadingFactor(7);

  // Thiết lập băng thông tín hiệu.
  LoRa.setSignalBandwidth(500E3);
  
}


void loop() {
  button.tick();

  // kiểm tra có gói tin nào được nhận
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // đọc các byte dữ liệu trong gói
    String receivedMessage = ""; 
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();

      Serial.println(receivedMessage);
    }

    // TOGGLE LED
    if(receivedMessage == "2")
      digitalWrite(LedPin, !digitalRead(LedPin));

  }
}

void attachClick()
{
  countSend += 1;
  // đóng gói dữ liệu và gửi
  LoRa.beginPacket();
  LoRa.print(countSend);
  LoRa.endPacket();
}
