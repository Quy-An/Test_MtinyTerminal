// Thêm bộ thư viện
// Add the library.
#include <MKL_LiquidCrystal_I2C.h>
#include "MKL_OneButton.h"

// Khởi tạo LCD
// LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

// Đặt tên cho chân kết nối Module
#define SIG_PIN 12     // Digital pin connected to the module

// Khai báo module.
// Declare module.
MKL_OneButton btn = MKL_OneButton(
    SIG_PIN, // Cấu hình đây là chân Digital Input.
    true,       // Nút nhấn kích hoạt LOW.
    false       // Kích hoạt điện trở nội "Pull-Up".
);

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
  btn.attachClick(myClickEvent);
  btn.attachDoubleClick(myDoubleClickEvent);
}

void loop()
{
  // Lấy giá trị module
  // Get data module
  btn.tick();
}

void myClickEvent(){
  //Gửi giá trị module lên LCD
  //Show the module value on LCD
  lcd.setCursor(1,0);
  lcd.print("Click");
  lcd.print("   ");

  // Hiển thị giá trị của module lên máy tính.
  // Show the module value on Arduno Serial Monitor
  Serial.println("Click");
}

void myDoubleClickEvent(){
  //Gửi giá trị module lên LCD
  //Show the module value on LCD
  lcd.setCursor(1,0);
  lcd.print("2x Click");
  lcd.print("   ");

  // Hiển thị giá trị của module lên máy tính.
  // Show the module value on Arduno Serial Monitor
  Serial.println("2x Click");
}