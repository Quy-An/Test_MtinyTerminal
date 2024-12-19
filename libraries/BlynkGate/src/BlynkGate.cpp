#include "BlynkGate.h"

DEFINE_QUEUE_BLYNK_GATE(BlynkGateQueue, int, float, 10)

void BlynkGate::SendStringToI2C(String kk){
    // DBSerial("String IN: " + kk);
        int len = kk.length();
        int timeSend = (len)/KXN_BYTE_PER_TIME_SEND;
        
        char inputCharArray[250];
        char outArray[32];
        char * pSplitArray;
        if(kk.indexOf("geti2c") > -1){
            this->checkI2CThenSendSerial();
            return;
        }
        kk.toCharArray(inputCharArray, len + 1);

        this->SetupCharArrayToBuffer4(inputCharArray, outArray, len + 1);
}

void BlynkGate::checkUartThenSendI2C4(){   // Run send 100 bytes to I2C
    if(PCSerial.available()){
        

        String kk = PCSerial.readStringUntil('\n');
        DBSerial("String IN: " + kk);
        if(kk.indexOf("checkConnect") > -1){
            this->connect(this->auth, this->ssid, this->pass);
        }else{
            this->SendStringToI2C(kk);
        }
        
        // int len = kk.length();
        // int timeSend = (len)/KXN_BYTE_PER_TIME_SEND;
        
        // char inputCharArray[250];
        // char outArray[32];
        // char * pSplitArray;
        // if(kk.indexOf("geti2c") > -1){
        //     this->checkI2CThenSendSerial();
        //     return;
        // }
        // kk.toCharArray(inputCharArray, len + 1);

        // this->SetupCharArrayToBuffer4(inputCharArray, outArray, len + 1);
    }
}

void BlynkGate::I2C_writeString(uint8_t myAdd, char* myString, uint8_t myLen){
    Wire.beginTransmission(myAdd); // transmit to device #8
    for(int cf = 0; cf < myLen; cf++){
        Wire.write(myString[cf]);        // sends string
    }
    Wire.endTransmission();    // stop transmitting
    delayMicroseconds(BLYNK_I2C_WRITE_DELAY_US);
}

void BlynkGate::SetupCharArrayToBuffer4(char *inputCharArray, char *tempArrChar, uint8_t len){   // Run send 100 bytes to I2C
    int timeSend = (len)/KXN_BYTE_PER_TIME_SEND;

    char * pSplitArray;

    for(int cf = 0; cf <= timeSend; cf++){
        str_SerialBlynkI2C_Data *temHeader;
        char tempArrChar[32];
        temHeader = (str_SerialBlynkI2C_Data*)tempArrChar;
        if(timeSend == cf){
            temHeader->lenData = len%KXN_BYTE_PER_TIME_SEND - 1;
        }else{
            temHeader->lenData = KXN_BYTE_PER_TIME_SEND;
        }
        temHeader->id = '0';
        temHeader->modeId = '2';
        temHeader->checkSumData = temHeader->lenData;
        
    //      cfStringTemp = kk.substring((cf*KXN_BYTE_PER_TIME_SEND), (cf*KXN_BYTE_PER_TIME_SEND) + temHeader->lenData);
        pSplitArray = inputCharArray + (cf * KXN_BYTE_PER_TIME_SEND);

        char showBuffer[29];
        memcpy(showBuffer, pSplitArray, temHeader->lenData+1);
    //      DBSerial("subString: ");
    //      DBSerial(showBuffer);
    //      DBSerial("temHeader->lenData: " + String(temHeader->lenData));
        
        memcpy(temHeader->data, showBuffer, temHeader->lenData+1);
    //      memcpy(temHeader->data, showBuffer, temHeader->lenData + 1);
        //  printBuff_HEX(tempArrChar,temHeader->lenData + 4);
        I2C_writeString(slaveAddress, tempArrChar, temHeader->lenData + 4);
        delayMicroseconds(1000);
    }
}

