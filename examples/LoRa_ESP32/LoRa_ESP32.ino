#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Configure LoRa module pins (adjust as needed)
  LoRa.setPins(SS, 13, 14);  // Replace RST with actual pin number

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Set spreading factor and bandwidth (adjust as needed)
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
}

void loop() {
  // Check for received packets
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }
  else
    Serial.print("khong nhan duoc");

    // Print received message to serial monitor
    Serial.println(receivedMessage);

  }
}