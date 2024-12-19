// Thêm bộ thư viện
// Add the library.
#include <MKL_LiquidCrystal_I2C.h>

// Khởi tạo LCD
// LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

// Đặt tên cho chân kết nối Module
#define SIG_PIN A1     // Digital pin connected to the module

int value;
void setup()
{
  // Khởi động LCD
  // LCD start
  lcd.init();
  lcd.backlight();

  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);
}

void loop()
{
  // Lấy giá trị module
  // Get data module
  value = analogRead(SIG_PIN);

  //Gửi giá trị module lên LCD
  //Show the module value on LCD
  lcd.setCursor(1,0);
  lcd.print("Value:");
  lcd.setCursor(1,1);
  lcd.print(value);
  lcd.print("   ");

  // Hiển thị giá trị của module lên máy tính.
  // Show the module value on Arduno Serial Monitor
  Serial.print("Value: ");
  Serial.println(value);
  
  // Chờ 100ms
  // Wait 100ms
  delay(100);
}