#include <SPI.h>
#include <LoRa.h>

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Configure LoRa module pins (adjust as needed)
  LoRa.setPins(SS, 9, 2);  // Replace RST with actual pin number

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Set spreading factor and bandwidth (adjust as needed)
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // gui goi tin
  LoRa.beginPacket();
  LoRa.print("Hello from Arduino: ");
  LoRa.print(counter);
  LoRa.endPacket();


  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String r = "";
    while (LoRa.available()) {
      r += (char)LoRa.read();
    }
    Serial.println(r);
    // if(r == "da nhan duoc")
    //   Serial.println("oke");
  }

  counter++;
  delay(5000);
}