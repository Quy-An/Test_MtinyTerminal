/*
##########################################################################################################
##########################################################################################################
  MakerLabvn_Trainee_engineer_Kĩ_sư_tập_sự
  Chỉnh sửa: 22/08/2024
  Người chỉnh sửa: Nguyễn hoàng Trung Sơn
##########################################################################################################
##########################################################################################################

  Tăng giảm độ sáng LED
  Với Arduino Uno chỉ có những chân có dấu "~" mới có chức năng tạo xung Pwm

*/

#define LED_PIN 10  // Định nghĩa cho chân số 10
#define PWM_Val 100 // Định nghĩa cho giá trị độ sáng từ 0-255 tương ứng với giá trị điện áp nhỏ nhất tới cao nhất
                    
// hàm setup chạy một lần khi bạn nhấn nút reset hoặc cấp nguồn cho bo mạch
void setup()
{
  // khởi tạo chân kỹ thuật số LED_PIN (chân 10) làm đầu ra.
  pinMode(LED_PIN, OUTPUT);
}

// hàm loop chạy lặp đi lặp lại mãi mãi
void loop()
{ 
  // digitalWrite(pin, value);
  // analogWrite(pin, value);
  analogWrite(LED_PIN, ...); // bật đèn LED (PWM_Val là mức điện áp)
}