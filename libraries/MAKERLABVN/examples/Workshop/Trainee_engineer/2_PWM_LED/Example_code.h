#define LED_PIN 10  // Định nghĩa cho chân số 10
#define PWM_Val 250 // Định nghĩa cho giá trị độ sáng từ 0-255 tương ứng với giá trị điện áp nhỏ nhất tới cao nhất
                    
// hàm setup chạy một lần khi bạn nhấn nút reset hoặc cấp nguồn cho bo mạch
void setup()
{
  // khởi tạo chân kỹ thuật số LED_PIN (chân 10) làm đầu ra.
  pinMode(LED_PIN, OUTPUT);
}

// hàm loop chạy lặp đi lặp lại mãi mãi
void loop()
{
  analogWrite(LED_PIN, PWM_Val); // bật đèn LED (PWM_Val là mức điện áp)
}