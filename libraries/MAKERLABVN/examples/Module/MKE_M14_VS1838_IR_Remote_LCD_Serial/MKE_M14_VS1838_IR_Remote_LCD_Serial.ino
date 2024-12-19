// Thêm bộ thư viện
// Add the library.
#include <MKL_LiquidCrystal_I2C.h>
#include "MKL_IRremote.h"

// Khởi tạo LCD
// LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

// Đặt tên cho chân kết nối Module
#define SIG_PIN 10     // Digital pin connected to the module

void setup() {
  // Khởi động LCD
  // LCD start
  lcd.init();
  lcd.backlight();

  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);

  // Khởi tạo module
  // init module
  IrReceiver.begin(SIG_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    /*
    * !!!Important!!! Enable receiving of the next value, because receiving
    * has stopped after the end of the current received data packet.
    */
    IrReceiver.resume();

    if (IrReceiver.decodedIRData.protocol != UNKNOWN) {
      
      // Hiển thị giá trị của module lên máy tính.
      // Show the module value on Arduno Serial Monitor
      Serial.println(IrReceiver.decodedIRData.command);

      //Gửi giá trị module lên LCD
      //Show the module value on LCD
      lcd.setCursor(0, 0);
      lcd.print(String() + F("IR Command:") + IrReceiver.decodedIRData.command + "    ");
    }
  }
}