/*
  ARDUINO_DAY_VIET_NAM_2024
  Title : Biến đèn nội thất thành thiết bị IoT
  Author: Nguyễn Sơn
  Date  : 6/7/2024
*/

// Định nghĩa các chân GPIO cho vi điều khiển
#define LED_PIN 11     // Chân điều khiển LED
#define LDR_PIN A2     // Chân kết nối cảm biến ánh sáng


#define BLYNK_TEMPLATE_ID "TMPL6I9MkL2Iy"                    // ID mẫu Blynk
#define BLYNK_TEMPLATE_NAME "IOT KIT"                        // Tên mẫu Blynk
#define BLYNK_AUTH_TOKEN "********************************"  // Mã xác thực Blynk


// Bao gồm các thư viện cần thiết
#include "BlynkGate.h"  // Thư viện BlynkGate cho kết nối Blynk


// Thiết lập WiFi
char auth[] = BLYNK_AUTH_TOKEN;    // Mã xác thực Blynk
char ssid[] = "SEAN_LAPTOP_4896";  // Tên mạng Wi-Fi (chỉ hoạt động với băng tần 2.4Ghz)
char pass[] = "123456789";         // Mật khẩu Wi-Fi


// Định nghĩa các chân Virtual Pins như trên Web BLYNK
const int Virtual_Pins_LED = 1;
const int Virtual_Pins_LDR = 2;


unsigned long lastTimeSend = 0;  // Biến thời gian gửi dữ liệu cuối cùng
int ledState = 0;                // Biến trạng thái của LED (bật/tắt)


void setup() {
  pinMode(LED_PIN, OUTPUT);               // Thiết lập chân LED là OUTPUT
  pinMode(LDR_PIN, INPUT);                // Thiết lập chân cảm biến ánh sáng là INPUT
  Serial.begin(115200);                   // Khởi tạo giao tiếp Serial để debug
  Serial.println("Start BlynkGate I2C");  // In ra thông báo khởi tạo BlynkGate I2C

  Blynk.begin(auth, ssid, pass);  // Kết nối với Blynk bằng thông tin xác thực và Wi-Fi
}


void loop() {
  Blynk.run();       // Xử lý các yêu cầu từ Blynk, không sử dụng delay trong loop này
  updateLedState();  // Cập nhật trạng thái của LED

  //################################----Gửi giá trị quang trở----##################################

  /*

   if (millis() - lastTimeSend >= 1000) {                               // Kiểm tra nếu đã qua 100ms kể từ lần gửi cuối cùng
     Blynk.virtualWrite(Virtual_Pins_LDR, map(analogRead(LDR_PIN), 0, 400, 100, 0));  // Gửi giá trị của cảm biến ánh sáng đến Blynk
     lastTimeSend = millis();                                          // Cập nhật thời gian gửi dữ liệu cuối cùng
   }
  
  */

  //###############################################################################################
}


// Nhận giá trị từ Virtual Pin
BLYNK_WRITE_DEFAULT() {
  int myInt = param.asInt();  // Nhận giá trị từ Blynk và chuyển đổi thành kiểu int

  Serial.print("input V");    // In ra pin đầu vào
  Serial.print(request.pin);  // In ra số pin
  Serial.print(": ");
  Serial.println(myInt);  // In ra giá trị nhận được

  if (request.pin == Virtual_Pins_LED) {  // Kiểm tra nếu là Virtual_Pins_LED
    if (myInt == 1) {                     // Nếu giá trị nhận được là 1
      ledState = 1;                       // Bật LED
    } else {                              // Nếu giá trị nhận được không phải là 1
      ledState = 0;                       // Tắt LED
    }
  }
}


void updateLedState() {
  digitalWrite(LED_PIN, ledState);  // Cập nhật trạng thái của LED (bật/tắt)
}
