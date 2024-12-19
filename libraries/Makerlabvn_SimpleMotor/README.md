# Makerlabvn_SimpleMotor

### Giới thiệu:

> Đây là bộ thư viện điều khiển động cơ đơn giản trên Arduino giúp điều khiển **2 x Động cơ DC** trên các mạch Driver hỗ trợ điều khiển đơn giản bằng **4 chân tín hiệu** (2 chân tín hiệu trên mỗi động cơ), quy ước:
>
> - **MotorA:** `IN1/IN2` (chân `IN2` **<span style="color:#FE0101">bắt buộc** phải có chức năng xuất *xung PWM*).
> - **MotorB:** `IN3/IN4` (chân `IN3` **<span style="color:#FE0101">bắt buộc** phải có chức năng xuất *xung PWM*).

## Hàm điều khiển motor

> Điều khiển độc lập từng motor của từng kênh A hoặc B.

|Hàm|Chức năng|
|---|---------|
|**<span style="color:#E47128">motorA_fw(`speed`)**|Điều khiển motor A quay thuận.<br>- *speed:* tốc độ quay (0% ~ 100%).
|**<span style="color:#E47128">motorA_bw(`speed`)**|Điều khiển motor A quay ngược.<br>- *speed:* tốc độ quay (0% ~ 100%).
|**<span style="color:#E47128">motorA_stop()**|Điều khiển motor A dừng lại.
|-|-|
|**<span style="color:#E47128">motorB_fw(`speed`)**|Điều khiển motor B quay thuận.<br>- *speed:* tốc độ quay (0% ~ 100%).
|**<span style="color:#E47128">motorB_bw(`speed`)**|Điều khiển motor B quay ngược.<br>- *speed:* tốc độ quay (0% ~ 100%).
|**<span style="color:#E47128">motorB_stop()**|Điều khiển motor B dừng lại.

## Hàm điều khiển xe

> Điều khiển kết hợp 2 kênh A & B.

|Hàm|Chức năng|
|---|---------|
|**<span style="color:#E47128">car_fw(`speedA`, `speedB`)**|Điều khiển xe đi tới.<br>- *speedA:* tốc độ quay bánh Trái (0% ~ 100%).<br>- *speedA:* tốc độ quay bánh Phải (0% ~ 100%).
|**<span style="color:#E47128">car_bw(`speedA`, `speedB`)**|Điều khiển xe đi lùi.<br>- *speedA:* tốc độ quay bánh Trái (0% ~ 100%).<br>- *speedA:* tốc độ quay bánh Phải (0% ~ 100%).
|-|-|
|**<span style="color:#E47128">car_rotateL(`speed`)**|Điều khiển xe xoay trái.<br>- *speed:* tốc độ xe (0% ~ 100%).
|**<span style="color:#E47128">car_rotateR(`speed`)**|Điều khiển xe xoay phải.<br>- *speed:* tốc độ xe (0% ~ 100%).
|-|-|
|**<span style="color:#E47128">car_stop()**|Điều khiển xe dừng lại.

> Để điều khiển xe đúng, cần kết nối Motor đến Driver đúng chiều.
>
> |Motor|Driver|
> |-----|------|
> |Motor Trái `(-)`|OUT1|
> |Motor Trái `(+)`|OUT2|
> |Motor Phải `(+)`|OUT3|
> |Motor Phải `(-)`|OUT4|
>
> Trong đó, khi bạn cấp nguồn đúng cực `(+)` và `(-)` của Motor, sẽ làm motor quay hướng giúp xe đi tới.

