// Thêm bộ thư viện
// Add the library.
#include <MKL_LiquidCrystal_I2C.h>
#include "MKL_DS18B20.h"

// Khởi tạo LCD
//LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

// Đặt tên cho chân kết nối cảm biến
#define DS18B20_PIN 11     // Digital pin connected to the sensor

OneWire oneWire_10(DS18B20_PIN);
MKL_DS18B20 sensor(&oneWire_10);

// Tạo biến lưu giá trị cảm biến
// value read from the sensor
float sensorValue1 = 0;

void setup()
{
  // Khởi động LCD
  // LCD start
  lcd.init();
  lcd.backlight();

  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);

  sensor.begin();
}

void loop()
{
  
  // Đọc giá trị cảm biến
  // Get value
  sensor.requestTemperatures();
  sensorValue1 = sensor.getTempC();

  //Gửi giá trị cảm biến lên LCD
  //Show the sensor value on LCD
  lcd.setCursor(1,0);
  lcd.print("Temp:");
  lcd.setCursor(1,1);
  lcd.print(sensorValue1);
  lcd.print("   ");

  // Hiển thị giá trị đo được của cảm biến lên máy tính.
  // Show the sensor value on Arduno Serial Monitor
  Serial.print("Temp: ");
  
  Serial.println(sensorValue1);
  
  // Chờ 2000ms
  // Wait 2000ms
  delay(2000);
}