#ifndef MKL_SIMPLE_MOTOR_H
#define MKL_SIMPLE_MOTOR_H

/**
 * Quy ước:
 * -" Kênh A" của driver điều khiển "động cơ bên TRÁI" của xe.
 * - "Kênh B" của driver điều khiển "động cơ bên PHẢI" của xe.
 */

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include <Arduino.h>

/* ------------------------------------------------------------------------- */
/*                                   CLASS                                   */
/* ------------------------------------------------------------------------- */

class Makerlabvn_SimpleMotor
{
public:
  /* ------------------------------- HÀM TẠO ------------------------------- */
  Makerlabvn_SimpleMotor(
      int pinIn1, int pinIn2,
      int pinIn3, int pinIn4);

  /* ------------------------- HÀM ĐIỀU KHIỂN MOTOR ------------------------ */

  void motorA_fw(int speed); // Điều khiển motor kênh A quay thuận
  void motorB_fw(int speed); // Điều khiển motor kênh B quay thuận

  void motorA_bw(int speed); // Điều khiển motor kênh A quay ngược
  void motorB_bw(int speed); // Điều khiển motor kênh B quay ngược

  void motorA_stop(); // Điều khiển motor kênh A dừng lại
  void motorB_stop(); // Điều khiển motor kênh B dừng lại

  /* -------------------------- HÀM ĐIỀU KHIỂN XE -------------------------- */

  void car_fw(int speedA, int speedB); // Điều khiển xe đi tới
  void car_bw(int speedA, int speedB); // Điều khiển xe đi lùi

  void car_rotateL(int speed); // Điều khiển xe xoay trái
  void car_rotateR(int speed); // Điều khiển xe xoay phải

  void car_stop(); // Điều khiển xe dừng lại

private:
  /* ----------------------- (BIẾN) CẤU HÌNH CÁC PIN ----------------------- */
  int _pinIn1;
  int _pinIn2;
  int _pinIn3;
  int _pinIn4;

  /* --------------------------- (HÀM) ĐẶT TỐC ĐỘ -------------------------- */

  /**
   * Đảm bảo giá trị tốc độ (%) nhận được trong khoảng 0% đến 100%
   * Đồng thời chuyển đổi tốc độ (%) sang thang (PWM) tương ứng
   */
  int calculate_speed(int speed);
};

/* ------------------------------------------------------------------------- */

#endif