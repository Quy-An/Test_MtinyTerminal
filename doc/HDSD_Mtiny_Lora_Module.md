thư viện:
	board esp32 phiên bản 3.0.7
	thư viện LoRa phiên bản 0.8.0


Khởi tạo và cấu hình
	LoRa.begin(frequency): Khởi tạo giao tiếp LoRa với tần số làm việc cụ thể (ví dụ: 915E6 cho vùng Bắc Mỹ). (thử test ở tần số 720 thì hoạt động đượcđược)
		Ví dụ: LoRa.begin(868E6); (cho vùng châu Âu)
	LoRa.setSpreadingFactor(sf): Thiết lập hệ số trải phổ, ảnh hưởng đến khoảng cách truyền và tốc độ truyền. Giá trị thường từ 7 đến 12.
	LoRa.setSignalBandwidth(bw): Thiết lập băng thông tín hiệu, ảnh hưởng đến tốc độ truyền và khả năng chống nhiễu. (7.8kHz 10.4kHz 15.6kHz 20.8kHz 31.25kHz 41.7kHz 62.5kHz 125kHz 250kHz 500kHz)
	LoRa.setCodingRate4(denominator): Thiết lập tỉ lệ mã hóa, ảnh hưởng đến khả năng sửa lỗi.
Gửi dữ liệu
	LoRa.beginPacket(): Bắt đầu tạo một gói tin mới.
	LoRa.print(data): Viết dữ liệu vào gói tin.
	LoRa.endPacket(): Gửi gói tin đi.
Nhận dữ liệu
	LoRa.parsePacket(): Kiểm tra xem có gói tin nào được nhận hay không. Trả về kích thước của gói tin nếu có.
	LoRa.available(): Kiểm tra xem còn bao nhiêu byte dữ liệu chưa đọc trong bộ đệm.
	LoRa.read(): Đọc một byte dữ liệu từ bộ đệm
Các hàm khác
	LoRa.packetRssi(): Trả về giá trị RSSI (Received Signal Strength Indicator) của gói tin vừa nhận được, cho biết cường độ tín hiệu.
	LoRa.packetSnr(): Trả về giá trị SNR (Signal-to-Noise Ratio) của gói tin vừa nhận được, cho biết tỉ lệ tín hiệu trên nhiễu.
	LoRa.setTxPower(power): Thiết lập công suất phát, ảnh hưởng đến khoảng cách truyền.
