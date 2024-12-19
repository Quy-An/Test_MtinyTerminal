// Thêm bộ thư viện
// Add the library.
#include <MKL_LiquidCrystal_I2C.h>

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include "MKL_Dabble.h"

// Khởi tạo LCD
// LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TX_PIN 12
#define RX_PIN 13

// Khai báo module.
// Declare module.
SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN);
MKE_M15_SSerial(mySoftwareSerial);

String value;

void setup()
{
  // Khởi động LCD
  // LCD start
  lcd.init();
  lcd.backlight();

  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);
  Serial.println("Start");

  // Khởi tạo module
  // init module
  
  // MKE_M15.setBaudrate(9600); // safe speed for SoftwareSerial is 9600
  // MKE_M15.setName("MKE-M15"); // max 12 characters
  mySoftwareSerial.begin(9600);
  Dabble.begin(mySoftwareSerial);
  
}

void loop()
{
  Dabble.processInput();

  if (GamePad.isUpPressed())
  {
    value = "UP";
  }
  else if (GamePad.isDownPressed())
  {
    value = "DOWN";
  }
  else if (GamePad.isLeftPressed())
  {
    value = "LEFT";
  }
  else if (GamePad.isRightPressed())
  {
    value = "RIGHT";
  }
  else{
    value = "0";
  }

  if(value == "0") return;

  // Hiển thị giá trị của module lên máy tính.
  // Show the module value on Arduno Serial Monitor
  Serial.println(value);

  //Gửi giá trị module lên LCD
  //Show the module value on LCD
  lcd.setCursor(0,0);
  lcd.print(value);
  lcd.print("   ");

  // Chờ 50ms
  // Wait 50ms  
  delay(50);
}