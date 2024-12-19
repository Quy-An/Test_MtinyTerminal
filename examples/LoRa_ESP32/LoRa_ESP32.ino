/*
  board esp32 phiên bản 3.0.7
  thư viện LoRa phiên bản 0.8.0
 */

#include <SPI.h>
#include <LoRa.h>

// khai báo kết nối chân Lora-ESP32
const int NSS = 5;
const int RST = 13;
const int DIO0 = 14;

// const char data = '012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678912345';

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // khởi tạo Lora
  LoRa.setPins(NSS, RST, DIO0);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Thiết lập hệ số trải phổ (spreading factor). 
  // Giá trị SF càng cao, khoảng cách truyền càng xa 
  // nhưng tốc độ truyền dữ liệu càng chậm và ngược lại.
  LoRa.setSpreadingFactor(7);

  // Thiết lập băng thông tín hiệu.
  LoRa.setSignalBandwidth(125E3);
  
  // for(int i = 0; i < 10; i++){
  //   Serial.println(i);
  //   LoRa.beginPacket();
  //   LoRa.print("012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678912345");
  //   LoRa.endPacket();

    
  //   // delay(100);
  // }
}


void loop() {
  // kiểm tra có dữ liệu gửi không
  if (Serial.available() > 255){
    Serial.println("kich thuoc qua lon, khong the gui");
  }
  else if (Serial.available() > 0){
    // đọc dữ liệu từ terminal
    String inputString = Serial.readStringUntil('\n');

    // đóng gói dữ liệu và gửi
    LoRa.beginPacket();
    LoRa.print(inputString);
    LoRa.endPacket();

    // hiển thị dữ liệu đã gửi đi
    Serial.print("gui: ");
    Serial.println(inputString);
  }

  // kiểm tra có gói tin nào được nhận
  // int packetSize = LoRa.parsePacket();
  if (LoRa.parsePacket()) {
    // đọc các byte dữ liệu trong gói
    String receivedMessage = ""; 
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    // hien thi goi tin
    Serial.print("nhan: ");
    Serial.println(receivedMessage);
  }
  Serial.flush();
}
