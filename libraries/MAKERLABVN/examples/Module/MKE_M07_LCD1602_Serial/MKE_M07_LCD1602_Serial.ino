// Thêm bộ thư viện
// Add the library.
#include <MKL_LiquidCrystal_I2C.h>

// Khởi tạo LCD
// LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned char value;

void setup()
{
  // Khởi động LCD
  // LCD start
  lcd.init();
  lcd.backlight();

  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);

  //Gửi giá trị module lên LCD
  //Show the module value on LCD
  lcd.setCursor(0,0);
  lcd.print("MKE-M07 LCD1602");
  
}

void loop()
{
  // Lấy giá trị module
  // Get data module
  value = value + 1;

  //Gửi giá trị module lên LCD
  //Show the module value on LCD
  lcd.setCursor(1,1);
  lcd.print("Value:");
  lcd.print(value);
  lcd.print("   ");

  // Hiển thị giá trị của module lên máy tính.
  // Show the module value on Arduno Serial Monitor
  Serial.print("Value: ");
  Serial.println(value);
  
  // Chờ 1000ms
  // Wait 1000ms
  delay(1000);
}