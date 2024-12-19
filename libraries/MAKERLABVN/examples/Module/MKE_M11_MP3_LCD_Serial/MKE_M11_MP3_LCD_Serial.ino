// Thêm bộ thư viện
// Add the library.
#include <MKL_LiquidCrystal_I2C.h>
#include "SoftwareSerial.h"
#include "MKL_DFRobotDFPlayerMini.h"

// Khởi tạo LCD
// LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TX_PIN 12
#define RX_PIN 13

// Khai báo module.
// Declare module.
SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN);
MKL_DFRobotDFPlayerMini myDFPlayer;

unsigned long timeDelay = 2000; //2000ms 

void setup()
{
  // Khởi động LCD
  // LCD start
  lcd.init();
  lcd.backlight();

  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);

  // Khởi tạo module
  // init module
  mySoftwareSerial.begin(9600);
  delay(200);
  myDFPlayer.begin(mySoftwareSerial, true,true);
  delay(100);
  
  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(30);
  
}

void loop()
{
  myDFPlayer.playMp3Folder(1);

  // Hiển thị giá trị của module lên máy tính.
  // Show the module value on Arduno Serial Monitor
  Serial.println("Play file 1");

  //Gửi giá trị module lên LCD
  //Show the module value on LCD
  lcd.setCursor(0,0);
  lcd.print("Play file 1");

  // Chờ 2000ms
  // Wait 2000ms  
  delay(2000);

  myDFPlayer.stop();

  // Hiển thị giá trị của module lên máy tính.
  // Show the module value on Arduno Serial Monitor
  Serial.println("Stop file 1");

  //Gửi giá trị module lên LCD
  //Show the module value on LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stop file 1");

  // Chờ 2000ms
  // Wait 2000ms  
  delay(2000);
}