#ifndef ampere_h_
#define ampere_h_

#include <Arduino.h>
#include "settings.h"

class output
{
public:
    output()
    {
        init();
    }
    void setPwm(int val)
    {
        if (val <= 0)
        {
            digitalWrite(PIN_PWM_AMPERE, LOW);
        }
        else if (val >= 1023)
        {
            digitalWrite(PIN_PWM_AMPERE, HIGH);
        }
        else
        {
            analogWrite(PIN_PWM_AMPERE, val);
        }
    }
    void setPowerOn(bool state)
    {
        digitalWrite(PIN_ITERNAL_POWER_SUPPLY, state);
    }

private:
    void init(void)
    {

        pinMode(PIN_ITERNAL_POWER_SUPPLY, OUTPUT);
        pinMode(PIN_PWM_AMPERE, OUTPUT);
        digitalWrite(PIN_ITERNAL_POWER_SUPPLY, LOW);
        digitalWrite(PIN_PWM_AMPERE, LOW);
        analogWriteResolution(PWM_RESOLUTION);
        analogWriteFreq(PWM_FREQUENCY);
    }
};

#endif