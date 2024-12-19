/*
  board esp32 phiên bản 3.0.7
  thư viện LoRa phiên bản 0.8.0
 */

#include <SPI.h>
#include <LoRa.h>

// khai báo kết nối chân Lora-Uno
const int NSS = 10;
const int RST = 9;
const int DIO0 = 2;

const int SF = 7;
const int BW = 500E3;


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

  // kiểm tra có gói tin nào được nhận
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // // phản hồi
    // LoRa.beginPacket();
    // LoRa.print("1");
    // LoRa.endPacket();

    // đọc các byte dữ liệu trong gói
    String receivedMessage = ""; 
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    // hien thi goi tin
    Serial.print("nhan: ");
    Serial.println(receivedMessage);

    LoRa.beginPacket();
    LoRa.print("1");
    LoRa.endPacket();
  }
  Serial.flush();
}
