#include "MKE_M15.h"

jdy33_info_Struct jdy33_baudTable[]={
  {115200,    8},
  {9600,      4},
  {2400,      2},
  {4800,      3},
  {19200,     5},
  {38400,     6},
  {57600,     7},
  {128000,    9}
};

uint16_t jdy33_sizeBaudTable = sizeof(jdy33_baudTable) / sizeof(jdy33_info_Struct);
// jdy33_class<HardwareSerial> MKE_M15(&Serial);
