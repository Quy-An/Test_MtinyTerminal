//
//    FILE: MKL_DS18B20_simple.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: equivalent of DallasTemperature library Simple
//     URL: https://github.com/RobTillaart/MKL_DS18B20_RT


#include "MKL_DS18B20.h"


#define ONE_WIRE_BUS              2

OneWire oneWire(ONE_WIRE_BUS);
MKL_DS18B20 sensor(&oneWire);


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MKL_DS18B20_LIB_VERSION: ");
  Serial.println(MKL_DS18B20_LIB_VERSION);
  Serial.println();

  sensor.begin();
  sensor.setResolution(10);
}


void loop(void)
{
  sensor.requestTemperatures();

  //  wait until sensor is ready
  while (!sensor.isConversionComplete())
  {
    delay(1);
  }

  Serial.print("Temp: ");
  Serial.println(sensor.getTempC());
}


//  -- END OF FILE --
