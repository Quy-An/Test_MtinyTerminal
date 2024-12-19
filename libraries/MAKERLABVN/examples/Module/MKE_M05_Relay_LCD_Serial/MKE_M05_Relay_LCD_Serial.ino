// Thêm bộ thư viện
// Add the library.
#include <MKL_LiquidCrystal_I2C.h>

// Khởi tạo LCD
// LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

// Đặt tên cho chân kết nối Module
#define SIG_PIN 10     // Digital pin connected to the module

void setup()
{
  // Khởi động LCD
  // LCD start
  lcd.init();
  lcd.backlight();

  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);

  // Cấu hình đây là chân Digital Output.
  // Config this is Digital Output.
  pinMode(SIG_PIN, OUTPUT);
}

void loop()
{
  // Bật.
  // Turn on.
  digitalWrite(SIG_PIN, HIGH);

  //Gửi giá trị module lên LCD
  //Show the module value on LCD
  lcd.setCursor(1,0);
  lcd.print("Status: ON");
  lcd.print("   ");

  // Hiển thị giá trị của module lên máy tính.
  // Show the module value on Arduno Serial Monitor
  Serial.println("ON");
  
  // Chờ 1000ms
  // Wait 1000ms
  delay(1000);

  // Tắt.
  // Turn off.
  digitalWrite(SIG_PIN, LOW);

  //Gửi giá trị module lên LCD
  //Show the module value on LCD
  lcd.setCursor(1,0);
  lcd.print("Status: OFF");
  lcd.print("   ");

  // Hiển thị giá trị của module lên máy tính.
  // Show the module value on Arduno Serial Monitor
  Serial.println("OFF");
  
  // Chờ 1000ms
  // Wait 1000ms
  delay(1000);
}