// Thêm bộ thư viện
// Add the library.
#include <MKL_LiquidCrystal_I2C.h>

// Khởi tạo LCD
//LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

// Đặt tên cho chân kết nối cảm biến
// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A1;  // Analog input pin that the sensor is attached to

// Tạo biến số nguyên lưu giá trị cảm biến
// value read from the sensor
int sensorValue = 0;  

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

  // Đọc giá trị cảm biến
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  //Gửi giá trị cảm biến lên LCD
  //Show the sensor value on LCD
  lcd.setCursor(1,0);
  lcd.print("Value:");
  lcd.setCursor(1,1);
  lcd.print(sensorValue);
  lcd.print("   ");

  // Hiển thị giá trị đo được của cảm biến lên máy tính.
  // Show the sensor value on Arduno Serial Monitor
  Serial.print("Value: ");
  Serial.println(sensorValue);
  
  // Chờ 500ms
  // Wait 500ms
  delay(500);
}