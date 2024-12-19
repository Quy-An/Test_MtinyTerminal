#ifndef MKL_LiquidCrystal_I2C_H__
#define MKL_LiquidCrystal_I2C_H__

#include "LiquidCrystal_I2C.h"

class MKL_LiquidCrystal_I2C: public LiquidCrystal_I2C
{
  public:

  MKL_LiquidCrystal_I2C(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows):LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows){

  }
};

#endif