// Thêm bộ thư viện
// Add the library.
#include "BlynkGate.h"

//Cấu hình Blynk Firmware (copy từ mục Blynk Firmware Info)
//Blynk Firmware Configuration (copy from Blynk Firmware Info)
#define BLYNK_TEMPLATE_ID "Copy_BLYNK_TEMPLATE_ID_From_BlynkCloud"
#define BLYNK_TEMPLATE_NAME "Copy_BLYNK_TEMPLATE_NAME_From_BlynkCloud"
#define BLYNK_AUTH_TOKEN "Copy_BLYNK_AUTH_TOKEN_From_BlynkCloud"

// Cấu hình Auth Token
// Auth Token Configuration
char auth[] = BLYNK_AUTH_TOKEN;

// Cấu hình Wifi (chỉ nhận wifi 2.4G)
// Wifi Configuration (only wifi 2.4G accepted)
char ssid[] = "WiFi name 2.4G";  // Wifi name (SSID)
char pass[] = "WiFi PassWord";          // Wifi password.

//Khai báo các biến sử dụng.
//Declare Variable
int ledPin = 11;
int sensorPin = A2;
unsigned long lasTimeRequestSensor = 0;

void setup() { 
// put your setup code here, to run once:

  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);
  Serial.println("Start");

  // Khởi động module BlynkGate
  // Init module BlynkGate
  Blynk.begin(auth, ssid, pass);

  pinMode(ledPin, OUTPUT);
}

void loop() { 
// put your main code here, to run repeatedly:
//[Lưu ý] Không sử dụng hàm delay()!!!
//[Impotant] Dont use delay() function here!!!
  
Blynk.run();

//2000ms gửi dữ liệu cảm biến về Blynk 1 lần
//2000ms per sensor data sent
  if(millis() - lasTimeRequestSensor >= 2000){
    lasTimeRequestSensor = millis();
    Blynk.virtualWrite(5, analogRead(sensorPin)); //Gửi giá trị về Vitual Pin V5 . Write sensor data to Vitual Pin V5
  }
}

BLYNK_WRITE_DEFAULT() {
  //Hàm quét sự thay đổi của các chân Vitual Pin . Vitual Pin Scan Change Function

  int DetectPin = request.pin;
  int PinValue = param.asInt();
  // double DetectData = param.asFloat();
  // String DetectData = param.asString();
  
  // Hiển thị giá trị của module lên máy tính.
  // Show the module value on Arduno Serial Monitor
  Serial.print("Detect V");
  Serial.print(DetectPin);
  Serial.print(": ");
  Serial.println(PinValue);

  // Control Led
  if(DetectPin == 1){
    digitalWrite(ledPin, PinValue);
  }

}
