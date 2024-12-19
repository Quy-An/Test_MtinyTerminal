#ifndef Blynk_I2C_Param__h_
#define Blynk_I2C_Param__h_

#include "Arduino.h"

class Blynk_I2C_Param{
    public:
        char*    buff;
        size_t   len;
        size_t   buff_size;

        const char* asStr() const       { return buff; }
        const char* asString() const    { return buff; }
        int         asInt() const       { return atoi(buff); }
        long        asLong() const      { return atol(buff); }
        float       asFloat() const     { return atof(buff); }
};

#endif