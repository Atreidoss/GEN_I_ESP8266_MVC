#ifndef eeprom_h
#define eeprom_h

#include "Arduino.h"
#include <pgmspace.h>
#include <EEPROM.h>

class Eeprom
{
public:
    Eeprom();
    void init(int eppromSize)
    {
        EEPROM.begin(eppromSize);
    }

    void writeInt(int address, int value)
    {
        byte *p = (byte *)&value;
        for (int i = 0; i < 3; i++)
        {
            EEPROM.write(address + i, *(p + i));
        };
        EEPROM.commit();
    }

    int getInt(int address)
    {
        int value;
        byte *p = (byte *)&value;
        for (int i = 0; i < 3; i++)
        {
            *(p + i) = EEPROM.read(address + i);
        };
        return value;
    }
};

#endif