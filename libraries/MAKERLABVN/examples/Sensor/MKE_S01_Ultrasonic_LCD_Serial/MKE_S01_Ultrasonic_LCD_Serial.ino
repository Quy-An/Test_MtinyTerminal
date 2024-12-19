// Thêm bộ thư viện
// Add the library.
#include <MKL_LiquidCrystal_I2C.h>
#include <MKL_HCSR04.h>

// Khởi tạo LCD
//LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

// Đặt tên cho chân kết nối cảm biến
#define ECHO_PIN 12
#define TRIG_PIN 13

// Cấu hình chân kết nối tín hiệu cho cảm biến.
// Configure the signal connection pins for the sensor.
MKL_HCSR04 ultra(TRIG_PIN, ECHO_PIN);

// Tạo biến số nguyên lưu giá trị cảm biến
// value read from the sensor
float sensorValue = 0;  

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
  sensorValue = ultra.dist();

  //Gửi giá trị cảm biến lên LCD
  //Show the sensor value on LCD
  lcd.setCursor(1,0);
  lcd.print("Value:");
  lcd.setCursor(1,1);
  lcd.print(sensorValue);
  lcd.print("   ");

  // Truyền khoảng cách đo được của cảm biến lên máy tính.
  // Show the sensor value on Arduno Serial Monitor
  Serial.print("Value: ");
  Serial.println(sensorValue);
  
  // Chờ 200ms
  // Wait 200ms
  delay(200);
}