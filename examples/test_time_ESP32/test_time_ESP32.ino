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

const int SF = 7;
const int BW = 500E3;

unsigned long transTime;

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
  LoRa.setSpreadingFactor(SF);

  // Thiết lập băng thông tín hiệu.
  LoRa.setSignalBandwidth(125E3);
  
}


void loop() {
  // kiểm tra có dữ liệu gửi không
  if (Serial.available() > 0){
    // đọc dữ liệu từ terminal
    String inputString = Serial.readStringUntil('\n');

    // đóng gói dữ liệu và gửi
    LoRa.beginPacket();
    LoRa.print(inputString);
    LoRa.endPacket();
    transTime = millis();

    // hiển thị dữ liệu đã gửi
    Serial.print("gui: ");
    Serial.println(inputString);

  }

  // kiểm tra có gói tin nào được nhận
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    unsigned long reTime = millis();
    Serial.print("phan hoi: ");
    Serial.println(reTime - transTime);
  }
  Serial.flush();
}
