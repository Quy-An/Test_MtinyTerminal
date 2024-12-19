/**
 * Kiểm tra điều khiển độc lập từng motor trên kênh A và B
 */

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "Makerlabvn_SimpleMotor.h"

/* ------------------------------------------------------------------------- */
/*                                   DEFINE                                  */
/* ------------------------------------------------------------------------- */

/**
 * Phần cấp nguồn cho Driver
 * +12V - ... có thể cấp nguồn trong khoảng 9V~6V
 * GND  - GND
 *
 * Dùng Jumper kết nối (mặc định)
 * ENA  - 5V
 * ENB  - 5V
 *
 * L298 : Arduino
 * IN1  : D4
 * IN2  : D5 (~)
 * IN3  : D6 (~)
 * IN4  : D7
 */
#define PIN_IN1 4 //! D4
#define PIN_IN2 5 //! D5 (~)
#define PIN_IN3 6 //! D6 (~)
#define PIN_IN4 7 //! D7

/* ------------------------------------------------------------------------- */
/*                                   OBJECT                                  */
/* ------------------------------------------------------------------------- */

Makerlabvn_SimpleMotor demo(PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4);

/* ------------------------------------------------------------------------- */
/*                                RUN ONE TIME                               */
/* ------------------------------------------------------------------------- */

void setup()
{
  Serial.begin(115200);
}

/* ------------------------------------------------------------------------- */
/*                                    MAIN                                   */
/* ------------------------------------------------------------------------- */

void loop()
{
  Serial.println("Điều khiển động cơ kênh A...");
  Serial.println();

  Serial.println("Quay thuận 100%");
  demo.motorA_fw(100);
  delay(5000);

  Serial.println("Quay ngược 50%");
  demo.motorA_bw(50);
  delay(5000);

  Serial.println("Đứng yên");
  demo.motorA_stop();
  delay(5000);

  /* ----------------------------------------------------------------------- */

  Serial.println("Điều khiển động cơ kênh B...");
  Serial.println();

  Serial.println("Quay thuận 100%");
  demo.motorB_fw(100);
  delay(5000);

  Serial.println("Quay ngược 50%");
  demo.motorB_bw(50);
  delay(5000);

  Serial.println("Đứng yên");
  demo.motorB_stop();
  delay(5000);
}