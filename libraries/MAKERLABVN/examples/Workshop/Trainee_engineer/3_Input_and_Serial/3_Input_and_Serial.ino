/*
##########################################################################################################
##########################################################################################################
  MakerLabvn_Trainee_engineer_Kĩ_sư_tập_sự
  Chỉnh sửa: 22/08/2024
  Người chỉnh sửa: Nguyễn hoàng Trung Sơn
##########################################################################################################
##########################################################################################################

  Đọc giá trị cảm biến và giao tiếp với vi điều khiển bằng máy tính.
  Đọc ở chân Analog hoặc digital
  Để mở màn hình hiển thị Serial monitor bạn ấn tổ hợp phím (Ctrl + Shift + M)
*/

#define Button_pin 11 // Định nghĩa cho chân số 11 cho nút nhấn
#define LDR_pin A1    // Định nghĩa cho giá trị độ sáng từ 0-255 tương ứng với giá trị điện áp nhỏ nhất tới cao nhất

// hàm setup chạy một lần khi bạn nhấn nút reset hoặc cấp nguồn cho bo mạch
void setup()
{
  Serial.begin(115200); // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
                        // thường đặt baudrate ở 115200 hoặc 9800

  pinMode(Button_pin, INPUT); // khởi tạo chân kỹ thuật số Button_pin (chân 11) làm đầu vào.
  pinMode(LDR_pin, INPUT);    // khởi tạo chân kỹ thuật số LDR_PIN (chân 11) làm đầu vào.
}

// hàm loop chạy lặp đi lặp lại mãi mãi
void loop()
{
  Serial.print("Button state: ");
  Serial.print(digitalRead(Button_pin));

  Serial.print("||");

  Serial.print("LDR: ");
  Serial.println(analogRead(LDR_pin));
}