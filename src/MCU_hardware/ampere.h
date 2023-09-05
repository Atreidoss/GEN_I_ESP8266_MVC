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

#define PWM_MIN 0
#define PWM_MAX 1023

#define AMPERE_PS_ON 1
#define AMPERE_PS_OFF 2

class output
{
public:
    output()
    {
        init();
    }

    void switcher(int mode, bool state)
    {
        if (state)
        {
            on(mode);
        }
        else
        {
            off();
        }
    }

    void setValue(int val)
    {
        int tempVal = map(val, 40, 200, 58, 743);
        setPwm(tempVal);
    }

private:
    void on(int mode)
    {
        switch (mode)
        {
        case AMPERE_PS_ON:
            setPowerOn(true);
            setPwm(0);
            break;
        case AMPERE_PS_OFF:
            setPowerOn(false);
            setPwm(0);
            break;
        default:
            break;
        }
    }

    void off(void)
    {
        setPowerOn(false);
        setPwm(0);
    }

    void setPwm(int val)
    {
        if (val <= PWM_MIN)
        {
            digitalWrite(PIN_PWM_AMPERE, LOW);
        }
        else if (val >= PWM_MAX)
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