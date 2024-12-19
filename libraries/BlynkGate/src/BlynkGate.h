#ifndef Blynk_I2C__H_
#define Blynk_I2C__H_

#include "Arduino.h"
#include "Wire.h"
#include "Blynk_I2C_Param.h"
#include "kxn_QueueKeyValue_BlynkGate.h"



#define PCSerial    Serial
#define DBSerial(...)    Serial.println(__VA_ARGS__)
#define DBSerial(...)    

#define KXN_BYTE_PER_TIME_SEND  (28)
#define BLYNK_WRITE_DEFAULT()       void BlynkGate::Blynk_I2C_WriteDefault(BlynkReq request, Blynk_I2C_Param  param)

#define BLYNK_I2C_CMD_VIRTUAL_PIN_RX        "EATR"
#define BLYNK_I2C_CMD_VIRTUAL_PIN_TX        "ATW"
#define BLYNK_I2C_WRITE_DELAY_US            (1000)

struct BlynkReq
{
    uint16_t pin;
};

typedef enum{
    BLYNK_I2C_SADDR_ID = 0,
    BLYNK_I2C_MODE_ID_GET_DATA,
    BLYNK_I2C_MODE_ID_DETECT_DEVICE,
    MODE_ID_SET_OUPUT,
    BLYNK_I2C_END_MODE_ID
}BlynkI2C_typeModeId;

typedef struct{
    uint8_t id;
    uint8_t modeId;
    uint8_t lenData;
    uint8_t checkSumData;
    char data[KXN_BYTE_PER_TIME_SEND];
}str_SerialBlynkI2C_Data;

typedef struct{
    uint8_t id;
    uint8_t modeId;
    uint8_t lenData;
    uint8_t checkSumData;
}str_SerialBlynkI2C_DataHeader;

DECLARE_QUEUE_BLYNK_GATE(BlynkGateQueue, int, float, 10);


class BlynkGate{
    public:
    uint8_t slaveAddress;
    String auth, ssid, pass;
    str_SerialBlynkI2C_Data *i2cData;
    unsigned long lastTimeVirtualWrite = 0;
    // String lastVirtualPinString;
    // String lastVirtualPinValueString;

    BlynkGate(uint8_t paAddress = 74){
        slaveAddress = paAddress;
    }

    void checkUartThenSendI2C4();
    void I2C_writeString(uint8_t myAdd, char* myString, uint8_t myLen);
    void checkI2CThenSendSerial();
    void checkSendVirtualWrite();
    void SetupCharArrayToBuffer4(char *inputCharArray, char *tempArrChar, uint8_t len);
    void SendStringToI2C(String kk);
    String splitString(String v_G_motherString, String v_G_Command, String v_G_Start_symbol, String v_G_Stop_symbol, unsigned char v_G_Offset);

    void CheckWifi();
    void connect(String auth_, String ssid_, String pass_);
    void begin(String auth_, String ssid_, String pass_);
    void virtualWrite(int vx_, String strValue_);
    // void virtualWrite(int vx_, long strValue_);
    void virtualWrite(int vx_, float strValue_);
    void run();
    void delayms();
    virtual void Blynk_I2C_WriteDefault(BlynkReq request, Blynk_I2C_Param  param);
};

extern BlynkGate Blynk;

// void __empty_BlynkI2C(BlynkReq request, Blynk_I2C_Param  param) {
//     // Empty
// }

// void Blynk_I2C_WriteDefault(BlynkReq request, Blynk_I2C_Param  param) __attribute__((weak, alias("__empty_BlynkI2C")));

// void __empty_BlynkI2C(BlynkReq request, Blynk_I2C_Param  param);
// // void Blynk_I2C_WriteDefault(BlynkReq request, Blynk_I2C_Param  param);
// void Blynk_I2C_WriteDefault(BlynkReq request, Blynk_I2C_Param  param) __attribute__((weak, alias("__empty_BlynkI2C")));

// void Blynk_I2C_GetWriteHandler(BlynkReq request, Blynk_I2C_Param  param);
// void __attribute__((unused)) Blynk_I2C_GetWriteHandler(BlynkReq request, Blynk_I2C_Param  param);
// virtual void Blynk_I2C_GetWriteHandler(BlynkReq request, Blynk_I2C_Param  param);

// static void __empty_BlynkI2C(BlynkReq request, Blynk_I2C_Param  param) {
//     // Empty
// }

// extern void Blynk_I2C_GetWriteHandler(BlynkReq request, Blynk_I2C_Param  param) __attribute__ ((weak, alias("__empty_BlynkI2C")));
#endif