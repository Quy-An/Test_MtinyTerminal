#define LED_PIN 11  // Định nghĩa hằng số cho chân số 11

// hàm setup chạy một lần khi bạn nhấn nút reset hoặc cấp nguồn cho bo mạch
void setup() {
  // khởi tạo chân kỹ thuật số LED_PIN (chân 11) làm đầu ra.
  pinMode(LED_PIN, OUTPUT);
}

// hàm loop chạy lặp đi lặp lại mãi mãi
void loop() {
  digitalWrite(LED_PIN, HIGH);  // bật đèn LED (HIGH là mức điện áp)
  delay(1000);                  // đợi một giây
  digitalWrite(LED_PIN, LOW);   // tắt đèn LED bằng cách giảm mức điện áp xuống LOW
  delay(1000);                  // đợi một giây
}