void BlynkGate::checkI2CThenSendSerial(){
    String dataString = "";
    bool isEmptyData = false;

    while(!isEmptyData){
        // gui lenh get data
    //    DBSerial("Gui lenh getData");
        char tempCharHeader[32];
        str_SerialBlynkI2C_Data *tempHeader = (str_SerialBlynkI2C_Data *)tempCharHeader;
        tempHeader->modeId = BLYNK_I2C_MODE_ID_GET_DATA;
        I2C_writeString(slaveAddress, tempCharHeader, sizeof(str_SerialBlynkI2C_DataHeader));
        // delay(1);
        delayMicroseconds(1000);
    
        
        Wire.requestFrom(slaveAddress, 32);    // request 6 bytes from slave device #8
        uint8_t countIndex = 0;
    //    Serial.print("[");
        while (Wire.available()) { // slave may send less than requested
        char c = Wire.read(); // receive a byte as character
    //      Serial.print(c, HEX);         // print the character
    //      Serial.print("\t");
    
        tempCharHeader[countIndex] = c;
        if(countIndex > 3){
            if(tempHeader->lenData != 0){
                if(countIndex < (tempHeader->lenData + 4)){
                    dataString += tempCharHeader[countIndex];
                }
            }else{
                isEmptyData = true;
            }
        }
        countIndex++;
        }
    //    Serial.println("]");
    }

    if(dataString.length() > 0){
        delay(10);
        // Serial.println(dataString);

        if(dataString.indexOf(BLYNK_I2C_CMD_VIRTUAL_PIN_RX) == 0){
            String tempVirtualPin = splitString(dataString, BLYNK_I2C_CMD_VIRTUAL_PIN_RX, " ", " ",0);
            String valueTemp = splitString(dataString, BLYNK_I2C_CMD_VIRTUAL_PIN_RX, " ", " ", 1);
            // Serial.println(tempVirtualPin);
            // Serial.println(valueTemp);

            BlynkReq request1;
            Blynk_I2C_Param  param;
            char rr[100];
            request1.pin = tempVirtualPin.toInt();
            param.len = valueTemp.length();
            valueTemp.toCharArray(rr, param.len+1);
            param.buff = rr;
            // param.len = sizeof(rr);
            param.buff_size = param.len;
            this->Blynk_I2C_WriteDefault(request1, param);
        }
        
    }
}

void BlynkGate::run(){
    this->checkUartThenSendI2C4();
    this->checkI2CThenSendSerial();
    this->checkSendVirtualWrite();
}

void BlynkGate::connect(String auth_, String ssid_, String pass_){
    // [0x1a] [connect] [32 bytes token] [ssid] [pass] [0x1a]
    // String loStr = char(0x1a) +"connect " + auth + " " + ssid + " " + pass + char(0x1a);
    String loStr = "connect " + auth_ + " " + ssid_ + " " + pass_ + '\n';
    this->auth = auth_;
    this->ssid = ssid_;
    this->pass = pass_;

    this->SendStringToI2C(loStr);
    DBSerial(loStr);
    // this->SendStringToI2C(loStr);

}

void BlynkGate::CheckWifi(){
    String tempStr = "wifi\n";
    this->SendStringToI2C(tempStr);
}

void BlynkGate::begin(String auth_, String ssid_, String pass_){
    // slaveAddress = 64;
    Wire.begin(); // join I2C bus (address optional for master)
    delay(1000);
    // this->CheckWifi();
    // delay(5000);
    this->connect(auth_, ssid_, pass_);

}

void BlynkGate::virtualWrite(int vx_, float strValue_){
    // this->virtualWrite(vx_, String(strValue_));
    ENQUEUE_BLYNK_GATE(BlynkGateQueue, vx_, strValue_);
}

void BlynkGate::checkSendVirtualWrite(){
    if(millis() - lastTimeVirtualWrite >= 2000){
        lastTimeVirtualWrite = millis();

        if(GETQUEUESIZE_BLYNK_GATE(BlynkGateQueue) > 0){
            STRUCT_QUEUE_BLYNK_GATE(BlynkGateQueue) tempValue = DEQUEUE_BLYNK_GATE(BlynkGateQueue);
            virtualWrite(tempValue.key, String(tempValue.value));
        }
    }
}

// void BlynkGate::virtualWrite(int vx_, long strValue_){
//     this->virtualWrite(vx_, String(strValue_));
// }

void BlynkGate::virtualWrite(int vx_, String strValue_){
    String tempStr = BLYNK_I2C_CMD_VIRTUAL_PIN_TX;
    tempStr += " ";
    tempStr += String(vx_);
    tempStr += " ";
    tempStr += strValue_;
    tempStr += "\n";
    this->SendStringToI2C(tempStr);

}

void BlynkGate::delayms(){
    
}

String BlynkGate::splitString(String v_G_motherString, String v_G_Command, String v_G_Start_symbol, String v_G_Stop_symbol, unsigned char v_G_Offset){
	unsigned char lenOfCommand=v_G_Command.length();
    unsigned char posOfCommand=v_G_motherString.indexOf(v_G_Command);
    int PosOfStartSymbol=v_G_motherString.indexOf(v_G_Start_symbol,posOfCommand+lenOfCommand);
	
    while(v_G_Offset>0){
        v_G_Offset--;
        PosOfStartSymbol=v_G_motherString.indexOf(v_G_Start_symbol,PosOfStartSymbol+1);
    }
	
    int PosOfStopSymbol=v_G_motherString.indexOf(v_G_Stop_symbol,PosOfStartSymbol+1);
	
	return v_G_motherString.substring(PosOfStartSymbol+1,PosOfStopSymbol);
}

BlynkGate Blynk(74);
