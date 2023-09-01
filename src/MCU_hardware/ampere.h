#ifndef ampere_h_
#define ampere_h_

#include <Arduino.h>
#include "settings.h"

#ifndef SETTINGS_AMPERE
#define PIN_PWM_AMPERE 14          // Номер ножки ШИМ генерации 4-20 мА
#define PIN_ITERNAL_POWER_SUPPLY 3 // Номер ножки подачи напряжения от внутреннего источника питания
#define PWM_RESOLUTION 10          // Разрешение ШИМ, бит
#define PWM_FREQUENCY 1000         // Частота ШИМ, Гц
#endif

class output
{
public:
    output()
    {
        init();
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
};

#endif