#ifndef button_h
#define button_h

#include "settings.h"
#include <Arduino.h>
#include "VirtualButton.h"

#define INVERSE_INPUT true
#define NO_INVERSE_INPUT false

class Button : public VButton
{
public:
    Button() {}

    Button(uint8_t pin, bool isInvers)
    {
         setHoldTimeout(BUTTON_HOLD_TIMEOUT);
         setStepTimeout(BUTTON_STEP_TIMEOUT);

        _pin = pin;
        _isInvers = isInvers;
        if (_isInvers == true)
        {
            pinMode(_pin, INPUT_PULLUP);
        }
        else
        {
            pinMode(_pin, INPUT);
        }
    }

    bool tick()
    {
        if (_isInvers == true)
        {
            return poll(!digitalRead(_pin));
        }
        else
        {
            return poll(digitalRead(_pin));
        }
    }

private:
    uint8_t _pin;
    uint8_t _isInvers;
};

#endif